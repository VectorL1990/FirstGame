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
	/** 触发道具函数的点有几个
	* 1. 生成卡牌时即触发
	* 2. 点击合成时触发
	* 2. 点击使用时触发
	* 3. 删除时触发
	*/

	//static void RecoverHp(APlayCard* pPlayCard, int32 recoverHp);

	//维修设备作用函数，提高所有道具的耐久度
	//static void IncreaseAllDeviceDurability(APlayCard* pPlayCard);

	//生成随机卡牌，如梦枕、探测器、观星仪等
	//static void GenerateCards(APlayCard* pPlayCard);

	//没丢弃一张卡牌，换得对应的金钱
	//static void Recycle(APlayCard* pPropCard, APlayCard* pDumpCard);

	//static void ShrinkThinkTime_End(ASingleProgressGameMode* pSPGM, FCardFunctionInfo info);

	//缩短工具合成时间
	//static void ShrinkForgeTime(FCardFunctionInfo info, AActionCard* pActionCard);

	//缩短所有合成时间
	//static void ShrinkAllTime(FCardFunctionInfo info, AActionCard* pActionCard);
	
	//复制某张丢弃的卡牌
	//static void RecoverDiscardByMoney(APlayCard* pPlayCard);
	/************************************************************************/
	/* 记忆模块技能
	/************************************************************************/
	
	//重新翻一次牌


	//重新翻开n分之一的牌
	//static void RevealNxNCards(APlayCard* pPlayCard);

	/************************************************************************/
	/* 推理模块
	/************************************************************************/

	//随机再翻开一张牌
	//static void CompareCoverCardToSpecificNb(APlayCard* pPlayCard);
	/************************************************************************/
	/* 整体指标模块
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
