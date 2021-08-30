// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "EventCard.h"


// Sets default values
AEventCard::AEventCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEventCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isFlip)
	{
		//说明目标是正面朝上
		if (GetActorRotation().Equals(FRotator(0, 0, 90), m_tolerance)) return;
		else
		{
			FRotator stepRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 0, 90), DeltaTime, m_rotateSpeed);
			SetActorRotation(stepRot);
		}
	}
	else
	{
		//说明目标是背面朝上
		if (GetActorRotation().Equals(FRotator(90, 0, 0), m_tolerance)) return;
		else
		{
			FRotator stepRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 0, 180), DeltaTime, m_rotateSpeed);
			SetActorRotation(stepRot);
		}
	}
}

void AEventCard::SetupPlayCard(UStaticMeshComponent* pCardImageMesh, UStaticMeshComponent* pCardMesh, UStaticMeshComponent* pCardRoundCircle, UStaticMeshComponent* pRewardMesh)
{
	m_pCardImageMesh = pCardImageMesh;
	m_pCardMesh = pCardMesh;
	m_pCardImageRoundCircle = pCardRoundCircle;
	m_pRewardMesh = pRewardMesh;
}

void AEventCard::UpdateWarp(float percent)
{
	m_pCardImageMesh->SetScalarParameterValueOnMaterials(FName(TEXT("BackDissolveTime")), percent);
	m_pCardMesh->SetScalarParameterValueOnMaterials(FName(TEXT("Amount")), percent);
	m_pCardImageRoundCircle->SetScalarParameterValueOnMaterials(FName(TEXT("BackDissolveTime")), percent);
}

void AEventCard::InitialPlayCard(uint8 cardType)
{
	
}

void AEventCard::StartWarpIn_Implementation()
{

}

void AEventCard::WarpInEnd()
{
	//m_pWarpPSComponent->Deactivate();
	m_isFlip = true;
}

void AEventCard::NotifyInitialCard_Implementation()
{

}

