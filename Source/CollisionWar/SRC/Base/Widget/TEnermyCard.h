// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "ScrollBox.h"
#include "TEnermyCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTEnermyCard : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	void SetEnermyTexture(UTexture* pTexture, UMaterialInstance* pMI);

	void AddStateToCard(FString stateName, UMaterialInstance* pMI);

	void RemoveState(FString stateName);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pEnermyImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCardNameText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UScrollBox* m_pScrollBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_stateList;
};
