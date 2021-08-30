// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Game/SingleProgress/SingleProgressGameMode.h"
#include "SPEventFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API USPEventFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** �������ߺ����ĵ��м���
	* 1. ���ɿ���ʱ������
	* 2. ����ϳ�ʱ����
	* 2. ���ʹ��ʱ����
	* 3. ɾ��ʱ����
	*/

	//static void RecoverHp(APlayCard* pPlayCard, int32 recoverHp);

	//ά���豸���ú�����������е��ߵ��;ö�
	//static void IncreaseAllDeviceDurability(APlayCard* pPlayCard);

	//����������ƣ�������̽�����������ǵ�
	//static void GenerateCards(APlayCard* pPlayCard);

	//û����һ�ſ��ƣ����ö�Ӧ�Ľ�Ǯ
	//static void Recycle(APlayCard* pPropCard, APlayCard* pDumpCard);

	//static void ShrinkThinkTime_End(ASingleProgressGameMode* pSPGM, FCardFunctionInfo info);

	//���̹��ߺϳ�ʱ��
	//static void ShrinkForgeTime(FCardFunctionInfo info, AActionCard* pActionCard);

	//�������кϳ�ʱ��
	//static void ShrinkAllTime(FCardFunctionInfo info, AActionCard* pActionCard);
	
	//����ĳ�Ŷ����Ŀ���
	//static void RecoverDiscardByMoney(APlayCard* pPlayCard);
	/************************************************************************/
	/* ����ģ�鼼��
	/************************************************************************/
	
	//���·�һ����


	//���·���n��֮һ����
	//static void RevealNxNCards(APlayCard* pPlayCard);

	/************************************************************************/
	/* ����ģ��
	/************************************************************************/

	//����ٷ���һ����
	//static void CompareCoverCardToSpecificNb(APlayCard* pPlayCard);
	/************************************************************************/
	/* ����ָ��ģ��
	/************************************************************************/
	static void IncreaseIndexSlope(const FOverallIndexExtraFunInfo& funInfo, uint8 index, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexSlopeByCardNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexSlopeByColorNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexSlopeByNumberNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexByDecreaseIndex(const FOverallIndexExtraFunInfo& funInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexSlopeByActionCardNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static int32 IncreaseEnergySlope(const FOverallIndexExtraFunInfo& funInfo,int32 energyReduction);

	static void IncreaseIndexSlopeIfIndexExceed(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexByDicard(const FOverallIndexExtraFunInfo& funInfo, ASingleProgressGameMode* pSPGM);

	static void IncreaseIndexSlopeByCardName(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM);

};
