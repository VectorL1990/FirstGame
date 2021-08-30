// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMathLibrary.h"
#include "DumpTreeBranch.h"


// Sets default values
ADumpTreeBranch::ADumpTreeBranch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADumpTreeBranch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADumpTreeBranch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADumpTreeBranch::ConstructBranch(USplineComponent* pBaseSpline)
{
	if (!m_pBranchMesh || !pBaseSpline) return;
	m_pBranchSpline = pBaseSpline;
	for (int32 i = 0; i < m_pBranchSplineMeshComponents.Num(); i++)
	{
		m_pBranchSplineMeshComponents[i]->DestroyComponent(false);
	}
	m_pBranchSplineMeshComponents.Empty();
	int32 splinePointNb = pBaseSpline->GetNumberOfSplinePoints();
	for (int32 i = 0; i < splinePointNb - 1; i++)
	{
		FString componentStr = "SplineMeshComponent_" + FString::FromInt(i);
		//AddComponent()
		USplineMeshComponent* pSplineMeshComponent = NewObject<USplineMeshComponent>(pBaseSpline, FName(*componentStr));
		pSplineMeshComponent->SetStaticMesh(m_pBranchMesh);
		pSplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
		FAttachmentTransformRules attachRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		pSplineMeshComponent->AttachToComponent(pBaseSpline, attachRules);
		pSplineMeshComponent->RegisterComponent();
		FVector startLoc;
		FVector startTangent;
		FVector endLoc;
		FVector endTangent;
		pBaseSpline->GetLocationAndTangentAtSplinePoint(i, startLoc, startTangent, ESplineCoordinateSpace::Local);
		pBaseSpline->GetLocationAndTangentAtSplinePoint(i + 1, endLoc, endTangent, ESplineCoordinateSpace::Local);
		pSplineMeshComponent->SetStartAndEnd(startLoc, startTangent, endLoc, endTangent);
		m_pBranchSplineMeshComponents.Add(pSplineMeshComponent);
		if (i >= m_branchScaleIndexList.Num()) continue;
		pSplineMeshComponent->SetStartScale(m_branchScaleIndexList[i]);
		if (i > 0) m_pBranchSplineMeshComponents[i - 1]->SetEndScale(m_branchScaleIndexList[i]);
		if (i == splinePointNb - 2) m_pBranchSplineMeshComponents[i]->SetEndScale(m_endBranchScaleIndex);

	}
}

void ADumpTreeBranch::AddLeaves(UStaticMesh* pLeavesMesh, float leavesMaxDis, float leavesMinDis, int32 leavesBranchNb, float maxRandPitch, float maxRandYaw, float scale)
{
	if (!pLeavesMesh || !m_pBranchSpline || leavesBranchNb <= 0) return;
	UInstancedStaticMeshComponent* pISMC = NewObject<UInstancedStaticMeshComponent>(this, "LeavesBranch");
	FAttachmentTransformRules attachRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	pISMC->SetStaticMesh(pLeavesMesh);
	pISMC->AttachToComponent(m_pBranchSpline, attachRules);
	float disStep = (leavesMaxDis - leavesMinDis) / (float)leavesBranchNb;
	for (int32 i=0; i<leavesBranchNb; i++)
	{
		float curLeavesBranchDis = leavesMinDis + (i + 1)*disStep;
		float randPitch = FMath::FRandRange(-maxRandPitch, maxRandPitch);
		float randYaw = FMath::FRandRange(-maxRandYaw, maxRandYaw);
		FRotator combineRot = UKismetMathLibrary::ComposeRotators(GetActorRotation(), FRotator(randPitch, randYaw, 0));
		FVector splineLoc = m_pBranchSpline->GetLocationAtTime(curLeavesBranchDis, ESplineCoordinateSpace::World, true);
		FTransform leavesBranchTransform(combineRot, splineLoc, FVector(scale, scale, scale));
		pISMC->AddInstance(leavesBranchTransform);
	}
	pISMC->RegisterComponent();
}

