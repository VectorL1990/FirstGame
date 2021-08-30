// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "../Task.h"
#include "../../Skills/BaseSkill.h"
#include "../Attachment/CharacterEquipInfo.h"
#include "../Physics/BasePhysGeo.h"
#include "../../Character/BaseCharacter.h"
#include "HolySpirit.generated.h"

UCLASS()
class COLLISIONWAR_API AHolySpirit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHolySpirit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		void SetSkillDetectComponent(uint8 skillNb, UShapeComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		void OnDetectComponentBeginOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		void OnDetectComponentEndOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		void ImplementSkill_Int(int32 campFlag);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void NotifyPlayPreParticleEffect(const FString& skillName);

	void EvaluateShortTask();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
		void InitialBaseEquipmentInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
		void UpdateAllSkills();

	void UpdateCurSkillState();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void StopContinuousTask();

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_entityID = 0;

	UPROPERTY()
	int32 m_originHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_Hp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_DFC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_magDFC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_ATKPercent = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_DFCPercent = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_magDFCPercent = 100;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_campFlag;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
		bool m_isInitialDoneFlag;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
		UCharacterEquipInfo* m_pBaseEquipment;

	UPROPERTY()
		FString m_attribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
		FString m_className;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
		FLogicVec2D m_logicPos2D;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
		FLogicVec2D m_curLogicForwardDir;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
		int32 m_defaultHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
		ECharacterThinkMode m_thinkMode;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
		int32 m_defRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
		TSubclassOf<class UObject> m_baseEquipInfoClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
		int32 m_speedRatePercent = 100;
	/************************************************************************/
	/* 操作接口变量
	/************************************************************************/

	UPROPERTY()
	int32 m_skillOperationNb;

	/************************************************************************/
	/* 实际操作变量
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_curSkillNb = -1;

	UPROPERTY()
		FString m_actionName;

	UPROPERTY()
		TArray<ABasePhysGeo*> m_pControlPhysGeos;

	UPROPERTY()
		TArray<ABasePhysGeo*> m_pNewSpawnPhysGeos;
	/************************************************************************/
	/* AI计算变量
	/************************************************************************/
	UPROPERTY()
		bool m_hasUpdateAI = false;

	UPROPERTY()
		UTask* m_pNormalShortTask;

	UPROPERTY()
		TArray<ABaseCharacter*> m_pOppCharacters;

	UPROPERTY()
		TArray<ABaseCharacter*> m_pMyCharacters;
	/************************************************************************/
	/* 蓝图默认变量
	/************************************************************************/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
		float m_deadTime = 0;

	UPROPERTY()
		float m_curDeadCount = 0;
};
