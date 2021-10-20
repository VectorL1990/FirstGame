// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "NavManager.h"
#include "RoguelikeBattleGameMode.h"
#include "Kismet/KismetMathLibrary.h"

class ABasePhysGeo;
class ADumpPhysActor;

// Sets default values
ANavManager::ANavManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANavManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANavManager::GetAllNeighborNodes(int32 X, int32 Y, TArray<URouteNode*>& NeighborNodes)
{
	if (RouteNodeMap->RowInfos.Contains(Y))
	{
		if (RouteNodeMap->RowInfos[Y]->ColumnNodes.Contains(X + 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y]->ColumnNodes[X + 1]);
		}
		if (RouteNodeMap->RowInfos[Y]->ColumnNodes.Contains(X - 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y]->ColumnNodes[X - 1]);
		}
	}
	if (RouteNodeMap->RowInfos.Contains(Y - 1))
	{
		if (RouteNodeMap->RowInfos[Y - 1]->ColumnNodes.Contains(X + 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y - 1]->ColumnNodes[X + 1]);
		}
		if (RouteNodeMap->RowInfos[Y - 1]->ColumnNodes.Contains(X - 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y - 1]->ColumnNodes[X - 1]);
		}
		if (RouteNodeMap->RowInfos[Y - 1]->ColumnNodes.Contains(X))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y - 1]->ColumnNodes[X]);
		}
	}
	if (RouteNodeMap->RowInfos.Contains(Y + 1))
	{
		if (RouteNodeMap->RowInfos[Y + 1]->ColumnNodes.Contains(X + 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y + 1]->ColumnNodes[X + 1]);
		}
		if (RouteNodeMap->RowInfos[Y + 1]->ColumnNodes.Contains(X - 1))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y + 1]->ColumnNodes[X - 1]);
		}
		if (RouteNodeMap->RowInfos[Y + 1]->ColumnNodes.Contains(X))
		{
			NeighborNodes.Add(RouteNodeMap->RowInfos[Y + 1]->ColumnNodes[X]);
		}
	}
}

void ANavManager::TracePath(URouteNode* FinalNode, URouteNode* EndNode, TArray<FVector>& OutputNodes)
{
	FVector2D ScanStepSize(ScanGridSize.X, ScanGridSize.Y);
	FVector RealEndNode = EndNode->GetRealCoordinate(ScanStartPoint, ScanStepSize);
	OutputNodes.Insert(RealEndNode, 0);
	URouteNode* CurrentNode = FinalNode;
	FVector RealPreEndNode = FinalNode->GetRealCoordinate(ScanStartPoint, ScanStepSize);
	OutputNodes.Insert(RealPreEndNode, 0);
	while (CurrentNode->ParentNode)
	{
		FVector RealCurrentNode = CurrentNode->GetRealCoordinate(ScanStartPoint, ScanStepSize);
		OutputNodes.Insert(RealCurrentNode, 0);
		CurrentNode = CurrentNode->ParentNode;
	}
}

void ANavManager::RefreshNetwork()
{

}

// Called every frame
void ANavManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANavManager::ExtractAllGridFromMap(FVector2D LBPoint, FVector2D RTPoint)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* RGM = Cast<ARoguelikeBattleGameMode>(GameMode);
	ScanStepNbX = (int32)((ScanEndPoint.X - ScanStartPoint.X) / ScanGridSize.X);
	ScanStepNbY = (int32)((ScanEndPoint.Y - ScanStartPoint.Y) / ScanGridSize.Y);
	RouteNodeMap = NewObject<URouteNodeMapInfo>();
	RouteNodeMap->RowInfos.Empty();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);
	
	// First we initial all scan grid
	for (int32 i=0; i<ScanStepNbY; i++)
	{
		for (int32 j=0; j<ScanStepNbY; j++)
		{

		}
	}

	for (int32 i = 0; i < ScanStepNbY; i++)
	{
		for (int32 j = 0; j < ScanStepNbX; j++)
		{
			float ScanLocX = ScanStartPoint.X + (float)(j * ScanGridSize.X);
			float ScanLocY = ScanStartPoint.Y + (float)(i * ScanGridSize.Y);
			float ScanLocZ = ScanStartPoint.Z;
			FVector ScanLoc(ScanLocX, ScanLocY, ScanLocZ);
			TArray<AActor*> IgnoreActors;
			TArray<AActor*> BasePhysGeoActors;
			TArray<AActor*> DumpActors;
			UKismetSystemLibrary::BoxOverlapActors(RGM, ScanLoc, ScanGridSize / 2.f, ObjectTypes, ABasePhysGeo::StaticClass(), IgnoreActors, BasePhysGeoActors);
			UKismetSystemLibrary::BoxOverlapActors(RGM, ScanLoc, ScanGridSize / 2.f, ObjectTypes, ADumpPhysActor::StaticClass(), IgnoreActors, DumpActors);
			if (BasePhysGeoActors.Num() <= 0 && DumpActors.Num() <= 0)
			{
				URouteNode* NewRouteNode = NewObject<URouteNode>(this);
				NewRouteNode->X = j;
				NewRouteNode->Y = i;
				if (RouteNodeMap->RowInfos.Contains(i))
				{
					// Which means row already exists, add column information only
					RouteNodeMap->RowInfos[i]->ColumnNodes.Add(j, NewRouteNode);
				}
				else
				{
					// Which means current row doesn't exist, add new row
					URouteNodeRowInfo* NewRow = NewObject<URouteNodeRowInfo>();
					NewRow->ColumnNodes.Add(j, NewRouteNode);
					RouteNodeMap->RowInfos.Add(i, NewRow);
				}
			}
		}
	}
}

