// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CollisionWarBpFunctionLibrary.h"
#include "../Game/Character/BaseCharacter.h"
#include "../Game/Battle/Physics/Effect.h"
#include "../Game/Battle/Physics/BasePhysGeo.h"
#include "EffectFunLib.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UEffectFunLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void AddStateToCharacter(ABaseCharacter* pCharacter, FString stateName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void PlayHitParticleSystem(UEffect* pEffect, ABaseCharacter* pCharacter);

	//static void PlaySuperposeParticleSystem(ABasePhysGeo* pGeo, FString superposeAttributeName);

	static void UpdateScores(int32 hurtVal, ABaseCharacter* pHurtCharacter, uint8 hurtType);

	static void DemonstrateActivateEffect(UEffect* pEffect, ABaseCharacter* pTarget);

	static void DemonstrateHurtNb(int32 hurtNb, ABaseCharacter* pTarget);

	static bool OneTimeJudgeListEffect(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void SpawnAppendGeoByName(ABasePhysGeo* pParentGeo, FString geoName, FVector logicSpawnLoc);

	static void SpawnGeoByName(ABaseCharacter* pHost, FString geoName, FVector spawnLoc, FRotator spawnRot);
	/************************************************************************/
	/* �˺���Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static bool Judge(int32& outColor, int32& outNb, UEffect* pJudgeEffect, ABaseCharacter* pTargetCharacter, ABaseCharacter* pSourceCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Hurt(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtNoHost(UEffect* pEffect, ABaseCharacter* pCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtAmplifiedByJudge(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Vampire(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void VampireRevert(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtAmplifiedByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByLeftCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByAttackCardNb(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Oppress(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Universe(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Eclosion(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void Eclosion_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtShareByCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByCompanionHpLess(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByAverageDefPercent(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtByCompareDfc(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtByCompareAttack(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByAverageAtkPercent(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtOrRecoverByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByDifCampFlag(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtByCompareAtkAndNoneAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtByCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtByCardAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtAccordLiveNb(UEffect* pEffect, ABaseCharacter* pCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtByCompareCardAndCharacterNb(UEffect* pEffect, ABaseCharacter* pCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtIfEvenCharacters(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ExtraHurtByCompareAtk(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ExtraHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ExtraHurtByCompareCardAndDifTagNb(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtByCoverCharacterGrade(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtByCoverCharacterAverageAtk(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtByCoverActorTag(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtBySpecificGradeNumber(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void HurtAmplifiedByDifSameFlag(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void ContinuousHurt(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtAmplifiedIfFoundationType(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	static void ExtractCompanyLifeToAttack(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ExtractCompanyLifeToAttack_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtByDefence(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ݹ����ĵ�˫�����ж��ǻ��⻹�Ǽӱ������˺�����
	*/
	static int32 AmplifyOrExemptHurtByOddOrEven(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	static void AmplifyOrExemptHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtByLeftHp(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2);

	/** ���ݹ����������Ŵ�ħ�����������˺�����
	*/
	static int32 HurtAmplifyByAttackTimes(UEffect* pEffect, UEffect* pHurtEffect, int32 hurtVal, ABaseCharacter* pTarget);

	static void HurtQuattuorByJudge(UEffect* pEffect, ABaseCharacter* pCharacter, int32 damageCoeK1, int32 damageCoeK2);

	/** ���˺�������˺�
	*/
	static void Poison(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �����ж�����Ͻ����˺�
	*/
	static void HurtByJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void HurtByLostHpAndJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ֱ�Ӵ����˺�
	*/
	static void HurtPiercing(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ͨ��ɾ���ж�������������˺�
	*/
	static void HurtByDeleteJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ָ���ж���
	*/
	static void AddSpecificJudgeCard(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �������ӵ�еĵ��߿��������˺�
	*/
	static void HurtAndRecoverByEquipmentName(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �������ӵ�еĵ��߿��������˺�
	*/
	static void HurtByEffectDelete(UEffect* pEffect, ABaseCharacter* pCharacter);
	/************************************************************************/
	/* ��Ѫ��Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Recover(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void RecoverByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void RecoverByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void RecoverByJudgeSource(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void RecoverByJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter);

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void DefSubOrDestroyCardByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);*/

	static void RecoverIfTargetAtkCardMoreThanNoneAtkCard(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void RecoverOrContinuousHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ͨ���ж�����Ѫ
	*/
	static void JudgeToRecover(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ͨ�����Я���ĵ����ƻָ�
	*/
	static void RecoverByItemCard(UEffect* pEffect, ABaseCharacter* pCharacter);

	/************************************************************************/
	/* ����������Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ClearResistByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ClearAllAppendEffects(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void ClearAllAppendEffectsByJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 Invincible(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 HurtToRecover(UEffect* pEffect, ABaseCharacter* pHurtTarget, int32 hurtVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 ResistHurt(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void CopyJudgeActivateTargetEffect(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void CopyPlayerAppendEffect(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void FireWoodSwitch(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 RecoverToHurt(UEffect* pEffect, ABaseCharacter* pCharacter, int32 recoverVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void IntoTheWind(UEffect* pEffect, UEffect* pHurtEffect, const int32& damageCoeK1, const int32& damageCoeK2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void RestrictJudgeColor(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void RestrictJudgeColor_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void RestrictJudgeNumber(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void RestrictJudgeNumber_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ֱ�ӽ����ʽ�Ϊ0�����б𼤷�
	*/
	static void FreezeByJudgeActivate(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void FreezeByJudgeActivate_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �ɽ�ɫ״̬�����ֶ�������������
	*/
	static void AttackDecreaseByAttribute(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttackDecreaseByAttribute_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ������ҷǹ���������������������
	*/
	static void AtkSubByNoneAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AtkSubByNoneAtkCardNb_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �ɽ�ɫ״̬�����ֶ�������������
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void DefenceDecreaseByAttribute(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void DefenceDecreaseByAttribute_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ݽ�ɫ����������������
	*/
	static void AtkSubByDef(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AtkSubByDef_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void DefSubByCardAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ݹ�����������������
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void DefSubByAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefSubByAtkCardNb_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �����»����ߵ�����ֵ�ٷֱ���������ɫ������
	*/
	static void DefenceDecreaseByHpPercent(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefenceDecreaseByHpPercent_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ݸ�������˵�������������ɫ������
	*/
	static void DefSubByCharacterNb(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefSubByCharacterNb_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefenceDecreaseByCD(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefenceDecreaseByCD_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void IncreaseCDByCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void IncreaseCDByCharacterHp(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void IncreaseCDByCoverCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void SubCD(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void SwitchHpPercentByOrder(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void SwitchHpPercentByOrder_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	//static void LimitAllImplementedCD(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ����������
	*/
	static void AttackDrop(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttackDrop_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �������Ŵ�
	*/
	static void DefenceIncrease(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefAdd_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ��������С
	*/
	static void DefSub(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DefSub_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �������Ŵ�
	*/
	static void AttackIncrease(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AtkAdd_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ��������С
	*/
	static void AttackDecrease(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttackDecrease_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttributeWeak(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttributeWeakByHostHp(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AttributeWeakByTargetHp(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ResourcesSub(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void FourColorWish(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void Assimilation(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void Assimilation_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	static int32 InvincibleIfNoCards(UEffect* pEffect, bool hurtEffectPhysOrMagFlag, ABaseCharacter* pCharacter, int32 hurtVal);

	/** ���ݸ��ǵļ���������Ƿ��޵�
	*/
	static int32 InvincibleIfCoverActorTag(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	static int32 Undead(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	/** ���������ߵ�״̬���Ƹ�������
	*/
	static void AbsortState(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void AbsortStatePassive(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	/** ���Լ���״̬������������
	*/
	static void BroadcastStates(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void CopyDefence(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void CopyDefence_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ������Ⱦ�����ջ���
	*/
	static void DiseaseInfection(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** �����ף�������
	*/
	static void IncreaseATKAndDecreaseDFC(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void IncreaseATKAndDecreaseDFC_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���Ӷ�
	*/
	static void IncreasePoison(UEffect* pEffect, ABaseCharacter* pCharacter);


	/** ͨ���ж����ӻ���
	*/
	static void JudgeToIncreaseDefence(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ����������
	*/
	static void DoubleAttack(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void DoubleAttack_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/************************************************************************/
	/* ������Ч��
	/************************************************************************/

	static void ContinuousHurtIfUnderDark(UEffect* pEffect, ABaseCharacter* pCharacter);

	
	/************************************************************************/
	/* ������Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void Slow(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void Slow_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ContinuousSlow(UEffect* pEffect, ABaseCharacter* pCharacter);

	static void ContinuousSlow_End(UEffect* pEffect, ABaseCharacter* pCharacter);

	/************************************************************************/
	/* ������Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void PureJudge(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void SpawnAppendEffect(UEffect* pEffect, ABaseCharacter* pCharacter);

	/** ���ڶ������ƴ�����Ч���Ǳ��������ģ������Ƶ�������Ϊ��ң����Ե�����ʱ��Ҫ�˺��������ӵ���Ӧ�ĵ���
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void SpawnAppendEffectBackward(UEffect* pEffect, ABaseCharacter* pHitCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void HurtCharacter(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget);

	static void HurtCharacterPiercing(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget);

	static void RecoverCharacter(int32 recoverVal, UEffect* pRecoverEffect, ABaseCharacter* pRecoverTarget);
	/************************************************************************/
	/* ����ʱ����Ч��
	/************************************************************************/
	static void DeadSpawnGeo(UEffect* pEffect, ABaseCharacter* pDeadCharacter);


	/************************************************************************/
	/* �˺�����Ч��
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 HurtTransfer(UEffect* pEffect, ABaseCharacter* pHurtTarget, int32 hurtVal);

	static void HostDieTogether(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 SortByEvenOdd(UEffect* pEffect, int32 hurtVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 ShareHurt(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static int32 HurtAmplified(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal);

	/** ��Լ������ԷŴ��˺���
	* ��FireWeak�����������ܹ���SuperposeFireAtkʱ�Ὣ�˺����Ŵ�
	*/
	static void SuperposeAttribute(UEffect* pEffect, ABasePhysGeo* pIntroGeo, int32 effectParamNb);

	static int32 HurtAmplifiedByAttribute(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal);

	static void HurtReflect(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHost, int32 hurtVal);

	static void AbsorbSameTagHurtToPlayer(UEffect* pEffect, ABaseCharacter* pCharacter);

	static int32 ExemptHurtIfEffectAppendString(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal);
	/************************************************************************/
	/* �ж�Ч����
	/************************************************************************/

	static void ChangeJudgeFromRedToBlack(UEffect* pEffect, int32& judgeColor, ABaseCharacter* pCharacter);

	/************************************************************************/
	/* ��Ч���ɺ���
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static void PlayHitBeamParticle(AActor* pSource, AActor* pTarget, UEffect* pEffect);

};
