// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Widget/TCardInfoMenu.h"
#include "../Widget/TSkillTree.h"
#include "../Widget/TActionPanel.h"
#include "../../Game/SingleProgress/PlayCard.h"
#include "../../Game/SingleProgress/NumericCard.h"
#include "../../Game/SingleProgress/EventCard.h"
#include "../Widget/TemplateSingleProgressMenu.h"
#include "../Widget/TDecipherMenu.h"
#include "../Widget/TBattleLineMenu.h"
#include "../Widget/TCardSelectMenu.h"
#include "../Widget/TDrawCardMenu.h"
#include "../Widget/TShopMenu.h"
#include "../Widget/TShadowModeMenu.h"
#include "../Widget/TemplateRunesMenu.h"
#include "../Widget/TCardCombineListMenu.h"
#include "../Widget/TemplatePreBattleMenu.h"
#include "../../Game/SingleProgress/SPSaveGame.h"
#include "../../Game/SingleProgress/OverallSaveGame.h"
#include "../Widget/TemplatePreBattleMenu.h"
#include "../Widget/SimpleMenu.h"
#include "../Widget/TemplateNotification.h"
#include "../Widget/TEndMenu.h"
#include "../Widget/DialogTextMenu.h"
#include "../Widget/TCalendarMenu.h"
#include "../Widget/TemplateEventSystem.h"
#include "../Widget/TSkillSelectMenu.h"
#include "../Widget/TRewardMenu.h"
#include "Engine/Texture2D.h"
#include "../../Game/SingleProgress/ShadowActor.h"
#include "../../Game/SingleProgress/AnimBook.h"
#include "../../Game/SingleProgress/EventNodeManager.h"
#include "../Widget/TTutorialMenu.h"
#include "../Widget/TTransitionMenu.h"
#include "SingleProgressPlayerController.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FSAOccupyInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 occupyRadiusPercent;
};

