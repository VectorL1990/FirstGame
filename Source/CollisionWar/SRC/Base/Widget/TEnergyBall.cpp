// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TEnergyBall.h"




void UTEnergyBall::NotifyInitial_Implementation()
{

}

void UTEnergyBall::SetEnergyBallTexture(uint8 type)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_pEnergyBallTextureMap.Contains(type)) return;
	m_type = type;
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pBLPC->m_pBattleMenu->m_pWidgetManager->m_pSkillIconButtonMat);
	pMI->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pBLPC->m_pEnergyBallTextureMap[type]);
	m_pImage->Brush.SetResourceObject(pMI);
}
