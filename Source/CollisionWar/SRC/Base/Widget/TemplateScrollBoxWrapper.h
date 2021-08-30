// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VerticalBox.h"
#include "TemplateScrollBoxWrapper.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateScrollBoxWrapper : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateScrollBoxWrapper(UVerticalBox* pVerticalBox);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pVerticalBox;
	
};
