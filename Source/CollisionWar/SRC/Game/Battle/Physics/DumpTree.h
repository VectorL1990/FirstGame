// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/DumpPhysActor.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "DumpTreeBranch.h"
#include "DumpTree.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FDumpBranchInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<FVector2D> splinePointScales;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FVector2D endSplinePointScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	float leavesMaxDis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	float leavesMinDis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 leavesBranchNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	float maxRandPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	float maxRandYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	float scale;
};

UCLASS()
class COLLISIONWAR_API ADumpTree : public ADumpPhysActor
{
	GENERATED_BODY()
	
public:
	ADumpTree();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ConstructDumpTree(TArray<USplineComponent*> pBaseSplines);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AddBranchToTree();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyAddChildActorComponent(TSubclassOf<class ADumpTreeBranch> branchClass, FVector relativeLoc, FRotator relativeRot);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyAddLeaves(FTransform leavesBranchTransform);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UStaticMesh* m_pTrunckMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
	UStaticMesh* m_pLeavesBranchMesh;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FDumpBranchInfo> m_allDumpBranchInfos;
	
	TArray<USplineMeshComponent*> m_pTrunckSplineMeshComponents;
};
