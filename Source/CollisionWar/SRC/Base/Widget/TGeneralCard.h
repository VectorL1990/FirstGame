// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TGeneralCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTGeneralCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton();

	void ClearCard();

	void AssignGeneralCardInfo(FString cardName);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSkillImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCardNameTextBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pNumericNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pDefaultSkillTexture;

	FString m_cardName;

	FString m_chCardName;

	/** domain��ʶGeneralCard�Ĺ���
	* 0 - ˵����ʱΪ���ܽ���
	* 1 - ˵����ʱΪ���׽���
	* 2 - ˵����ʱΪ���Ƹ��ƽ���
	* 3 - ˵����ʱΪ�¼���������
	*/
	uint8 m_domain;
};
