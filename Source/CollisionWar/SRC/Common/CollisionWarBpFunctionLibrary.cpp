// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "CollisionWarBpFunctionLibrary.h"
#include "../Game/Character/BaseCharacter.h"




float UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment(FVector2D pt1, FVector2D pt2, FVector2D pt3)
{
	//如果在实际世界中（因为ue4的坐标是Y轴向下，X轴向右）L13转到L12是顺时针，那么返回值为正
	return (pt3.X - pt1.X)*(pt2.Y - pt1.Y) - (pt2.X - pt1.X)*(pt3.Y - pt1.Y);
}

int32 UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3)
{
	//如果在实际世界中（因为ue4的坐标是Y轴向下，X轴向右）L13转到L12是顺时针，那么返回值为正
	return (pt3.X - pt1.X)*(pt2.Y - pt1.Y) - (pt2.X - pt1.X)*(pt3.Y - pt1.Y);
}

bool UCollisionWarBpFunctionLibrary::IsPointInRectDefineByTwoPoints_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3)
{
	if (pt3.X >= FMath::Min(pt1.X, pt2.X) && pt3.X <= FMath::Max(pt1.X, pt2.X) && pt3.Y >= FMath::Min(pt1.Y, pt2.Y) && pt3.Y <= FMath::Max(pt1.Y, pt2.Y))
		return true;
	else return false;
}

UCollisionWarSingleton* UCollisionWarBpFunctionLibrary::GetGlobalSingleton(bool& IsValid)
{
	IsValid = false;
	UCollisionWarSingleton* pCWSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);

	if (!pCWSingleton) return NULL;
	if (!pCWSingleton->IsValidLowLevel()) return NULL;

	IsValid = true;
	return pCWSingleton;
}

void UCollisionWarBpFunctionLibrary::IntBigAdd(TArray<int32> a, TArray<int32> b, TArray<int32>& c, uint8 aSym, uint8 bSym, uint8& sym)
{
	if (aSym == bSym || aSym == 0 || bSym == 0)
	{
		bool isNonZero = false;
		int32 i, carry = 0;
		for (i = 4; i >= 0; i--)
		{
			c[i] = a[i] + b[i] + carry;
			if (c[i] != 0) isNonZero = true;
			if (c[i] < 10000) carry = 0;
			else
			{
				c[i] = c[i] - 10000;
				carry = 1;
			}
		}
		if (!isNonZero) sym = 0;
		else if (aSym == 0) sym = bSym;
		else if (bSym == 0) sym = aSym;
		else sym = aSym;
	}
	else
	{
		bool aLargerThanb = false;
		for (int32 j = 0; j < 5; j++)
		{
			if (a[j] == b[j]) continue;
			else if (a[j] > b[j])
			{
				aLargerThanb = true;
				break;
			}
			else break;
		}
		bool isEqual = true;
		int32 i, borrow = 0;
		for (i = 4; i >= 0; i--)
		{
			if (aLargerThanb) c[i] = a[i] - b[i] - borrow;
			else c[i] = b[i] - a[i] - borrow;
			if (c[i] != 0) isEqual = false;
			if (c[i] >= 0) borrow = 0;
			else
			{
				c[i] = c[i] + 10000;
				borrow = 1;
			}
		}

		if (isEqual) sym = 0;
		else if (aLargerThanb) sym = aSym;
		else
		{
			if (aSym == 1) sym = 2;
			else if (aSym == 2) sym = 1;
		}
	}
}

void UCollisionWarBpFunctionLibrary::IntBigSub(TArray<int32> a, TArray<int32> b, TArray<int32>& c, uint8 aSym, uint8 bSym, uint8& sym)
{
	if (aSym == bSym || aSym == 0 || bSym == 0)
	{
		bool aLargerThanb = false;
		for (int32 j = 0; j < 5; j++)
		{
			if (a[j] == b[j]) continue;
			else if (a[j] > b[j])
			{
				aLargerThanb = true;
				break;
			}
			else break;
		}
		bool isEqual = true;
		int32 i, borrow = 0;
		for (i = 4; i >= 0; i--)
		{
			if (aLargerThanb) c[i] = a[i] - b[i] - borrow;
			else c[i] = b[i] - a[i] - borrow;
			if (c[i] != 0) isEqual = false;
			if (c[i] >= 0) borrow = 0;
			else
			{
				c[i] = c[i] + 10000;
				borrow = 1;
			}
		}
		if (isEqual) sym = 0;
		else if (aLargerThanb) sym = aSym;
		else
		{
			if (aSym == 1) sym = 2;
			else if (aSym == 2) sym = 1;
			else
			{
				if (bSym == 1) sym = 2;
				else sym = 1;
			}
		}
	}
	else
	{
		bool isNonZero = false;
		int32 i, carry = 0;
		for (i = 4; i >= 0; i--)
		{
			c[i] = a[i] + b[i] + carry;
			if (c[i] != 0) isNonZero = true;
			if (c[i] < 10000) carry = 0;
			else
			{
				c[i] = c[i] - 10000;
				carry = 1;
			}
		}
		if (!isNonZero) sym = 0;
		else if (aSym == 0) sym = bSym;
		else if (bSym == 0) sym = aSym;
		else sym = aSym;
	}
}

void UCollisionWarBpFunctionLibrary::IntBigMul(int32 a, int32 b, TArray<int32>& c, uint8& symbol)
{
	int32 absA = FMath::Abs(a);
	int32 absB = FMath::Abs(b);
	int32 absT = 0;
	int32 q1, q2, q3 = 0;
	bool aLargerThanb = false;
	if (absA >= absB) aLargerThanb = true;
	if (!aLargerThanb)
	{
		q1 = absB % 10000;
		q2 = (absB / 10000) % 10000;
		q3 = (absB / 100000000) % 10000;
		absT = absA;
	}
	else
	{
		q1 = absA % 10000;
		q2 = (absA / 10000) % 10000;
		q3 = (absA / 100000000) % 10000;
		absT = absB;
	}
	TArray<int32> bigQ = {0,0,q3, q2, q1};
	int32 i, temp, carry = 0;
	for (i = 4; i >= 0; i--)
	{
		temp = bigQ[i] * absT + carry;
		//c.Insert(temp % 1000, 0);
		c[i] = temp % 10000;
		carry = temp / 10000;
	}
	if ((a > 0 && b > 0) || (a < 0 && b < 0)) symbol = 1;
	else if (a == 0 || b == 0) symbol = 0;
	else symbol = 2;
}