UCLASS()
class COLLISIONWAR_API ASingleProgressPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void GetControl();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PauseOrUnPauseGame();

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

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealLeftClickDownEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealScrollEvent(bool upOrDown);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealTickEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealLeftClickUpEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DealRightClickDownEvent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SaveGame(FString slotName, int32 index);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SaveProgressInfo(FString slotName, bool isNewSlot);

	/** loadtype标识了读取的种类
	* 0. 正常读取
	* 1. 战斗结束读取
	* 2. 切换场景读取
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void LoadGame(FString slotName, int32 index, uint8 loadType);

	void ApplyLoadDynamic();

	UFUNCTION()
	void WaitToLoad();

	void ApplyBackToMainMenu();

	UFUNCTION()
	void WaitToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	virtual void WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PressRuneKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PressEndRuneKey();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void CaptureScene();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTutorial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AddTestCard(const TArray<FString>& cardNames);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetTestAttribute(int32 hp, int32 atk, int32 dfc);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyShakeCamera();
		
	/** 与SPGM中一样，用于记录当前游戏模式
	*/
	uint8 m_gameState = 0;

	UPROPERTY()
	FString m_nextMenuName;

	UPROPERTY()
		bool m_isPressLeftKey = false;
	UPROPERTY()
		bool m_isPressRightKey = false;
	UPROPERTY()
		bool m_isPressUpKey = false;
	UPROPERTY()
		bool m_isPressDownKey = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_movableLBPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_theorizeMovableLBPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_diceMovableLBPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_movableRTPoin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_theorizeMovableRTPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_diceMovableRTPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_scrollBottomZ = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_scrollTopZ = 2500;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_HMoveV = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_VMoveV = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_scrollDeltaZ = 10;

	FVector m_mouseClickDownLoc;

	float m_dragCardZ = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_mouseHitTolerence = 5;

	UPROPERTY()
	UPrimitiveComponent* m_pMouseClickDownHitComponent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USPSaveGame* m_pSPSaveGameObject;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UOverallSaveGame* m_pOverallSaveGameObject;

	FTimerHandle m_runeSwitchTimerHandler;

	FTimerHandle m_hoverSkillIconTimerHandler;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_waitToLoadTime = 0.5;

	FString m_waitToLoadSlotName;

	FTimerHandle m_waitToLoadTimerHandler;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UPostProcessComponent* m_pPPComponent;

	bool m_isInTutorial = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_blendViewTargetTime = 1.f;

	UPROPERTY()
	AEventCard* m_pPointingEventCard;
	/************************************************************************/
	/* UI部分
	/************************************************************************/
	/** 切换UI
	* 0 = 切换到SPMenu
	* 1 = 切换到DiceMenu
	* 2 = 切换到DecipherMenu
	* 3 = 切换到抽卡menu
	* 4 = 切换到交易Menu
	*/
	void SwitchMenu(uint8 menuState);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadSPMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadDiceBattleMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadDecipherMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadDrawCardMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadTradingMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadShadowModeMenu();

	void LoadTutorialSerialMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyLoadRuneMenu();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyLoadEventMenu();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void LoadRuneMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, FString chSkillDomainTitle, FString skillDomainTitle,
			FString chWormDomainTitle, FString wormDomainTitle, FString chCombineDomainTitle, FString combineDomainTitle, FString chNumericDomainTitle, FString numericDomainTitle);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void LoadCardCombineListMenu(UWidgetManager* pWidgetManager, FString chExploreTitle, FString enExploreTitle, FString chCommunicationTitle, FString enCommunicationTitle, FString chForgeTitle, FString enForgeTitle, FString chResearchTitle, FString enResearchTitle,
			FString consumeTitle, FString lifeTitle, FString energyTitle, FString activityTitle, FString darknessTitle, FString mentalityTitle, FString moneyTitle,
			FString suppressionTitle, FString flameTitle, FString sunTitle, FString chconsumeTitle, FString chlifeTitle, FString chenergyTitle, FString chactivityTitle, FString chdarknessTitle, FString chmentalityTitle, FString chmoneyTitle,
			FString chsuppressionTitle, FString chflameTitle, FString chsunTitle);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DeleteMenu(const FString& menuName);

	void LoadExtraBounusCard(const TArray<FString>& mustBonus, uint8 type);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void ReadCharacterAppearanceInfo(const FString& characterName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void WriteCharacterAppearanceInfo(const FCharacterAppearanceInfo& appearanceInfo);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void LoadEndSPMenu(int32 curProgress);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void LoadSimpleMenu(FString chSaveText, FString enSaveText);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void LoadTutorialmenu();

	void LoadSkillSelectMenu();

	/** 展示字符
	* 0 - dice胜利
	* 1 - dice失败
	* 2 - theorize胜利
	* 3 - theorize失败
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyLoadDemoWords(uint8 type, bool chOrEn);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadMustBonusCardTexture();

	/** 用以读取一些前缀词句，如选择事件选择后会获得卡牌这时需要展示文字，就需要一些修饰词句
	* 0. 代表选择事件进行选择后的时候
	* 1. GetEventCard
	* 2. GetRandDiceSkillCard
	* 3. GetRandTheorizeSkillCard
	* 4. GetRandWeapon
	* 5. IncreaseMoney
	* 6. IncreaseMaxHp
	* 7. IncreaseAtk
	* 8. IncreaseMaxDfc
	* 9. LoseWeapon
	* 10. GetRandEventCard
	* 11. LoseEventCard
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FString ReadDemoWordPrefix(uint8 type, bool chOrEn);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	bool TellWhetherHitSkillTree(FVector2D hitLoc);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTActionPanel* m_pActionPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateSingleProgressMenu* m_pSPMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTCardSelectMenu* m_pCardSelectMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateRunesMenu* m_pRuneMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTCardCombineListMenu* m_pCardCombineListMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplatePreBattleMenu* m_pSaveMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TArray<FCharacterAppearanceInfo> m_characterAppearanceInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USimpleMenu* m_pPauseMenu;

	UPROPERTY()
	UTemplateNotification* m_pNotificationMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTEndMenu* m_pEndMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UDialogTextMenu* m_pTutorialMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTSkillSelectMenu* m_pSkillSelectMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTRewardMenu* m_pRewardMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTTutorialMenu* m_pTutorialSerialMenu;

	UTTransitionMenu* m_pTransitionMenu;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTTutorialMenu> m_pTutorialMenuClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UTexture*> m_pMustBonusCardTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FChAndEnDescription> m_mustBonusDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isWidgetClick = false;

	bool m_isPauseMenuOn = false;

	bool m_hasShownActionNodeDescription = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_skillTreeTopLeftCorner;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_skillTreeRightBottomCorner;
	/************************************************************************/
	/* SP游戏逻辑部分
	/************************************************************************/
	UPROPERTY()
	AEventCard* m_pCurSelectEventCard;

	UPROPERTY()
	APlayCard* m_pCurSelectPlayCard;

	
	/************************************************************************/
	/* DiceBattle逻辑部分
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DropDiceSkillCard();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FDiceBattleSkillInfo> m_dicSkillMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTBattleLineMenu* m_pDiceBattleMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTActionCard* m_pSelectDiceBattleSkill;

	FString m_curDragSkillName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FDiceBattleAndTheorizeSkillInfo> m_allDiceBattleSkillInfos;

	TArray<FString> m_curTheorizeSkills;

	float m_curDiceSkillLeftTime = 0;
	/************************************************************************/
	/* 推理猜牌逻辑部分
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DropDecipherCard();

	UPROPERTY()
	UTActionCard* m_pSelectTheorizeCard;

	UPROPERTY()
	ANumericCard* m_pCurSelectTheorizeNumericCard;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTDecipherMenu* m_pTheorizeMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FDiceBattleAndTheorizeSkillInfo> m_alltheorizeSkillInfos;

	TArray<FString> m_curDiceSkills;
	/************************************************************************/
	/* 抽卡逻辑部分
	/************************************************************************/
	UPROPERTY()
	UTDrawCardMenu* m_pDrawCardMenu;

	/************************************************************************/
	/* 购买卡牌部分
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTShopMenu* m_pShopMenu;

	/************************************************************************/
	/* 暗影模式部分
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void NormalModeToShadowMode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ShadowModeToNormalMode();

	bool CheckWhetherAbleToBuildShadowActor(FVector cursorLoc);

	UPROPERTY(EditDefaultsOnly, Category = "ColllisionWar")
	TSubclassOf<class AActor> m_SAOccupyInfoActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "ColllisionWar")
	int32 m_occupyActorRadius;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, int32> m_allSAOccupyInfos;

	FString m_curSelectSAOccupyInfo;

	UPROPERTY()
	AShadowActor* m_pSAOccupyInfoActor;

	UPROPERTY()
	AShadowActor* m_pSelectShadowActor;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTShadowModeMenu* m_pShadowModeMenu;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_shadowActorSpawnDelayTime = 1.f;

	FTimerHandle m_shadowModeTimerHandle;
	/************************************************************************/
	/* 事件部分
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTCalendarMenu* m_pEventMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateEventSystem* m_pMissionMenu;
	/************************************************************************/
	/* Control Animation Book
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupBookControl(AAnimBook* pAnimBook);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void MoveBookToPlayer(bool returnBook);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPlayMoveBookTimeLine(bool returnBook);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateMoveBook(float time);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FinishMoveBook();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTimelineComponent* m_pMoveToCamera;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USceneComponent* m_pDestinationLocation;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pOriginLocation;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pOffsetLocation;

	AAnimBook* m_pAnimBook;

	UEventNodeManager* m_pEventNodeManager;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_bookDisFromCam;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FRotator m_bookViewAngle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_bookOriginOpenAmount = 0.f;

	bool m_moveEnded = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_openBookHowWide = 0.8;
};
