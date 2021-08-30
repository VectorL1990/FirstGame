// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../../Common/SPEventFunctionLib.h"
#include "TShopMenu.h"




void UTShopMenu::NotifyInitial_Implementation()
{

}

void UTShopMenu::ClickButton(FString buttonFunction)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(m_pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (buttonFunction == "Buy")
	{
		if (!m_pCurSelectActionCard) return;
		if (!pSPGM->m_pPlayCardTextureMap.Contains(m_pCurSelectActionCard->m_cardName)) return;
		if (pSPGM->m_curMoney >= pSPGM->m_cardValuePriceMap[pSPGM->m_pPlayCardTextureMap[m_pCurSelectActionCard->m_cardName].cardValueLevel] &&
			!m_usedCardNames.Contains(m_pCurSelectActionCard->m_cardName))
		{
			if (pSPGM->m_pPlayCardTextureMap[m_pCurSelectActionCard->m_cardName].tags.Contains("Service"))
			{
				//说明是服务类卡牌，到函数类直接操作
				//USPEventFunctionLib::
				/*if (pSPGM->m_pPlayCardTextureMap[m_pCurSelectActionCard->m_cardName].tags.Contains("Icy Hospital"))
				{
					int32 recoverValue = FCString::Atoi(*pSPGM->m_pPlayCardTextureMap[m_pCurSelectActionCard->m_cardName].tags.Last());
					USPEventFunctionLib::RecoverHp(pSPPC->m_pSelectActionCard,recoverValue);
				}*/
			}
			else
			{
				//说明是购买类卡牌，直接生成卡牌，同时将该卡牌翻面
				pSPGM->SpawnNewPlayCard(m_pCurSelectActionCard->m_nb, m_pCurSelectActionCard->m_color, m_pCurSelectActionCard->m_cardName);
			}
			pSPGM->m_curMoney -= pSPGM->m_cardValuePriceMap[pSPGM->m_pPlayCardTextureMap[m_pCurSelectActionCard->m_cardName].cardValueLevel];
			m_pCurSelectActionCard->SetFadeType(true, true);
			m_pCurSelectActionCard->SetupFadeInTimer(0, false);
			m_pCurSelectActionCard->m_highHightFlag = false;
			m_pCurSelectActionCard->NotifySetTimer(1);
			m_usedCardNames.Add(m_pCurSelectActionCard->m_cardName);
			m_pCurSelectActionCard = NULL;
		}
	}
	else if (buttonFunction == "Cancel")
	{
		pSPGM->m_shopState = 1;
	}
}

void UTShopMenu::FadeOut_Implementation()
{

}
