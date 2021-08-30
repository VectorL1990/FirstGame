// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Base/SingleProgress/SingleProgressPlayerController.h"
#include "SPEventFunctionLib.h"




/*
void USPEventFunctionLib::RecoverHp(APlayCard* pPlayCard, int32 recoverHp)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pPlayCard);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	pSPGM->m_curLife += recoverHp;
	if (pSPGM->m_curLife >= pSPGM->m_originLife) pSPGM->m_curLife = pSPGM->m_originLife;
}*/

/*
void USPEventFunctionLib::IncreaseAllDeviceDurability(APlayCard* pPlayCard)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pPlayCard);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	for (int32 i=0; i<pSPGM->m_pPlayCards.Num(); i++)
	{
		if (!pSPGM->m_pPlayCards[i] || pSPGM->m_pPlayCards[i] == pPlayCard || !pSPGM->m_pPlayCards[i]->m_tags.Contains("Device") ||
			pSPGM->m_pPlayCards[i]->m_durability == -1) continue;
		pSPGM->m_pPlayCards[i]->m_durability += pPlayCard->m_functionValues[0];
	}
}*/
/*

void USPEventFunctionLib::GenerateCards(APlayCard* pPlayCard)
{
	int32 cardFunctionIndex = pPlayCard->m_tags.Find(pPlayCard->m_cardFunction);
	if (cardFunctionIndex == -1) return;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pPlayCard);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	for (int32 i=0; i<pPlayCard->m_functionValues[0]; i++)
	{
		int32 randNb = FMath::RandRange(cardFunctionIndex + 1, pPlayCard->m_tags.Num() - 1);
		if (!pSPGM->m_pPlayCardTextureMap.Contains(pPlayCard->m_tags[randNb])) continue;
		pSPGM->SpawnNewPlayCard(-1, 5, pPlayCard->m_tags[randNb]);
	}
}

void USPEventFunctionLib::Recycle(APlayCard* pPropCard, APlayCard* pDumpCard)
{

}

void USPEventFunctionLib::ShrinkThinkTime_End(ASingleProgressGameMode* pSPGM, FCardFunctionInfo info)
{
	pSPGM->m_actionCombineDuration += info.functionValues[0];
}

void USPEventFunctionLib::ShrinkForgeTime(FCardFunctionInfo info, AActionCard* pActionCard)
{
	if (pActionCard->m_curCardTransformInfo.actionType != 3) return;
	pActionCard->m_originLoadTime -= info.functionValues[0] * pActionCard->m_originLoadTime / 100;
	pActionCard->m_curLoadTime -= info.functionValues[0] * pActionCard->m_curLoadTime / 100;
}

void USPEventFunctionLib::ShrinkAllTime(FCardFunctionInfo info, AActionCard* pActionCard)
{
	if (pActionCard->m_curCardTransformInfo.actionType == 0) return;
	pActionCard->m_originLoadTime -= info.functionValues[0] * pActionCard->m_originLoadTime / 100;
	pActionCard->m_curLoadTime -= info.functionValues[0] * pActionCard->m_curLoadTime / 100;
}

void USPEventFunctionLib::RecoverDiscardByMoney(APlayCard* pPlayCard)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pPlayCard);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pSPGM->m_curOverallIndex.money < pPlayCard->m_functionValues[0]) return;
	int32 recoverNb = FMath::Max(pPlayCard->m_functionValues[1], pSPGM->m_dumpCardList.Num());
	for (int32 i=0; i<recoverNb; i++)
	{
		pSPGM->SpawnNewPlayCard(-1, 5, pSPGM->m_dumpCardList.Last());
		pSPGM->m_dumpCardList.Pop();
	}
}

void USPEventFunctionLib::RevealNxNCards(APlayCard* pPlayCard)
{

}

void USPEventFunctionLib::CompareCoverCardToSpecificNb(APlayCard* pPlayCard)
{

}*/

