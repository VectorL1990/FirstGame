// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "../../Game/Skills/BaseSkill.h"
#include "TemplateBattleSkillIcon.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateBattleSkillIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialSkillIcon(const FString& skillName, UImage* pMask);

	void UpdateSkillState();

	UPROPERTY()
	FString m_skillName;
	
	UPROPERTY()
	UBaseSkill* m_pRelateSkill;

	UPROPERTY()
	UImage* m_pMask;
};
