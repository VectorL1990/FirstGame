// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Character/BaseCharacter.h"
#include "../../Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "King.generated.h"

/**
 * 
 */
//class ABasePhysActor;
class ARoguelikeBattleGameMode;

USTRUCT(BlueprintType, Blueprintable)
struct FAttachMutationPSInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TMap<int32, UParticleSystem*> mutationPSMap;
};

UCLASS()
class COLLISIONWAR_API AKing : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AKing();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void InitialBaseEquipmentInfo() override;

	//void CalPlayerCharacterVel_Int(bool canMove);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void SetCollectActorDetectComponent(UShapeComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "CollsionWar/Game/Character")
	void OnCollectActorDetectoBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollsionWar/Game/Character")
	void OnCollectActorDetectoEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void AddGeometrySkills();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void SetupItemComponentList(USkeletalMeshComponent* pBaseMesh,const TArray<FCharacterSKComponentInfo>& pSMComponents);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	UShapeComponent* m_pCollectPhysActorDetectComponent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCharacterSKComponentInfo> m_pItemComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TMap<int32, USkeletalMeshComponent*> m_pItemComponentMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TMap<int32, uint8> m_itemComponentType;

	//ECharacterIdleMotionType m_characterIdleMotionState;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	bool m_pressLeftKeyFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	bool m_pressRightKeyFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	bool m_pressUpKeyFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	bool m_pressDownKeyFlag;
	UPROPERTY()
	bool m_pressSpellKeyFlag;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UParticleSystemComponent* m_pPSComponent;

	bool m_shouldCountToReload = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_reloadTime = 10.f;

	float m_curReloadTime = 0.f;

	ARoguelikeBattleGameMode* m_pRGM;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	FName m_attachMutationPSSocketName;
	/************************************************************************/
	/* 操作接口变量
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	TArray<TSubclassOf<class UObject> > m_geometrySkillClasses;

	/************************************************************************/
	/* 操作接口变量
	/************************************************************************/
	UPROPERTY()
	int32 m_collectPhysOperationNb;

	/************************************************************************/
	/* 操作变量
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_minLocX = -18800;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_maxLocX = 18800;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_minLocY = -18800;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_maxLocY = 18800;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	FVector m_controllerHitLoc;

	UPROPERTY()
	TArray<ABasePhysActor*> m_pCanCollectPhysActors;

	UPROPERTY()
	TArray<UBaseSkill*> m_pGeometrySkills;

	TMap<int32, ABasePhysGeo*> m_pRestrictMoveEffect;

	UPROPERTY()
	bool m_hasUpdateMotionState = false;

	/************************************************************************/
	/* 召唤技能接口
	/************************************************************************/

	void ImplementBlockSkill();

	void ImplementDodgeSkill();

	void DyeCSCharacter(ABaseCharacter* pCharacter);

	void FadeCSCharacter();

	void MessAllSkillCard();

	TArray<FString> m_allAvailableSkills;

	UPROPERTY()
	UBaseSkill* m_pBlockSkill;

	UPROPERTY()
	UBaseSkill* m_pDodgeSkill;

	UPROPERTY()
	FSkillIndependentFXInfo m_pCSAttachPS;

	UPROPERTY()
	ABaseCharacter* m_pCSCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_skillAccumulationLimit = 300;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_forceAccumulateStep = 100;

	int32 m_forceAccumulation = 0;
	/************************************************************************/
	/* 技能运算部分
	/************************************************************************/
	virtual void UpdateAllSkills(float dT) override;

	//virtual void UpdateCurSkillState(float dT) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
		virtual void NotifyLaunchSkill() override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
		virtual void NotifyEndSkill() override;

	virtual void ImplementSkill_Int(int32 campFlag) override;

	void AddSkill(FString skillName, int32 insertLoc, bool isFirstAdd, uint8 skillType);

	virtual void DeleteSkill(int32 deleteSkillNb) override;

	UFUNCTION()
	void UpdateFastEquip(FString itemName, int32 slotNb, bool addOrSub);

	virtual void StopContinuousTask() override;

	void DeleteEquipment(int32 equipNb);

	void ConsumeEnergyBall();

	void RecoverEnergyBall(float dT);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_energyBallRecoverInterval = 4.f;

	float m_curEnergyBallRecoverTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxEnergyBallNb = 5;

	int32 m_energyBallList;

	UParticleSystemComponent* m_pBlockSkillPSComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pBlockSkillPS;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, FAttachMutationPSInfo> m_attachMutationSkillPSInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_hurtImmuneTime = 0.3;

	float m_curHurtImmuneTimeCount = 0.f;

	/************************************************************************/
	/* 卡牌合成部分
	/************************************************************************/
	int32 GenCardID();

	virtual bool AddNewItem(FString itemName);

	//virtual void RemoveItem(int32 itemID);

	void UpdateItemMap(FString itemName, int32 nb);

	TMap<int32, FItemCardCondition> m_allNumericCardMap;

	TMap<FString, int32> m_allItemCardMap;
};
