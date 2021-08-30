// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "DevelopBaseGameMode.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBEngine.h"



/*
void ADevelopBaseGameMode::BeginePlay()
{
	// 每次进入到这个界面时对KBE做一次清理，否则KBE插件内缓存的内容将一直存在
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
