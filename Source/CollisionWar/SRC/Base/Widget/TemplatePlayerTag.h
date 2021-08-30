// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplatePlayerTag.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerTagClickDelegate, FString, buttonFunction);

UCLASS()
class COLLISIONWAR_API UTemplatePlayerTag : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplatePlayerTag(UButton* pInvisibleButton, UImage* pHeadShot, UTextBlock* pPlayerName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void PlayerTagClick();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetDeactive();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetActive();

	UPROPERTY(BlueprintReadWrite , Category = "CollisionWar/Widget")
	UButton * m_pInvisibleButton;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pHeadShot;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pPlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_playerName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_buttonFunction;

	FPlayerTagClickDelegate m_playerTagClickDelegate;
};