int32 UCollisionWarBpFunctionLibrary::IntBigDiv(TArray<int32>& a, int32 b, uint8 aSymbol)
{
	int32 absB = FMath::Abs(b);
	int32 resultA0 = 0;
	int32 resultA1 = 0;
	int32 resultA2 = 0;
	int32 resultA3 = 0;
	int32 resultA4 = 0;
	if (absB > 100000000)
	{
		int32 tempB = absB / 10;
		//tempB为8位数
		if (a[0] >= 10)
		{
			//a[0]为2位数，补7个0
			resultA0 = a[0] * 10000000 / tempB*100000000;
		}
		else if (a[0] > 0)
		{
			//a[0]为1位数，补8个0
			resultA0 = a[0] * 100000000 / tempB * 10000000;
		}
		/************************************************************************/
		if (a[1] >= 1000)
		{
			//a[1]为4位数，补5个0
			resultA1 = a[1] * 100000 / tempB * 1000000;
		}
		else if (a[1] >= 100)
		{
			//a[1]为3位数，补6个0
			resultA1 = a[1] * 1000000 / tempB * 100000;
		}
		else if (a[1] >= 10)
		{
			//a[1]为3位数，补7个0
			resultA1 = a[1] * 10000000 / tempB * 10000;
		}
		else if (a[1] >= 0)
		{
			//a[1]为3位数，补8个0
			resultA1 = a[1] * 100000000 / tempB * 1000;
		}
		/************************************************************************/
		if (a[2] >= 1000)
		{
			//a[1]为4位数，补5个0
			resultA2 = a[2] * 100000 / tempB * 100;
		}
		else if (a[2] >= 100)
		{
			//a[1]为3位数，补6个0
			resultA2 = a[2] * 1000000 / tempB * 10;
		}
		else if (a[2] >= 10)
		{
			//a[1]为2位数，补7个0
			resultA2 = a[2] * 10000000 / tempB;
		}
		else if (a[2] >= 0)
		{
			//a[1]为1位数，补8个0
			resultA2 = a[2] * 10000000 / tempB;
		}
	}
	else
	{
		//此时b为8位数及以下
		if (a[0] >= 10)
		{
			//a[0]为2位数，补7个0
			resultA0 = a[0] * 10000000 / absB * 1000000000;
		}
		else if (a[0] > 0)
		{
			//a[0]为1位数，补8个0
			resultA0 = a[0] * 100000000 / absB * 100000000;
		}
		/************************************************************************/
		if (a[1] >= 1000)
		{
			//a[1]为4位数，补5个0
			resultA1 = a[1] * 100000 / absB * 10000000;
		}
		else if (a[1] >= 100)
		{
			//a[1]为3位数，补6个0
			resultA1 = a[1] * 1000000 / absB * 1000000;
		}
		else if (a[1] >= 10)
		{
			//a[1]为3位数，补7个0
			resultA1 = a[1] * 10000000 / absB * 100000;
		}
		else if (a[1] >= 0)
		{
			//a[1]为3位数，补8个0
			resultA1 = a[1] * 100000000 / absB * 10000;
		}
		/************************************************************************/
		if (a[2] >= 1000)
		{
			//a[1]为4位数，补5个0
			resultA2 = a[2] * 100000 / absB * 1000;
		}
		else if (a[2] >= 100)
		{
			//a[1]为3位数，补6个0
			resultA2 = a[2] * 1000000 / absB * 100;
		}
		else if (a[2] >= 10)
		{
			//a[1]为2位数，补7个0
			resultA2 = a[2] * 10000000 / absB * 10;
		}
		else if (a[2] >= 0)
		{
			//a[1]为1位数，补8个0
			resultA2 = a[2] * 100000000 / absB;
		}
		/************************************************************************/
		resultA3 = a[3] * 10000 / absB;
		resultA4 = a[4] / absB;
	}
	int32 sum = resultA0 + resultA1 + resultA2 + resultA3 + resultA4;
	if ((aSymbol == 1 && b > 0) || (aSymbol == 2 && b < 0)) return sum;
	else if (aSymbol == 0 || b == 0) sum = 0;
	else return -sum;
	return sum;
}

int32 UCollisionWarBpFunctionLibrary::IntSqrt(int32 n)
{
	bool isValid = true;
	UCollisionWarSingleton* pCWSingleton = GetGlobalSingleton(isValid);
	if (!isValid) return 0;

	int xn;
	if (n >= 0x7FFEA810) return 0xB504;
	if (n >= 0x10000)
	{
		if (n >= 0x1000000)
		{
			if (n >= 0x10000000)
			{
				if (n >= 0x40000000)
				{
					xn = pCWSingleton->m_intSqrtList[n >> 24] << 8;
				}
				else
				{
					xn = pCWSingleton->m_intSqrtList[n >> 22] << 7;
				}
			}
			else
			{
				if (n >= 0x4000000) 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 20] << 6;
				}
				else 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 18] << 5;
				}
			}

			xn = (xn + 1 + (n / xn)) >> 1;
			xn = (xn + 1 + (n / xn)) >> 1;
			return ((xn * xn) > n) ? --xn : xn;
		}
		else 
		{
			if (n >= 0x100000) 
			{
				if (n >= 0x400000) 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 16] << 4;
				}
				else 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 14] << 3;
				}
			}
			else 
			{
				if (n >= 0x40000) 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 12] << 2;
				}
				else 
				{
					xn = pCWSingleton->m_intSqrtList[n >> 10] << 1;
				}
			}

			xn = (xn + 1 + (n / xn)) >> 1;
			return ((xn * xn) > n) ? --xn : xn;
		}
	}
	else 
	{
		if (n >= 0x100) 
		{
			if (n >= 0x1000) 
			{
				if (n >= 0x4000) 
				{
					xn = (pCWSingleton->m_intSqrtList[n >> 8]) + 1;
				}
				else 
				{
					xn = (pCWSingleton->m_intSqrtList[n >> 6] >> 1) + 1;
				}
			}
			else 
			{
				if (n >= 0x400) 
				{
					xn = (pCWSingleton->m_intSqrtList[n >> 4] >> 2) + 1;
				}
				else 
				{
					xn = (pCWSingleton->m_intSqrtList[n >> 2] >> 3) + 1;
				}
			}
			return ((xn * xn) > n) ? --xn : xn;
		}
		else 
		{
			if (n >= 0) 
			{
				return pCWSingleton->m_intSqrtList[n] >> 4;
			}
		}
	}
	return -1;
}

int32 UCollisionWarBpFunctionLibrary::GetLogicVecSize(const FLogicVec2D& vec)
{
	int32 size = IntSqrt(vec.X*vec.X + vec.Y*vec.Y);
	return size;
}

FLogicVec2D UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(const FLogicVec2D& originVec,const int32& scale)
{
	FLogicVec2D returnVec(0,0);
	if (scale <= 0) return returnVec;
	else if (scale == 1)
	{
		returnVec = originVec;
		return returnVec;
	}
	else
	{
		if (FMath::Abs(originVec.X) < 10 && FMath::Abs(originVec.Y) < 10)
		{
			//将XY放大是因为如果XY太小，算出来的size误差较大
			returnVec.X = originVec.X * 10;
			returnVec.Y = originVec.Y * 10;
		}
		else
		{
			returnVec.X = originVec.X;
			returnVec.Y = originVec.Y;
		}
		//这里算出来的向量长度是经过放大了10倍的向量长度
		int32 len = GetLogicVecSize(returnVec);
		if (len == 0)
		{
			returnVec.X = 0;
			returnVec.Y = 0;
		}
		else
		{
			returnVec.X = returnVec.X * scale / len;
			returnVec.Y = returnVec.Y * scale / len;
		}
		return returnVec;
	}
}

