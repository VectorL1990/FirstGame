// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../../Game/BattleLevelGameModeBase.h"
#include "UniformGridSlot.h"
#include "TemplateCharacterStatus.h"




void UTemplateCharacterStatus::NotifyInitial_Implementation()
{

}

void UTemplateCharacterStatus::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "Close")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		pBLPC->SwitchHoverCharacter(NULL, NULL);
		//pBLPC->m_pHoveredCharacter = NULL;
		pBLPC->DeleteMenu("CharacterStatus");

	}
}

void UTemplateCharacterStatus::LoadBaseCharacterInfo(ABaseCharacter* pTargetCharacter)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	m_pHpTextBlock->SetText(FText::FromString(FString::FromInt(pTargetCharacter->m_Hp)));
	m_pDFCTextBlock->SetText(FText::FromString(FString::FromInt(pTargetCharacter->m_DFC)));
	m_pATKTextBlock->SetText(FText::FromString(FString::FromInt(pTargetCharacter->m_ATK + pTargetCharacter->m_ATKAddition)));
	m_pBeAttackTimesBlock->SetText(FText::FromString(FString::FromInt(pTargetCharacter->m_beAttackedNb)));
	for (int32 i=0; i<pTargetCharacter->m_pEffects.Num(); i++)
	{
		if (!pTargetCharacter->m_pEffects[i] || pTargetCharacter->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		if (!pBLPC->m_stateCardInfoMap.Contains(pTargetCharacter->m_pEffects[i]->m_effectName)) continue;
		UTJudgeInfo* pStateInfo = CreateWidget<UTJudgeInfo>(pPC, m_pWidgetManager->m_widgetClassMap["EffectStateInfo"]);
		pStateInfo->NotifyInitial();
		pStateInfo->m_pColorImage->Brush.SetResourceObject(pBLPC->m_stateCardInfoMap[pTargetCharacter->m_pEffects[i]->m_effectName].pTexture);
		FLinearColor color = pBLPC->m_stateCardInfoMap[pTargetCharacter->m_pEffects[i]->m_effectName].color;
		pStateInfo->m_pColorImage->SetColorAndOpacity(color);
		if (m_pWidgetManager->m_language == "Chinese")
			pStateInfo->m_pJudgeNb->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[pTargetCharacter->m_pEffects[i]->m_effectName].chCardName));
		else
			pStateInfo->m_pJudgeNb->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[pTargetCharacter->m_pEffects[i]->m_effectName].cardName));
		pStateInfo->m_description = pTargetCharacter->m_pEffects[i]->m_description;
		FString prefix = "CharacterState_";
		pStateInfo->m_buttonFunction = prefix.Append(pTargetCharacter->m_pEffects[i]->m_effectName);
		m_pCharacterStateVBox->AddChild(pStateInfo);
		m_pCharacterStateList.Add(pTargetCharacter->m_pEffects[i], pStateInfo);
	}
	/*for (int32 i=0; i<pTargetCharacter->m_allJudgeCardInfos.Num(); i++)
	{
		int32 color = (pTargetCharacter->m_allJudgeCardInfos[i] - 1) / 13;
		int32 nb = pTargetCharacter->m_allJudgeCardInfos[i] - color * 13;
		UTJudgeInfo* pJudgeInfo = CreateWidget<UTJudgeInfo>(pPC, m_pWidgetManager->m_widgetClassMap["JudgeDemoInfo"]);
		pJudgeInfo->NotifyInitial();
		pJudgeInfo->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[color]);
		pJudgeInfo->m_pJudgeNb->SetText(FText::FromString(FString::FromInt(nb)));
		UPanelSlot* pPanelSlot = m_pJudgeGridPanel->AddChild(pJudgeInfo);
		m_pJudgeInfoList.Add(pJudgeInfo);
		UUniformGridSlot* pUSlot = Cast<UUniformGridSlot>(pPanelSlot);
		int32 row = i / m_maxCol;
		pUSlot->SetRow(row);
		int32 col = i - row * m_maxCol;
		pUSlot->SetColumn(col);
	}*/
	FString characterDes = "NULL";
	if (m_pWidgetManager->m_language == "Chinese")
	{
		if (m_chCharacterRaceStringMap.Contains(pTargetCharacter->m_characterRace))
			characterDes = m_chCharacterRaceStringMap[pTargetCharacter->m_characterRace] + "-" + pTargetCharacter->m_chDescription;
		else
			characterDes = pTargetCharacter->m_chDescription;
	}
	else
	{
		if (m_enCharacterRaceStringMap.Contains(pTargetCharacter->m_characterRace))
			characterDes = m_enCharacterRaceStringMap[pTargetCharacter->m_characterRace] + "-" + pTargetCharacter->m_enDescription;
		else
			characterDes = pTargetCharacter->m_enDescription;
	}
	m_pCharacterDescriptionBox->SetText(FText::FromString(characterDes));
	m_pCharacter = pTargetCharacter;
}

