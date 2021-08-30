// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplateSkillTreeIcon.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateSkillTreeIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage * m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pNbText;
};