bool UCollisionWarBpFunctionLibrary::IsSegmentsIntersect_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3, FLogicVec2D pt4)
{
	int32 dirPt3ToPt12 = GetDirectionOfPointToSegment_Int(pt1, pt2, pt3);
	int32 dirPt4ToPt12 = GetDirectionOfPointToSegment_Int(pt1, pt2, pt4);
	int32 dirPt1ToPt34 = GetDirectionOfPointToSegment_Int(pt3, pt4, pt1);
	int32 dirPt2ToPt34 = GetDirectionOfPointToSegment_Int(pt3, pt4, pt2);

	if (dirPt3ToPt12 > 0 && dirPt4ToPt12 < 0 && dirPt1ToPt34 > 0 && dirPt2ToPt34 < 0) return true;
	else if (dirPt3ToPt12 < 0 && dirPt4ToPt12 > 0 && dirPt1ToPt34 > 0 && dirPt2ToPt34 < 0) return true;
	else if (dirPt3ToPt12 > 0 && dirPt4ToPt12 < 0 && dirPt1ToPt34 < 0 && dirPt2ToPt34 > 0) return true;
	else if (dirPt3ToPt12 < 0 && dirPt4ToPt12 > 0 && dirPt1ToPt34 < 0 && dirPt2ToPt34 > 0) return true;
	else if (FMath::Abs(dirPt3ToPt12) == 0 && IsPointInRectDefineByTwoPoints_Int(pt1, pt2, pt3)) return true;
	else if (FMath::Abs(dirPt4ToPt12) == 0 && IsPointInRectDefineByTwoPoints_Int(pt1, pt2, pt4)) return true;
	else if (FMath::Abs(dirPt1ToPt34) == 0 && IsPointInRectDefineByTwoPoints_Int(pt3, pt4, pt1)) return true;
	else if (FMath::Abs(dirPt2ToPt34) == 0 && IsPointInRectDefineByTwoPoints_Int(pt3, pt4, pt2)) return true;
	else return false;
}

int32 UCollisionWarBpFunctionLibrary::GetDisOfPointToLine_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3)
{
	int32 A = pt1.Y - pt2.Y;
	int32 B = pt2.X - pt1.X;
	int32 C = pt1.X*pt2.Y - pt2.X*pt1.Y;
	int32 root = A * A + B * B;
	if (root == 0) return 0;
	//取整
	int32 squareRoot = IntSqrt(root);
	int32 result = FMath::Abs(A*pt3.X + B * pt3.Y + C) / squareRoot;
	return result;
}

float UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint(FVector2D pt1, FVector2D pt2)
{
	float xDif = pt1.X - pt2.X;
	float yDif = pt1.Y - pt2.Y;
	return sqrtf(xDif*xDif + yDif*yDif);
}

int32 UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint_Int(FLogicVec2D pt1, FLogicVec2D pt2)
{
	FLogicVec2D logicOffset = pt1 - pt2;
	return GetLogicVecSize(logicOffset);
}

float UCollisionWarBpFunctionLibrary::GetExpandCosAngleOfTwoVector(FVector2D v1, FVector2D v2)
{
	/*int32 v1_len = GetLogicVecSize(v1);
	int32 v2_len = GetLogicVecSize(v2);
	if (v1_len == 0 || v2_len == 0) return 0;
	int32 product = v1.X*v2.X + v1.Y*v2.Y;
	int32 denominator = v1_len*v2_len;
	//取整

	TArray<int32> result = {0,0,0,0,0};
	uint8 productSymbol = 0;
	IntBigMul(product, 10000, result, productSymbol);
	int32 finalResult = IntBigDiv(result, denominator, productSymbol);
	return finalResult;*/
	float v1Len = v1.Size();
	float v2Len = v2.Size();
	if (v1Len == 0 || v2Len == 0) return 0;
	float product = v1.X*v2.X + v1.Y*v2.Y;
	float denominator = v1.Size()*v2.Size();
	float cos = product / denominator;
	float angle = FMath::Acos(cos)*180.f / 3.1416;
	return angle;
}

FLogicVec2D UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(int32 yaw)
{
	return GetPtRotateAroundPtByAlpha_Int(FLogicVec2D(100, 0), FLogicVec2D(0, 0), yaw);
}

float UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(FVector2D vec)
{
	/*int32 len = GetLogicVecSize(vec);
	if (len == 0) return 0;
	int32 expandCos = vec.X * 10000 / len;
	int32 yaw = LogicACos(expandCos);
	if (GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), FLogicVec2D(1, 0), vec) > 0) yaw = -yaw;
	return yaw;*/
	float len = vec.Size();
	if (len == 0) return 0;
	float cos = vec.X / len;
	float angle = FMath::Acos(cos)*180.f/3.1416;
	if (vec.Y < 0) angle = -angle;
	return angle;
}

bool UCollisionWarBpFunctionLibrary::TellWhetherPointInsideConvex_Int(TArray<FLogicVec2D> pts, FLogicVec2D pt)
{
	if (pts.Num() < 3) return false;
	for (int32 i = 0; i < pts.Num(); i++)
	{
		int32 nextIndex = (i + 1) % pts.Num();
		if (GetDirectionOfPointToSegment_Int(pts[i], pts[nextIndex], pt) > 0) return false;
		else continue;
	}
	return true;
}

FLogicVec2D UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(FLogicVec2D rotatePt, FLogicVec2D origine, int32 alpha)
{
	//当alpha为正值时，往现实中逆时针方向转
	//取整
	FLogicVec2D expandResultVector(0,0);
	expandResultVector.X = (rotatePt.X - origine.X)*LogicCos(alpha) - (rotatePt.Y - origine.Y)*LogicSin(alpha) + origine.X * 10000;
	expandResultVector.Y = (rotatePt.X - origine.X)*LogicSin(alpha) + (rotatePt.Y - origine.Y)*LogicCos(alpha) + origine.Y * 10000;
	int32 resultX = expandResultVector.X / 10000;
	int32 resultY = expandResultVector.Y / 10000;
	FLogicVec2D result(resultX, resultY);
	return result;
}

bool UCollisionWarBpFunctionLibrary::GetInteractionOfTwoLines_Int(FLogicVec2D line1Pt1, FLogicVec2D line1Pt2, FLogicVec2D line2Pt1, FLogicVec2D line2Pt2, FLogicVec2D& interaction)
{
	int32 a = line1Pt2.Y - line1Pt1.Y;
	int32 b = line1Pt1.X - line1Pt2.X;
	int32 e = line1Pt1.X*line1Pt2.Y - line1Pt1.Y*line1Pt2.X;
	int32 c = line2Pt2.Y - line2Pt1.Y;
	int32 d = line2Pt1.X - line2Pt2.X;
	int32 f = line2Pt1.X*line2Pt2.Y - line2Pt1.Y*line2Pt2.X;

	int32 denominator = a * d - b * c;
	if (denominator == 0) return false;
	else
	{
		//取整
		TArray<int32> edMul = { 0,0,0,0,0 };
		uint8 edMulSymbol = 0;
		IntBigMul(e, d, edMul, edMulSymbol);

		TArray<int32> bfMul = { 0,0,0,0,0 };
		uint8 bfMulSymbol = 0;
		IntBigMul(f, b, bfMul, bfMulSymbol);

		TArray<int32> edbfSub = {0,0,0,0,0};
		uint8 edbfSubSymbol = 0;
		IntBigSub(edMul, bfMul, edbfSub, edMulSymbol, bfMulSymbol, edbfSubSymbol);

		int32 interX = IntBigDiv(edbfSub, denominator, edbfSubSymbol);
		interaction.X = interX;


		TArray<int32> afMul = { 0,0,0,0,0 };
		uint8 afMulSymbol = 0;
		IntBigMul(f, a, afMul, afMulSymbol);

		TArray<int32> ceMul = { 0,0,0,0,0 };
		uint8 ceMulSymbol = 0;
		IntBigMul(e, c, ceMul, ceMulSymbol);

		TArray<int32> afceSub = { 0,0,0,0,0 };
		uint8 afceSubSymbol = 0;
		IntBigSub(afMul, ceMul, afceSub, afMulSymbol, ceMulSymbol, afceSubSymbol);

		int32 interY = IntBigDiv(afceSub, denominator, afceSubSymbol);
		interaction.Y = interY;
	}
	return true;
}

