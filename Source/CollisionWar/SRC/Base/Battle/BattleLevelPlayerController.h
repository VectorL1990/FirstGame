// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerController.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../Game/Battle/Team/Team.h"
#include "../Widget/TemplateBattleElementSystem.h"
#include "../Widget/SimpleMenu.h"
#include "../Widget/DialogTextMenu.h"
#include "../Widget/TSkillTree.h"
#include "../Widget/TemplateCharacterStatus.h"
#include "../Widget/DialogTextMenu.h"
#include "../Widget/TTutorialMenu.h"
#include "BattleLevelPlayerController.generated.h"

/**
 * 
 */
class ABasePhysActor;

UCLASS()
class COLLISIONWAR_API ABattleLevelPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
public:
	ABattleLevelPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;
	/************************************************************************/
	/* 关卡开始前的初始化操作
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	bool GetControllFromGameMode();
	/************************************************************************/

	UFUNCTION(BlueprintCallable)
	void TestAttributeReaction(TArray<uint8> atkAttributes);


	/************************************************************************/
	/* 移动
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Client_ApplyMoveLeft();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ReleaseLeftKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Client_ApplyMoveRight();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ReleaseRightKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Client_ApplyMoveUp();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ReleaseUpKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Client_ApplyMoveDown();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ReleaseDownKey();
	/************************************************************************/

	/************************************************************************/
	/*鼠标事件
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealLeftClickDownEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealLeftClickUpEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealTickEvent(float dT);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealRightClickDownEvent();

	UPROPERTY()
	bool m_isLeftKeyDownFlag = false;
	UPROPERTY()
	bool m_isPressLeftKey = false;
	UPROPERTY()
	bool m_isPressRightKey = false;
	UPROPERTY()
	bool m_isPressUpKey = false;
	UPROPERTY()
	bool m_isPressDownKey = false;
	UPROPERTY()
	bool m_isPressBlockKey = false;
	UPROPERTY()
	int32 m_targetYaw = 0;

	UPROPERTY()
	FString m_recognizeString;
	UPROPERTY()
	int32 m_recognizeNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isWidgetClick = false;
	/************************************************************************/

	/************************************************************************/
	/*技能相关
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ChangeOperationEquipmentNb(int32 nb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ChangeOperationSkillNb(int32 nb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickBlockKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickDodgeKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ReleaseBlockKey();

	int32 FindMatchRecognizeSkill(FString recognizeString);

	/**
	* 读取所有技能组合键映射
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadSkillCombineKeyList();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	virtual void WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo) override;

	void ReadPreAssignItemCardInfo();

	/**
	* 清除所有按下的组合键按钮
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClearCombineKeyList();

	/**
	* 添加组合键到组合键数组中
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AppendCombineKey(FString key);

	/**
	* 通过组合键寻找对应的技能编号
	*/
	int32 FindSkillByCombineKey();

	UFUNCTION()
	void ChangeOperationSkillNbByClick(int32 cardNb, bool skillOrEquip);

	int32 m_applyEquipmentNb = -1;

	int32 m_applySkillNb = 0;

	UPROPERTY()
	bool m_hasBindSkillToMenu = false;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<FString, FString> m_basicKeyMap;

	//技能与组合键的映射Map
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FString> m_skillCombineKeyMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_combinationKeys;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curPressSkillNb = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curSelectFCNb = -1;

	/************************************************************************/



	/************************************************************************/
	/*功能函数
	/************************************************************************/

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar")
	void NotifyGeoRecognize();

	int32 GeometryRecognize();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PauseOrUnPauseGame();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPlayPPTimeLine(FVector playerLoc, bool switchToFCDomain);

	void SwitchViewTarget();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	bool TellWhetherFitTutorialStep(const FString& stepName);

	void DeleteTutorialStep();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void EndTutorial();

	void ApplyBackToMainMenu();

	UFUNCTION()
		void WaitToMainMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShakeCamera();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void EndBattle();

	bool m_isGamePaused = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FFoundationCharacterOccupyInfo m_curFCOccupyInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FLogicVec2D m_targetBuildLogicLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_waitToFadeTime = 1.f;

	FTimerHandle m_timerHandle;

	/** 记录viewTarget实时状态
	* 0 - 正在操作主角
	* 1 - 正在从控制主角切换到控制建造角色
	* 2 - 正在操作建造角色
	* 3 - 正在从控制建造角色切换到控制主角
	*/
	uint8 m_viewTargetState = 0;

	ACharacter* m_pBuildViewTargetCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_buildViewTargetMoveSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isInTutorial = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_shakeCamHurtThreshold = 100;
	/************************************************************************/
	/* 战斗界面
	/************************************************************************/

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadBattleMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadLoadMenu();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void LoadESCMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadConcludeScoresMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadConcludePrizeMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadConcludeEXPMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadConcludeTextMenu(const TArray<FString>& text);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void LoadChangeRoundTextMenu(const TArray<FString>& text);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadTradeItemSelectMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadSkillTreeMenu();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DeleteMenu(FString menuName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SwitchMenu(FString menuName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateInitialResources();

	//void AddPreAssignCards();

	void LoadCharacterStatusMenu(ABaseCharacter* pCharacter);

	void LoadTutorialmenu();

	void LoadTutorialSerialMenu();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTutorial();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateBattleElementSystem* m_pBattleMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USimpleMenu* m_pESCMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UDialogTextMenu* m_pDialogTextMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_curConcludeMenuName;

	UPROPERTY()
	FString m_nextMenuName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTTradeCard* m_pCurDragBattleCard;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_curMenuName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateCharacterStatus* m_pCharacterStatusMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UDialogTextMenu* m_pTutorialMenu;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTTutorialMenu> m_pTutorialMenuClass;

	UTTutorialMenu* m_pTutorialSerialMenu;

	bool m_isPauseMenuOn = false;
	/************************************************************************/
	/* FC功能部分
	/************************************************************************/

	void SwitchHoverCharacter(UPrimitiveComponent* pHitComponent, AActor* pHitActor);

	void SwitchHoverPhysActor(AActor* pActor);

	bool FindCardCombineInfo(TArray<FString> inputList, FString FCName, FCardCombineInfo& combineInfo);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	ABaseCharacter* m_pHoveredCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	AActor* m_pHoveredPhysActor;

	/************************************************************************/
	/* 测试部分
	/************************************************************************/

	//一键恢复生命值
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void TestRecoverHpFull();

	//一键生成敌人
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void TestSpawnEnermy(int32 level);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void TestDrawNavMeshLine();
};
