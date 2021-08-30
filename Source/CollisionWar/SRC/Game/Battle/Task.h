// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "Task.generated.h"

/**
 * 
 */
class ABaseCharacter;

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	TT_NULL,
	TT_StayAndAim,
	TT_Rush,
	TT_ChaseEnermy,
	TT_MeleeAttack,
	TT_RangeAttack,
	TT_SpecialAttack,
	TT_Capture,
	TT_ImplementSkill,
};

UCLASS()
class COLLISIONWAR_API UTask : public UObject
{
	GENERATED_BODY()

public:
	
	//void reset(FLogicVec2D curPos);

	UPROPERTY()
	ETaskType m_taskType = ETaskType::TT_NULL;

	UPROPERTY()
	ABaseCharacter* m_pTarget = NULL;
	
	UPROPERTY()
	FVector m_destination = FVector::ZeroVector;

	UPROPERTY()
	FString m_evaluateActionName = "NULL";

	UPROPERTY()
	int32 m_evaSkillNb = -1;

	UPROPERTY()
	FVector2D m_evaLogicVelocity = FVector2D(0, 0);

	UPROPERTY()
	int32 m_evaYaw = 0;
};
