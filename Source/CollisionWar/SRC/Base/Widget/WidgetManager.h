// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Image.h"
#include "WidgetManager.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	WidgetType_null,
	WidgetType_button,
	WidgetType_invisibleButton,
	WidgetType_scrollBox,
	WidgetType_inputText,
	WidgetType_textLine,
	WidgetType_comboBox,
	WidgetType_checkBox,
	WidgetType_spacer,
	WidgetType_chatBox,
	WidgetType_friendListMenu,
	WidgetType_selectFriendMenu,
	WidgetType_playerDetail,
	WidgetType_notification,
	WidgetType_playerTag,
	WidgetType_progressSlider,
	WidgetType_rankInfo,
	WidgetType_ensureEnterRoomMenu,
	WidgetType_playerConclude,
	WidgetType_skillTree,
	WidgetType_skillTreeIcon,
	WidgetType_characterStatus,
	WidgetType_runeMenu,
	WidgetType_cardCombineListMenu,
	WidgetType_runeElement,
	WidgetType_loginMenu,
	WidgetType_CombineElement,
	WidgetType_ItemMenu,
	WidgetType_InventoryMenu,
	WidgetType_MenuTitle,
	WidgetType_physActorPopButton,
	WidgetType_physActorTradeMenu,
	WidgetType_BattleLineMenu,
	WidgetType_DecipherMenu,
	WidgetType_CardInfoMenu,
	WidgetType_GeneralCard,
	WidgetType_TradeMenu,
	WidgetType_TradeCard,
	WidgetType_TradeItemSelectMenu,
	WidgetType_SingleCardMenu,
	WidgetType_AltarMenu,
	WidgetType_ActionPanel,
};

UENUM(BlueprintType)
enum class EWidgetTheme : uint8
{
	WT_normal,
};

UENUM(BlueprintType)
enum class EInvisibleButtonLocation : uint8
{
	IBL_ScrollMenu_NULL,
	IBL_ScrollMenu_PreBattleMenu,
	IBL_TopMenu_PreBattleMenu,
	IBL_Others_PreBattleMenu,
	IBL_TopMenu_SelectBattleMenu,
	IBL_TopMenu_MainMenu,
	IBL_SideMenu_MainMenu,
};

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	ST_HSlot,
	ST_VSlot,
	ST_SSlot,
	ST_CSlot,
	ST_OSlot,
};

UENUM(BlueprintType)
enum class EDrawType : uint8
{
	DT_Null,
	DT_Box,
	DT_Border,
	DT_Image
};

UENUM(BlueprintType)
enum class ESizeRule : uint8
{
	SR_Automatic,
	SR_Fill,
};

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	MT_SimpleMenu,
	MT_MainMenu,
	MT_PreBattleMenu,
	MT_SelectMapMenu,
	MT_BattleMenu,
};

UENUM(BlueprintType)
enum class EHorizontalAlignmentType : uint8
{
	HAT_Fill,
	HAT_Left,
	HAT_Right,
	HAT_Center,
};

UENUM(BlueprintType)
enum class ELevelStage : uint8
{
	LS_LoginMenu,
	LS_MainMenu,
	LS_PreBattleMenu,
	LS_SelectMapMenu,
	LS_BattleMenu,
};

USTRUCT(BlueprintType, Blueprintable)
struct FBasicInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FSlateColor themeColorNormal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FSlateColor themeColorHover;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FSlateColor themeColorExtra;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor themeColorDisable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textHeaderFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textHeaderChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor textHeaderColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textFooterFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textFooterChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor textFooterColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textElementFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textChineseElementFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor textElementColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textAndCaptionFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo textAndCaptionChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor textAndCaptionColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo firstClassFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo firstClassChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor firstClassColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo secondClassFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo secondClassChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor secondClassColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo thirdClassFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo thirdClassChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor thirdClassColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo fourthClassFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateFontInfo fourthClassChineseFont;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor fourthClassColor;
};

USTRUCT(BlueprintType, Blueprintable)
struct FInputTextInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTexture* pBGTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FVector2D size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	EDrawType drawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FMargin imageMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FMargin padding;
};

USTRUCT(BlueprintType, Blueprintable)
struct FButtonInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pBGTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pBorderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType drawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin imageMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin normalPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin pressedPadding;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCheckBoxInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pUncheckTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pCheckTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pUndetermineTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType drawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin padding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor foregroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor borderColor;
};

