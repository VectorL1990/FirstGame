// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "WidgetManager.h"
#include "MultiLineEditableTextBox.h"
#include "TTradeCard.h"
#include "TSkillSelectIcon.h"
#include "TSkillTree.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTSkillTree : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadSkillTreeInfo(const FString& skillTreeName, const TArray<FString>& availableSkillNames);

	void ClearSkillTree();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeIn();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FadeOutDone(FString fadeOutName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnHoveredEnter();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnHoveredEndEnd();

	/************************************************************************/
	/* “ª∞„–≈œ¢
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxColPerRow;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTTradeCard*> m_pAllSkillCardList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_curSkillTreeName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UUniformGridPanel* m_pSkillGridPanel;

	UPROPERTY()
	TMap<UUserWidget*, UTTradeCard*> m_pBattleCardSkillCardMap;

	UTSkillSelectIcon* m_pCurHighLightSelectIcon;

	bool m_isFading = false;
};
