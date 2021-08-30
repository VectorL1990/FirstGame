// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "GeometricRecognizer.h"

UGeometricRecognizer::UGeometricRecognizer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//--- How many templates do we have to compare the user's gesture against?
	//--- Can get ~97% accuracy with just one template per symbol to recognize
	//numTemplates = 16;
	//--- How many points do we use to represent a gesture
	//--- Best results between 32-256
	m_numPointsInGesture = 128;
	//--- Before matching, we stretch the symbol across a square
	//--- That way we don't have to worry about the symbol the user drew
	//---  being smaller or larger than the one in the template
	m_squareSize = 250;
	//--- 1/2 max distance across a square, which is the maximum distance
	//---  a point can be from the center of the gesture
	m_halfDiagonal = 0.5 * FMath::Sqrt((250.0 * 250.0) + (250.0 * 250.0));
	//--- Before matching, we rotate the symbol the user drew so that the 
	//---  start point is at degree 0 (right side of symbol). That's how 
	//---  the templates are rotated so it makes matching easier
	//--- Note: this assumes we want symbols to be rotation-invariant, 
	//---  which we might not want. Using this, we can't tell the difference
	//---  between squares and diamonds (which is just a rotated square)
	SetRotationInvariance(true);
	m_anglePrecision = 2.0;
	//--- A magic number used in pre-processing the symbols
	m_goldenRatio = 0.5 * (-1.0 + FMath::Sqrt(5.0));

	m_canCollectPt = true;

	m_curCollectTime = 0;

	m_maxCollectTime = 5;
}

void UGeometricRecognizer::SetRotationInvariance(bool ignoreRotation)
{
	m_shouldIgnoreRotation = ignoreRotation;
	if (m_shouldIgnoreRotation)
	{
		m_angleRange = 45.0;
	}
	else
	{
		m_angleRange = 15.0;
	}
}

float UGeometricRecognizer::PathLength(TArray<FVector2D> points)
{
	if (points.Num() <= 1) return 0;
	float distance = 0;
	for (int32 i = 1; i < points.Num(); i++)
		distance += UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint(points[i - 1], points[i]);
	return distance;
}

void UGeometricRecognizer::Resample(TArray<FVector2D> points, TArray<FVector2D>& samplePts)
{
	float interval = PathLength(points) / (m_numPointsInGesture - 1); // interval length
	float D = 0.0;

	//--- Store first point since we'll never resample it out of existence
	samplePts.Add(points[0]);
	for (int32 i = 1; i < points.Num(); i++)
	{
		FVector2D currentPoint = points[i];
		FVector2D previousPoint = points[i - 1];
		float d = UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint(previousPoint, currentPoint);
		if ((D + d) >= interval)
		{
			float qx = previousPoint.X + ((interval - D) / d) * (currentPoint.X - previousPoint.X);
			float qy = previousPoint.Y + ((interval - D) / d) * (currentPoint.Y - previousPoint.Y);
			FVector2D point(qx, qy);
			samplePts.Add(point);
			points.Insert(point,i);
			D = 0.0;
		}
		else D += d;
	}

	// somtimes we fall a rounding-error short of adding the last point, so add it if so
	if (samplePts.Num() == (m_numPointsInGesture - 1))
	{
		samplePts.Add(points.Last());
	}
}

void UGeometricRecognizer::RotateBy(TArray<FVector2D> points, float rotation, TArray<FVector2D>& rotatedPts)
{
	FVector2D c = UCollisionWarBpFunctionLibrary::GetCenterPt(points);
	//--- can't name cos; creates compiler error since VC++ can't
	//---  tell the difference between the variable and function
	float cosine = FMath::Cos(rotation);
	float sine = FMath::Sin(rotation);

	for (int32 i=0; i<points.Num(); i++)
	{
		FVector2D point = points[i];
		float qx = (point.X - c.X) * cosine - (point.Y - c.Y) * sine + c.X;
		float qy = (point.X - c.X) * sine + (point.Y - c.Y) * cosine + c.Y;
		rotatedPts.Add(FVector2D(qx, qy));
	}
}

void UGeometricRecognizer::RotateToZero(TArray<FVector2D> points, TArray<FVector2D>& rotatedPts)
{
	FVector2D c = UCollisionWarBpFunctionLibrary::GetCenterPt(points);
	float rotation = FMath::Atan2(c.Y - points[0].Y, c.X - points[0].X);
	RotateBy(points, -rotation, rotatedPts);
}

