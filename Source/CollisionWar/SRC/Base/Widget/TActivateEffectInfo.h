// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplateCharacterInfo.h"
#include "TActivateEffectInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTActivateEffectInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	bool SetupInfo(FString effectName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pActivateEffectImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateCharacterInfo* m_pParentCharacterInfo;
};
