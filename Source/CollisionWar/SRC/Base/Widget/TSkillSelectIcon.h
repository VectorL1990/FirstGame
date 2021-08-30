// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "Image.h"
#include "VerticalBox.h"
#include "TEnergyBall.h"
#include "TSkillSelectIcon.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTSkillSelectIcon : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick();

	void AddAttributeIcon(uint8 attribute);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnHoverBeginEnter();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnHoverEndEnd();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSkillImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pDynaRotator;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pAttributeVerticalBox;

	TArray<UTEnergyBall*> m_pEnergyBalls;

	FString m_buttonFunction;

	FString m_skillName = "NULL";

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 m_domain = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 m_skillType = 0;
};
