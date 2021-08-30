// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "HorizontalBox.h"
#include "TemplateCharacterStateElement.h"
#include "TEnergyBall.h"
#include "THpBar.h"
#include "CanvasPanel.h"
#include "TemplateCharacterInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateCharacterInfo : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION()
	void NotifyHpChange(int32 hp, int32 curDFC);

	void NotifyAtkChange(int32 atkAddition);

	void ChangeMaxHpAndDFC(int32 maxHp, int32 maxDFC);

	void UpdateEnergyBall(bool addOrSub, uint8 type);

	void UpdateJudgeList(int32 judge);

	void InitialHpBar();

	void InitialEnergyBar(int32 energyBallNb);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateCharacterStateElement> m_characterStateElementClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTEnergyBall> m_energyBallClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	FMargin m_stateMargin;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTHpBar* m_pHpBar;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UHorizontalBox* m_pStateHorizontalBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UHorizontalBox* m_pEnergyBallBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UHorizontalBox* m_pJudgeHBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateCharacterStateElement*> m_pStateElements;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTEnergyBall*> m_pEnergyBallList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FString> m_stateElements;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_maxHp;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_curHp;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_maxDFC;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_curDFC;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_atkAddition;
};
