// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateColumn.h"




void UTemplateColumn::NotifyInitial_Implementation()
{

}

void UTemplateColumn::InitialColumn(UVerticalBox* pVBox)
{
	m_pVBox = pVBox;
}
