// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "DumpTreeBranch.generated.h"

UCLASS()
class COLLISIONWAR_API ADumpTreeBranch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADumpTreeBranch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ConstructBranch(USplineComponent* pBaseSpline);

	void AddLeaves(UStaticMesh* pLeavesMesh, float leavesMaxDis, float leavesMinDis, int32 leavesBranchNb, float maxRandPitch, float maxRandYaw, float scale);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UStaticMesh* m_pBranchMesh;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FVector2D> m_branchScaleIndexList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector2D m_endBranchScaleIndex;

	USplineComponent* m_pBranchSpline;

	TArray<USplineMeshComponent*> m_pBranchSplineMeshComponents;
	
};
