// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "EditableTextBox.h"
#include "TemplateNotification.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateNotification : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void EnsureSlotName(FString slotName);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_slotName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pSaveText;

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pCancelText;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chButtonText;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enButtonText;
};