FRectangle UGeometricRecognizer::BoundingBox(TArray<FVector2D> points)
{
	float minX = 0;
	float maxX = 0;
	float minY = 0;
	float maxY = 0;

	for (int32 i=0; i<points.Num(); i++)
	{
		FVector2D point = points[i];
		if (i == 0)
		{
			minX = point.X;
			maxX = point.X;
			minY = point.Y;
			maxY = point.Y;
		}
		else
		{
			if (point.X < minX)
				minX = point.X;
			if (point.X > maxX)
				maxX = point.X;
			if (point.Y < minY)
				minY = point.Y;
			if (point.Y > maxY)
				maxY = point.Y;
		}
		
	}
	FRectangle bounds(minX, minY, (maxX - minX), (maxY - minY));
	return bounds;
}

void UGeometricRecognizer::ScaleToSquare(TArray<FVector2D> points, TArray<FVector2D>& scaledPts)
{
	//--- Figure out the smallest box that can contain the path
	FRectangle box = BoundingBox(points);
	for (int32 i=0; i<points.Num(); i++)
	{
		FVector2D point = points[i];
		//--- Scale the points to fit the main box
		//--- So if we wanted everything 100x100 and this was 50x50,
		//---  we'd multiply every point by 2
		float scaledX = point.X * (m_squareSize / box.width);
		float scaledY = point.Y * (m_squareSize / box.height);
		//--- Why are we adding them to a new list rather than 
		//---  just scaling them in-place?
		// TODO: try scaling in place (once you know this way works)
		scaledPts.Add(FVector2D(scaledX, scaledY));
	}
}

void UGeometricRecognizer::TranslateToOrigin(TArray<FVector2D> points, TArray<FVector2D>& translatedPts)
{
	FVector2D c = UCollisionWarBpFunctionLibrary::GetCenterPt(points);
	for (int32 i=0; i<points.Num(); i++)
	{
		FVector2D point = points[i];
		float qx = point.X - c.X;
		float qy = point.Y - c.Y;
		translatedPts.Add(FVector2D(qx, qy));
	}
}

void UGeometricRecognizer::NormalizePath(TArray<FVector2D> points, TArray<FVector2D>& normalizedPts)
{
	/* Recognition algorithm from
	http://faculty.washington.edu/wobbrock/pubs/uist-07.1.pdf
	Step 1: Resample the Point Path
	Step 2: Rotate Once Based on the "Indicative Angle"
	Step 3: Scale and Translate
	Step 4: Find the Optimal Angle for the Best Score
	*/
	// TODO: Switch to $N algorithm so can handle 1D shapes

	//--- Make everyone have the same number of points (anchor points)
	TArray<FVector2D> samplePts;
	Resample(points, samplePts);

	//--- Pretend that all gestures began moving from right hand side
	//---  (degree 0). Makes matching two items easier if they're
	//---  rotated the same
	TArray<FVector2D> rotatedPts;
	if (m_shouldIgnoreRotation)
		RotateToZero(samplePts, rotatedPts);
	else rotatedPts = samplePts;
	//--- Pretend all shapes are the same size. 
	//--- Note that since this is a square, our new shape probably
	//---  won't be the same aspect ratio
	TArray<FVector2D> scaledPts;
	ScaleToSquare(rotatedPts, scaledPts);
	//--- Move the shape until its center is at 0,0 so that everyone
	//---  is in the same coordinate system
	TArray<FVector2D> translatedPts;
	TranslateToOrigin(scaledPts, translatedPts);

	normalizedPts = translatedPts;
}

float UGeometricRecognizer::DistanceAtAngle(TArray<FVector2D> points, FGestureTemplate temp, float rotation)
{
	TArray<FVector2D> rotatedPts;
	RotateBy(points, rotation, rotatedPts);
	return PathDistance(rotatedPts, temp.points);
}

float UGeometricRecognizer::PathDistance(TArray<FVector2D> pts1, TArray<FVector2D> pts2)
{
	if (pts1.Num() <= 1 || pts2.Num() <= 1) return 0;
	float distance = 0.0;
	for (int32 i = 0; i < pts1.Num(); i++)
		distance += UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint(pts1[i], pts2[i]);
	return (distance / pts1.Num());
}

float UGeometricRecognizer::DistanceAtBestAngle(TArray<FVector2D> points, FGestureTemplate temp)
{
	float startRange = -m_angleRange;
	float endRange = m_angleRange;
	float x1 = m_goldenRatio * startRange + (1.0 - m_goldenRatio) * endRange;
	float f1 = DistanceAtAngle(points, temp, x1);
	float x2 = (1.0 - m_goldenRatio) * startRange + m_goldenRatio * endRange;
	float f2 = DistanceAtAngle(points, temp, x2);
	while (FMath::Abs(endRange - startRange) > m_anglePrecision)
	{
		if (f1 < f2)
		{
			endRange = x2;
			x2 = x1;
			f2 = f1;
			x1 = m_goldenRatio * startRange + (1.0 - m_goldenRatio) * endRange;
			f1 = DistanceAtAngle(points, temp, x1);
		}
		else
		{
			startRange = x1;
			x1 = x2;
			f1 = f2;
			x2 = (1.0 - m_goldenRatio) * startRange + m_goldenRatio * endRange;
			f2 = DistanceAtAngle(points, temp, x2);
		}
	}
	if (f1 <= f2) return f1;
	else return f2;
}

