// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Login/LoginPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "TemplateComboBox.h"




void UTemplateComboBox::NotifyInitial_Implementation()
{

}

void UTemplateComboBox::ComboSelectionChange(FString selectItem)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (m_function.Contains("Language_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (!pLPC->m_pLoginMenu || !pLPC->m_pOptionMenu) return;
		
		if (selectItem == "Chinese")
		{
			pCWGI->m_language = "Chinese";
			for (int32 i=0; i<pLPC->m_pOptionMenu->m_pSliders.Num(); i++)
			{
				pLPC->m_pOptionMenu->m_pSliders[i]->m_pCaption->SetText(FText::FromString(pLPC->m_pOptionMenu->m_sliderInfos[i].chsliderTitle));
			}
			for (int32 i=0; i<pLPC->m_pOptionMenu->m_pComboboxes.Num(); i++)
			{
				pLPC->m_pOptionMenu->m_pComboboxes[i]->m_pCaption->SetText(FText::FromString(pLPC->m_pOptionMenu->m_comboboxInfos[i].chcomboboxTitle));
			}
			for (int32 i=0; i<pLPC->m_pLoginMenu->m_pButtons.Num(); i++)
			{
				pLPC->m_pLoginMenu->m_pButtons[i]->m_pRuneName->SetText(FText::FromString(pLPC->m_pLoginMenu->m_chButtonTexts[i]));
			}
		}
		else
		{
			pCWGI->m_language = "English";
			for (int32 i = 0; i < pLPC->m_pOptionMenu->m_pSliders.Num(); i++)
			{
				pLPC->m_pOptionMenu->m_pSliders[i]->m_pCaption->SetText(FText::FromString(pLPC->m_pOptionMenu->m_sliderInfos[i].sliderTitle));
			}
			for (int32 i = 0; i < pLPC->m_pOptionMenu->m_pComboboxes.Num(); i++)
			{
				pLPC->m_pOptionMenu->m_pComboboxes[i]->m_pCaption->SetText(FText::FromString(pLPC->m_pOptionMenu->m_comboboxInfos[i].chcomboboxTitle));
			}
			for (int32 i = 0; i < pLPC->m_pLoginMenu->m_pButtons.Num(); i++)
			{
				pLPC->m_pLoginMenu->m_pButtons[i]->m_pRuneName->SetText(FText::FromString(pLPC->m_pLoginMenu->m_buttonTexts[i]));
			}
		}
		
	}
	if (pCWGI->m_comboboxOption.Contains(m_function))
		pCWGI->m_comboboxOption[m_function] = selectItem;
}