void UCollisionWarBpFunctionLibrary::SortPointsClockwise_Int(TArray<FLogicVec2D>& pts)
{
	if (pts.Num() < 3) return;
	FLogicVec2D center = GetCenterPt_Int(pts);
	FLogicVec2D unitX(1, 0);
	TArray<int32> angles;
	for (int32 i = 0; i < pts.Num(); i++)
	{
		FLogicVec2D vector(pts[i].X - center.X, pts[i].Y - center.Y);
		int32 expandCosAlpha = 0;
		if (GetLogicVecSize(vector) == 0) expandCosAlpha = 0;
		else 
		{
			int32 expandX = vector.X * 10000;
			int32 vectorSize = GetLogicVecSize(vector);
			expandCosAlpha = (expandX - (expandX % vectorSize)) / vectorSize;
		}
		int32 alpha = LogicACos(expandCosAlpha);
		if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0,0), vector, unitX) > 0) alpha = -alpha;
		angles.Add(alpha);
	}
	for (int32 i = 0; i < angles.Num() - 1; i++)
	{
		for (int32 j = i + 1; j < angles.Num(); j++)
		{
			if (angles[i] <= angles[j])
			{
				int32 tmpAngle = angles[i];
				angles[i] = angles[j];
				angles[j] = tmpAngle;
				FLogicVec2D tmpPt = pts[i];
				pts[i] = pts[j];
				pts[j] = tmpPt;
			}
		}
	}
}

FVector2D UCollisionWarBpFunctionLibrary::GetCenterPt(TArray<FVector2D> pts)
{
	if (pts.Num() == 0) return FVector2D::ZeroVector;
	FVector2D center = FVector2D::ZeroVector;
	for (int32 i=0; i<pts.Num(); i++)
	{
		center.X += pts[i].X;
		center.Y += pts[i].Y;
	}
	center.X = center.X / pts.Num();
	center.Y = center.Y / pts.Num();
	return center;
}

FLogicVec2D UCollisionWarBpFunctionLibrary::GetCenterPt_Int(TArray<FLogicVec2D> pts)
{
	if (pts.Num() == 0) return FLogicVec2D(0,0);
	FLogicVec2D center(0,0);
	for (int32 i = 0; i < pts.Num(); i++)
	{
		center.X += pts[i].X;
		center.Y += pts[i].Y;
	}
	center.X = center.X / pts.Num();
	center.Y = center.Y / pts.Num();
	return center;
}

bool UCollisionWarBpFunctionLibrary::GetPointSymmetryToLine_Int(FLogicVec2D linePt1, FLogicVec2D linePt2, FLogicVec2D pt, FLogicVec2D& symmetryPt)
{
	int32 A = linePt2.Y - linePt1.Y;
	int32 B = linePt1.X - linePt2.X;
	int32 C = linePt2.X*linePt1.Y - linePt1.X*linePt2.Y;
	int32 denominator = A * A + B * B;
	if (denominator == 0) return false;
	/*symmetryPt.X = pt.X - (2 * B*B*pt.Y + 2 * A*B*pt.X + 2 * B*C) / denominator;
	symmetryPt.Y = ((A*A - B*B)*pt.Y - 2 * A*B*pt.X - 2 *B*C) / denominator;*/
	int32 t = A * pt.X + B * pt.Y + C;
	TArray<int32> A2tMul = { 0,0,0,0,0 };
	uint8 A2tMulSym = 0;
	IntBigMul(t, 2 * A, A2tMul, A2tMulSym);
	int32 resultX = IntBigDiv(A2tMul, denominator, A2tMulSym);
	symmetryPt.X = pt.X - resultX;


	TArray<int32> B2tMul = { 0,0,0,0,0 };
	uint8 B2tMulSym = 0;
	IntBigMul(t, 2 * B, B2tMul, B2tMulSym);
	int32 resultY = IntBigDiv(B2tMul, denominator, B2tMulSym);
	symmetryPt.Y = pt.Y - resultY;
	return true;
}

void UCollisionWarBpFunctionLibrary::GetNormalLine_Int(FLogicVec2D footPt, FLogicVec2D baseLinePt1, FLogicVec2D baseLinePt2, FLogicVec3D& line)
{
	int32 A = baseLinePt2.Y - baseLinePt1.Y;
	int32 B = baseLinePt1.X - baseLinePt2.X;
	line.X = B;
	line.Y = -A;
	line.Z = A * footPt.Y - B * footPt.X;
}

void UCollisionWarBpFunctionLibrary::DynamicUpdateBox(FVector startPt, FVector endPt,
	FVector& newWorldLoc, float& newLineLengthHalf, FRotator& newWorldRotator)
{
	newWorldLoc = (startPt + endPt) / 2.f;
	newWorldLoc.Z = startPt.Z;

	FVector offset = endPt - startPt;
	offset.Z = 0;
	newLineLengthHalf = offset.Size() / 2.f;
	offset.Normalize();
	newWorldRotator = offset.ToOrientationRotator();
}

bool UCollisionWarBpFunctionLibrary::GetReflectVectorWithDirAndNormalVector(const FVector2D& originVec, const FVector2D& normalVec, FVector2D& reflectVec)
{
	if (normalVec.Size() <= 0.1f || originVec.Size() <= 0.1) return false;
	float dotProduct = FVector2D::DotProduct(originVec, normalVec);
	reflectVec = originVec - 2.f * dotProduct * normalVec;
	return true;
}

/*

bool UCollisionWarBpFunctionLibrary::GetReflectPointWithDirAndBaseLine_Int(FLogicVec2D originPt, FLogicVec2D dir, FLogicVec2D baseLinePt1, FLogicVec2D baseLinePt2, FLogicVec2D& reflectPoint, FLogicVec2D& interPt)
{
	//return false的情形
	//入射方向与基线平行，找不到交点
	//在入射前，入射点已经越过基线
	//入射方向与基线垂直
	int32 expandCos = GetExpandCosAngleOfTwoVector_Int(dir, baseLinePt2 - baseLinePt1);
	if (expandCos >= 10000 || expandCos <= -10000) return false;
	FLogicVec2D line2Pt1 = originPt;
	FLogicVec2D line2Pt2 = line2Pt1 + dir;
	if (UCollisionWarBpFunctionLibrary::GetInteractionOfTwoLines_Int(baseLinePt1, baseLinePt2, line2Pt1, line2Pt2, interPt))
	{
		if (interPt.X == line2Pt1.X && interPt.Y == line2Pt1.Y) line2Pt1 = line2Pt1 - dir;
		FLogicVec3D normalLine;
		UCollisionWarBpFunctionLibrary::GetNormalLine_Int(interPt, baseLinePt1, baseLinePt2, normalLine);
		FLogicVec2D normalLinePt2 = interPt;
		if (normalLine.Y == 0) normalLinePt2.Y = interPt.Y + 100;
		else
		{
			normalLinePt2.X = interPt.X + 100;
			normalLinePt2.Y = -(normalLine.X*normalLinePt2.X + normalLine.Z) / normalLine.Y;
		}
		FLogicVec2D symmetryPt;
		if (UCollisionWarBpFunctionLibrary::GetPointSymmetryToLine_Int(interPt, normalLinePt2, line2Pt1, symmetryPt))
		{
			reflectPoint = symmetryPt;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("BPFunctionLib::GetReflectPointWithDirAndBaseLine_Int  no symmetry!!!!"));
			return false;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("BPFunctionLib::GetReflectPointWithDirAndBaseLine_Int  no interaction!!!!"));
		return false;
	}
}*/

