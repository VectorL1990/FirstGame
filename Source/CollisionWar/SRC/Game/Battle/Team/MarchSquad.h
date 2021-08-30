// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Character/BaseCharacter.h"
#include "MarchSquad.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UMarchSquad : public UObject
{
	GENERATED_BODY()
public:
	UMarchSquad(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<ABaseCharacter*> m_pMembers;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	ABaseCharacter* m_pTarget;

	UPROPERTY()
	ECharacterAtkRange m_atkRange;
};
