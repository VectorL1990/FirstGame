#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavManager.generated.h"

enum class EPathNodeState : uint8
{
	Default,
	InOpenList,
	InCloseList
};

/**
 * Route node stores informations like distance between path start point and end point
 * X, Y represents coordinate in map
 * G represents cost from start point to current point
 * H represents cost from current point to destination
 * F is equal to G + H
 */
UCLASS()
class COLLISIONWAR_API URouteNode : public UObject
{
	GENERATED_BODY()
public:
	void Reset()
	{
		NodeState = EPathNodeState::Default;
		G = 999999999;
		H = 0;
		F = 0;
	}

	FVector GetRealCoordinate(FVector OriginPoint, FVector2D Offset)
	{
		float OutputX = OriginPoint.X + (float)(X)*Offset.X;
		float OutputY = OriginPoint.Y + (float)(Y)*Offset.Y;
		float OutputZ = OriginPoint.Z;
		return FVector(OutputX, OutputY, OutputZ);
	}

	EPathNodeState NodeState;
	URouteNode* ParentNode;
	int32 X = 0;
	int32 Y = 0;
	int32 G = 999999999;
	int32 H = 0;
	int32 F = 0;
};

UCLASS()
class COLLISIONWAR_API URouteNodeRowInfo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<int32, URouteNode*> ColumnNodes;
};

/**
 * We use a special struct to store node informations is because we want to get adjacent nodes
 * information quickly, and the whole map is a sparse matrix, it will consume lots of useless memory to store nodes that
 * roads don't access
 */
UCLASS()
class COLLISIONWAR_API URouteNodeMapInfo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<int32, URouteNodeRowInfo*> RowInfos;
};

UCLASS()
class COLLISIONWAR_API ANavManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetAllNeighborNodes(int32 X, int32 Y, TArray<URouteNode*>& NeighborNodes);

	void TracePath(URouteNode* FinalNode, URouteNode* EndNode, TArray<FVector>& OutputNodes);

	void RefreshNetwork();

	// OpenList store all nodes that are waiting for inspect, node with least F value is at back
	TArray<URouteNode*> OpenList;

	UPROPERTY(EditAnywhere)
	FVector ScanRoadGridSize;

	UPROPERTY(EditAnywhere)
	FVector ScanStartPoint;

	UPROPERTY(EditAnywhere)
	int32 ScanStepNbX;

	UPROPERTY(EditAnywhere)
	int32 ScanStepNbY;

	UPROPERTY(EditAnywhere)
	int32 NormalDistance = 10;

	UPROPERTY(EditAnywhere)
	int32 DiagonalDistance = 14;

	UPROPERTY()
	URouteNodeMapInfo* RouteNodeMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ConvertRealCoordinateToGrid(FVector InPos, int32& OutX, int32& OutY);

	URouteNode* FindNearestNodeByCoordinate(int32 X, int32 Y);

	void FindPath(URouteNode* StartNode, URouteNode* EndNode, float PathHeight, TArray<FVector>& OutputNodes);

	void ConvertAStartPointsToCriticalPoints(const TArray<FVector>& AStarPoints, TArray<FVector>& OutCriticalPoints);

	UPROPERTY(EditAnywhere)
	float CriticalPointCaptureRadius = 2000.f;

	UPROPERTY(EditAnywhere)
	TArray<FVector> CriticalPoints;
	
};