USTRUCT(BlueprintType, Blueprintable)
struct FComboBoxInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pComboBGTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D bgImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType bgDrawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin bgMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pArrowTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D arrowImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin arrowMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType arrowDrawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pBorderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D borderSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin borderMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType borderDrawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FMargin normalPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FMargin pressedPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FMargin menuBorderPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor itemBGColor;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSliderInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pBarTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D barImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType barDrawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor barNormalTint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor barDisableTint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTexture* pThumbTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FVector2D thumbSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EDrawType thumbDrawAs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor thumbNormalTint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSlateColor thumbDisableTint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	float barThickness;
};

USTRUCT(BlueprintType, Blueprintable)
struct FThemeInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		EWidgetTheme theme;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FBasicInfo basicTheme;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FButtonInfo buttonInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FInputTextInfo inputTextInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FComboBoxInfo comboBoxInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FCheckBoxInfo checkBoxInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FSliderInfo sliderInfo;
};

class UTemplateInvisibleButton;
class UTemplateColumn;
class UTemplatePlayerDetail;
class UTemplate_Button;
class UTemplateSpacer;
class UTemplateProgressSlider;
class UTemplateItemElement;

UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void MenuFadeOutDone(FString menuName);

	/** Callback Function Domain
	*/
	void ButtonClickCallback(FString buttonFunction);

	virtual	void InvisibleButtonClickCallback(FString buttonFunction, EInvisibleButtonLocation location) {};

	virtual void InputTextCommitCallback(FString text, FString function) {};

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetTheme(EWidgetTheme theme);

	/** Get InputText Properties
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetInputTextStyle(FSlateBrush& normalBrush, FSlateBrush& hoveredBrush, FSlateBrush& pressedBrush, FSlateBrush& disableBrush,
		FMargin& padding, FSlateFontInfo& font, FSlateColor& foreGroundColor, FSlateFontInfo& captionFont, FSlateColor& captionColor);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetButtonStyle(FSlateBrush& normalBrush, FSlateBrush& hoveredBrush, FSlateBrush& pressedBrush, FSlateBrush& disableBrush,
		FSlateBrush& borderBrush, FMargin& normalPadding, FMargin& pressedPadding, FSlateFontInfo& buttonTextFont, FSlateColor& buttonTextColor);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetComboBoxStyle(FComboButtonStyle& comboButtonStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetCheckBoxStyle(FCheckBoxStyle& checkBoxStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetSliderStyle(FSliderStyle& sliderStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void GetElementTextStyle(FSlateFontInfo& font, FSlateColor& color);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TArray<FThemeInfo> m_allThemeData;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	EWidgetTheme m_theme;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CollisionWar/Widget")
	FBasicInfo m_basicInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FInputTextInfo m_inputTextInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FButtonInfo m_buttonInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FCheckBoxInfo m_checkBoxInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FComboBoxInfo m_comboBoxInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FSliderInfo m_sliderInfo;

	/** All default bp widget class
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateInvisibleButton> m_BPInvisibleButtonClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateColumn> m_BPColumnClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplatePlayerDetail> m_BPPlayerDetailClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplatePlayerTag> m_BPPlayerTagClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplate_Button> m_BPButtonClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateScrollBox> m_BPScrollBoxClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateSpacer> m_BPSpacerClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
		TSubclassOf<class UTemplateScrollBoxWrapper> m_BPWrapperClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
		TSubclassOf<class UTemplateTextLine> m_BPTextLineClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
		TSubclassOf<class UTemplateProgressSlider> m_BPProgressSliderClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TSubclassOf<class UTemplateItemElement> m_BPItemElementClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	TMap<FString, TSubclassOf<class UUserWidget> > m_widgetClassMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterialInstance* m_pSkillIconButtonMat;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterialInstance* m_pActivateEffectInfoMat;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterialInstance* m_dissolveUIMat;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pBattleSkillCardDefaultTex;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_pColorTextureMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UTexture2D*> m_pAttributeTextureMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_yearStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_monthStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_dayStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_hourStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_minStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chyearStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chmonthStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chdayStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chhourStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chminStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_saveDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chsaveDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_language;
};
