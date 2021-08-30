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

/*
void ACWBaseGameMode::Destroyed()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
	Super::Destroyed();
}

void ACWBaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}*/

/*
void ACWBaseGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// 可以在这里理解为玩家编辑器Stop游戏或者离开了这个场景
	if (Exiting)
	{
		KBENGINE_DEREGISTER_ALL_EVENT();
	}
}*/
/*

void ACWBaseGameMode::installEvents()
{
	// common
	/ *KBENGINE_REGISTER_EVENT("onKicked", onKicked);
	KBENGINE_REGISTER_EVENT("onDisconnected", onDisconnected);
	KBENGINE_REGISTER_EVENT("onConnectionState", onConnectionState);
	KBENGINE_REGISTER_EVENT("dispatchAddFriendRequest", dispatchAddFriendRequest);
	KBENGINE_REGISTER_EVENT("dispatchDisapproveAddFriendAnswer", dispatchDisapproveAddFriendAnswer);
	KBENGINE_REGISTER_EVENT("dispatchApproveAddFriendAnswer", dispatchApproveAddFriendAnswer);
	KBENGINE_REGISTER_EVENT("dispatchTeamMatchStatus", dispatchTeamMatchStatus);
	KBENGINE_REGISTER_EVENT("dispatchTeamMatchInvitation", dispatchTeamMatchInvitation);
	KBENGINE_REGISTER_EVENT("dispatchMatchStatus", dispatchMatchStatus);
	KBENGINE_REGISTER_EVENT("dispatchCancelMatch", dispatchCancelMatch);
	KBENGINE_REGISTER_EVENT("dispatchAllPlayerRoletypeAndAssignNb", dispatchAllPlayerRoletypeAndAssignNb);
	KBENGINE_REGISTER_EVENT("dispatchMatchResult", dispatchMatchResult);
	KBENGINE_REGISTER_EVENT("dispatchMessageFromFriend", dispatchMessageFromFriend);
	KBENGINE_REGISTER_EVENT("onEnterWorld", onEnterWorld);
	KBENGINE_REGISTER_EVENT("onLeaveWorld", onLeaveWorld);* /
}



void ACWBaseGameMode::fire(const FString& eventName, UKBEventData* pEventData)
{
	KBENGINE_EVENT_FIRE(eventName, pEventData);
}


void ACWBaseGameMode::reloginBaseapp()
{
	UKBEventData_onReloginBaseapp* pEventData = NewObject<UKBEventData_onReloginBaseapp>();
	KBENGINE_EVENT_FIRE("reloginBaseapp", pEventData);
}*/
/*

void ACWBaseGameMode::ReqAnswerAddFriendRequest(bool answer, FString applierName)
{
	UKBEventData_reqAnswerAddFriendRequest* pEventData = NewObject<UKBEventData_reqAnswerAddFriendRequest>();
	pEventData->answer = answer;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	for (int32 i = 0; i < pCWGameInstance->m_addFriendRequestList.Num(); i++)
	{
		if (pCWGameInstance->m_addFriendRequestList[i] == applierName)
		{
			uint64 applierDBID = pCWGameInstance->m_addFriendRequestDBIDList[i];
			pEventData->applierDBID = applierDBID;
			pCWGameInstance->m_addFriendRequestList.RemoveAt(i);
			pCWGameInstance->m_addFriendRequestDBIDList.RemoveAt(i);
			break;
		}
	}
	KBENGINE_EVENT_FIRE("ReqAnswerAddFriendRequest", pEventData);
}*/
/*

void ACWBaseGameMode::ReqAnswerFriendMatch(bool result, FString hostName, FString roleType, int32 groupNb)
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	UKBEventData_reqAnswerFriendMatch* pEventData = NewObject<UKBEventData_reqAnswerFriendMatch>();
	pEventData->result = result;
	pEventData->hostName = hostName;
	pEventData->roleType = pCWGameInstance->m_playerInfo.lastSelectRoleType;
	pEventData->groupNb = groupNb;
	if (pEventData->hostName == "") pEventData->hostName = "NULL";
	if (pEventData->roleType == "") pEventData->roleType = "NULL";
	KBENGINE_EVENT_FIRE("ReqAnswerFriendMatch", pEventData);
}*/