bool UCollisionWarBpFunctionLibrary::AreTwoLinesParallel_Int(FLogicVec2D line1Pt1, FLogicVec2D line1Pt2, FLogicVec2D line2Pt1, FLogicVec2D line2Pt2)
{
	int32 A1 = line1Pt2.Y - line1Pt1.Y;
	int32 B1 = line1Pt1.X - line1Pt2.X;
	int32 C1 = line1Pt2.X*line1Pt1.Y - line1Pt1.X*line1Pt2.Y;
	int32 A2 = line2Pt2.Y - line2Pt1.Y;
	int32 B2 = line2Pt1.X - line2Pt2.X;
	int32 C2 = line2Pt2.X*line2Pt1.Y - line2Pt1.X*line2Pt2.Y;
	if (B1 == 0 && B2 == 0) return true;
	else if ((B1 == 0 && B2 != 0) || (B1 != 0 && B2 == 0)) return false;
	else if (A1 * B2  == A2 * B1) return true;
	else return false;
}

bool UCollisionWarBpFunctionLibrary::GetCOCAndRadiusFromThreePoints_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3, FLogicVec2D& coc, int32& r)
{
	if (AreTwoLinesParallel_Int(pt1, pt2, pt2, pt3)) return false;
	int32 a = 2 * (pt2.X - pt1.X);
	int32 b = 2 * (pt2.Y - pt1.Y);
	int32 c = pt2.X*pt2.X + pt2.Y*pt2.Y - pt1.X*pt1.X - pt1.Y*pt1.Y;
	int32 d = 2 * (pt3.X - pt2.X);
	int32 e = 2 * (pt3.Y - pt2.Y);
	int32 f = pt3.X*pt3.X + pt3.Y*pt3.Y - pt2.X*pt2.X - pt2.Y*pt2.Y;
	int32 denominator = b * d - e * a;

	TArray<int32> fbMul = { 0,0,0,0,0 };
	uint8 fbMulSym = 0;
	IntBigMul(f, b, fbMul, fbMulSym);
	TArray<int32> ceMul = { 0,0,0,0,0 };
	uint8 ceMulSym = 0;
	IntBigMul(c, e,ceMul, ceMulSym);
	TArray<int32> fbceSub = { 0,0,0,0,0 };
	uint8 fbceSubSym = 0;
	IntBigSub(fbMul, ceMul, fbceSub, fbMulSym, ceMulSym, fbceSubSym);
	coc.X = IntBigDiv(fbceSub, denominator, fbceSubSym);


	TArray<int32> cdMul = { 0,0,0,0,0 };
	uint8 cdMulSym = 0;
	IntBigMul(c, d, cdMul, cdMulSym);
	TArray<int32> faMul = { 0,0,0,0,0 };
	uint8 faMulSym = 0;
	IntBigMul(f, a, faMul, faMulSym);
	TArray<int32> cdfaSub = { 0,0,0,0,0 };
	uint8 cdfaSubSym = 0;
	IntBigSub(cdMul, faMul, cdfaSub, cdMulSym, faMulSym, cdfaSubSym);
	coc.Y = IntBigDiv(cdfaSub, denominator, cdfaSubSym);

	//取整
	r = IntSqrt((coc.X - pt1.X)*(coc.X - pt1.X) + (coc.Y - pt1.Y)*(coc.Y - pt1.Y));
	return true;
}

bool UCollisionWarBpFunctionLibrary::GetInterPtOfSegmentAndCircle_Int(FLogicVec2D coc, int32 r, FLogicVec2D segmentPt1, FLogicVec2D segmentPt2, TArray<FLogicVec2D>& interPt)
{
	int32 e = segmentPt2.Y - segmentPt1.Y;
	int32 f = segmentPt1.X - segmentPt2.X;
	int32 g = segmentPt2.X*segmentPt1.Y - segmentPt1.X*segmentPt2.Y;
	if (e == 0 && f == 0) return false;
	else if (f != 0)
	{
		int32 k = -e / f;
		int32 b = -g / f;
		int32 c = coc.X;
		int32 d = coc.Y;
		int32 A = (k*b - k * d - c) / (k*k + 1);
		int32 B = (r*r - c * c - b * b + 2 * b*d - d * d) / (k*k + 1);
		int32 C = A * A + B;
		if (C < 0) return false;
		FLogicVec2D interPt1(0,0);
		FLogicVec2D interPt2(0,0);
		interPt1.X = IntSqrt(C) - A;
		interPt1.Y = k * interPt1.X + b;
		interPt2.X = -IntSqrt(C) - A;
		interPt2.Y = k * interPt2.X + b;
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt1)) interPt.Add(interPt1);
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt2)) interPt.Add(interPt2);
	}
	else
	{
		FLogicVec2D interPt1(0, 0);
		FLogicVec2D interPt2(0, 0);
		int32 b = g / e;
		interPt1.X = -b;
		interPt2.X = -b;
		int32 c = coc.X;
		int32 d = coc.Y;
		if (FMath::Abs(r*r - (b + c)*(b + c)) >= 0x7FFFFFFF)
		{
			int32 A = r * r / 10000 - (b + c) / 10000 * (b + c);
			if (A < 0) return false;
			interPt1.Y = IntSqrt(A) * 100 + d;
			interPt2.Y = -IntSqrt(A) * 100 + d;
		}
		else
		{
			int32 A = r * r - (b + c)*(b + c);
			if (A < 0) return false;
			interPt1.Y = IntSqrt(A) + d;
			interPt2.Y = -IntSqrt(A) + d;
		}

		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt1)) interPt.Add(interPt1);
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt2)) interPt.Add(interPt2);
	}
	return true;
}

bool UCollisionWarBpFunctionLibrary::GetFirstInterPtOfSegmentAndCircle_Int(FLogicVec2D coc, int32 r, FLogicVec2D segmentPt1, FLogicVec2D segmentPt2, FLogicVec2D& interPt)
{
	int32 e = segmentPt2.Y - segmentPt1.Y;
	int32 f = segmentPt1.X - segmentPt2.X;
	int32 g = segmentPt2.X*segmentPt1.Y - segmentPt1.X*segmentPt2.Y;
	if (e == 0 && f == 0) return false;
	else if (f != 0)
	{
		int32 k = -e / f;
		int32 b = -g / f;
		int32 c = coc.X;
		int32 d = coc.Y;
		int32 A = (k*b - k * d - c) / (k*k + 1);
		int32 B = (r*r - c * c - b * b + 2 * b*d - d * d) / (k*k + 1);
		int32 C = A * A + B;
		if (C < 0) return false;
		FLogicVec2D interPt1(0, 0);
		FLogicVec2D interPt2(0, 0);
		interPt1.X = IntSqrt(C) - A;
		interPt1.Y = k * interPt1.X + b;
		interPt2.X = -IntSqrt(C) - A;
		interPt2.Y = k * interPt2.X + b;
		int32 size1 = GetLogicVecSize(segmentPt1 - interPt1);
		int32 size2 = GetLogicVecSize(segmentPt1 - interPt2);
		bool pt1OnLine = false;
		bool pt2OnLine = false;
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt1)) pt1OnLine = true;
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt2)) pt2OnLine = true;
		if (pt1OnLine && pt2OnLine)
		{
			if (size1 <= size2) interPt = interPt1;
			else interPt = interPt2;
		}
		else if (pt1OnLine && !pt2OnLine) interPt = interPt1;
		else if (!pt1OnLine && pt2OnLine) interPt = interPt2;
	}
	else
	{
		int32 b = g / e;
		int32 c = coc.X;
		int32 d = coc.Y;
		FLogicVec2D interPt1(0, 0);
		FLogicVec2D interPt2(0, 0);
		interPt1.X = -b;
		interPt2.X = -b;
		if (FMath::Abs(r * r - (b + c)*(b + c)) >= 0x7FFFFFFF)
		{
			int32 A = r * r / 10000 - (b + c) / 10000 * (b + c);
			if (A < 0) return false;
			interPt1.Y = IntSqrt(A) * 100 + d;
			interPt2.Y = -IntSqrt(A) * 100 + d;
		}
		else
		{
			int32 A = r * r - (b + c)*(b + c);
			if (A < 0) return false;
			interPt1.Y = IntSqrt(A) + d;
			interPt2.Y = -IntSqrt(A) + d;
		}
		int32 size1 = GetLogicVecSize(segmentPt1 - interPt1);
		int32 size2 = GetLogicVecSize(segmentPt1 - interPt2);
		bool pt1OnLine = false;
		bool pt2OnLine = false;
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt1)) pt1OnLine = true;
		if (IsPointInRectDefineByTwoPoints_Int(segmentPt1, segmentPt2, interPt2)) pt2OnLine = true;
		if (pt1OnLine && pt2OnLine)
		{
			if (size1 <= size2) interPt = interPt1;
			else interPt = interPt2;
		}
		else if (pt1OnLine && !pt2OnLine) interPt = interPt1;
		else if (!pt1OnLine && pt2OnLine) interPt = interPt2;
	}
	return true;
}

