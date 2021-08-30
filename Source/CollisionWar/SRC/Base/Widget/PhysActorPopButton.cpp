// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/CWBaseGameMode.h"
#include "PhysActorPopButton.h"




void UPhysActorPopButton::NotifyInitial_Implementation()
{

}

void UPhysActorPopButton::InitialButton(UButton* pButton, UTextBlock* pTextBlock)
{
	m_pButton = pButton;
	m_pTextBlock = pTextBlock;
}

void UPhysActorPopButton::ClickButton(int32 geoID)
{
	m_physPopButtonDelegate.Broadcast(geoID);
}