/*
void ACWBaseGameMode::ReqSendMessageToFriend(FString message, FString friendName)
{
	if (friendName == "" || message == "") return;
	UKBEventData_reqSendMessageToFriend* pEventData = NewObject<UKBEventData_reqSendMessageToFriend>();
	pEventData->message = message;
	pEventData->friendName = friendName;
	KBENGINE_EVENT_FIRE("ReqSendMessageToFriend", pEventData);
}

void ACWBaseGameMode::ReqEnsureEnterRoom()
{
	UKBEventData_reqEnsureEnterRoom* pEventData = NewObject<UKBEventData_reqEnsureEnterRoom>();
	KBENGINE_EVENT_FIRE("ReqEnsureEnterRoom", pEventData);
}*/
/*

void ACWBaseGameMode::dispatchAddFriendRequest(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchAddFriendRequest* pData = Cast<UKBEventData_dispatchAddFriendRequest>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	if (pCWGameInstance->m_addFriendRequestList.Contains(pData->name)) return;
	FString notification = "AddFriend/" + pData->name + "/" + pData->name + " asks to be your friend";
	pCWGameInstance->m_notifications.Add(notification);
	pCWGameInstance->m_addFriendRequestList.Add(pData->name);
	pCWGameInstance->m_addFriendRequestDBIDList.Add(pData->applierDBID);
	NewNotification();
}

void ACWBaseGameMode::dispatchDisapproveAddFriendAnswer(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchDisapproveAddFriendAnswer* pData = Cast<UKBEventData_dispatchDisapproveAddFriendAnswer>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	FString notification = pData->name + " has disapproved your request";
	pCWGameInstance->m_notifications.Add(notification);
	NewNotification();
}

void ACWBaseGameMode::dispatchApproveAddFriendAnswer(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchApproveAddFriendAnswer* pData = Cast<UKBEventData_dispatchApproveAddFriendAnswer>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	FString notification = "NewFriend/" + pData->name + "/" + pData->name + " has approved your request";
	pCWGameInstance->m_notifications.Add(notification);
	pCWGameInstance->m_playerInfo.friendList.playerTagInfoList.Add(pData->playerTagInfo);
	NewNotification();
}

void ACWBaseGameMode::dispatchDeleteFriendRequestResult(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchDeleteFriendRequestResult* pData = Cast<UKBEventData_dispatchDeleteFriendRequestResult>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	FString notification;
	if (pData->result == false) notification = "Fail to delete friend.";
	else
	{
		notification = "Success to delete friend " + pData->deleteName + " .";
		for (int32 i = 0; i < pCWGameInstance->m_playerInfo.friendList.playerTagInfoList.Num(); i++)
		{
			if (pCWGameInstance->m_playerInfo.friendList.playerTagInfoList[i].playerName == pData->deleteName)
			{
				pCWGameInstance->m_playerInfo.friendList.playerTagInfoList.RemoveAt(i);
				pCWGameInstance->m_playerInfo.friendList.dbidList.RemoveAt(i);
				break;
			}
		}
	}
	pCWGameInstance->m_notifications.Add(notification);
	NewNotification();
}

void ACWBaseGameMode::dispatchTeamMatchStatus(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchTeamMatchStatus* pData = Cast<UKBEventData_dispatchTeamMatchStatus>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	pCWGameInstance->m_curMatchHostName = pData->hostName;
	NewMessage(pData->message);
}

void ACWBaseGameMode::dispatchTeamMatchInvitation(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchTeamMatchInvitation* pData = Cast<UKBEventData_dispatchTeamMatchInvitation>(pEventData);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	FString notification = pData->matchType + "/" + pData->hostName + "/" + FString::FromInt(pData->groupNb) +
		"/" + pData->hostName + " asks you to play.";
	pCWGameInstance->m_notifications.Add(notification);
	NewNotification();
}

void ACWBaseGameMode::dispatchMatchStatus(const UKBEventData* pEventData)
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance * pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	const UKBEventData_dispatchMatchStatus* pData = Cast<UKBEventData_dispatchMatchStatus>(pEventData);
	if (pData->status == "Fail") NewMessage("Player is already matching");
	else if (pData->status == "NotMatching")
	{
		pCWGameInstance->m_accountStatus = "PreState";
		NewMessage("Player is not matching");
	}
	else if (pData->status == "EnsureEnterRoom")
	{
		pCWGameInstance->m_accountStatus = pData->status;
		NewMessage("EnsureEnterRoom");
	}
	else
	{
		pCWGameInstance->m_accountStatus = pData->status;
		NewMessage("Player apply matching successfully");
	}
}

void ACWBaseGameMode::dispatchCancelMatch(const UKBEventData* pEventData)
{
	ResetAccountStatus();
	NewMessage("Cancel match already");
}

void ACWBaseGameMode::dispatchAllPlayerRoletypeAndAssignNb(const UKBEventData* pEventData)
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	const UKBEventData_dispatchAllPlayerRoletypeAndAssignNb* pData = Cast<UKBEventData_dispatchAllPlayerRoletypeAndAssignNb>(pEventData);
	pCWGameInstance->m_curLevelName = pData->levelName;
	pCWGameInstance->m_playerID = pData->playerID;
	pCWGameInstance->m_playerInfosInBattle = pData->playerRoletypeAssignnumList;
	pCWGameInstance->m_battleResult = pData->battleResult;
	pCWGameInstance->m_hasRecieveAllPlayerAssignNbs = true;
	pCWGameInstance->m_accountStatus = TEXT("EnsureEnterRoom");
	pCWGameInstance->m_battleInfo.maxFrame = pData->maxFrameNb;
	NewMessage(TEXT("dispatchAllPlayerRoletypeAndAssignNb"));
}

void ACWBaseGameMode::dispatchMessageFromFriend(const UKBEventData* pEventData)
{
	const UKBEventData_dispatchMessageFromFriend* pData = Cast<UKBEventData_dispatchMessageFromFriend>(pEventData);
	if (!m_pLuaActor) return;
	m_pLuaActor->LuaDealNewChatMessage(pData->friendName, pData->message);
}

void ACWBaseGameMode::onEnterWorld(const UKBEventData* pEventData)
{
	const UKBEventData_onEnterWorld* pData = Cast<UKBEventData_onEnterWorld>(pEventData);
	if (pData->isPlayer)
	{
		UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		if (!pGameInstance) return;
		UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
		if (!pCWGameInstance) return;
		pCWGameInstance->m_accountStatus = TEXT("EnsureEnterRoom");
		pCWGameInstance->m_hasCSEnterWorld = true;
		NewMessage(TEXT("PlayerEnterWorld"));
	}
}

void ACWBaseGameMode::onLeaveWorld(const UKBEventData* pEventData)
{
	const UKBEventData_onLeaveWorld* pData = Cast<UKBEventData_onLeaveWorld>(pEventData);
	if (pData->isPlayer)
	{
		UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		if (!pGameInstance) return;
		UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
		if (!pCWGameInstance) return;
		pCWGameInstance->m_hasCSEnterWorld = false;
		NewMessage(TEXT("PlayerLeaveWorld"));
	}
}
*/