bool UCollisionWarBpFunctionLibrary::IsPointPolyIntercept(const TArray<FLogicVec2D>& polyPoints, const FLogicVec2D& logicPos, const bool& isCircular, const int32& pointRadius)
{
	if (!isCircular)
	{
		for (int32 i = 0; i < polyPoints.Num(); i++)
		{
			int32 nextPtIndex = (i + 1) % polyPoints.Num();
			int32 dis = GetDisOfPointToLine_Int(polyPoints[i], polyPoints[nextPtIndex], logicPos);
			if (dis <= pointRadius) return true;
		}
	}
	else
	{
		FLogicVec2D coc;
		int32 radius;
		UCollisionWarBpFunctionLibrary::GetCOCAndRadiusFromThreePoints_Int(polyPoints[0], polyPoints[1], polyPoints[2], coc, radius);
		int32 dis = UCollisionWarBpFunctionLibrary::GetLogicVecSize(logicPos - coc);
		if (dis <= (radius + pointRadius)) return true;
	}
	return false;
}

bool UCollisionWarBpFunctionLibrary::IsPointLineIntercept(const FLogicVec2D& lineStartPoint, const FLogicVec2D& lineEndPoint, const FLogicVec2D& logicPos, const int32& pointRadius)
{
	int32 dis = UCollisionWarBpFunctionLibrary::GetDisOfPointToLine_Int(lineStartPoint, lineEndPoint, logicPos);
	if (dis <= pointRadius) return true;
	else return false;
}

bool UCollisionWarBpFunctionLibrary::IsPointPointIntercept(const FLogicVec2D& pt1Loc, const int32& pt1Radius, const FLogicVec2D& pt2Loc, const int32 pt2Radius)
{
	int32 dis = UCollisionWarBpFunctionLibrary::GetLogicVecSize(pt1Loc - pt2Loc);
	if (dis <= (pt1Radius + pt2Radius)) return true;
	else return false;
}

bool UCollisionWarBpFunctionLibrary::IsLinePolyIntercept(const FLogicVec2D& startPoint, const FLogicVec2D& endPoint, const TArray<FLogicVec2D>& polyPts, const int32& errorTolerance)
{
	for (int32 i = 0; i < polyPts.Num(); i++)
	{
		int32 nextPtIndex = (i + 1) % polyPts.Num();
		if (IsSegmentsIntersect_Int(startPoint, endPoint, polyPts[i], polyPts[nextPtIndex]))
		{
			/*GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PhysLine::IsLinePolyIntercept ") +
			GetName() + TEXT(" is intercept with polygon"));*/
			return true;
		}
	}
	return false;
}

/*
bool UCollisionWarBpFunctionLibrary::IsLineActorIntercept(const FLogicVec2D& linePt1, const FLogicVec2D& linePt2, const FLogicVec2D& pt3, const int32& actorRadius, const int32& errorTolerance)
{
	if (linePt1 == linePt2) return false;
	FLogicVec2D vec1 = pt3 - linePt1;
	FLogicVec2D vec2 = linePt2 - linePt1;
	int32 expandCosAlpha1 = GetExpandCosAngleOfTwoVector_Int(vec1, vec2);
	int32 alpha1 = LogicACos(expandCosAlpha1);
	if (alpha1 > 90) return false;

	FLogicVec2D vec3 = pt3 - linePt2;
	FLogicVec2D vec4 = linePt1 - linePt2;
	int32 expandCosAlpha2 = GetExpandCosAngleOfTwoVector_Int(vec3, vec4);
	int32 alpha2 = LogicACos(expandCosAlpha2);
	if (alpha2 > 90) return false;

	int32 dis = GetDisOfPointToLine_Int(linePt1, linePt2, pt3);
	if (dis <= (actorRadius - errorTolerance)) return true;
	else return false;
}*/

bool UCollisionWarBpFunctionLibrary::IsPolyPolyIntercept(const TArray<FLogicVec2D>& polyPoints1, const TArray<FLogicVec2D>& polyPoints2)
{
	for (int32 i=0; i<polyPoints1.Num() + polyPoints2.Num(); i++)
	{
		int32 nextPtNb = 0;
		FLogicVec2D curEdgeVec(0, 0);
		FLogicVec2D curEdgePerpendicularVec(0, 0);
		if (i < polyPoints1.Num())
		{
			nextPtNb = (i + 1) % polyPoints1.Num();
			if (polyPoints1[nextPtNb].X == polyPoints1[i].X && polyPoints1[nextPtNb].Y == polyPoints1[i].Y) return false;
			curEdgeVec = polyPoints1[nextPtNb] - polyPoints1[i];
			curEdgePerpendicularVec.X = -curEdgeVec.Y;
			curEdgePerpendicularVec.Y = curEdgeVec.X;
		}
		else
		{
			nextPtNb = (i + 1 - polyPoints1.Num()) % polyPoints2.Num();
			if (polyPoints2[nextPtNb].X == polyPoints2[i - polyPoints1.Num()].X && polyPoints2[nextPtNb].Y == polyPoints2[i - polyPoints1.Num()].Y) return false;
			curEdgeVec = polyPoints2[nextPtNb] - polyPoints2[i - polyPoints1.Num()];
			curEdgePerpendicularVec.X = -curEdgeVec.Y;
			curEdgePerpendicularVec.Y = curEdgeVec.X;
		}
		int32 minProjection1 = 0;
		int32 maxProjection1 = 0;
		for (int32 j=0; j<polyPoints1.Num(); j++)
		{
			int32 dotProduct = curEdgePerpendicularVec.X*polyPoints1[j].X + curEdgePerpendicularVec.Y*polyPoints1[j].Y;
			if (j == 0)
			{
				minProjection1 = dotProduct;
				maxProjection1 = dotProduct;
			}
			else
			{
				if (dotProduct < minProjection1) minProjection1 = dotProduct;
				if (dotProduct > maxProjection1) maxProjection1 = dotProduct;
			}
		}
		int32 minProjection2 = 0;
		int32 maxProjection2 = 0;
		for (int32 j=0; j<polyPoints2.Num(); j++)
		{
			int32 dotProduct = curEdgePerpendicularVec.X*polyPoints2[j].X + curEdgePerpendicularVec.Y*polyPoints2[j].Y;
			if (j == 0)
			{
				minProjection2 = dotProduct;
				maxProjection2 = dotProduct;
			}
			else
			{
				if (dotProduct < minProjection2) minProjection2 = dotProduct;
				if (dotProduct > maxProjection2) maxProjection2 = dotProduct;
			}
		}

		if (minProjection1 < minProjection2 && minProjection2 > maxProjection1) return false;
		else if (minProjection2 < minProjection1 && minProjection1 > maxProjection2) return false;
	}
	return true;
}

