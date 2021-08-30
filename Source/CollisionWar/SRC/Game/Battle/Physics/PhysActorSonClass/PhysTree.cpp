// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysTree.h"




void APhysTree::ConstructTree(TArray<USplineComponent*> pBaseSplines)
{
	if (!m_pTrunckMesh) return;
	/*for (int32 i=0; i<m_pTrunckSplineMeshComponents.Num(); i++)
	{
		m_pTrunckSplineMeshComponents[i]->DestroyComponent(false);
	}
	m_pTrunckSplineMeshComponents.Empty();*/

	int32 branchNb = 0;
	for (int32 i = 0; i < pBaseSplines.Num(); i++)
	{
		if (!pBaseSplines[i]) continue;
		int32 splinePointNb = pBaseSplines[i]->GetNumberOfSplinePoints();
		TArray<USplineMeshComponent*> pTrunckSplineMeshComponents;
		for (int32 j = 0; j < splinePointNb - 1; j++)
		{
			FString componentStr = "SplineMeshComponent_" + FString::FromInt(branchNb);
			USplineMeshComponent* pSplineMeshComponent = NewObject<USplineMeshComponent>(pBaseSplines[i], FName(*componentStr));
			pSplineMeshComponent->SetStaticMesh(m_pTrunckMesh);
			pSplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
			FAttachmentTransformRules attachRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
			pSplineMeshComponent->AttachToComponent(pBaseSplines[i], attachRules);
			pSplineMeshComponent->RegisterComponent();
			FVector startLoc;
			FVector startTangent;
			FVector endLoc;
			FVector endTangent;
			pBaseSplines[i]->GetLocationAndTangentAtSplinePoint(j, startLoc, startTangent, ESplineCoordinateSpace::Local);
			pBaseSplines[i]->GetLocationAndTangentAtSplinePoint(j + 1, endLoc, endTangent, ESplineCoordinateSpace::Local);
			pSplineMeshComponent->SetStartAndEnd(startLoc, startTangent, endLoc, endTangent);
			pTrunckSplineMeshComponents.Add(pSplineMeshComponent);
			branchNb += 1;

			if (i >= m_allDumpBranchInfos.Num() || j >= m_allDumpBranchInfos[i].splinePointScales.Num()) continue;
			pSplineMeshComponent->SetStartScale(m_allDumpBranchInfos[i].splinePointScales[j]);
			if (j > 0) pTrunckSplineMeshComponents[j - 1]->SetEndScale(m_allDumpBranchInfos[i].splinePointScales[j]);
			if (j == splinePointNb - 2) pTrunckSplineMeshComponents[j]->SetEndScale(m_allDumpBranchInfos[i].endSplinePointScale);

			float disStep = (m_allDumpBranchInfos[i].leavesMaxDis - m_allDumpBranchInfos[i].leavesMinDis) / (float)m_allDumpBranchInfos[i].leavesBranchNb;
			for (int32 k = 0; k < m_allDumpBranchInfos[i].leavesBranchNb; k++)
			{
				float curLeavesBranchDis = m_allDumpBranchInfos[i].leavesMinDis + (k + 1)*disStep;
				float randPitch = FMath::FRandRange(-m_allDumpBranchInfos[i].maxRandPitch, m_allDumpBranchInfos[i].maxRandPitch);
				float randYaw = FMath::FRandRange(-m_allDumpBranchInfos[i].maxRandYaw, m_allDumpBranchInfos[i].maxRandYaw);
				FRotator combineRot = UKismetMathLibrary::ComposeRotators(GetActorRotation(), FRotator(randPitch, randYaw, 0));
				FVector splineLoc = pBaseSplines[i]->GetLocationAtTime(curLeavesBranchDis, ESplineCoordinateSpace::World, true);
				FTransform leavesBranchTransform(combineRot, splineLoc, FVector(m_allDumpBranchInfos[i].scale, m_allDumpBranchInfos[i].scale, m_allDumpBranchInfos[i].scale));
				NotifyAddLeaves(leavesBranchTransform);
			}
		}
	}
}

void APhysTree::AddBranchToTree()
{

}

void APhysTree::NotifyAddChildActorComponent_Implementation(TSubclassOf<class ADumpTreeBranch> branchClass, FVector relativeLoc, FRotator relativeRot)
{

}

void APhysTree::NotifyAddLeaves_Implementation(FTransform leavesBranchTransform)
{

}
