// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerController.h"
#include "../Widget/TemplatePreBattleMenu.h"
#include "../Widget/TemplateLoginMenu.h"
#include "../Widget/TemplateMainMenu.h"
#include "../../Game/SingleProgress/OverallSaveGame.h"
#include "../Widget/TTransitionMenu.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ALoginPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DeleteMenu(const FString& menuName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyLoadTransitionMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyLoadLogoMenu();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateLoginMenu* m_pLoginMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplatePreBattleMenu* m_pPreBattleMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateMainMenu* m_pOptionMenu;

	UTTransitionMenu* m_pLoadMenu;

	UPROPERTY()
	UOverallSaveGame* m_pOverallSaveGameObject;
};
