// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "THurtNbInfo.h"




void UTHurtNbInfo::NotifyInitial_Implementation()
{

}

void UTHurtNbInfo::SetupNb(int32 nb)
{
	FString nbStr = FString::FromInt(nb);
	m_pNbText->SetText(FText::FromString(nbStr));
}

void UTHurtNbInfo::NotifyFadeOut_Implementation()
{

}