FRecognitionResult UGeometricRecognizer::Recognize()
{
	//--- Make sure we have some templates to compare this to
	//---  or else recognition will be impossible
	//if (m_templates.gestureTemplates.Num() == 0) return FRecognitionResult("Unknown", 0);
	if (m_collectPts.Num() == 0) return FRecognitionResult("Unknown", 0);

	TArray<FVector2D> normalizedPts;
	NormalizePath(m_collectPts,normalizedPts);
	//--- Initialize best distance to the largest possible number
	//--- That way everything will be better than that
	float bestDistance = 0;
	//--- We haven't found a good match yet
	int32 indexOfBestMatch = -1;

	//--- Check the shape passed in against every shape in our database
	for (int32 i = 0; i < m_templates.Num(); i++)
	{
		//--- Calculate the total distance of each point in the passed in
		//---  shape against the corresponding point in the template
		//--- We'll rotate the shape a few degrees in each direction to
		//---  see if that produces a better match
		float distance = DistanceAtBestAngle(normalizedPts, m_templates[i]);
		if (i == 0)
		{
			bestDistance = distance;
			indexOfBestMatch = i;
		}
		else if (distance < bestDistance)
		{
			bestDistance = distance;
			indexOfBestMatch = i;
		}
	}

	//--- Turn the distance into a percentage by dividing it by 
	//---  half the maximum possible distance (across the diagonal 
	//---  of the square we scaled everything too)
	//--- Distance = hwo different they are
	//--- Subtract that from 1 (100%) to get the similarity
	float score = 1.0 - (bestDistance / m_halfDiagonal);

	//--- Make sure we actually found a good match
	//--- Sometimes we don't, like when the user doesn't draw enough points
	if (-1 == indexOfBestMatch) return FRecognitionResult("Unknown", 0);

	FRecognitionResult bestMatch(m_templates[indexOfBestMatch].name, score);
	return bestMatch;
}

void UGeometricRecognizer::LoadTemplates()
{
	FString _xmlpath = FPaths::GameDir() + "Gestures.xml";
	char* charPath = TCHAR_TO_ANSI(*_xmlpath);
	XMLDocument* doc = new XMLDocument();
	XMLError loadResult = doc->LoadFile(charPath);
	if (loadResult != XML_SUCCESS)
	{
		delete doc;
		return;
	}
	XMLElement* pRootNode = doc->RootElement();
	if (!pRootNode)
	{
		delete doc;
		return;
	}
	XMLElement* pWorkSheetNode = UCollisionWarBpFunctionLibrary::GetXMLFirstWorksheetNode(pRootNode);
	while (pWorkSheetNode)
	{
		FGestureTemplate gestureTemplate;
		FString nameAttributeString = TEXT("ss:Name");
		char* nameAttributeChar = TCHAR_TO_ANSI(*nameAttributeString);
		const char* attributeChar = pWorkSheetNode->Attribute(nameAttributeChar);
		if (attributeChar != 0)
		{
			FString attribute = ANSI_TO_TCHAR(attributeChar);
			gestureTemplate.name = attribute;
		}
		if (!pWorkSheetNode)
		{
			delete doc;
			return;
		}
		XMLElement* pTableNode = pWorkSheetNode->FirstChildElement();
		XMLElement* pPointCoordinatesRow = UCollisionWarBpFunctionLibrary::GetXMLRowByContentFromTableNode(pTableNode, "x");
		XMLElement* pCurRowNode = pPointCoordinatesRow->NextSiblingElement();
		TArray<FVector2D> points;
		while (pCurRowNode)
		{
			XMLElement* pCellNode = pCurRowNode->FirstChildElement();
			const char* xChar = pCellNode->FirstChildElement()->GetText();
			FString xString = ANSI_TO_TCHAR(xChar);
			float x = FCString::Atof(*xString);
			pCellNode = pCellNode->NextSiblingElement();
			const char* yChar = pCellNode->FirstChildElement()->GetText();
			FString yString = ANSI_TO_TCHAR(yChar);
			float y = FCString::Atof(*yString);
			FVector2D point2D(x, y);
			points.Add(point2D);
			pCurRowNode = pCurRowNode->NextSiblingElement();
		}
		NormalizePath(points, gestureTemplate.points);
		m_templates.Add(gestureTemplate);
		pWorkSheetNode = pWorkSheetNode->NextSiblingElement();
	}
	delete doc;
}

