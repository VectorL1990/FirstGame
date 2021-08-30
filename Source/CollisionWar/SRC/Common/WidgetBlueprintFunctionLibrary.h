// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "HorizontalBoxSlot.h"
#include "VerticalBoxSlot.h"
#include "SizeBoxSlot.h"
#include "CanvasPanelSlot.h"
#include "OverlaySlot.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "../Base/Widget/Template_Button.h"
#include "../Base/Widget/TemplateScrollBoxWrapper.h"
#include "../Base/Widget/TemplateInvisibleButton.h"
#include "../Base/Widget/TemplateSpacer.h"
#include "../Base/Widget/TemplateInputText.h"
#include "../Base/Widget/TemplateRow.h"
#include "../Base/Widget/TemplateCheckBox.h"
#include "../Base/Widget/TemplateTextLine.h"
#include "../Base/Widget/TemplateNotification.h"
#include "../Base/Widget/TemplateNotificationShowUpButton.h"
#include "../Base/Widget/WidgetManager.h"
#include "../Base/Widget/SimpleMenu.h"
#include "../Base/Widget/TemplateMainMenu.h"
#include "../Base/Widget/TemplatePreBattleMenu.h"
#include "../Base/Widget/TemplateFriendListMenu.h"
#include "../Base/Widget/TemplateRuneElement.h"
#include "../Base/Widget/TemplateRunesMenu.h"
#include "../Base/Widget/TemplateSkillTreeIcon.h"
#include "../Base/Widget/TemplatePlayerTag.h"
#include "../Base/Widget/TemplatePlayerConclude.h"
#include "../Base/Widget/TemplateLoginMenu.h"
#include "../Base/Widget/TemplateCharacterInfo.h"
#include "../Base/Widget/TemplateCharacterStateElement.h"
#include "../Base/Widget/TemplateItemElement.h"
#include "../Base/Widget/TCombineElement.h"
#include "../Base/Widget/TPhysActorPopMenu.h"
#include "../Base/Widget/PhysActorPopButton.h"
#include "../Base/Widget/TBattleLineMenu.h"
#include "../Base/Widget/TDecipherMenu.h"
#include "../Base/Widget/TemplateSingleProgressMenu.h"
#include "../Base/Widget/TCardInfoMenu.h"
#include "../Base/Widget/TGeneralCard.h"
#include "../Base/Widget/TSkillSelectIcon.h"
#include "../Base/Widget/TActionPanel.h"
#include "../Base/Widget/TCardSelectMenu.h"
#include "../Base/Widget/TShopMenu.h"
#include "../Base/Widget/TShadowModeMenu.h"
#include "../Base/Widget/TSkillSelectIcon.h"
#include "../Base/Widget/TSkillTreeIcon.h"
#include "../Base/Widget/TCardCombineListMenu.h"
#include "../Base/Widget/TEndMenu.h"
#include "../Game/SingleProgress/ActionCard.h"
#include "../Game/SingleProgress/EventCard.h"
#include "../Base/Widget/DialogTextMenu.h"
#include "../Base/Widget/TCalendarMenu.h"
#include "../Base/Widget/TSkillSelectMenu.h"
#include "../Base/Widget/TRewardMenu.h"
#include "../Game/Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UWidgetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** General Function
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void SetPad(UWidget* pWidget, ESlotType slotType, float leftPad, float topPad, float rightPad, float bottomPad);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void SetSlateSize(UWidget* pWidget, ESlotType slotType, ESizeRule sizeRule, float size);

	/** Simple Menu Domain
	* this domain contains all functions for simpleMenu
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static USimpleMenu* CreateSimpleMenu(UWidgetManager* pWidgetManager, uint8 phase, uint8 doamin);

	/** Set Property To Widgets
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void ApplyThemeToElement(UWidgetManager* pWidgetManager, UUserWidget* pWidget, EWidgetType widgetType);

	/** Main menu domain functions
	*/
	static UTemplateMainMenu* CreateMainMenu(UWidgetManager* pWidgetManager, uint8 domain);

	/** PreBattleMenu Domain Functions
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTemplatePreBattleMenu* CreatePreBattleMenu(UWidgetManager* pWidgetManager, uint8 type);

	/************************************************************************/
	/* BattleMenu Related Functions
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTemplateBattleElementSystem* CreateBattleMenu(UObject* pWorldContextObject, UWidgetManager* pWidgetManager);

	//static void AddEnermyInfoToBattleMenu(uint8 race, FString enermyName, TArray<FString> stateList, UTemplateBattleElementSystem* pBattleMenu);

	/*static void RemoveEnermyCardInfoFromBattleMenu(FString enermyName, const TArray<FString>& deleteEnermyStateList, 
		const TArray<FString>& allStatesExcludeDeleteEnermy, UTemplateBattleElementSystem* pBattleMenu);*/

	/************************************************************************/
	/* Skill tree related functions
	/************************************************************************/
	
	/** Character status menu domain functions
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTemplateCharacterStatus* CreateCharacterStatusMenu(UWidgetManager* pWidgetManager);

	/** Rune menu domain functions
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTemplateRunesMenu* CreateRuneMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, FString chSkillDomainTitle, FString skillDomainTitle,
		FString chWormDomainTitle, FString wormDomainTitle, FString chCombineDomainTitle, FString combineDomainTitle, FString chNumericDomainTitle, FString numericDomainTitle);

	/** Card Combine List menu domain functions
	*/
	static UTCardCombineListMenu* CreateCardCombineListMenu(UWidgetManager* pWidgetManager, FString chExploreTitle, FString enExploreTitle, FString chCommunicationTitle, FString enCommunicationTitle, FString chForgeTitle, FString enForgeTitle, FString chResearchTitle, FString enResearchTitle,
		FString consumeTitle, FString lifeTitle, FString energyTitle, FString activityTitle, FString darknessTitle, FString mentalityTitle, FString moneyTitle,
		FString suppressionTitle, FString flameTitle, FString sunTitle, FString chconsumeTitle, FString chlifeTitle, FString chenergyTitle, FString chactivityTitle, FString chdarknessTitle, FString chmentalityTitle, FString chmoneyTitle,
		FString chsuppressionTitle, FString chflameTitle, FString chsunTitle);

	/** Login menu domain functions
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTemplateLoginMenu* CreateLoginMenu(UWidgetManager* pWidgetManager);

	/************************************************************************/
	/* CharacterInfo menu domain
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void AddStateElementToCharacterInfoBar(UObject* pWorldContextObject, UTemplateCharacterInfo* pInfo, FString stateName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void RemoveStateElementFromCharacterInfoBar(UTemplateCharacterInfo* pInfo, FString stateName);
	
	/************************************************************************/
	/* BattleLine Menu Domain Functions
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTBattleLineMenu* CreateBattleLineMenu(UObject* pObject, UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle);

	/************************************************************************/
	/* Decipher Menu Domain Functions
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTDecipherMenu* CreateDecipherMenu(UObject* pObject, UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle);

	/************************************************************************/
	/* Card Select Menu Domain Functions
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTCardSelectMenu* CreateCardSelectMenu(UWidgetManager* pWidgetManager);

	/************************************************************************/
	/* SingleProgress Menu Domain Functions
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		static UTemplateSingleProgressMenu* CreateSingleProgressMenu(UObject* pObject, UWidgetManager* pWidgetManager,
			FString durabilityNbTitle, FString chDurabilityNbTitle);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static UTCardInfoMenu* CreateCardInfoMenu(UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle);
/*

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	static void AddSkillIconToCardInfoMenu(UTCardInfoMenu* pCardInfoMenu, UTexture* pTexture, FString chineseText, FString englishText, FVector2D loc, FString iconName);
*/

	/************************************************************************/
	/* ActionCard Domain Functions
	/************************************************************************/

	static UTActionPanel* CreateActionPanel(UWidgetManager* pWidgetManager, UEventNodeManager* pEventNodeManager, uint8 actionType);

	/************************************************************************/
	/* Singleprogress Shop Menu Domain Functions
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static UTShopMenu* CreateShopMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle);

	/************************************************************************/
	/* ShadowMode Menu Domain Functions
	/************************************************************************/
	static TArray<UTexture2D*> LoadTexture2D(FString path);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		static UTShadowModeMenu* CreateShadowModeMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, FString chDeleteButtonStr,
			FString enDeleteButtonStr, FString lifeSlopeTitle, FString energySlopeTitle, FString activitySlopeTitle, FString darknessSlopeTitle, FString flameSlopeTitle,
			FString mentalitySlopeTitle, FString moneySlopeTitle, FString sunSlopeTitle, FString suppressionSlopeTitle, FString lifeMaxTitle, FString energyMaxTitle,
			FString activityMaxTitle, FString darknessMaxTitle, FString flameMaxTitle, FString mentalityMaxTitle, FString moneyMaxTitle, FString sunMaxTitle, FString suppressionMaxTitle,
			FString chlifeSlopeTitle, FString chenergySlopeTitle, FString chactivitySlopeTitle, FString chdarknessSlopeTitle, FString chflameSlopeTitle,
			FString chmentalitySlopeTitle, FString chmoneySlopeTitle, FString chsunSlopeTitle, FString chsuppressionSlopeTitle, FString chlifeMaxTitle, FString chenergyMaxTitle,
			FString chactivityMaxTitle, FString chdarknessMaxTitle, FString chflameMaxTitle, FString chmentalityMaxTitle, FString chmoneyMaxTitle, FString chsunMaxTitle, FString chsuppressionMaxTitle,
			FString changeIntervalTitle, FString chChangeIntervalTitle);

	static void ScanDirectory(TArray<FString>& Files, FString FilePath);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static UTEndMenu* CreateEndMenu(UWidgetManager* pWidgetManager);
	/************************************************************************/
	/* Tutorial Menu Domain
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static UDialogTextMenu* CreateTutorialMenu(UWidgetManager* pWidgetManager, uint8 state);

	/************************************************************************/
	/* Event Menu
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		static UTCalendarMenu* CreateCalendarMenu(UWidgetManager* pWidgetManager);

	/************************************************************************/
	/* SkillSelect Menu
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static UTSkillSelectMenu* CreateSkillSelectMenu(UWidgetManager* pWidgetManager);

	/************************************************************************/
	/* Reward Menu
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	static UTRewardMenu* CreateRewardMenu(UWidgetManager* pWidgetManager);
};
