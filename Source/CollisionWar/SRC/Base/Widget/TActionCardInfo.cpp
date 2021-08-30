// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TActionCardInfo.h"




void UTActionCardInfo::NotifyInitial_Implementation()
{

}

void UTActionCardInfo::NotifyDemoWords_Implementation(const FString& demoWords)
{

}

void UTActionCardInfo::SetLoadProgress(float percent)
{
	UObject* pObj = m_pLoadImage->Brush.GetResourceObject();
	UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObj);
	pMI->SetScalarParameterValue(FName(TEXT("Progress")), percent);
}
