// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "DevelopBaseGameMode.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBEngine.h"



/*
void ADevelopBaseGameMode::BeginePlay()
{
	// ÿ�ν��뵽�������ʱ��KBE��һ����������KBE����ڻ�������ݽ�һֱ����
	KBEngineApp::getSingleton().reset();

	Super::BeginPlay();
}*/

void ADevelopBaseGameMode::Destroyed()
{
	Super::Destroyed();
}

/*
void ADevelopBaseGameMode::installEvents()
{
	Super::installEvents();

	// login
	KBENGINE_REGISTER_EVENT("onDevelopEvent1", onDevelopEvent1);
	KBENGINE_REGISTER_EVENT("onDevelopEvent2", onDevelopEvent2);
}*/

void ADevelopBaseGameMode::onDevelopEvent1_Implementation(const UKBEventData* pEventData)
{

}

void ADevelopBaseGameMode::onDevelopEvent2_Implementation(const UKBEventData* pEventData)
{

}
