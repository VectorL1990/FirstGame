// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "VerticalBox.h"
#include "TemplateRuneElement.h"
#include "TPage.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTPage : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pBodyText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTemplateRuneElement*> m_pChoiceElements;
};