/*
void ACWBaseGameMode::ChatBoxSendMessageCallback(FString friendName, FString message)
{
	ReqSendMessageToFriend(message, friendName);
}*/

/*
void ACWBaseGameMode::DealNotificationButtonCallback(FString buttonFunction, FString& functionType, FString& function, FString& keyWords)
{
	FString chopPrefix = buttonFunction.RightChop(20);
	int32 functionSeperatorLoc = chopPrefix.Find("_");
	function = chopPrefix.Left(functionSeperatorLoc);
	FString chopFunction = chopPrefix.RightChop(functionSeperatorLoc + 1);
	int32 typeSperatorLoc = chopFunction.Find("_");
	functionType = chopFunction.Left(typeSperatorLoc);
	keyWords = chopFunction.RightChop(typeSperatorLoc + 1);
}*/

/*
bool ACWBaseGameMode::TellWhetherEnterRoomInfoComplete()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return false;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return false;
	if (pCWGameInstance->m_hasRecieveAllPlayerAssignNbs &&
		pCWGameInstance->m_hasRecievePlayerAssignNbInBattle &&
		pCWGameInstance->m_hasRecievePlayerInfo &&
		pCWGameInstance->m_hasRecieveMallInfo &&
		pCWGameInstance->m_hasCSEnterWorld)
		return true;
	else return false;
}*/

/*
void ACWBaseGameMode::ResetAccountStatus()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	pCWGameInstance->m_accountStatus = "PreState";
	pCWGameInstance->m_hasRecievePlayerAssignNbInBattle = false;
	pCWGameInstance->m_hasRecieveAllPlayerAssignNbs = false;
	pCWGameInstance->m_hasCSEnterWorld = false;
	pCWGameInstance->m_curMatchHostName = "NULL";
	pCWGameInstance->m_curLevelName = "NULL";
	pCWGameInstance->m_curBattleType = "NULL";
	pCWGameInstance->m_playerTagListInBattle.playerTagInfoList.Empty();
	pCWGameInstance->m_isNormalEnterBattle = true;
	pCWGameInstance->m_playerAssignNbInBattle = 0;
	pCWGameInstance->m_playerInfosInBattle.values.Empty();
	pCWGameInstance->m_battleResult.reset();
	pCWGameInstance->m_battleInfo.maxFrame = 0;
}*/

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