// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "VerticalBox.h"
#include "UniformGridPanel.h"
#include "TJudgeInfo.h"
#include "TextBlock.h"
#include "MultiLineEditableTextBox.h"
#include "../../Game/Character/BaseCharacter.h"
#include "TemplateCharacterStatus.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTemplateCharacterStatus : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(const FString& buttonFunction);

	void LoadBaseCharacterInfo(ABaseCharacter* pTargetCharacter);

	void ClearAllInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateCharacterStatus();

	void UpdateJudgeInfoList();

	void UpdateStateList(UEffect* pEffect, bool addOrSub);

	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pHpTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pDFCTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pATKTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pBeAttackTimesBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pCharacterStateVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UUniformGridPanel* m_pJudgeGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pCharacterDescriptionBox;

	UPROPERTY()
	TArray<UTJudgeInfo*> m_pJudgeInfoList;

	UPROPERTY()
	TMap<UEffect*, UTJudgeInfo*> m_pCharacterStateList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxCol = 5;

	UPROPERTY()
	ABaseCharacter* m_pCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FString> m_chCharacterRaceStringMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TMap<uint8, FString> m_enCharacterRaceStringMap;
};
