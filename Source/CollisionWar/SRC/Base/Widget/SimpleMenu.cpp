// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "../../Game/CWBaseGameMode.h"
#include "WidgetTree.h"
#include "SimpleMenu.h"




void USimpleMenu::NotifyInitial_Implementation()
{

}

void USimpleMenu::AskMenuFadeOut_Implementation()
{

}

void USimpleMenu::ClickButton(const FString& buttonFunction)
{
	/*if (buttonFunction == "SaveGame")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		/ *pSPPC->m_pSaveMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(m_pWidgetManager, 2);
		pSPPC->m_pSaveMenu->AddToViewport();* /
		m_curPhase = 1;
		NotifyVBoxFadeOut();
	}
	else if (buttonFunction == "Option")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		m_curPhase = 2;
		AskMenuFadeOut();
		pSPPC->PauseOrUnPauseGame();
	}*/
	if (buttonFunction == "Cancel")
	{
		if (m_domain == 0)
		{
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			AskMenuFadeOut();
			pSPPC->m_isPauseMenuOn = false;
			pSPPC->PauseOrUnPauseGame();
		}
		else if (m_domain == 1)
		{
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
			AskMenuFadeOut();
			pBLPC->m_isPauseMenuOn = false;
			pBLPC->PauseOrUnPauseGame();
		}
	}
	else if (buttonFunction == "Battle_Cancel")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		AskMenuFadeOut();
		pBLPC->m_isPauseMenuOn = false;
		pBLPC->PauseOrUnPauseGame();
	}
}

void USimpleMenu::NotifyFirstSwitchPhase_Implementation()
{

}

void USimpleMenu::SwitchPhase()
{
	while (m_pButtons.Num() > 0)
	{
		m_pButtons.Last()->RemoveFromParent();
		if (m_pButtons.Last()->IsValidLowLevel())
			m_pButtons.Last()->ConditionalBeginDestroy();
		m_pButtons.Pop();
	}
	while (m_pSliders.Num() > 0)
	{
		m_pSliders.Last()->RemoveFromParent();
		if (m_pSliders.Last()->IsValidLowLevel())
			m_pSliders.Last()->ConditionalBeginDestroy();
		m_pSliders.Pop();
	}
	while (m_pComboBoxes.Num() > 0)
	{
		m_pComboBoxes.Last()->RemoveFromParent();
		if (m_pComboBoxes.Last()->IsValidLowLevel())
			m_pComboBoxes.Last()->ConditionalBeginDestroy();
		m_pComboBoxes.Pop();
	}
	TArray<FString> buttonFunctions = m_phaseInfos[m_curPhase].buttonFunctions;
	TArray<FString> chTexts = m_phaseInfos[m_curPhase].chTexts;
	TArray<FString> enTexts = m_phaseInfos[m_curPhase].enTexts;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i = 0; i < m_phaseInfos[m_curPhase].sliderInfos.Num(); i++)
	{
		UTemplateProgressSlider* pSlider = CreateWidget<UTemplateProgressSlider>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_widgetClassMap["OptionSlider"]);
		pSlider->NotifyInitial();
		pSlider->m_function = m_phaseInfos[m_curPhase].sliderInfos[i].sliderFunction;
		if (m_pWidgetManager->m_language == "Chinese")
			pSlider->m_pCaption->SetText(FText::FromString(m_phaseInfos[m_curPhase].sliderInfos[i].chsliderTitle));
		else
			pSlider->m_pCaption->SetText(FText::FromString(m_phaseInfos[m_curPhase].sliderInfos[i].sliderTitle));
		if (pCWGI->m_sliderOptionPercent.Contains(pSlider->m_function))
			pSlider->m_pSlider->SetValue(pCWGI->m_sliderOptionPercent[pSlider->m_function]);
		m_pSliders.Add(pSlider);
		UPanelSlot* pSlot = m_pVBox->AddChild(pSlider);
		UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVSlot->SetPadding(m_defaultVBoxMargin);
	}
	for (int32 i = 0; i < m_phaseInfos[m_curPhase].comboBoxInfos.Num(); i++)
	{
		UTemplateComboBox* pComboBox = CreateWidget<UTemplateComboBox>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_widgetClassMap["OptionCombobox"]);
		pComboBox->NotifyInitial();
		pComboBox->m_function = m_phaseInfos[m_curPhase].comboBoxInfos[i].chcomboboxFunction;
		for (int32 j = 0; j < m_phaseInfos[m_curPhase].comboBoxInfos[i].comboboxOptions.Num(); j++)
		{
			pComboBox->m_pComboBox->AddOption(m_phaseInfos[m_curPhase].comboBoxInfos[i].comboboxOptions[j]);
		}
		if (m_pWidgetManager->m_language == "Chinese")
			pComboBox->m_pCaption->SetText(FText::FromString(m_phaseInfos[m_curPhase].comboBoxInfos[i].chcomboboxTitle));
		else
			pComboBox->m_pCaption->SetText(FText::FromString(m_phaseInfos[m_curPhase].comboBoxInfos[i].comboboxTitle));
		if (pCWGI->m_comboboxOption.Contains(pComboBox->m_function))
			pComboBox->m_pComboBox->SetSelectedOption(pCWGI->m_comboboxOption[pComboBox->m_function]);
		m_pComboBoxes.Add(pComboBox);
		UPanelSlot* pSlot = m_pSlotVBox->AddChild(pComboBox);
		UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVSlot->SetPadding(m_defaultSlotVBoxMargin);
	}
	for (int32 i=0; i<buttonFunctions.Num(); i++)
	{
		UTemplateRuneElement* pSimpleButton = CreateWidget<UTemplateRuneElement>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_widgetClassMap["SimpleMenuButton"]);
		pSimpleButton->NotifyInitial();
		pSimpleButton->m_buttonFunction = buttonFunctions[i];
		if (m_pWidgetManager->m_language == "Chinese")
			pSimpleButton->m_pRuneName->SetText(FText::FromString(chTexts[i]));
		else
			pSimpleButton->m_pRuneName->SetText(FText::FromString(enTexts[i]));
		m_pButtons.Add(pSimpleButton);
		UPanelSlot* pSlot = m_pVBox->AddChild(pSimpleButton);
		UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVSlot->SetPadding(m_defaultVBoxMargin);
	}
	
	if (m_curPhase == 1)
	{
		for (int32 i = 0; i < pCWGI->m_playerSingleProgressInfos.Num(); i++)
		{
			if (pCWGI->m_playerSingleProgressInfos[i].progressName == "") continue;
			UTemplateRow* pRow = CreateWidget<UTemplateRow>(pGI, m_pWidgetManager->m_widgetClassMap["Row"]);
			pRow->NotifyIntial();
			pRow->m_type = 2;
			FString slotNamePrefix = "LoadSlot_";
			pRow->m_buttonFunction = slotNamePrefix.Append(pCWGI->m_playerSingleProgressInfos[i].progressName);
			pRow->m_pSlotText->SetText(FText::FromString(pCWGI->m_playerSingleProgressInfos[i].progressName));
			UPanelSlot* pSlot = m_pSlotVBox->AddChild(pRow);
			UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
			pVSlot->SetPadding(m_defaultSlotVBoxMargin);
			m_pRows.Add(pRow);
		}
	}
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);
	pCWGM->TestShipping("SwitchPhase_now phase is:" + FString::FromInt(m_curPhase));*/
	NotifyVBoxFadeInt(m_curPhase);
}

void USimpleMenu::NotifyVBoxFadeInt_Implementation(uint8 phase)
{

}

void USimpleMenu::NotifyVBoxFadeOut_Implementation()
{

}
