// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "DemoCharacter.h"


// Sets default values
ADemoCharacter::ADemoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADemoCharacter::SetupItemComponentList(USkeletalMeshComponent* pBaseMesh, const TArray<FCharacterSKComponentInfo>& pSMComponents)
{
	if (!pBaseMesh) return;
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!m_itemComponentType.Contains(iter->Key)) continue;
		if (m_itemComponentType[iter->Key] == 0)
			iter->Value->SetMasterPoseComponent(pBaseMesh);
		else if (m_itemComponentType[iter->Key] == 1)
			iter->Value->AttachTo(pBaseMesh, FName(TEXT("NeckSocket")));
	}

	/*for (int32 i = 0; i < pSMComponents.Num(); i++)
	{
		if (!pSMComponents[i].pComponent) continue;
		m_pItemComponents.Add(pSMComponents[i]);
		if (pSMComponents[i].componentType == 0)
			m_pItemComponents.Last().pComponent->SetMasterPoseComponent(pBaseMesh);
		else if (pSMComponents[i].componentType == 1)
			m_pItemComponents.Last().pComponent->AttachTo(pBaseMesh, FName(TEXT("NeckSocket")));
		m_pItemComponents.Last().pComponent->SetSkeletalMesh(NULL);
	}*/
}

void ADemoCharacter::TriggerDemoAnim(FString motionName)
{
	m_pAnimInstance->NotifyImplementSkill(motionName);
}