void USPEventFunctionLib::IncreaseIndexSlope(const FOverallIndexExtraFunInfo& funInfo, uint8 index, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	// index == 0，金钱
	if (index == 0)
		slopeInfo.money = slopeInfo.money * funInfo.values[0] / 100;
	else if (index == 1)
		slopeInfo.activity = slopeInfo.activity * funInfo.values[0] / 100;
	else if (index == 2)
		slopeInfo.darkness = slopeInfo.darkness * funInfo.values[0] / 100;
	else if (index == 3)
		slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[0] / 100;
	else if (index == 4)
		slopeInfo.mentality = slopeInfo.mentality * funInfo.values[0] / 100;
	else if (index == 5)
		slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[0] / 100;
	else if (index == 6)
		slopeInfo.suppression = slopeInfo.suppression * funInfo.values[0] / 100;
}

void USPEventFunctionLib::IncreaseIndexSlopeByCardNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	int32 cardNb = pSPGM->m_pPlayCards.Num();
	bool increaseFlag = false;
	if (cardNb >= funInfo.values[2]) increaseFlag = true;
	// index == 0，金钱
	if (increaseFlag)
	{
		if (funInfo.values[0] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[1] / 100;
		else if (funInfo.values[0] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[1] / 100;
	}
}

void USPEventFunctionLib::IncreaseIndexSlopeByColorNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	bool increaseFlag = false;
	int32 colorNb = 0;
	for (int32 i=0; i<pSPGM->m_pNumericCards.Num(); i++)
	{
		ANumericCard* pNumericCard = Cast<ANumericCard>(pSPGM->m_pNumericCards[i]);
		if ((int32)pNumericCard->m_color == funInfo.values[0]) colorNb += 1;
	}
	if (colorNb >= funInfo.values[4]) increaseFlag = true;
	// index == 0，金钱
	if (increaseFlag)
	{
		if (funInfo.values[1] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[3] / 100;
		else if (funInfo.values[1] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[3] / 100;
	}
	else
	{
		if (funInfo.values[1] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[2] / 100;
		else if (funInfo.values[1] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[2] / 100;
	}
}

void USPEventFunctionLib::IncreaseIndexSlopeByNumberNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	TArray<int32> targetNumber;
	int32 funValuesNb = funInfo.values.Num() - 5;
	for (int32 i=0; i<funValuesNb; i++)
	{
		targetNumber.Add(funInfo.values[i]);
	}
	bool increaseFlag = false;
	int32 numberNb = 0;
	for (int32 i = 0; i < pSPGM->m_pNumericCards.Num(); i++)
	{
		ANumericCard* pNumericCard = Cast<ANumericCard>(pSPGM->m_pNumericCards[i]);
		if (targetNumber.Contains(pNumericCard->m_nb)) numberNb += 1;
	}
	if (numberNb >= funInfo.values[funValuesNb]) increaseFlag = true;
	// index == 0，金钱
	if (increaseFlag)
	{
		if (funInfo.values[3] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[funValuesNb + 2] / 100;
		else if (funInfo.values[3] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[funValuesNb + 2] / 100;
	}
	else
	{
		if (funInfo.values[3] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[funValuesNb + 3] / 100;
		else if (funInfo.values[3] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[funValuesNb + 3] / 100;
	}
}

void USPEventFunctionLib::IncreaseIndexByDecreaseIndex(const FOverallIndexExtraFunInfo& funInfo, ASingleProgressGameMode* pSPGM)
{
	if (funInfo.values[0] == 0)
	{
		pSPGM->m_curOverallIndex.money += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.money >= pSPGM->m_maxOverallIndexValue.money) pSPGM->m_curOverallIndex.money = pSPGM->m_maxOverallIndexValue.money;
	}
	else if (funInfo.values[0] == 1)
	{
		pSPGM->m_curOverallIndex.activity += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.activity >= pSPGM->m_maxOverallIndexValue.activity) pSPGM->m_curOverallIndex.activity = pSPGM->m_maxOverallIndexValue.activity;
	}
	else if (funInfo.values[0] == 2)
	{
		pSPGM->m_curOverallIndex.darkness += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.darkness >= pSPGM->m_maxOverallIndexValue.darkness) pSPGM->m_curOverallIndex.darkness = pSPGM->m_maxOverallIndexValue.darkness;
	}
	else if (funInfo.values[0] == 3)
	{
		pSPGM->m_curOverallIndex.flameFaith += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.flameFaith >= pSPGM->m_maxOverallIndexValue.flameFaith) pSPGM->m_curOverallIndex.flameFaith = pSPGM->m_maxOverallIndexValue.flameFaith;
	}
	else if (funInfo.values[0] == 4)
	{
		pSPGM->m_curOverallIndex.mentality += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.mentality >= pSPGM->m_maxOverallIndexValue.mentality) pSPGM->m_curOverallIndex.mentality = pSPGM->m_maxOverallIndexValue.mentality;
	}
	else if (funInfo.values[0] == 5)
	{
		pSPGM->m_curOverallIndex.sunFaith += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.sunFaith >= pSPGM->m_maxOverallIndexValue.sunFaith) pSPGM->m_curOverallIndex.sunFaith = pSPGM->m_maxOverallIndexValue.sunFaith;
	}
	else if (funInfo.values[0] == 6)
	{
		pSPGM->m_curOverallIndex.suppression += funInfo.values[2];
		if (pSPGM->m_curOverallIndex.suppression >= pSPGM->m_maxOverallIndexValue.suppression) pSPGM->m_curOverallIndex.suppression = pSPGM->m_maxOverallIndexValue.suppression;
	}

	if (funInfo.values[1] == 0)
	{
		pSPGM->m_curOverallIndex.money -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.money <= 0) pSPGM->m_curOverallIndex.money = 0;
	}
	else if (funInfo.values[1] == 1)
	{
		pSPGM->m_curOverallIndex.activity -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.activity <= 0) pSPGM->m_curOverallIndex.activity = 0;
	}
	else if (funInfo.values[1] == 2)
	{
		pSPGM->m_curOverallIndex.darkness -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.darkness <= 0) pSPGM->m_curOverallIndex.darkness = 0;
	}
	else if (funInfo.values[1] == 3)
	{
		pSPGM->m_curOverallIndex.flameFaith -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.flameFaith <= 0) pSPGM->m_curOverallIndex.flameFaith = 0;
	}
	else if (funInfo.values[1] == 4)
	{
		pSPGM->m_curOverallIndex.mentality -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.mentality <= 0) pSPGM->m_curOverallIndex.mentality = 0;
	}
	else if (funInfo.values[1] == 5)
	{
		pSPGM->m_curOverallIndex.sunFaith -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.sunFaith <= 0) pSPGM->m_curOverallIndex.sunFaith = 0;
	}
	else if (funInfo.values[1] == 6)
	{
		pSPGM->m_curOverallIndex.suppression -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.suppression <= 0) pSPGM->m_curOverallIndex.suppression = 0;
	}
	else if (funInfo.values[1] == 7)
	{
		pSPGM->m_curOverallIndex.life -= funInfo.values[3];
		if (pSPGM->m_curOverallIndex.life <= 0) pSPGM->m_curOverallIndex.life = 0;
	}
}

