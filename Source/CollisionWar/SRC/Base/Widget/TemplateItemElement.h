// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "Image.h"
#include "TemplateItemElement.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FItemButtonClickDelegate, FString, itemName, int32, row, int32, col, FString, domain);

UCLASS()
class COLLISIONWAR_API UTemplateItemElement : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void ClickButton();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClearItem();

	void UpdateElement();

	void SetElementTexture();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pItemImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pItemNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_itemName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_itemNbString = "x0";
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_itemNum = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_row;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_col;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_domain;

	FItemButtonClickDelegate m_buttonClickDelegate;
};
