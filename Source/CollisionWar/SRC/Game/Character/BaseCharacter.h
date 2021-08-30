// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "AI/Navigation/NavigationPath.h"
#include "../Battle/Task.h"
#include "../Skills/BaseSkill.h"
#include "../../Base/Animation/BaseAnimInstance.h"
#include "../Battle/Attachment/BaseSkeletalMeshComponent.h"
#include "../Battle/Attachment/CharacterEquipInfo.h"
#include "../Battle/Physics/BasePhysGeo.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "../Battle/Physics/Effect.h"
#include "../../Base/Widget/TemplateCharacterInfo.h"
#include "BaseCharacter.generated.h"

using namespace std;

class APhysPolygon;
class APhysLine;
class APhysPoint;
class ABasePhysActor;


USTRUCT(BlueprintType, Blueprintable)
struct FAttributeInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float time;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 hostAttribute;

	/** ���Է�ӦЧ��������Ҫ�����ڽ�ɫ�������ԣ��������л����ԣ�������ˮ����ʱ���ħ���ֻ���ĳЩˮϵ������ӹ������ʱ������˺�
	* key��������������Ӧ�����ԣ�value����Ӧ�����
	* 0 - ��ħ
	* 1 - ����
	* 2 - ֱ���˺�����������
	* 3 - �����˺�
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<uint8, uint8> reactionType;

	/** ���ڱ�ʶ���Է�Ӧ��Ч����ֵ��������ɳ����˺���ÿ����ɶ����˺���������������������
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<uint8, int32> reactionValues;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDefaultAttributeRestrainInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 advantageAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 weakAttribute;

	/** ����Ԫ���Ƿ���Թ���
	* 0 - ������������ˮ��𡢻��ڱ�������ˮ
	* 1 - ��������ˮ������Թ���
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 continuousType;

	/** ���Ĭ�ϵ�Ԫ���໥�������ͣ�������Ԫ���ǽ�����ʱ����ˮ�����
	* 0 - ʹ��ɫ�����������˰�
	* 1 - �ӳɣ�ʹ��ɫ��ǿ����ľ��������ˮ
	* 2 - �����˺��������ľ������ˮ��ˮ����
	* 3 - ����˺��Ŵ󣬵��Ǽ���������ʱ��ֱ���˺�
	* 4 - ����
	* 5 - ��ħ
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FEffectParams effectParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 effectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float time;
};

USTRUCT()
struct FActiveAttributeReactionInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	uint8 reactionAttribute1;

	UPROPERTY()
	uint8 reactionAttribute2;

	/** ���Ĭ�ϵ�Ԫ���໥��������
	* 0 - ���ƣ�ʹ�ý�ɫ�����������˰�
	* 1 - �ӳɣ�ʹ��ɫ��ǿ����ľ��������ˮ
	* 2 - �����˺��������ľ������ˮ��ˮ����
	* 3 - ֱ���˺�
	* 4 - �����˺�
	* 5 - ��ħ
	*/
	UPROPERTY()
		FEffectParams reactionEffectParam;
	
	UPROPERTY()
		TArray<int32> reactionValues;

	UPROPERTY()
	uint8 exertType;

	UPROPERTY()
		float time;

	FActiveAttributeReactionInfo()
	{
		exertType = 0;
		time = 0;
	}

	FActiveAttributeReactionInfo(FEffectParams effectParamList, uint8 type, float T)
	{
		reactionEffectParam = effectParamList;
		exertType = type;
		time = T;
	}
};

USTRUCT()
struct FTimeDilationInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	float duration;

	UPROPERTY()
	int32 timeDilationPercent;

	/** ����ʲô���͵�ʱ���ӳ�
	* 0 - ���������ӳپ��ڵ�����
	* 1 - �����岻�ڻ�û����Ҳ���ӳ�
	*/
	UPROPERTY()
	uint8 type;

	FTimeDilationInfo()
	{
		type = 0;
		duration = 0.f;
		timeDilationPercent = 100;
	}

	FTimeDilationInfo(float time, int32 percent, uint8 dilationType)
	{
		duration = time;
		timeDilationPercent = percent;
		type = dilationType;
	}
};

USTRUCT()
struct FEffectList
{
	GENERATED_USTRUCT_BODY()
public:

	TArray<UEffect*> Effects;

};