void UTemplateCharacterStatus::ClearAllInfo()
{
	/*m_pJudgeGridPanel->ClearChildren();
	for (int32 i = 0; i < m_pJudgeInfoList.Num(); i++)
	{
		if (m_pJudgeInfoList[i]->IsValidLowLevel())
			m_pJudgeInfoList[i]->ConditionalBeginDestroy();
	}
	m_pJudgeInfoList.Empty();*/
	m_pCharacterStateVBox->ClearChildren();
	for (TMap<UEffect*, UTJudgeInfo*>::TConstIterator iter = m_pCharacterStateList.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value->IsValidLowLevel())
			iter->Value->ConditionalBeginDestroy();
	}
	m_pCharacterStateList.Empty();
	m_pHpTextBlock->SetText(FText::FromString(FString::FromInt(0)));
	m_pDFCTextBlock->SetText(FText::FromString(FString::FromInt(0)));
	m_pATKTextBlock->SetText(FText::FromString(FString::FromInt(0)));
	m_pBeAttackTimesBlock->SetText(FText::FromString(FString::FromInt(0)));
	m_pCharacter = NULL;
}

void UTemplateCharacterStatus::UpdateCharacterStatus()
{
	if (!m_pCharacter) return;
	m_pHpTextBlock->SetText(FText::FromString(FString::FromInt(m_pCharacter->m_Hp)));
	m_pDFCTextBlock->SetText(FText::FromString(FString::FromInt(m_pCharacter->m_DFC)));
	m_pATKTextBlock->SetText(FText::FromString(FString::FromInt(m_pCharacter->m_ATK + m_pCharacter->m_ATKAddition)));
	m_pBeAttackTimesBlock->SetText(FText::FromString(FString::FromInt(m_pCharacter->m_beAttackedNb)));
}

void UTemplateCharacterStatus::UpdateJudgeInfoList()
{
	/*m_pJudgeGridPanel->ClearChildren();
	for (int32 i=0; i<m_pJudgeInfoList.Num(); i++)
	{
		if (m_pJudgeInfoList[i]->IsValidLowLevel())
			m_pJudgeInfoList[i]->ConditionalBeginDestroy();
	}
	m_pJudgeInfoList.Empty();
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	for (int32 i = 0; i < m_pCharacter->m_allJudgeCardInfos.Num(); i++)
	{
		int32 color = m_pCharacter->m_allJudgeCardInfos[i] / 13;
		int32 nb = m_pCharacter->m_allJudgeCardInfos[i] - color * 13;
		UTJudgeInfo* pJudgeInfo = CreateWidget<UTJudgeInfo>(pPC, m_pWidgetManager->m_widgetClassMap["JudgeDemoInfo"]);
		pJudgeInfo->NotifyInitial();
		pJudgeInfo->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[color]);
		pJudgeInfo->m_pJudgeNb->SetText(FText::FromString(FString::FromInt(nb)));
		UPanelSlot* pPanelSlot = m_pJudgeGridPanel->AddChild(pJudgeInfo);
		m_pJudgeInfoList.Add(pJudgeInfo);
		UUniformGridSlot* pUSlot = Cast<UUniformGridSlot>(pPanelSlot);
		int32 row = i / m_maxCol;
		pUSlot->SetRow(row);
		int32 col = i - row * m_maxCol;
		pUSlot->SetColumn(col);
	}*/
}

void UTemplateCharacterStatus::UpdateStateList(UEffect* pEffect, bool addOrSub)
{
	if (addOrSub)
	{
		if (!pEffect) return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		if (!pBLPC->m_stateCardInfoMap.Contains(pEffect->m_effectName)) return;
		UTJudgeInfo* pStateInfo = CreateWidget<UTJudgeInfo>(pPC, m_pWidgetManager->m_widgetClassMap["EffectStateInfo"]);
		pStateInfo->NotifyInitial();
		pStateInfo->m_pColorImage->Brush.SetResourceObject(pBLPC->m_stateCardInfoMap[pEffect->m_effectName].pTexture);
		FLinearColor color = pBLPC->m_stateCardInfoMap[pEffect->m_effectName].color;
		pStateInfo->m_pColorImage->SetColorAndOpacity(color);
		if (m_pWidgetManager->m_language == "Chinese")
			pStateInfo->m_pJudgeNb->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[pEffect->m_effectName].chCardName));
		else
			pStateInfo->m_pJudgeNb->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[pEffect->m_effectName].cardName));
		FString prefix = "CharacterState_";
		pStateInfo->m_buttonFunction = prefix.Append(pEffect->m_effectName);
		m_pCharacterStateVBox->AddChild(pStateInfo);
		m_pCharacterStateList.Add(pEffect, pStateInfo);
	}
	else
	{
		if (!pEffect || !m_pCharacterStateList.Contains(pEffect)) return;
		m_pCharacterStateList[pEffect]->RemoveFromParent();
		if (m_pCharacterStateList[pEffect]->IsValidLowLevel())
			m_pCharacterStateList[pEffect]->ConditionalBeginDestroy();
		m_pCharacterStateList.Remove(pEffect);
	}
}

