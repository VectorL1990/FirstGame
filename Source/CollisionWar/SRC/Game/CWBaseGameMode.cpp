// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "CWBaseGameMode.h"
#include "../Base/CollisionWarGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBEngine.h"



void ACWBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	//installEvents();
}

AActor* ACWBaseGameMode::GetPrefabActorByTag(const FName& tag)
{
	TArray<AActor*> pActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), pActors);
	for (int32 i=0; i<pActors.Num(); i++)
	{
		ACharacter* pCharacter = Cast<ACharacter>(pActors[i]);
		if (!pCharacter) continue;
		if (pCharacter->GetCapsuleComponent()->ComponentHasTag(tag))
			return pActors[i];
	}
	return NULL;
}

void ACWBaseGameMode::CallLuaFunction(FString functionName)
{
	/*if (!m_pLuaActor) return;
	m_pLuaActor->LuaCallFunction(functionName);*/
}

void ACWBaseGameMode::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit);
}

void ACWBaseGameMode::InterludeParticle(FString text)
{

}

void ACWBaseGameMode::TestShipping(FString str)
{
	FString projectDir = FPaths::GameDir();
	projectDir += "Content/TextFile.txt";
	TArray<FString> StringArray;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);
	FString newLine = str + "\n";

	FFileHelper::SaveStringToFile(newLine, *(projectDir), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void ACWBaseGameMode::RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type)
{

}

FTutorialStepSerial ACWBaseGameMode::ReadTutorialInfoByName_Implementation(const FString& serialName)
{
	FTutorialStepSerial info;
	return info;
}

void ACWBaseGameMode::NotifyMusicFadeOut_Implementation()
{

}

void ACWBaseGameMode::NotifyChangeSoundClassVolume_Implementation(const FString& soundClassName, float value)
{

}

void ACWBaseGameMode::NotifyPlaySound2DByName_Implementation(const FString& name)
{

}

void ACWBaseGameMode::NotifyPlaySound2D_Implementation(const int32& type, uint8 progress)
{

}

void ACWBaseGameMode::NotifyPlaySoundAtLoc_Implementation(const FString& soundInfo, const FString& specificName, const FVector& loc)
{

}

void ACWBaseGameMode::GetItemListByName_Implementation(const FString& characterName, const FString& itemListName)
{

}

void ACWBaseGameMode::PlayFadeInLevelSequencePlayer_Implementation(const FString& levelName)
{

}

void ACWBaseGameMode::PlayFadeOutLevelSequencePlayer_Implementation(const FString& levelName)
{

}
/*

void ACWBaseGameMode::ButtonClickCallback(const FString& buttonFunction)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaButtonClickCallback(buttonFunction);
}

void ACWBaseGameMode::MenuFadeInDoneCallback(FString menuName)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaMenuFadeInDoneCallback(menuName);
}

void ACWBaseGameMode::MenuFadeOutDoneCallback(FString menuName)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaMenuFadeOutDoneCallback(menuName);
}

void ACWBaseGameMode::InputTextCommitCallback(FString text, FString function)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaInputTextCommitCallback(text, function);
}

void ACWBaseGameMode::ProgressSliderReachLimit()
{

}

void ACWBaseGameMode::CheckBoxClickCallback(FString function, bool isCheck)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaCheckBoxClickCallback(function, isCheck);
}

void ACWBaseGameMode::ComboBoxSwitchOptionCallback(FString function, FString newOption)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaComboBoxSwitchOptionCallback(function, newOption);
}

void ACWBaseGameMode::InvisibleButtonClickCallback(FString function, EInvisibleButtonLocation location)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaInvisibleButtonClickCallback(function, location);
}

void ACWBaseGameMode::PhysActorPopButtonClickCallback(int32 geoID)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaPhysActorPopButtonClickCallback(geoID);
}

void ACWBaseGameMode::ItemElementButtonClickCallback(FString itemName, int32 row, int32 col, FString domain)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaItemElementButtonClickCallback(itemName, row, col, domain);
}

void ACWBaseGameMode::PlayerTagClickCallback(FString function)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaPlayerTagClickCallback(function);
}

void ACWBaseGameMode::ElementFadeOutDoneCallback(FString caption)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaElementFadeOutDoneCallback(caption);
}
*/

/*
void ACWBaseGameMode::NewMessage(const FString& message)
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaDealNewMessage(message);
}*/

/*
void ACWBaseGameMode::NewNotification()
{
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaNewNotification();
}*/

void ACWBaseGameMode::TellBPBeginPlay_Implementation()
{

}

/*
void ACWBaseGameMode::onKicked_Implementation(const UKBEventData* pEventData)
{
}*/

/*
void ACWBaseGameMode::onDisconnected_Implementation(const UKBEventData* pEventData)
{
}*/

/*
void ACWBaseGameMode::onConnectionState_Implementation(const UKBEventData* pEventData)
{
}*/