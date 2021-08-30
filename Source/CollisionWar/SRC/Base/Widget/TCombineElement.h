// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "Image.h"
#include "TextBlock.h"
#include "TCombineElement.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCombineElementButtonClickDelegate,const FString&, itemName);

UCLASS()
class COLLISIONWAR_API UTCombineElement : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ResetCombineElement();

	UFUNCTION()
	void SetText();

	UFUNCTION()
	void ModifyElementNb(bool addOrSub);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pLeftButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pRightButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pElementImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_itemName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_itemNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_buttonFunction;

	FCombineElementButtonClickDelegate m_buttonClickDelegate;
};