void USPEventFunctionLib::IncreaseIndexSlopeByActionCardNb(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	bool increaseFlag = false;
	int32 actionCardNb = pSPGM->m_pActionCards.Num();
	if (actionCardNb >= funInfo.values[1]) increaseFlag = true;
	// index == 0，金钱
	if (increaseFlag)
	{
		if (funInfo.values[0] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[2] / 100;
	}
}

int32 USPEventFunctionLib::IncreaseEnergySlope(const FOverallIndexExtraFunInfo& funInfo, int32 energyReduction)
{
	int32 modifyValue = funInfo.values[0] * energyReduction / 100;
	return modifyValue;
}

void USPEventFunctionLib::IncreaseIndexSlopeIfIndexExceed(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	bool increaseFlag = false;
	if (funInfo.values[1] == 0)
	{
		if (pSPGM->m_curOverallIndex.money >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 1)
	{
		if (pSPGM->m_curOverallIndex.activity >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 2)
	{
		if (pSPGM->m_curOverallIndex.darkness >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 3)
	{
		if (pSPGM->m_curOverallIndex.flameFaith >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 4)
	{
		if (pSPGM->m_curOverallIndex.mentality >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 5)
	{
		if (pSPGM->m_curOverallIndex.sunFaith >= funInfo.values[4]) increaseFlag = true;
	}
	else if (funInfo.values[1] == 6)
	{
		if (pSPGM->m_curOverallIndex.suppression >= funInfo.values[4]) increaseFlag = true;
	}
	// index == 0，金钱
	if (increaseFlag)
	{
		if (funInfo.values[0] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[2] / 100;
		else if (funInfo.values[0] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[2] / 100;
	}
	else
	{
		if (funInfo.values[0] == 0)
			slopeInfo.money = slopeInfo.money * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 1)
			slopeInfo.activity = slopeInfo.activity * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 2)
			slopeInfo.darkness = slopeInfo.darkness * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 3)
			slopeInfo.flameFaith = slopeInfo.flameFaith * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 4)
			slopeInfo.mentality = slopeInfo.mentality * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 5)
			slopeInfo.sunFaith = slopeInfo.sunFaith * funInfo.values[3] / 100;
		else if (funInfo.values[0] == 6)
			slopeInfo.suppression = slopeInfo.suppression * funInfo.values[3] / 100;
	}
}

void USPEventFunctionLib::IncreaseIndexByDicard(const FOverallIndexExtraFunInfo& funInfo, ASingleProgressGameMode* pSPGM)
{
	if (funInfo.values[0] == 0)
		pSPGM->m_curOverallIndex.money += funInfo.values[1];
	else if (funInfo.values[0] == 1)
		pSPGM->m_curOverallIndex.activity += funInfo.values[1];
	else if (funInfo.values[0] == 2)
		pSPGM->m_curOverallIndex.darkness += funInfo.values[1];
	else if (funInfo.values[0] == 3)
		pSPGM->m_curOverallIndex.flameFaith += funInfo.values[1];
	else if (funInfo.values[0] == 4)
		pSPGM->m_curOverallIndex.mentality += funInfo.values[1];
	else if (funInfo.values[0] == 5)
		pSPGM->m_curOverallIndex.sunFaith += funInfo.values[1];
	else if (funInfo.values[0] == 6)
		pSPGM->m_curOverallIndex.suppression += funInfo.values[1];
}

void USPEventFunctionLib::IncreaseIndexSlopeByCardName(const FOverallIndexExtraFunInfo& funInfo, FOverallIndexSlopeInfo& slopeInfo, ASingleProgressGameMode* pSPGM)
{
	bool increaseFlag = false;
	int32 cardNb = 0;
	FString cardName = funInfo.functionName.RightChop(32);
	for (int32 i = 0; i < pSPGM->m_pPlayCards.Num(); i++)
	{
		//ANumericCard* pNumericCard = Cast<ANumericCard>(pSPGM->m_pNumericCards[i]);
		if (pSPGM->m_pPlayCards[i]->m_cardName != cardName) continue;
		cardNb += 1;
	}
	//if (cardNb >= funInfo.values[0]) increaseFlag = true;
	// index == 0，金钱
	int32 increasePercent = funInfo.values[1] * cardNb + 100;
	if (increasePercent >= funInfo.values[2]) increasePercent = funInfo.values[2];
	if (funInfo.values[0] == 0)
		slopeInfo.money = slopeInfo.money * increasePercent / 100;
	else if (funInfo.values[0] == 1)
		slopeInfo.activity = slopeInfo.activity * increasePercent / 100;
	else if (funInfo.values[0] == 2)
		slopeInfo.darkness = slopeInfo.darkness * increasePercent / 100;
	else if (funInfo.values[0] == 3)
		slopeInfo.flameFaith = slopeInfo.flameFaith * increasePercent / 100;
	else if (funInfo.values[0] == 4)
		slopeInfo.mentality = slopeInfo.mentality * increasePercent / 100;
	else if (funInfo.values[0] == 5)
		slopeInfo.sunFaith = slopeInfo.sunFaith * increasePercent / 100;
	else if (funInfo.values[0] == 6)
		slopeInfo.suppression = slopeInfo.suppression * increasePercent / 100;
}


