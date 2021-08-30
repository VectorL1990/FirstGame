// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBEvent.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/LogicEvents.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
//#include "Lua/LuaActor.h"
//#include "../Base/CWSoundMix.h"
#include "../Base/Widget/TFlipImage.h"
#include "../Base/Widget/TTutorialMenu.h"
#include "CWBaseGameMode.generated.h"

/**
 * 
 */




UCLASS()
class COLLISIONWAR_API ACWBaseGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	/*virtual void Destroyed() override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;*/

	/** Called when a Controller with a PlayerState leaves the match. */
	//virtual void Logout(AController* Exiting) override;

	/*
	安装登陆时需要监听的KBE事件
	*/
	/*virtual void installEvents();

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void fire(const FString& eventName, UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onKicked(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onDisconnected(const UKBEventData* pEventData);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onConnectionState(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
	void reloginBaseapp();*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void TellBPBeginPlay();

	/************************************************************************/
	/* 通用申请函数                                                                     */
	/************************************************************************/
	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/PreBattle")
	void ReqAnswerAddFriendRequest(bool answer, FString applierName);*/

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/PreBattle")
	void ReqAnswerFriendMatch(bool result, FString hostName, FString roleType, int32 groupNb);*/

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/PreBattle")
	void ReqSendMessageToFriend(FString message, FString friendName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/ChooseMap")
	void ReqEnsureEnterRoom();*/

	/************************************************************************/
	/* KBE回调函数                                                                     */
	/************************************************************************/
	/*void dispatchAddFriendRequest(const UKBEventData* pEventData);

	void dispatchDisapproveAddFriendAnswer(const UKBEventData* pEventData);

	void dispatchApproveAddFriendAnswer(const UKBEventData* pEventData);

	void dispatchDeleteFriendRequestResult(const UKBEventData* pEventData);
	
	void dispatchTeamMatchStatus(const UKBEventData* pEventData);

	void dispatchTeamMatchInvitation(const UKBEventData* pEventData);

	void dispatchMatchStatus(const UKBEventData* pEventData);

	void dispatchCancelMatch(const UKBEventData* pEventData);

	void dispatchAllPlayerRoletypeAndAssignNb(const UKBEventData* pEventData);
	
	void dispatchMessageFromFriend(const UKBEventData* pEventData);

	void onEnterWorld(const UKBEventData* pEventData);

	void onLeaveWorld(const UKBEventData* pEventData);*/
	/************************************************************************/
	/* UI按键回调函数                                                                     */
	/************************************************************************/
	/*UFUNCTION()
	void ChatBoxSendMessageCallback(FString friendName, FString message);*/
/*

	UFUNCTION()
		void ButtonClickCallback(const FString& buttonFunction);

	UFUNCTION()
	void MenuFadeInDoneCallback(FString menuName);

	UFUNCTION()
		void MenuFadeOutDoneCallback(FString menuName);

	UFUNCTION()
		void InputTextCommitCallback(FString text, FString function);

	UFUNCTION()
		void ProgressSliderReachLimit();

	UFUNCTION()
		void CheckBoxClickCallback(FString function, bool isCheck);

	UFUNCTION()
		void ComboBoxSwitchOptionCallback(FString function, FString newOption);

	UFUNCTION()
	void InvisibleButtonClickCallback(FString function, EInvisibleButtonLocation location);

	UFUNCTION()
	void PhysActorPopButtonClickCallback(int32 geoID);

	UFUNCTION()
	void ItemElementButtonClickCallback(FString itemName, int32 row, int32 col, FString domain);

	UFUNCTION()
	void PlayerTagClickCallback(FString function);

	UFUNCTION()
	void ElementFadeOutDoneCallback(FString caption);
*/

	/************************************************************************/
	/* 功能函数                                                                     */
	/************************************************************************/
	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/PreBattle")
	void DealNotificationButtonCallback(FString buttonFunction, FString& functionType, FString& function, FString& keyWords);*/

	/*UFUNCTION()
	void NewNotification();*/

	/*UFUNCTION()
	void NewMessage(const FString& message);*/

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	bool TellWhetherEnterRoomInfoComplete();*/

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void ResetAccountStatus();*/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	AActor* GetPrefabActorByTag(const FName& tag);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void CallLuaFunction(FString functionName);

	UFUNCTION()
	void QuitGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar/Game")
	void PlayFadeInLevelSequencePlayer(const FString& levelName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar/Game")
	void PlayFadeOutLevelSequencePlayer(const FString& levelName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	virtual void InterludeParticle(FString text);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void GetItemListByName(const FString& characterName, const FString& itemListName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPlaySoundAtLoc(const FString& soundInfo, const FString& specificName, const FVector& loc);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyPlaySound2D(const int32& type, uint8 progress);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyPlaySound2DByName(const FString& name);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyChangeSoundClassVolume(const FString& soundClassName, float value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
		void NotifyMusicFadeOut();

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Login")
	TSubclassOf<class ALuaActor> m_BPLuaActorClass;*/

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Login")
	ALuaActor* m_pLuaActor;*/

	void TestShipping(FString str);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FTutorialStepSerial ReadTutorialInfoByName(const FString& serialName);

	virtual void RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_defaultTutorialNames;

	FString m_curTutorialName;
};
