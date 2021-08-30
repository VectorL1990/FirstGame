// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TCardInfoMenu.h"




void UTCardInfoMenu::NotifyInitial_Implementation()
{

}

void UTCardInfoMenu::ButtonClick(FString buttonFunction)
{
	m_buttonClickDelegate.Broadcast(buttonFunction);
}

void UTCardInfoMenu::FadeOutDone(FString menuName)
{
	m_menuFadeOutDelegate.Broadcast(menuName);
}

void UTCardInfoMenu::NotifyFadeOut_Implementation()
{

}
