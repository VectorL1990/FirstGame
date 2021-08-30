// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "TemplateRow.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyIntial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pSlotText;

	FString m_buttonFunction;

	uint8 m_type;
};
