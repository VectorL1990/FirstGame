// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../../ThirdParty/tinyxml2.h"
#include "../../Character/BaseCharacter.h"
#include "../Physics/BasePhysGeo.h"
#include "GeometricRecognizer.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable, BlueprintType)
struct FKeyPoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FVector2D> points;

	FKeyPoint()
	{
		
	}

	FKeyPoint(TArray<FVector2D> pts)
	{
		points = pts;
	}
};

USTRUCT(Blueprintable, BlueprintType)
struct FRectangle
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	float posX;
	
	UPROPERTY()
	float posY;
	
	UPROPERTY()
	float width;
	
	UPROPERTY()
	float height;

	FRectangle()
	{
		posX = 0;
		posY = 0;
		width = 0;
		height = 0;
	}

	FRectangle(float x, float y, float w, float h)
	{
		posX = x;
		posY = y;
		width = w;
		height = h;
	}
};

USTRUCT(Blueprintable, BlueprintType)
struct FRecognitionResult
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FString name;

	UPROPERTY()
	float score;

	FRecognitionResult()
	{
		name = TEXT("Unknown");
		score = 0;
	}

	FRecognitionResult(FString n, float s)
	{
		name = n;
		score = s;
	}
};

USTRUCT(Blueprintable, BlueprintType)
struct FGestureTemplate
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	FString name;

	UPROPERTY()
	TArray<FVector2D> points;

	FGestureTemplate()
	{
		name = TEXT("Unknown");
	}

	FGestureTemplate(FString n, TArray<FVector2D> pts)
	{
		name = n;
		points = pts;
	}
};

UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UGeometricRecognizer : public UObject
{
	GENERATED_BODY()

	
protected:
	//--- These are variables because C++ doesn't (easily) allow
	//---  constants to be floating point numbers
	float m_halfDiagonal;
	float m_angleRange;
	float m_anglePrecision;
	float m_goldenRatio;

	//--- How many points we use to define a shape
	int32 m_numPointsInGesture;
	//---- Square we resize the shapes to
	int32 m_squareSize;

	//--- What we match the input shape against
	TArray<FGestureTemplate> m_templates;

public:
	UGeometricRecognizer(const FObjectInitializer& ObjectInitializer);

	//int32 AddTemplate(FString name, FPath2D points);

	FRectangle BoundingBox(TArray<FVector2D> points);

	float DistanceAtAngle(TArray<FVector2D> points, FGestureTemplate temp, float rotation);

	float DistanceAtBestAngle(TArray<FVector2D> points, FGestureTemplate temp);

	void NormalizePath(TArray<FVector2D> points, TArray<FVector2D>& normalizedPts);

	float PathDistance(TArray<FVector2D> pts1, TArray<FVector2D> pts2);

	float PathLength(TArray<FVector2D> points);

	UFUNCTION()
	FRecognitionResult Recognize();

	void Resample(TArray<FVector2D> points, TArray<FVector2D>& samplePts);

	void RotateBy(TArray<FVector2D> points, float rotation, TArray<FVector2D>& rotatedPts);

	void RotateToZero(TArray<FVector2D> points, TArray<FVector2D>& rotatedPts);

	void ScaleToSquare(TArray<FVector2D> points, TArray<FVector2D>& scaledPts);

	void TranslateToOrigin(TArray<FVector2D> points, TArray<FVector2D>& translatedPts);

	void LoadTemplates();

	void SetRotationInvariance(bool ignoreRotation);

	bool m_shouldIgnoreRotation;
	UPROPERTY()
	bool m_canCollectPt;

	UPROPERTY()
	TArray<FName> m_collectTags;
	UPROPERTY()
	TArray<FVector2D> m_collectPts;
	UPROPERTY()
	float m_curCollectTime;
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_maxCollectTime;
};
