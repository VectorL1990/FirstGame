// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateScrollBoxWrapper.h"




void UTemplateScrollBoxWrapper::NotifyInitial_Implementation()
{

}

void UTemplateScrollBoxWrapper::InitialTemplateScrollBoxWrapper(UVerticalBox* pVerticalBox)
{
	m_pVerticalBox = pVerticalBox;
}
