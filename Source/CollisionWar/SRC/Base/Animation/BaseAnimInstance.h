// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNotifyChaImplementSkill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNotifyChaStopTransientMotion);

class AKing;

UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UBaseAnimInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Base/Animation")
	void UpdateAnimStateEveryTick();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Base/Animation")
	void NotifyImplementSkill(const FString& skillAnimName);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void NotifyStopAnim();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void NotifyEffectChange(const FString& effectName, const TArray<float>& values);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void NotifyCharacterDead();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Base/Animation")
	void NotifyOwnCharacterImplementSkill();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Base/Animation")
	void NotifyOwnCharacterStopTransientMotion();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Base/Animation")
	void NotifySpeedRateChange(int32 speedRate);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void ChangeMotionState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToTransientPunchState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToContinuousPunchState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToContinuousBlockState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToContinuousSpellState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToNullMotionState();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToSingleHandThrow();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToSingleHandWield();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToDoubleHandWield();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void SwitchToDoubleHandThrow();

	void TellCharacterDead();

	void ChangeSpeedRate(const int32& speedRate);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Base/Animation")
	void NotifyCurMontageChangeRate(UAnimMontage* pCurMontage, float rate);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PlayFootStepSound();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PlayAttachMutationPS();

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/Animation")
		UParticleSystem* m_pParticleSystem;*/

	AKing* m_pCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base/Animation")
	uint8 m_idleMotionState;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base/Animation")
	float m_direction;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base/Animation")
	float m_speed;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base/Animation")
	float m_speedRate = 1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base/Animation")
	bool m_isCharacterDead = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "CollisionWar/Base/Animation")
	FString m_motionStateString;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "CollisionWar/Base/Animation")
	FString m_preMotionStateString;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "CollisionWar/Base/Animation")
	TMap<int32, USoundBase*> m_pFootStepSounds;

	FNotifyChaImplementSkill m_notifyChaImplementSkillDelegate;
	FNotifyChaStopTransientMotion m_notifyChaStopTrasientMotionDelegate;
};
