// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TActivateEffectInfo.h"




void UTActivateEffectInfo::NotifyInitial_Implementation()
{

}

bool UTActivateEffectInfo::SetupInfo(FString effectName)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_stateCardInfoMap.Contains(effectName)) return false;
	UTexture* pTexutre = pBLPC->m_stateCardInfoMap[effectName].pTexture;
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pBLPC->m_pBattleMenu->m_pWidgetManager->m_pActivateEffectInfoMat);
	pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexutre);
	m_pActivateEffectImage->Brush.SetResourceObject(pMI);
	return true;
}

void UTActivateEffectInfo::NotifyFadeOut_Implementation()
{

}