bool UCollisionWarBpFunctionLibrary::IsPolyCircleIntercept(const TArray<FLogicVec2D>& polyPoints, const FLogicVec2D& centerPt, const int32& radius)
{
	for (int32 i=0; i<polyPoints.Num(); i++)
	{
		int32 nextPtNb = (i + 1) % polyPoints.Num();
		if (polyPoints[nextPtNb].X == polyPoints[i].X && polyPoints[nextPtNb].Y == polyPoints[i].Y) return false;
		FLogicVec2D curEdgeVec = polyPoints[nextPtNb] - polyPoints[i];
		FLogicVec2D curEdgePerpendicularVec(-curEdgeVec.Y, curEdgeVec.X);
		FLogicVec2D circleRadiusExtent = NormalizeLogicVecToPositiveScale(curEdgePerpendicularVec, radius);
		FLogicVec2D extentPt1 = centerPt + circleRadiusExtent;
		FLogicVec2D extentPt2 = centerPt - circleRadiusExtent;
		int32 minCircleProjection = 0;
		int32 maxCircleProjection = 0;
		int32 circleProjection1 = curEdgePerpendicularVec.X*extentPt1.X + curEdgePerpendicularVec.Y*extentPt1.Y;
		int32 circleProjection2 = curEdgePerpendicularVec.X*extentPt2.X + curEdgePerpendicularVec.Y*extentPt2.Y;
		if (circleProjection1 <= circleProjection2)
		{
			minCircleProjection = circleProjection1;
			maxCircleProjection = circleProjection2;
		}
		else
		{
			minCircleProjection = circleProjection2;
			maxCircleProjection = circleProjection1;
		}

		int32 minProjection = 0;
		int32 maxProjection = 0;
		for (int32 j = 0; j < polyPoints.Num(); j++)
		{
			int32 dotProduct = curEdgePerpendicularVec.X*polyPoints[j].X + curEdgePerpendicularVec.Y*polyPoints[j].Y;
			if (j == 0)
			{
				minProjection = dotProduct;
				maxProjection = dotProduct;
			}
			else
			{
				if (dotProduct < minProjection) minProjection = dotProduct;
				if (dotProduct > maxProjection) maxProjection = dotProduct;
			}
		}

		if (minCircleProjection < minProjection && minProjection > maxCircleProjection) return false;
		else if (minProjection < minCircleProjection && minCircleProjection > maxProjection) return false;
	}
	return true;
}
/*

void UCollisionWarBpFunctionLibrary::GetReflectDirWithDirAndBaseLine_Int(FLogicVec3D originDir, FLogicVec2D baseLinePt1, FLogicVec2D baseLinePt2, FLogicVec3D& reflectDir)
{
	originDir.Z = 0;
	FLogicVec2D originDir2D(originDir.X, originDir.Y);
	FLogicVec2D baseLineDir = baseLinePt2 - baseLinePt1;
	int32 expandCosAlpha = GetExpandCosAngleOfTwoVector_Int(originDir2D, baseLineDir);
	int32 alpha = LogicACos(expandCosAlpha);
	FLogicVec2D rotateDir2D(0,0);
	if (GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), baseLineDir, originDir2D) > 0)
		rotateDir2D = GetPtRotateAroundPtByAlpha_Int(originDir2D, FLogicVec2D(0, 0), 2 * alpha);
	else rotateDir2D = GetPtRotateAroundPtByAlpha_Int(originDir2D, FLogicVec2D(0, 0), 2 * alpha);
	reflectDir.X = rotateDir2D.X;
	reflectDir.Y = rotateDir2D.Y;
	reflectDir.Z = 0;
}*/

UTexture2D* UCollisionWarBpFunctionLibrary::GetTextureFromName(const FString& actorName, const FString& typeName)
{
	FString textureName = FString(TEXT("T_")) + actorName;
	FString texturePath = TEXT("/Game/TopDown/Texture2D/");
	texturePath += typeName;
	texturePath += TEXT("/");
	texturePath = texturePath + textureName + TEXT(".") + textureName;
	const TCHAR* pathChar = *texturePath;
	UTexture2D* pTexture = (UTexture2D*)(StaticLoadObject(UTexture2D::StaticClass(), NULL, pathChar, NULL, LOAD_None, NULL));
	return pTexture;
}

UClass* UCollisionWarBpFunctionLibrary::GetAttachEquipBlueprintClassDynamic(FString className)
{
	FString BPClassName = FString(TEXT("BP_")) + className;
	FString classPath = TEXT("/Game/TopDown/Blueprints/EquipmentInfo/");
	classPath = classPath + BPClassName + TEXT(".") + BPClassName + TEXT("_C");
	const TCHAR* pathChar = *classPath;
	UClass* pBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, pathChar));
	//auto cls = StaticLoadObject(UClass::StaticClass(), nullptr, pathChar);
	//UClass* pBP = Cast<UClass>(cls);
	//TSubclassOf<class UObject> BPClass;
	//BPClass = (UClass*)pBP->GeneratedClass;
	return pBP;
}

FVector2D UCollisionWarBpFunctionLibrary::GetMouseScreenPosition(APlayerController* pController)
{
	float mouseScreenX = 0;
	float mouseScreenY = 0;
	FVector2D result = FVector2D::ZeroVector;
	if (pController && pController->GetMousePosition(mouseScreenX, mouseScreenY))
	{
		float scale = UWidgetLayoutLibrary::GetViewportScale(pController);
		mouseScreenX = mouseScreenX / scale;
		mouseScreenY = mouseScreenY / scale;
		result.X = mouseScreenX;
		result.Y = mouseScreenY;
		return result;
	}
	return result;
}

