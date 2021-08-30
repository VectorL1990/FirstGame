// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Skills/BaseSkill.h"
#include "../../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "CharacterEquipInfo.generated.h"

/**
 * 
 */

UCLASS(BlueprintType,Blueprintable)
class COLLISIONWAR_API UCharacterEquipInfo : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void ParticleEmit(const FName& reactionTag);

	void CorrectEquipment(const FEquipmentInfo& equipInfo);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void InitialEquipInfo(bool isPlayerCharacter = false);

	FEquipmentInfo ConstructEquipInfo();

	/************************************************************************/
	/* 蓝图初始化变量
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FString m_equipmentName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<FName> m_actorTags;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	ECharacterIdleMotionType m_holdMotionType;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	USkeletalMesh* m_pSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	UParticleSystem* m_pParticleTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	FVector m_equipPSRelativeLoc = FVector(0,0,100);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<TSubclassOf<class UObject> > m_skillClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 m_maxCardNb = 6;
	/************************************************************************/
	/* 计算变量
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<UBaseSkill*> m_pSkills;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<UBaseSkill*> m_pSpellSkill;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 m_equipmentNb;

	TArray<FString> m_waitDiscardSkillNameList;
	/************************************************************************/
	/* 技能相关
	/************************************************************************/
	void AddSkill(FString skillName, int32 insertLoc, bool needToAddExtraCD);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, TSubclassOf<class UBaseSkill> > m_skillClassMap;
};
