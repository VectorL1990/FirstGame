// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateNotificationShowUpButton.h"




void UTemplateNotificationShowUpButton::NotifyInitial_Implementation()
{

}

void UTemplateNotificationShowUpButton::InitialTemplateNotificationShowUpButton(UButton* pButton)
{
	m_pButton = pButton;
}

void UTemplateNotificationShowUpButton::ClickShowUpButton()
{
	m_clickShowUpButtonDelegate.Broadcast("Button_NotificationShowHide");
}
