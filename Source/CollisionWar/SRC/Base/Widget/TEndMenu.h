// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFlipImage.h"
#include "MultiLineEditableTextBox.h"
#include "WidgetManager.h"
#include "TEndMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTEndMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION()
	void DemoTextTick();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPlaySwitchTextAnimation();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ActivateSwitchTextTick();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ClearSwitchTextTimer();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void SetBackToLoginMenuTimer();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OpenLoginLevel();

	UWidgetManager* m_pWidgetManager;

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTFlipImage* m_pFlipImage;*/
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDemoText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_demoText;

	int32 m_curTick = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_switchTextInterval = 100;

	int32 m_curTextNb = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTimerHandle m_switchTextTimerHandler;

	bool m_canTick = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "CollisionWar")
	float m_backToLoginMenuWaitTime = 2.f;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTimerHandle m_backToLoginTimerHandler;
};