XMLElement* UCollisionWarBpFunctionLibrary::SearchXMLNodeByAttribute(XMLElement* pSourceNode, FString targetNodeName, FString targetNodeAttribute, FString attributeValue)
{
	if (!pSourceNode) return NULL;
	XMLElement* pCurChildNode = pSourceNode->FirstChildElement();
	if (!pCurChildNode) return NULL;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == targetNodeName)
		{
			char* targetAttribute = TCHAR_TO_ANSI(*targetNodeAttribute);
			const char* attributeChar = pCurChildNode->Attribute(targetAttribute);
			if (attributeChar != 0)
			{
				FString attribute = ANSI_TO_TCHAR(attributeChar);
				if (attribute == attributeValue) return pCurChildNode;
			}
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	pCurChildNode = pSourceNode->FirstChildElement();
	while (pCurChildNode)
	{
		XMLElement* pResult = SearchXMLNodeByAttribute(pCurChildNode, targetNodeName, targetNodeAttribute, attributeValue);
		if (pResult) return pResult;
		else pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	return NULL;
}

XMLElement* UCollisionWarBpFunctionLibrary::SearchXMLNodeByContent(XMLElement* pSourceNode, FString targetNodeName, FString content)
{
	if (!pSourceNode) return NULL;
	XMLElement* pCurChildNode = pSourceNode->FirstChildElement();
	if (!pCurChildNode) return NULL;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == targetNodeName)
		{
			const char* nodeContentChar = pCurChildNode->GetText();
			if (nodeContentChar != 0)
			{
				FString nodeContent = ANSI_TO_TCHAR(nodeContentChar);
				if (nodeContent == content) return pCurChildNode;
			}
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	pCurChildNode = pSourceNode->FirstChildElement();
	while (pCurChildNode)
	{
		XMLElement* pResult = SearchXMLNodeByContent(pCurChildNode, targetNodeName, content);
		if (pResult) return pResult;
		else pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	return NULL;
}

XMLElement* UCollisionWarBpFunctionLibrary::GetXMLFirstWorksheetNode(XMLElement* pSourceNode)
{
	if (!pSourceNode) return NULL;
	XMLElement* pCurChildNode = pSourceNode->FirstChildElement();
	if (!pCurChildNode) return NULL;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == TEXT("Worksheet")) return pCurChildNode;
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	return NULL;
}

XMLElement* UCollisionWarBpFunctionLibrary::GetXMLRowByContentFromTableNode(XMLElement* pTableNode, FString content)
{
	if (!pTableNode) return NULL;
	XMLElement* pCurChildNode = pTableNode->FirstChildElement();
	if (!pCurChildNode) return NULL;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == "Row")
		{
			XMLElement* pCellNode = pCurChildNode->FirstChildElement();
			while (pCellNode)
			{
				XMLElement* pDataNode = pCellNode->FirstChildElement();
				if (pDataNode)
				{
					const char* nodeDataChar = pDataNode->GetText();
					FString nodeData = ANSI_TO_TCHAR(nodeDataChar);
					if (nodeData == content) return pCurChildNode;
				}
				pCellNode = pCellNode->NextSiblingElement();
			}
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	return NULL;
}

bool UCollisionWarBpFunctionLibrary::IsStringArrayContaintString(TArray<FString> strings, FString string)
{
	for (int32 i=0; i<strings.Num(); i++)
	{
		if (strings[i] == string) return true;
	}
	return false;
}

FVector2D UCollisionWarBpFunctionLibrary::GetVectorByBreakComma(FString string)
{
	int32 commaPos = string.Find(TEXT(","));
	if (commaPos == -1) return FVector2D::ZeroVector;
	int32 stringLen = string.Len();
	FString XString = string.Mid(0, commaPos);
	FString YString = string.Mid(commaPos + 1, stringLen - commaPos - 1);
	float x = FCString::Atof(*XString);
	float y = FCString::Atof(*YString);
	FVector2D result(x, y);
	return result;
}

void UCollisionWarBpFunctionLibrary::LoadPlayerInfo(FString playerName, TArray<FString>& kingCharacterTypes)
{
	FString _xmlpath = FPaths::GameDir() + "PlayerInfos.xml";
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
	XMLElement* pTargetWorkSheetNode = UCollisionWarBpFunctionLibrary::SearchXMLNodeByAttribute(pRootNode, "Worksheet", "ss:Name", playerName);
	if (!pTargetWorkSheetNode)
	{
		delete doc;
		return;
	}
	XMLElement* pTableNode = pTargetWorkSheetNode->FirstChildElement();
	XMLElement* pPlayerOwnKingTypesInfoRow = UCollisionWarBpFunctionLibrary::GetXMLRowByContentFromTableNode(pTableNode, "PlayerOwnKingTypes:");
	XMLElement* pPlayerEndInfoRow = UCollisionWarBpFunctionLibrary::GetXMLRowByContentFromTableNode(pTableNode, "PlayerEnd");
	XMLElement* pCurRowNode = pPlayerOwnKingTypesInfoRow;
	/*读取玩家生成信息*/
	pCurRowNode = pCurRowNode->NextSiblingElement();
	while (pCurRowNode != pPlayerEndInfoRow)
	{
		XMLElement* pCellNode = pCurRowNode->FirstChildElement();
		const char* cellTextChar = pCellNode->FirstChildElement()->GetText();
		FString cellTextString = ANSI_TO_TCHAR(cellTextChar);
		kingCharacterTypes.Add(cellTextString);
		pCurRowNode = pCurRowNode->NextSiblingElement();
	}
}

void UCollisionWarBpFunctionLibrary::PushStringIntoArray(FString str, TArray<FString>& stringArray)
{
	stringArray.Add(str);
}

void UCollisionWarBpFunctionLibrary::AppendStringListToStringList(TArray<FString>& newList, TArray<FString>& originalList)
{
	for (int32 i=0; i<newList.Num(); i++)
	{
		originalList.Add(newList[i]);
	}
}

void UCollisionWarBpFunctionLibrary::CopyReactionInfo(FReactionInfo copyInfo, FReactionInfo& targetInfo)
{
	targetInfo.reactionType = copyInfo.reactionType;
	targetInfo.reactionTag = copyInfo.reactionTag;
	targetInfo.BPSpawnActorClass = copyInfo.BPSpawnActorClass;
	targetInfo.BPTransformActor1Class = copyInfo.BPTransformActor1Class;
	targetInfo.BPTransformActor2Class = copyInfo.BPTransformActor2Class;
	targetInfo.HostTag = copyInfo.HostTag;
	targetInfo.modifyTag1 = copyInfo.modifyTag1;
	targetInfo.modifyTag2 = copyInfo.modifyTag2;
}

int32 UCollisionWarBpFunctionLibrary::LogicCos(int32 angle)
{
	bool isValid = true;
	UCollisionWarSingleton* pCWSingleton = GetGlobalSingleton(isValid);
	if (!isValid) return 0;

	if (angle < 0) angle = -angle;
	if (FMath::Abs(angle) > 360) angle = angle % 360;
	if (angle > 180)
	{
		angle = angle % 180;
		return -pCWSingleton->m_cosExpandList[angle];
	}
	else return pCWSingleton->m_cosExpandList[angle];
}

int32 UCollisionWarBpFunctionLibrary::LogicSin(int32 angle)
{
	return LogicCos(angle - 90);
}

int32 UCollisionWarBpFunctionLibrary::CheckACosList(const TArray<int32>& list, const int32& target, int32 head, int32 end)
{
	if (FMath::Abs(head - end) <= 1) return head;
	else
	{
		if (list[head] == target) return head;
		if (list[end] == target) return end;

		int32 mid = 0;
		int32 mod = (head + end) % 2;
		if (mod == 1) mid = (head + end - 1) / 2;
		else mid = (head + end) / 2;
		if (list[mid] == target) return mid;
		else if (list[mid] < target) return CheckACosList(list, target, head, mid);
		else return CheckACosList(list, target, mid, end);
	}
}

int32 UCollisionWarBpFunctionLibrary::LogicACos(int32 expandCos)
{
	if (expandCos > 10000 || expandCos < -10000) return 0;
	bool isValid = true;
	UCollisionWarSingleton* pCWSingleton = GetGlobalSingleton(isValid);
	if (!isValid) return 0;

	int32 angle = CheckACosList(pCWSingleton->m_cosExpandList, expandCos, 0, 180);
	return angle;
}

int32 UCollisionWarBpFunctionLibrary::CalExpByLevel(const int32& K, const int32& N, const int32& C, const int32& level)
{
	int32 upperExp = FMath::Pow(level - 1, K) * N + C;
	return upperExp;
}

