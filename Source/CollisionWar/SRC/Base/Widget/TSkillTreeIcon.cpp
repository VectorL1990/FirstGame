// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TSkillTreeIcon.h"




void UTSkillTreeIcon::NotifyInitial_Implementation()
{

}

void UTSkillTreeIcon::ButtonClick()
{
	FString buttonFunction = TEXT("Button_SkillIcon_") + m_skillIconName;
	m_buttonClickDelegate.Broadcast(buttonFunction);
}
