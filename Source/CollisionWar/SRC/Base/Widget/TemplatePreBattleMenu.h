// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiLineEditableTextBox.h"
#include "TemplateRow.h"
#include "VerticalBox.h"
#include "Widgetmanager.h"
#include "TemplateNotification.h"
#include "TemplatePreBattleMenu.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FPreBattleMenuChoice
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString choiceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString enName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString enDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString function;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isAvailable = true;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPreBattleMenuChoiceList
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FPreBattleMenuChoice> list;

};

UCLASS()
class COLLISIONWAR_API UTemplatePreBattleMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void AskFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadDescription();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyVBoxFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyVBoxFadeInt();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SwitchPhase();

	/** General components
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	FMargin m_margin;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVBox;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FPreBattleMenuChoiceList> m_phaseChoiceMap;

	TArray<UTemplateRow*> m_pLoadSlots;

	UTemplateRow* m_pCurSelectRow;

	UTemplateNotification* m_pChangeSlotNameMenu;

	/** menutype记录了当前菜单的类型
	* 0 - 开始新游菜单
	* 1 - 开始读档菜单
	* 2 - 
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_menuType;

	/** 记录当前属于什么状态
	* 0 - 开始新游时的状态
	* 1 - 读档状态
	* 3 - 开始新游时选择地图状态
	*/
	uint8 m_curPhase = 0;

	FString m_selectSlotName;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chNotAvailableNotification;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_enNotAvailableNotification;
};
