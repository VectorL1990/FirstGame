// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplateCharacterStateElement.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateCharacterStateElement : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialCharacterStateElement(UImage* pImage);

	UFUNCTION()
	void LoadStateImage();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pStateName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_stateName;
	
};
