// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Common/CollisionWarBpFunctionLibrary.h"
#include "Widget/WidgetManager.h"
#include "Widget/TTransitionMenu.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void MenuFadeOutDoneCallback(const FString& menuName);
	
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void ButtonClickCallback(const FString& buttonFunction);

	UFUNCTION()
		void ReadAllTextureInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void ReadCharacterSkillTextureInfo(const FString& roleName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void ReadCharacterStateTextureInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadGeneralTextureInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadItemCardInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadCardTypeTextureMap();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadPlayerCharacterSkills(const FString& playerName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	virtual void WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadFCInfos();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void WriteFCInfo(bool isBattleMap, const FFoundationCharacterInfo& FCInfo);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadCardCombineInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void WriteCardCombineInfo(bool isBattleMap, const FCardCombineInfo& cardCombineInfo);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySpawnMenuTutorIndicator(const FString& operationName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	UTTransitionMenu* LoadTransitionMenu(FString menuName, TArray<float> transitionTimeSteps, uint8 type);

	UFUNCTION()
	void SwitchNextTransitionStep();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySwitchTransitionStepTimeUp();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, UTexture*> m_pAllSkillTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<uint8, UTexture*> m_pCardTypeTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FStateCardInfo> m_stateCardInfoMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FItemCardInfo> m_itemCardInfoMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_pEnergyBallTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FFoundationCharacterInfo> m_FCInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCardCombineInfo> m_cardCombineInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCharacterSkillAvailableInfo> m_playerSkillInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FFoundationCharacterConsumeInfo> m_cardCopyConsumptionMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FFoundationCharacterConsumeInfo> m_eventCardConsuptionMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UUserWidget*> m_pTutorialIndicators;

	FTimerHandle m_transitionTimerHandler;

	TArray<float> m_transitionCountTimeList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		int32 m_curTransitionMenuPhaseNb = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curTransitionCountNb = 0;
};
