// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateSpacer.h"




void UTemplateSpacer::NotifyInitial_Implementation()
{

}

void UTemplateSpacer::InitialTemplateSpacer(USpacer* pSpacer)
{
	m_pSpacer = pSpacer;
}
