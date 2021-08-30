// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "WidgetManager.h"
#include "VerticalBox.h"
#include "TemplateRuneElement.h"
#include "TemplateLoginMenu.generated.h"



UCLASS()
class COLLISIONWAR_API UTemplateLoginMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Initial menu
	*/

	/** Tell menu to initial
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void AskFadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton(const FString& buttonFunction);

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pNewGameText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pLoadGameText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pExitText;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chButtonTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_buttonTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_buttonFunctions;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_buttonMargin;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pVBox;

	TArray<UTemplateRuneElement*> m_pButtons;
};
