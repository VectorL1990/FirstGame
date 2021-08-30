// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "THpBar.h"




void UTHpBar::NotifyInitial_Implementation()
{

}

void UTHpBar::SetHp(float percent, int32 curHp, int32 maxHp, int32 curDFC, int32 maxDFC)
{
	//if (m_pProgressBar) m_pProgressBar->SetPercent(percent);
	/*if (!m_pHpBar) return;
	UObject* pObject = m_pHpBar->Brush.GetResourceObject();
	UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
	pMI->SetScalarParameterValue(FName(TEXT("Progress")), percent);
	FString curHpStr = FString::FromInt(curHp);
	FString maxHpStr = FString::FromInt(maxHp);
	FString bar = TEXT("/");
	FString hpStr = (curHpStr.Append(bar)).Append(maxHpStr);
	m_pHpText->SetText(FText::FromString(hpStr));
	FString curDFCStr = FString::FromInt(curDFC);
	FString maxDFCStr = FString::FromInt(maxDFC);
	FString dfcStr = (curDFCStr.Append(bar)).Append(maxDFCStr);
	m_pDFCText->SetText(FText::FromString(dfcStr));*/
	if (m_pProgressBar) m_pProgressBar->SetPercent(percent);
}
