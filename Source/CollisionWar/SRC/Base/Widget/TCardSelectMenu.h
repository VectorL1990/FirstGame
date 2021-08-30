// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "TActionCard.h"
#include "CanvasPanel.h"
#include "MultiLineEditableTextBox.h"
#include "TextBlock.h"
#include "TCardSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTCardSelectMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	/** �����������˼����Ϊ���������������ģ���Ϊ�ؽ�ϵ�к������ϵ�У��ؽ��Ļ�ϵͳ�ֻ����ɼ��ſ������ѡ�����ѡ�����Զ��л����������
	* ��������Ҫ��һ���л��������ݵĺ��������Ǽ��űؽ����Ƴ��£�Ȼ���л���������Ŀ���
	*/
	void StartSwitchDomain();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SwitchDomain();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifySetTimer();

	/** ��������������ǰѽ�����������ϵ�ѡ���˵���
	* domain - ������ĸ�����Ľ������ƣ�0����ؽ����ƣ�1���������������
	*/
	void AddActionCardToPanel(uint8 domain);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTitles();

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pBonusCanvas;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pInstructionText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_cardInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTActionCard> m_pBonusCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_bonusCardSize;

	TArray<FString> m_allBonusCardNames;

	UPROPERTY()
	TArray<UTActionCard*> m_pAllBonusCards;

	UTActionCard* m_pCurSelectCard;

	int32 m_curDomainNb = 0;

	TArray<FString> m_mustBonusCards;

	uint8 m_bonusType = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chInstruction;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enInstruction;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_chTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitles;
};