UCLASS()
class COLLISIONWAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetTorsoMeshComponent(USkeletalMeshComponent* pBaseMesh, USkeletalMeshComponent* pHeadMesh, USkeletalMeshComponent* pHeadMesh1, USkeletalMeshComponent* pHeadMesh2, 
		USkeletalMeshComponent* pHandMesh, USkeletalMeshComponent* pHandMesh2, USkeletalMeshComponent* pHandMesh3, USkeletalMeshComponent* pHandMesh4,
		USkeletalMeshComponent* pHandMesh5, USkeletalMeshComponent* pHandMesh6, USkeletalMeshComponent* pHandMesh7, USkeletalMeshComponent* pHandMesh8,
		USkeletalMeshComponent* pTorsoMesh, USkeletalMeshComponent* pBackMesh, USkeletalMeshComponent* pHipMesh, USkeletalMeshComponent* pLegMesh,
		USkeletalMeshComponent* pLegMesh2, USkeletalMeshComponent* pLegMesh3, USkeletalMeshComponent* pLegMesh4, USkeletalMeshComponent* pAttachMesh);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetSpawnPointComponent(USphereComponent* pComponent);
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnCapsuleComponentOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnCapsuleComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	void AddOrRemoveAttachPS(uint8 attribute, bool addOrSub);

	/************************************************************************/
	/* ״̬����
	/************************************************************************/
	FString m_tempName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_grade = 1;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_entityID = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_originHp;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_Hp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
		int32 m_ATK;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
		int32 m_magATK;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_DFC;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_maxDFC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_magDFC;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_ATKAddition;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_maxATKAddition;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_DFCPercent = 100;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_magDFCPercent = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_MaxSPD;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_acc;

	UPROPERTY()
	int32 m_expandLogicTickTimeDelta = 40;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_campFlag;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_originCampFlag;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_level;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	bool m_isInitialDoneFlag;

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_logicReachDesOffset = 50;*/

	/** ��ǽ�ɫ������
	* 0����˽�ɫ����ͨ���˽�ɫ
	* 1������ҽ�ɫ
	* 2����������ɫ
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	uint8 m_characterType;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	TSubclassOf<class UObject> m_baseEquipInfoClass;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	UCharacterEquipInfo* m_pBaseEquipment;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	TArray<UCharacterEquipInfo*> m_pEquipmentInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	TMap<int32, UCharacterEquipInfo*> m_fastEquipInfoMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	UParticleSystemComponent* m_pParticleSystemComponent = NULL;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	TArray<FString> m_beCarriedSkillNames;

	UPROPERTY()
	UBaseAnimInstance* m_pBaseAnimInstance;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TArray<uint8> m_intrinsicAttibutes;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TArray<FDefaultAttributeRestrainInfo> m_intrinsicAttributeReactionInfos;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TArray<FName> m_amplifiedHurtTag;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
		TArray<FName> m_resistHurtTag;

	UPROPERTY()
	TMap<uint8, float> m_tempAttributes;

	UPROPERTY()
	TArray<FActiveAttributeReactionInfo> m_curTempActiveAttributeInfo;

	UPROPERTY()
	TMap<uint8, FEffectList> m_curIntrinsicActiveAttributeInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	FString m_characterClassName;

	UPROPERTY()
	int32 m_defRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_characterRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	int32 m_characterHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_relativeHeight;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_defaultHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_speedRatePercent = 100;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	USphereComponent* m_pSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	float m_defaultAtkRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	ECharacterThinkMode m_thinkMode;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	TArray<UEffect*> m_pEffects;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	TArray<FString> m_stateNames;

	/** ��ɫ����
	* 0 - ����
	* 1 - ħ��
	* 2 - ����
	* 3 - ����
	* 4 - ������
	* 5 - ���
	* 6 - ����
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	uint8 m_characterRace = 0;

	int32 m_surviveTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_enDescription;

	TMap<FString, FTimeDilationInfo> m_timeDilationParams;

	TMap<uint8, UParticleSystemComponent*> m_attachAttributePS;
	/************************************************************************/
	/* �����ӿڱ���
	/************************************************************************/
	UPROPERTY()
	FVector2D m_logicVelOperation;

	UPROPERTY()
	FVector2D m_logicForwardOperation;

	UPROPERTY()
	int32 m_skillOperationNb;

	UPROPERTY()
	FVector m_targetLoc;

	UPROPERTY()
	int32 m_equipOperationNb = -1;

	/************************************************************************/
	/* ʵ�ʲ�������
	/************************************************************************/
	UPROPERTY()
	FVector2D m_curLogicVelocity;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	int32 m_curSkillNb = -1;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Character")
	int32 m_curEquipNb = -1;

	int32 m_curBuildPhysID = -1;

	int32 m_curSpellSkillNb = 0;

	/** ���ܷ�������
	* 0 = ��ͨ����
	* 1 = �ٻ�����
	* 2 = ���켼��
	*/
	uint8 m_implementSkillType = 0;

	UPROPERTY()
	bool m_doingContinuousSkill = false;

	UPROPERTY()
	FString m_actionName;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pControlPhysGeos;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pNewSpawnPhysGeos;
	/************************************************************************/
	/* AI�������
	/************************************************************************/
	UPROPERTY()
	bool m_hasUpdateAI = false;

	UPROPERTY()
	UTask* m_pNormalShortTask;

	UPROPERTY()
	UTask* m_pNormalLongTask;

	UPROPERTY()
	TArray<ABaseCharacter*> m_pOppCharacters;

	UPROPERTY()
	TArray<ABaseCharacter*> m_pMyCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	ECharacterAtkRange m_characterAtkRange;

	float m_patrolRange = 0.f;

	FVector m_spawnLoc;
	/************************************************************************/
	/* ��ͼĬ�ϱ���
	/************************************************************************/

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Character")
	TMap<FString, FSkillIndependentFXInfo> m_skillParticleMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	float m_deadTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Character")
	TSubclassOf<class UObject> m_fixDeadSkillGeoClass;

	UPROPERTY()
	float m_curDeadCount = 0;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void ReadSkillIndependentFXInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void SetSkillDetectComponent(uint8 skillNb, UShapeComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void OnDetectComponentBeginOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void OnDetectComponentEndOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void AnimNotifyImplementSkill();

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void AnimNotifyStopTransientMotion();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void NotifyAnimStopMotion();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void NotifyAnimEffectChange(UEffect* pEffect, TArray<float> values);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void NotifyBeingHurt();

	void NotifyAnimCharacterDead();

	void SetSkillIndependentFXTemplate(const FString& skillName);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void EquipInfoNotifySpawnParticleEmitter(const FName& reactionTag);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void ImplementSkill_Int(int32 campFlag);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void ImplementSkillAttachEffect(FEffectParams effectParam, ABasePhysGeo* pGeo);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void InitialCharacterDone();

	//void Accelerate_Int();

	/*UFUNCTION(BlueprintCallable, Category = "CollsionWar/Game/Character")
	void Brake_Int();*/

	bool HasReachCurDes_Int(FVector des);

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void MoveToTarget_Int(bool isPlayer, bool canMove);*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void InitialCharacterAnim();

	void KillCharacter();

	void RecoverPhysics();

	void EvaluateConditionAround();

	virtual void EvaluateLongTaskUnderRandomAttackState();

	void EvaluateLongTaskUnderStrongholdDestroyerState();

	void EvaluateLongTaskUnderPlayerHunterState();

	void EvaluateLongTaskPatrolling();

	virtual void EvaluateShortTask();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void InitialBaseEquipmentInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void StopContinuousTask();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void UpdateAllSkills(float dT);

	void UpdateAllTimeDilationEffects(float dT);

	//virtual void UpdateCurSkillState(float dT);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void NotifyLaunchSkill();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	virtual void NotifyEndSkill();

	UFUNCTION()
	bool TellWhetherCharacterContainEffect(FString effectName);

	/************************************************************************/
	/* ��ͼЭ������
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	bool IsContainEffect(FString effectName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Character")
	void EffectOnFx(bool goodOrBad);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Character")
	void NotifyAddCharacterState(const FString& stateName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Character")
	void NotifyCSDyeing();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Character")
	void NotifyCSFade();

	/************************************************************************/
	/* UMG����
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Character")
	void NotifySetCharacterInfoWidget();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void SetCharacterInfoWidget(UTemplateCharacterInfo* pInfoWidget);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Character")
	UTemplateCharacterInfo* m_pCharacterInfoWidget;

	/************************************************************************/
	/* ����ģ��
	/************************************************************************/

	virtual void DeleteSkill(int32 deleteSkillNb);

	void NotifyRemoveCharacterState(FString stateName);

	void UpdateJudgeCardList(int32 judgeCard);

	void UpdateAllAttributes(float dT);

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FJudgeInfo m_judgeInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxJudgeCardNb = 5;

	TArray<int32> m_allJudgeCardInfos;

	/************************************************************************/
	/* ����ģ��
	/************************************************************************/
	UFUNCTION()
	void ChangeEquipment(int32 equipNb);

	virtual bool AddNewItem(FString itemName);

	virtual void RemoveItem(int32 itemID);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyChangeEquipmentMesh(USkeletalMesh* pSkeletonMesh);

	
	/**
	*��Ч������ģ��
	*
	*
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Attachment")
	void AttachAttachmentTest(TSubclassOf<UBaseSkeletalMeshComponent> attachmentClass);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Attachment")
	void CursorHovered();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Attachment")
	void HoveredCancel();

	UPROPERTY()
	TSubclassOf<UBaseSkeletalMeshComponent> m_BPAttachmentClass;
	
	UBaseSkeletalMeshComponent* m_pHandAttachment;
	/************************************************************************/
	/* �˺���¼����
	/************************************************************************/
	int32 m_beAttackedNb = 0;
};
