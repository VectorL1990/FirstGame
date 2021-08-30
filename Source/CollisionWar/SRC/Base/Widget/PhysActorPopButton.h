// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "PhysActorPopButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhysPopButtonClickDelegate, int32, geoID);

UCLASS()
class COLLISIONWAR_API UPhysActorPopButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialButton(UButton* pButton, UTextBlock* pTextBlock);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(int32 geoID);

	UButton* m_pButton;
	
	UTextBlock* m_pTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_physActorID;
	
	FPhysPopButtonClickDelegate m_physPopButtonDelegate;
};
