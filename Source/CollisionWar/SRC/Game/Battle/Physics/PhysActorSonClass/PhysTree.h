// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "../DumpTreeBranch.h"
#include "../DumpTree.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "PhysTree.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API APhysTree : public ABasePhysActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void ConstructTree(TArray<USplineComponent*> pBaseSplines);

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
