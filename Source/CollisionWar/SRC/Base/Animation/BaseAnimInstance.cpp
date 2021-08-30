// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../CollisionWarGameInstance.h"
#include "../../Game/Character/KingCharacter/King.h"
#include "BaseAnimInstance.h"





UBaseAnimInstance::UBaseAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	m_preMotionStateString = "PMS_NULL";
	m_motionStateString = "PMS_NULL";
	//m_idleMotionState = ECharacterIdleMotionType::CHAMT_HoldWeapon;
}

void UBaseAnimInstance::UpdateAnimStateEveryTick()
{
	APawn* pPawn = TryGetPawnOwner();
	if (pPawn)
	{
		FVector characterVelocity = pPawn->GetVelocity();
		FRotator characterRot = pPawn->GetActorRotation();
		m_direction = CalculateDirection(characterVelocity, characterRot);
		if (m_motionStateString != m_preMotionStateString)
		{
			ChangeMotionState();
			m_preMotionStateString = m_motionStateString;
		}
	}
}

void UBaseAnimInstance::NotifyImplementSkill_Implementation(const FString& skillAnimName)
{

}

void UBaseAnimInstance::NotifyOwnCharacterImplementSkill()
{
	m_notifyChaImplementSkillDelegate.Broadcast();
}

void UBaseAnimInstance::NotifyOwnCharacterStopTransientMotion()
{
	m_notifyChaStopTrasientMotionDelegate.Broadcast();
}

void UBaseAnimInstance::NotifySpeedRateChange_Implementation(int32 speedRate)
{

}

void UBaseAnimInstance::TellCharacterDead()
{
	NotifyCharacterDead();
	m_isCharacterDead = true;
}

void UBaseAnimInstance::ChangeSpeedRate(const int32& speedRate)
{
	m_speedRate = speedRate / 100.f;
	UAnimMontage* pCurMontage = GetCurrentActiveMontage();
	if (!pCurMontage) return;
	NotifyCurMontageChangeRate(pCurMontage, m_speedRate);
}

void UBaseAnimInstance::PlayFootStepSound()
{
	APawn* pPawn = TryGetPawnOwner();
	if (!pPawn) return;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pPawn);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (!m_pFootStepSounds.Contains(pCWGI->m_curPlayerSPInfo.curProgress)) return;
	UGameplayStatics::PlaySoundAtLocation(pPawn, m_pFootStepSounds[pCWGI->m_curPlayerSPInfo.curProgress], pPawn->GetActorLocation());
}

void UBaseAnimInstance::PlayAttachMutationPS()
{
	if (!m_pCharacter) return;
	//UGameplayStatics::SpawnEmitterAttached(GetSkelMeshComponent())
	FString skillName = m_pCharacter->m_pBaseEquipment->m_pSkills[m_pCharacter->m_curSkillNb]->m_skillName;
	if (!m_pCharacter->m_attachMutationSkillPSInfo.Contains(skillName)) return;
	int32 mutationType = m_pCharacter->m_pBaseEquipment->m_pSkills[m_pCharacter->m_curSkillNb]->m_mutationType;
	if (!m_pCharacter->m_attachMutationSkillPSInfo[skillName].mutationPSMap.Contains(mutationType)) return;
	UParticleSystem* pPS = m_pCharacter->m_attachMutationSkillPSInfo[skillName].mutationPSMap[mutationType];
	UGameplayStatics::SpawnEmitterAttached(pPS, GetSkelMeshComponent(), m_pCharacter->m_attachMutationPSSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
}

void UBaseAnimInstance::NotifyCurMontageChangeRate_Implementation(UAnimMontage* pCurMontage, float rate)
{
	
}
