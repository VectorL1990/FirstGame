// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "TemplateMenuTitle.h"




void UTemplateMenuTitle::DeleteDemoText()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (pSPPC->m_pSPMenu)
	{
		for (TMap<int32, UTemplateMenuTitle*>::TConstIterator iter = pSPPC->m_pSPMenu->m_pDemoTexts.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value != this) continue;
			pSPPC->m_pSPMenu->m_pDemoTexts.Remove(iter->Key);
			break;
		}
	}
	if (IsValidLowLevel()) ConditionalBeginDestroy();
}

void UTemplateMenuTitle::NotifyShowDemoText_Implementation()
{

}

void UTemplateMenuTitle::NotifyInitial_Implementation()
{

}