void ANavManager::ConvertRealCoordinateToGrid(FVector InPos, int32& OutX, int32& OutY)
{
	FVector Offset = InPos - ScanStartPoint;
	OutX = (int32)(Offset.X / ScanGridSize.X);
	OutY = (int32)(Offset.Y / ScanGridSize.Y);
}

URouteNode* ANavManager::FindNearestNodeByCoordinate(int32 X, int32 Y)
{
	int32 MiniumDistance = 999999999;
	URouteNode* ClosestNode = NULL;
	for (TMap<int32, URouteNodeRowInfo*>::TConstIterator RowIter = RouteNodeMap->RowInfos.CreateConstIterator(); RowIter; ++RowIter)
	{
		for (TMap<int32, URouteNode*>::TConstIterator ColIter = RowIter->Value->ColumnNodes.CreateConstIterator(); ColIter; ++ColIter)
		{
			int32 Offset = UKismetMathLibrary::Abs_Int(ColIter->Value->X - X) + UKismetMathLibrary::Abs_Int(ColIter->Value->Y - Y);
			if (Offset == 0)
			{
				ClosestNode = ColIter->Value;
				break;
			}
			else if (Offset < MiniumDistance)
			{
				MiniumDistance = Offset;
				ClosestNode = ColIter->Value;
			}
		}
	}
	return ClosestNode;
}

void ANavManager::FindPath(URouteNode* StartNode, URouteNode* EndNode, float PathHeight, TArray<FVector>& OutputNodes)
{
	OpenList.Empty();
	StartNode->G = 0;
	StartNode->H = 0;
	StartNode->F = 0;
	OpenList.Add(StartNode);
	StartNode->NodeState = EPathNodeState::InOpenList;
	FVector2D ScanStepSize(ScanGridSize.X, ScanGridSize.Y);
	while (OpenList.Num() != 0)
	{
		// OpenList is sort by F value(which is actually the cost value from start point to end point)
		// So the last node is always the node with minimum distance, we should search it first
		URouteNode* LastNode = OpenList.Last();
		OpenList.Pop();
		LastNode->NodeState = EPathNodeState::InCloseList;
		if (LastNode == EndNode)
		{
			// Which means it reaches the end, return immediatly
			TracePath(LastNode, EndNode, OutputNodes);
		}

		// Get all neighbor nodes, inspect them one by one
		TArray<URouteNode*> NeighborNodes;
		GetAllNeighborNodes(LastNode->X, LastNode->Y, NeighborNodes);
		FVector LastNodeRealCoord = LastNode->GetRealCoordinate(ScanStartPoint, ScanStepSize);
		for (int32 i = 0; i < NeighborNodes.Num(); i++)
		{
			if (NeighborNodes[i]->NodeState == EPathNodeState::InCloseList)
			{
				// This node has already been inspected, skip it
				continue;
			}
			FVector NeighborRealCoord = NeighborNodes[i]->GetRealCoordinate(ScanStartPoint, ScanStepSize);
			int32 Distance = 0;
			if (NeighborNodes[i]->X == LastNode->X || NeighborNodes[i]->Y == LastNode->Y)
			{
				Distance = NormalDistance;
			}
			else
			{
				Distance = DiagonalDistance;
			}
			int32 NeighborG = LastNode->G + Distance;

			if (NeighborNodes[i]->NodeState == EPathNodeState::Default || NeighborG < NeighborNodes[i]->G)
			{
				NeighborNodes[i]->G = NeighborG;
				NeighborNodes[i]->H = UKismetMathLibrary::Abs_Int(NeighborNodes[i]->X - LastNode->X) +
					UKismetMathLibrary::Abs_Int(NeighborNodes[i]->Y - LastNode->Y);
				NeighborNodes[i]->F = NeighborNodes[i]->G + NeighborNodes[i]->H;
				NeighborNodes[i]->ParentNode = LastNode;
				if (NeighborNodes[i]->NodeState == EPathNodeState::Default)
				{
					NeighborNodes[i]->NodeState = EPathNodeState::InOpenList;
					if (OpenList.Num() == 0)
					{
						OpenList.Add(NeighborNodes[i]);
					}
					else
					{
						for (int32 j = 0; j < OpenList.Num(); j++)
						{
							if (NeighborNodes[i]->F > OpenList[j]->F)
							{
								OpenList.Insert(NeighborNodes[i], j);
								break;
							}
						}
					}
				}
				else
				{
					int32 CurrentNodePos = OpenList.Find(NeighborNodes[i]);
					if (CurrentNodePos < OpenList.Num() - 2)
					{
						while (NeighborNodes[i]->F < OpenList[CurrentNodePos + 1]->F)
						{
							if (CurrentNodePos >= OpenList.Num() - 1)
							{
								break;
							}
							URouteNode* TempNode = OpenList[CurrentNodePos + 1];
							OpenList[CurrentNodePos + 1] = NeighborNodes[i];
							OpenList[CurrentNodePos] = TempNode;
							CurrentNodePos += 1;
						}
						if (CurrentNodePos > 0)
						{
							while (NeighborNodes[i]->F > OpenList[CurrentNodePos - 1]->F)
							{
								if (CurrentNodePos <= 0)
								{
									break;
								}
								URouteNode* TempNode = OpenList[CurrentNodePos - 1];
								OpenList[CurrentNodePos - 1] = NeighborNodes[i];
								OpenList[CurrentNodePos] = TempNode;
								CurrentNodePos -= 1;
							}
						}
					}
				}
			}
		}
	}
	RefreshNetwork();
}

void ANavManager::ConvertAStartPointsToCriticalPoints(const TArray<FVector>& AStarPoints, TArray<FVector>& OutCriticalPoints)
{

}

