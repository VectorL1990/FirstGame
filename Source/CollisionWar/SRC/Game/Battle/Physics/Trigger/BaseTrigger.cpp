// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../../Character/BaseCharacter.h"
#include "BaseTrigger.h"


// Sets default values
ABaseTrigger::ABaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_isTriggerOnFlag = false;
	m_onCampFlag = 0;
}

// Called when the game starts or when spawned
void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugPoint(GetWorld(), GetActorLocation(), 20, FColor::Red, false, 0.1);
}

void ABaseTrigger::InitialTrigger(FLogicVec2D logicLoc, FString spawnGroupName, bool isAutoGenerate)
{
	m_trigType = spawnGroupName;
	m_logicTriggerLoc = logicLoc;
	m_isAutoGenerate = isAutoGenerate;
}

void ABaseTrigger::OverlapTrigger(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (pCharacter && pCharacter->m_campFlag != m_onCampFlag) m_isTriggerOnFlag = true;
		}
	}
}

