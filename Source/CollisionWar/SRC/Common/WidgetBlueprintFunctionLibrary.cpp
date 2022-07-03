// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Base/CollisionWarGameInstance.h"
#include "../Game/CWBaseGameMode.h"
#include "../Base/Login/LoginPlayerController.h"
#include "../Base/BasePlayerController.h"
#include "../Base/SingleProgress/SingleProgressPlayerController.h"
//#include "../Base/MainMenu/MainMenuPlayerController.h"
//#include "../Base/PreBattle/PreBattlePlayerController.h"
//#include "../Base/ChooseMap/ChooseMapPlayerController.h"
#include "../Base/Battle/BattleLevelPlayerController.h"
#include "../Game/CWBaseGameMode.h"
#include "../Game/Login/LoginGameModeBase.h"
//#include "../Game/MainMenu/MainMenuGameMode.h"
//#include "../Game/PreBattle/PreBattleGameMode.h"
//#include "../Game/ChooseMap/ChooseMapGameModeBase.h"
#include "../Game/BattleLevelGameModeBase.h"
#include "../Game/SingleProgress/SingleProgressGameMode.h"
#include "CollisionWarBpFunctionLibrary.h"
#include "UniformGridSlot.h"
#include "GridSlot.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h" 
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "WidgetBlueprintFunctionLibrary.h"


void UWidgetBlueprintFunctionLibrary::SetPad(UWidget* pWidget, ESlotType slotType, float leftPad, float topPad, float rightPad, float bottomPad)
{
	if (!pWidget || !pWidget->Slot) return;
	if (slotType == ESlotType::ST_HSlot)
	{
		UHorizontalBoxSlot * pHSlot = Cast<UHorizontalBoxSlot>(pWidget->Slot);
		if (!pHSlot) return;
		pHSlot->SetPadding(FMargin(leftPad, topPad, rightPad, bottomPad));
	}
	else if (slotType == ESlotType::ST_VSlot)
	{
		UVerticalBoxSlot * pVSlot = Cast<UVerticalBoxSlot>(pWidget->Slot);
		if (!pVSlot) return;
		pVSlot->SetPadding(FMargin(leftPad, topPad, rightPad, bottomPad));
	}
	else if (slotType == ESlotType::ST_SSlot)
	{
		USizeBoxSlot * pSSlot = Cast<USizeBoxSlot>(pWidget->Slot);
		if (!pSSlot) return;
		pSSlot->SetPadding(FMargin(leftPad, topPad, rightPad, bottomPad));
	}
	else if (slotType == ESlotType::ST_OSlot)
	{
		UOverlaySlot * pOSlot = Cast<UOverlaySlot>(pWidget->Slot);
		if (!pOSlot) return;
		pOSlot->SetPadding(FMargin(leftPad, topPad, rightPad, bottomPad));
	}
}

void UWidgetBlueprintFunctionLibrary::SetSlateSize(UWidget* pWidget, ESlotType slotType, ESizeRule sizeRule, float size)
{
	if (!pWidget || !pWidget->Slot) return;
	FSlateChildSize slateSize;
	slateSize.Value = size;
	if (sizeRule == ESizeRule::SR_Automatic)
		slateSize.SizeRule = ESlateSizeRule::Automatic;
	else
		slateSize.SizeRule = ESlateSizeRule::Fill;

	if (slotType == ESlotType::ST_HSlot)
	{
		UHorizontalBoxSlot * pHSlot = Cast<UHorizontalBoxSlot>(pWidget->Slot);
		if (!pHSlot) return;
		pHSlot->SetSize(slateSize);
	}
	else if (slotType == ESlotType::ST_VSlot)
	{
		UVerticalBoxSlot * pVSlot = Cast<UVerticalBoxSlot>(pWidget->Slot);
		if (!pVSlot) return;
		pVSlot->SetSize(slateSize);
	}
}

USimpleMenu* UWidgetBlueprintFunctionLibrary::CreateSimpleMenu(UWidgetManager* pWidgetManager, uint8 phase, uint8 doamin)
{
	if (!pWidgetManager) return NULL;
	//生成Widget
	USimpleMenu* pSimpleMenu = NULL;
	if (doamin == 0)
		pSimpleMenu = CreateWidget<USimpleMenu>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["SimpleMenu"]);
	else if (doamin == 1)
		pSimpleMenu = CreateWidget<USimpleMenu>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["BattleSimpleMenu"]);
	
	//对一般变量进行赋值
	pSimpleMenu->m_pWidgetManager = pWidgetManager;
	pSimpleMenu->NotifyInitial();
	pSimpleMenu->m_curPhase = phase;
	pSimpleMenu->m_domain = doamin;
	pSimpleMenu->NotifyFirstSwitchPhase();

	return pSimpleMenu;
}

void UWidgetBlueprintFunctionLibrary::ApplyThemeToElement(UWidgetManager* pWidgetManager, UUserWidget* pWidget, EWidgetType widgetType)
{
	if (!pWidget || !pWidgetManager) return;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	if (widgetType == EWidgetType::WidgetType_button)
	{
		UTemplate_Button* pButton = Cast<UTemplate_Button>(pWidget);
		if (!pButton) return;
		FButtonStyle buttonStyle;
		FSlateBrush normalBrush;
		FSlateBrush hoveredBrush;
		FSlateBrush pressedBrush;
		FSlateBrush disableBrush;
		FSlateBrush borderBrush;
		FMargin normalPadding;
		FMargin pressPadding;
		FSlateFontInfo buttonTextFont;
		FSlateColor buttonTextColor;
		pWidgetManager->GetButtonStyle(normalBrush, hoveredBrush, pressedBrush, disableBrush, borderBrush, normalPadding,
			pressPadding, buttonTextFont, buttonTextColor);
		pButton->m_pButton->WidgetStyle.Normal = normalBrush;
		pButton->m_pButton->WidgetStyle.Hovered = hoveredBrush;
		pButton->m_pButton->WidgetStyle.Pressed = pressedBrush;
		pButton->m_pButton->WidgetStyle.Disabled = disableBrush;
		pButton->m_pButton->WidgetStyle.SetNormalPadding(normalPadding);
		pButton->m_pButton->WidgetStyle.SetPressedPadding(pressPadding);
		pButton->m_pBorderImage->SetBrush(borderBrush);
		if (pButton->m_pCaption)
		{
			pButton->m_pCaption->SetFont(buttonTextFont);
			pButton->m_pCaption->SetColorAndOpacity(buttonTextColor);
		}
	}
	else if (widgetType == EWidgetType::WidgetType_invisibleButton)
	{
		UTemplateInvisibleButton * pInvisibleButton = Cast<UTemplateInvisibleButton>(pWidget);
		if (!pInvisibleButton || !pInvisibleButton->m_pButtonText) return;
		if (pWidgetManager->m_language == "Chinese")
			pInvisibleButton->m_pButtonText->SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		else
			pInvisibleButton->m_pButtonText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pInvisibleButton->m_pButtonText->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
	}
	else if (widgetType == EWidgetType::WidgetType_inputText)
	{
		UTemplateInputText * pInputText = Cast<UTemplateInputText>(pWidget);
		if (!pInputText || !pInputText->m_pEditBox || !pInputText->m_pCaption) return;
		FEditableTextBoxStyle widgetStyle;
		FSlateBrush normalBrush;
		FSlateBrush hoveredBrush;
		FSlateBrush pressedBrush;
		FSlateBrush disableBrush;
		FMargin padding;
		FSlateFontInfo font;
		FSlateColor foreGroundColor;
		FSlateFontInfo captionFont;
		FSlateColor captionColor;
		pWidgetManager->GetInputTextStyle(normalBrush, hoveredBrush, pressedBrush, disableBrush, padding, font, foreGroundColor, captionFont, captionColor);
		widgetStyle.BackgroundImageNormal = normalBrush;
		widgetStyle.BackgroundImageHovered = hoveredBrush;
		widgetStyle.BackgroundImageFocused = pressedBrush;
		widgetStyle.BackgroundImageReadOnly = disableBrush;
		widgetStyle.Padding = padding;
		widgetStyle.Font = font;
		widgetStyle.ForegroundColor = foreGroundColor;
		if (!pInputText->m_pEditBox) return;
		pInputText->m_pEditBox->WidgetStyle = widgetStyle;
		if (!pInputText->m_pCaption) return;
		pInputText->m_pCaption->SetFont(captionFont);
		pInputText->m_pCaption->SetColorAndOpacity(captionColor);
	}
	else if (widgetType == EWidgetType::WidgetType_checkBox)
	{
		UTemplateCheckBox * pCheckBox = Cast<UTemplateCheckBox>(pWidget);

		FCheckBoxStyle checkBoxStyle;
		FSlateFontInfo captionFont;
		FSlateColor captionColor;
		pWidgetManager->GetCheckBoxStyle(checkBoxStyle, captionFont, captionColor);
		if (pCheckBox->m_pCheckBox)
		{
			pCheckBox->m_pCheckBox->WidgetStyle = checkBoxStyle;
		}
		if (pCheckBox->m_pCaption)
		{
			pCheckBox->m_pCaption->SetFont(captionFont);
			pCheckBox->m_pCaption->SetColorAndOpacity(captionColor);
		}
	}
	else if (widgetType == EWidgetType::WidgetType_textLine)
	{
		UTemplateTextLine * pTextLine = Cast<UTemplateTextLine>(pWidget);

		FCheckBoxStyle checkBoxStyle;
		FSlateFontInfo font;
		FSlateColor color;
		pWidgetManager->GetElementTextStyle(font, color);
		if (pTextLine->m_pTextBlock)
		{
			pTextLine->m_pTextBlock->SetFont(font);
			pTextLine->m_pTextBlock->SetColorAndOpacity(color);
		}
	}
	else if (widgetType == EWidgetType::WidgetType_playerDetail)
	{
		UTemplatePlayerDetail* pPlayerDetailMenu = Cast<UTemplatePlayerDetail>(pWidget);
		if (!pPlayerDetailMenu) return;
		if (pPlayerDetailMenu->m_pPlayerNameCaption)
		{
			pPlayerDetailMenu->m_pPlayerNameCaption->SetFont(pWidgetManager->m_basicInfo.textElementFont);
			pPlayerDetailMenu->m_pPlayerNameCaption->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		}
		if (pPlayerDetailMenu->m_pPlayerNameText)
		{
			pPlayerDetailMenu->m_pPlayerNameText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
			pPlayerDetailMenu->m_pPlayerNameText->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		}
		if (pPlayerDetailMenu->m_pTotalWinCaption)
		{
			pPlayerDetailMenu->m_pTotalWinCaption->SetFont(pWidgetManager->m_basicInfo.textElementFont);
			pPlayerDetailMenu->m_pTotalWinCaption->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		}
		if (pPlayerDetailMenu->m_pTotalWinNbText)
		{
			pPlayerDetailMenu->m_pTotalWinNbText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
			pPlayerDetailMenu->m_pTotalWinNbText->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		}
	}
	else if (widgetType == EWidgetType::WidgetType_notification)
	{

	}
	else if (widgetType == EWidgetType::WidgetType_playerTag)
	{
		UTemplatePlayerTag* pPlayerTag = Cast<UTemplatePlayerTag>(pWidget);
		if (!pPlayerTag || !pWidgetManager) return;
		if (pPlayerTag->m_pPlayerName)
		{
			pPlayerTag->m_pPlayerName->SetFont(pWidgetManager->m_basicInfo.textElementFont);
			pPlayerTag->m_pPlayerName->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		}
	}
	else if (widgetType == EWidgetType::WidgetType_playerConclude)
	{
		UTemplatePlayerConclude* pPlayerConclude = Cast<UTemplatePlayerConclude>(pWidget);
		if (!pPlayerConclude || !pWidgetManager) return;
		pPlayerConclude->m_pPlayerNameText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pCaption1->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pCaption2->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pCaption3->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pCaption4->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pContent1->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pContent2->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pContent3->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		pPlayerConclude->m_pContent4->SetFont(pWidgetManager->m_basicInfo.textElementFont);

		pPlayerConclude->m_pCaption1->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pCaption2->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pCaption3->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pCaption4->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pContent1->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pContent2->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pContent3->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
		pPlayerConclude->m_pContent4->SetColorAndOpacity(pWidgetManager->m_basicInfo.textElementColor);
	}
	else if (widgetType == EWidgetType::WidgetType_skillTree)
	{
		
	}
	else if (widgetType == EWidgetType::WidgetType_skillTreeIcon)
	{
		UTSkillTreeIcon* pSkillTreeIcon = Cast<UTSkillTreeIcon>(pWidget);
		if (!pSkillTreeIcon || !pWidgetManager) return;
		if (pWidgetManager->m_language == "Chinese")
		{
			pSkillTreeIcon->m_pContentTextBox->WidgetStyle.SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		}
		else
		{
			pSkillTreeIcon->m_pContentTextBox->WidgetStyle.SetFont(pWidgetManager->m_basicInfo.textElementFont);
		}
		pSkillTreeIcon->m_pContentTextBox->WidgetStyle.ReadOnlyForegroundColor = pWidgetManager->m_basicInfo.textElementColor;
	}
	else if (widgetType == EWidgetType::WidgetType_characterStatus)
	{
		
	}
	else if (widgetType == EWidgetType::WidgetType_runeMenu)
	{
		UTemplateRunesMenu* pRunesMenu = Cast<UTemplateRunesMenu>(pWidget);
		if (!pRunesMenu || !pWidgetManager) return;

	}
	else if (widgetType == EWidgetType::WidgetType_runeElement)
	{
		UTemplateRuneElement* pElement = Cast<UTemplateRuneElement>(pWidget);
		if (!pElement || !pWidgetManager) return;


	}
	else if (widgetType == EWidgetType::WidgetType_cardCombineListMenu)
	{
		UTCardCombineListMenu* pMenu = Cast<UTCardCombineListMenu>(pWidget);
		if (!pMenu || !pWidgetManager) return;
		if (pWidgetManager->m_language == "Chinese")
		{
			pMenu->m_pAllCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassChineseFont);
			pMenu->m_pExploreCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassChineseFont);
			pMenu->m_pCommunicationCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassChineseFont);
			pMenu->m_pForgeCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassChineseFont);
			pMenu->m_pResearchCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassChineseFont);
			pMenu->m_pSearchText->WidgetStyle.Font = pWidgetManager->m_basicInfo.thirdClassChineseFont;
			pMenu->m_combineInfoFont = pWidgetManager->m_basicInfo.thirdClassChineseFont;
		}
		else
		{
			pMenu->m_pAllCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassFont);
			pMenu->m_pExploreCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassFont);
			pMenu->m_pCommunicationCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassFont);
			pMenu->m_pForgeCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassFont);
			pMenu->m_pResearchCombineInfoTitle->SetFont(pWidgetManager->m_basicInfo.thirdClassFont);
			pMenu->m_pSearchText->WidgetStyle.Font = pWidgetManager->m_basicInfo.thirdClassFont;
			pMenu->m_combineInfoFont = pWidgetManager->m_basicInfo.thirdClassFont;
		}
	}
	else if (widgetType == EWidgetType::WidgetType_loginMenu)
	{
		/*UTemplateLoginMenu* pLoginMenu = Cast<UTemplateLoginMenu>(pWidget);
		if (!pLoginMenu || !pWidgetManager) return;
		if (pCWGameInstance->m_language == "Chinese")
		{
			pLoginMenu->m_pTitleText->SetFont(pWidgetManager->m_basicInfo.firstClassChineseFont);
		}
		else
			pLoginMenu->m_pTitleText->SetFont(pWidgetManager->m_basicInfo.firstClassFont);*/
	}
	else if (widgetType == EWidgetType::WidgetType_CombineElement)
	{
		UTCombineElement* pCombineElement = Cast<UTCombineElement>(pWidget);
		if (!pCombineElement) return;
		if (pCWGameInstance->m_language == "Chinese")
			pCombineElement->m_pTextBlock->SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		else
			pCombineElement->m_pTextBlock->SetFont(pWidgetManager->m_basicInfo.textElementFont);
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		if (!pCombineElement->m_pButton || !pSingleton->m_itemTextureMap.Contains(pCombineElement->m_itemName)) return;
		UTexture2D* pTexture2D = pSingleton->m_itemTextureMap[pCombineElement->m_itemName];
		pCombineElement->m_pButton->WidgetStyle.Normal.SetResourceObject(pTexture2D);
		pCombineElement->m_pButton->WidgetStyle.Hovered.SetResourceObject(pTexture2D);
		pCombineElement->m_pButton->WidgetStyle.Pressed.SetResourceObject(pTexture2D);
		pCombineElement->m_pButton->WidgetStyle.Disabled.SetResourceObject(pTexture2D);
		pCombineElement->m_pButton->WidgetStyle.Normal.ImageSize.X = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Normal.ImageSize.Y = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Hovered.ImageSize.X = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Hovered.ImageSize.Y = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Pressed.ImageSize.X = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Pressed.ImageSize.Y = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Disabled.ImageSize.X = 32.f;
		pCombineElement->m_pButton->WidgetStyle.Disabled.ImageSize.Y = 32.f;
		FLinearColor linearColor(1, 1, 1, 1);
		FSlateColor color(linearColor);
		pCombineElement->m_pButton->WidgetStyle.Normal.TintColor = color;
		pCombineElement->m_pButton->WidgetStyle.Hovered.TintColor = color;
		pCombineElement->m_pButton->WidgetStyle.Pressed.TintColor = color;
		pCombineElement->m_pButton->WidgetStyle.Disabled.TintColor = color;
	}
	else if (widgetType == EWidgetType::WidgetType_MenuTitle)
	{
		UTemplateMenuTitle* pMenuTitle = Cast<UTemplateMenuTitle>(pWidget);
		if (!pMenuTitle || !pMenuTitle->m_pTitle) return;
		if (pCWGameInstance->m_language == "Chinese")
			pMenuTitle->m_pTitle->SetFont(pWidgetManager->m_basicInfo.textHeaderChineseFont);
		else
			pMenuTitle->m_pTitle->SetFont(pWidgetManager->m_basicInfo.textHeaderFont);
		pMenuTitle->m_pTitle->SetColorAndOpacity(pWidgetManager->m_basicInfo.textHeaderColor);
	}
	else if (widgetType == EWidgetType::WidgetType_physActorPopButton)
	{
		UPhysActorPopButton* pButton = Cast<UPhysActorPopButton>(pWidget);
		if (!pButton || !pButton->m_pTextBlock) return;
		if (pCWGameInstance->m_language == "Chinese")
			pButton->m_pTextBlock->SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		else
			pButton->m_pTextBlock->SetFont(pWidgetManager->m_basicInfo.textElementFont);
	}
	else if (widgetType == EWidgetType::WidgetType_BattleLineMenu)
	{
		UTBattleLineMenu* pMenu = Cast<UTBattleLineMenu>(pWidget);
		if (!pMenu || !pMenu->m_pWidgetManager || !pMenu->m_pEnsureButtonText) return;
		if (pCWGameInstance->m_language == "Chinese")
			pMenu->m_pEnsureButtonText->SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		else
			pMenu->m_pEnsureButtonText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
	}
	else if (widgetType == EWidgetType::WidgetType_DecipherMenu)
	{
		UTDecipherMenu* pMenu = Cast<UTDecipherMenu>(pWidget);
		if (!pMenu || !pMenu->m_pWidgetManager || !pMenu->m_pMenuTitle) return;
		ApplyThemeToElement(pMenu->m_pWidgetManager, pMenu->m_pMenuTitle, EWidgetType::WidgetType_MenuTitle);
	}
	else if (widgetType == EWidgetType::WidgetType_CardInfoMenu)
	{
		UTCardInfoMenu* pCardInfoMenu = Cast<UTCardInfoMenu>(pWidget);
		if (!pCardInfoMenu || !pCardInfoMenu->m_pWidgetManager || !pCardInfoMenu->m_pTitleText) return;
		if (pCWGameInstance->m_language == "Chinese")
			pCardInfoMenu->m_pTitleText->SetFont(pWidgetManager->m_basicInfo.textChineseElementFont);
		else
			pCardInfoMenu->m_pTitleText->SetFont(pWidgetManager->m_basicInfo.textElementFont);
	}
	else if (widgetType == EWidgetType::WidgetType_GeneralCard)
	{
		UTGeneralCard* pCard = Cast<UTGeneralCard>(pWidget);
		if (!pCard) return;
		if (pCWGameInstance->m_language == "Chinese")
			pCard->m_pCardNameTextBox->SetFont(pWidgetManager->m_basicInfo.secondClassChineseFont);
		else
			pCard->m_pCardNameTextBox->SetFont(pWidgetManager->m_basicInfo.secondClassFont);

	}
	else if (widgetType == EWidgetType::WidgetType_TradeCard)
	{
		UTTradeCard* pTradeCard = Cast<UTTradeCard>(pWidget);
		if (!pTradeCard || !pTradeCard->m_pButton) return;
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pWidgetManager, pWidgetManager->m_pSkillIconButtonMat);
		pTradeCard->m_pButton->WidgetStyle.Normal.SetResourceObject(pMI);
		pTradeCard->m_pButton->WidgetStyle.Hovered.SetResourceObject(pMI);
		pTradeCard->m_pButton->WidgetStyle.Pressed.SetResourceObject(pMI);
		pTradeCard->m_pButton->WidgetStyle.Disabled.SetResourceObject(pMI);
	}
}

UTemplateMainMenu* UWidgetBlueprintFunctionLibrary::CreateMainMenu(UWidgetManager* pWidgetManager, uint8 domain)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	UTemplateMainMenu* pMenu = NULL;
	if (domain == 0)
		pMenu = CreateWidget<UTemplateMainMenu>(pGI, pWidgetManager->m_widgetClassMap["LoginOptionMenu"]);
	if (!pMenu) return NULL;
	pMenu->NotifyInitial();
	for (int32 i=0; i<pMenu->m_sliderInfos.Num(); i++)
	{
		UTemplateProgressSlider* pSlider = CreateWidget<UTemplateProgressSlider>(pGI, pWidgetManager->m_widgetClassMap["OptionSlider"]);
		pSlider->NotifyInitial();
		if (pWidgetManager->m_language == "Chinese")
			pSlider->m_pCaption->SetText(FText::FromString(pMenu->m_sliderInfos[i].chsliderTitle));
		else
			pSlider->m_pCaption->SetText(FText::FromString(pMenu->m_sliderInfos[i].sliderTitle));
		pSlider->m_function = pMenu->m_sliderInfos[i].sliderFunction;
		pMenu->m_pSliders.Add(pSlider);
		UPanelSlot* pSlot = pMenu->m_pSliderVBox->AddChild(pSlider);
		UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVBoxSlot->SetPadding(pMenu->m_sliderMargin);
	}
	for (int32 i = 0; i < pMenu->m_comboboxInfos.Num(); i++)
	{
		UTemplateComboBox* pCombobox = CreateWidget<UTemplateComboBox>(pGI, pWidgetManager->m_widgetClassMap["OptionCombobox"]);
		pCombobox->NotifyInitial();
		pCombobox->m_function = pMenu->m_comboboxInfos[i].chcomboboxFunction;
		for (int32 j = 0; j < pMenu->m_comboboxInfos[i].comboboxOptions.Num(); j++)
		{
			pCombobox->m_pComboBox->AddOption(pMenu->m_comboboxInfos[i].comboboxOptions[j]);
		}
		if (pWidgetManager->m_language == "Chinese")
			pCombobox->m_pCaption->SetText(FText::FromString(pMenu->m_comboboxInfos[i].chcomboboxTitle));
		else
			pCombobox->m_pCaption->SetText(FText::FromString(pMenu->m_comboboxInfos[i].comboboxTitle));
		if (pCWGI->m_comboboxOption.Contains(pCombobox->m_function))
			pCombobox->m_pComboBox->SetSelectedOption(pCWGI->m_comboboxOption[pCombobox->m_function]);
		pMenu->m_pComboboxes.Add(pCombobox);
		UPanelSlot* pSlot = pMenu->m_pComboboxVBox->AddChild(pCombobox);
		UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVBoxSlot->SetPadding(pMenu->m_comboboxMargin);
	}
	return pMenu;
}

UTemplatePreBattleMenu* UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(UWidgetManager* pWidgetManager, uint8 type)
{
	if (!pWidgetManager) return NULL;
	//生成Widget
	UTemplatePreBattleMenu* pPreBattleMenu = NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (type == 0)
		pPreBattleMenu = CreateWidget<UTemplatePreBattleMenu>(pGI, pWidgetManager->m_widgetClassMap["NewGameMenu"]);
	else if (type == 1)
		pPreBattleMenu = CreateWidget<UTemplatePreBattleMenu>(pGI, pWidgetManager->m_widgetClassMap["LoadGameMenu"]);
	else
		pPreBattleMenu = CreateWidget<UTemplatePreBattleMenu>(pGI, pWidgetManager->m_widgetClassMap["SaveGameMenu"]);

	//对一般变量进行赋值
	pPreBattleMenu->m_pWidgetManager = pWidgetManager;
	pPreBattleMenu->NotifyInitial();
	//pPreBattleMenu->ReadDescription();
	pPreBattleMenu->m_menuType = type;

	if (type == 1 || type == 2)
	{
		//说明是读取界面
		for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
		{
			if (pCWGI->m_playerSingleProgressInfos[i].progressName == "") continue;
			UTemplateRow* pRow = CreateWidget<UTemplateRow>(pGI, pWidgetManager->m_widgetClassMap["Row"]);
			pRow->NotifyIntial();
			pRow->m_type = type;
			FString slotNamePrefix = "LoadSlot_";
			pRow->m_buttonFunction = slotNamePrefix.Append(pCWGI->m_playerSingleProgressInfos[i].progressName);
			pRow->m_pSlotText->SetText(FText::FromString(pCWGI->m_playerSingleProgressInfos[i].progressName));
			UPanelSlot* pSlot = pPreBattleMenu->m_pVBox->AddChild(pRow);
			UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
			pVSlot->Padding.Bottom = 10;
			pVSlot->Padding.Top = 10;
			pPreBattleMenu->m_pLoadSlots.Add(pRow);
		}
		pPreBattleMenu->m_curPhase = 1;
	}
	else if (type == 0)
	{
		pPreBattleMenu->m_curPhase = 0;
		pPreBattleMenu->SwitchPhase();
		
	}
	else if (type == 3)
	{

	}
	
	return pPreBattleMenu;
}

UTemplateBattleElementSystem* UWidgetBlueprintFunctionLibrary::CreateBattleMenu(UObject* pWorldContextObject, UWidgetManager* pWidgetManager)
{
	if (!pWorldContextObject || !pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWorldContextObject);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	//生成Widget
	TSubclassOf<class UTemplateBattleElementSystem> battleElementSystemClass = pWidgetManager->m_widgetClassMap["BattleMenu"];
	if (!battleElementSystemClass) return NULL;
	UTemplateBattleElementSystem* pBattleMenu = CreateWidget<UTemplateBattleElementSystem>(UGameplayStatics::GetGameInstance(pWorldContextObject), battleElementSystemClass);

	//对一般变量进行赋值
	pBattleMenu->m_pWidgetManager = pWidgetManager;
	pBattleMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	//绑定fadeout事件
	pBattleMenu->NotifyInitial();
	
	for (int32 i=0; i< pBattleMenu->m_pSkillBattleCardList.Num(); i++)
	{
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pWidgetManager, pBattleMenu->m_pBattleCardMat);
		pBattleMenu->m_pSkillBattleCardList[i]->m_pSkillImage->Brush.SetResourceObject(pMI);
	}
	for (int32 i = 0; i < pBattleMenu->m_pEquipBattleCardList.Num(); i++)
	{
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pWidgetManager, pBattleMenu->m_pBattleCardMat);
		pBattleMenu->m_pEquipBattleCardList[i]->m_pSkillImage->Brush.SetResourceObject(pMI);
	}

	int32 curCol = 0;
	int32 curRow = 0;
	for (int32 i=0; i<pBattleMenu->m_numericGridPanelCol; i++)
	{
		for (int32 j=0; j<pBattleMenu->m_numericGridPanelRow; j++)
		{
			UTTradeCard* pNumericCard = CreateWidget<UTTradeCard>(pGameInstance, pWidgetManager->m_widgetClassMap["TradeCard"]);
			pNumericCard->NotifyInitial();

			UMaterialInstanceDynamic* pDMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pWidgetManager, pBattleMenu->m_pNumericCardMat);
			FString paramStr = "ButtonTexture";
			pDMI->SetTextureParameterValue(FName(*paramStr), pBattleMenu->m_pDefaultNumericCardText);

			pNumericCard->m_pButton->WidgetStyle.Normal.SetResourceObject(pDMI);
			pNumericCard->m_pButton->WidgetStyle.Hovered.SetResourceObject(pDMI);
			pNumericCard->m_pButton->WidgetStyle.Pressed.SetResourceObject(pDMI);

			pNumericCard->m_cardName = "NULL";
			pNumericCard->SetVisibility(ESlateVisibility::Hidden);

			UPanelSlot* pPanelSlot = pBattleMenu->m_pNumericGridPanel->AddChild(pNumericCard);
			UGridSlot* pUniformGridPanelSlot = Cast<UGridSlot>(pPanelSlot);
			if (curCol >= pBattleMenu->m_numericGridPanelCol)
			{
				curRow += 1;
				curCol = 0;
			}
			pUniformGridPanelSlot->SetColumn(curCol);
			pUniformGridPanelSlot->SetRow(curRow);
			pBattleMenu->m_pAllNumericCards.Add(pNumericCard);
			curCol += 1;
		}
	}

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
	pBattleMenu->m_targetKillEnermyNb = pBLGM->m_pAIManager->m_battleInfo.targetKill;
	if (pBattleMenu->m_pTargetKillText) pBattleMenu->m_pTargetKillText->SetText(FText::FromString(FString::FromInt(pBLGM->m_pAIManager->m_battleInfo.targetKill)));
	
	return pBattleMenu;
}
/*

void UWidgetBlueprintFunctionLibrary::AddEnermyInfoToBattleMenu(uint8 race, FString enermyName, TArray<FString> stateList, UTemplateBattleElementSystem* pBattleMenu)
{
	if (!pBattleMenu || !pBattleMenu->m_pWidgetManager) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pBattleMenu->m_pWidgetManager, 0);
	ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
	if (!pBPC->m_pAllRaceTextureMap.Contains(race) || !pBPC->m_pAllRaceTextureMap[race]) return;
	bool enermyCardExist = false;
	for (uint8 i=0; i<pBattleMenu->m_enermyCardInfoList.Num(); i++)
	{
		if (pBattleMenu->m_enermyCardInfoList[i].cardName != enermyName) continue;
		enermyCardExist = true;
		TArray<FString> missingStateList;
		for (int32 j = 0; j < stateList.Num(); j++)
		{
			if (!pBattleMenu->m_enermyCardInfoList[i].stateNameList.Contains(stateList[j]))
				missingStateList.Add(stateList[j]);
		}
		for (int32 j=0; j<missingStateList.Num(); j++)
		{
			pBattleMenu->m_enermyCardInfoList[i].pEnermyCard->AddStateToCard(missingStateList[j], pBattleMenu->m_pWidgetManager->m_pSkillIconButtonMat);
		}
		pBattleMenu->m_enermyCardInfoList[i].enermyNb += 1;
		break;
	}
	if (enermyCardExist) return;
	UTEnermyCard* pEnermyCard = CreateWidget<UTEnermyCard>(UGameplayStatics::GetGameInstance(pBattleMenu->m_pWidgetManager), pBattleMenu->m_pWidgetManager->m_widgetClassMap["EnermyCard"]);
	pEnermyCard->NotifyInitial();
	UTexture* pTexture = pBPC->m_pAllRaceTextureMap[race];
	pEnermyCard->SetEnermyTexture(pTexture, pBattleMenu->m_pWidgetManager->m_pSkillIconButtonMat);
	FEnermyCardInfo enermyCardInfo;
	enermyCardInfo.cardName = enermyName;
	enermyCardInfo.pEnermyCard = pEnermyCard;
	enermyCardInfo.enermyNb = 1;
	pBattleMenu->m_enermyCardInfoList.Add(enermyCardInfo);
	for (int32 i=0; i<stateList.Num(); i++)
	{
		pEnermyCard->AddStateToCard(stateList[i], pBattleMenu->m_pWidgetManager->m_pSkillIconButtonMat);
	}
	pBattleMenu->m_pScrollBox->AddChild(pEnermyCard);
}*/
/*

void UWidgetBlueprintFunctionLibrary::RemoveEnermyCardInfoFromBattleMenu(FString enermyName, const TArray<FString>& deleteEnermyStateList, 
	const TArray<FString>& allStatesExcludeDeleteEnermy, UTemplateBattleElementSystem* pBattleMenu)
{
	if (!pBattleMenu) return;
	for (uint8 i=0; i<pBattleMenu->m_enermyCardInfoList.Num(); i++)
	{
		if (pBattleMenu->m_enermyCardInfoList[i].cardName != enermyName) continue;
		if (pBattleMenu->m_enermyCardInfoList[i].enermyNb <= 1)
		{
			pBattleMenu->m_pScrollBox->RemoveChild(pBattleMenu->m_enermyCardInfoList[i].pEnermyCard);
			pBattleMenu->m_enermyCardInfoList[i].pEnermyCard->RemoveFromParent();
			if (pBattleMenu->m_enermyCardInfoList[i].pEnermyCard->IsValidLowLevel())
				pBattleMenu->m_enermyCardInfoList[i].pEnermyCard->ConditionalBeginDestroy();
			pBattleMenu->m_enermyCardInfoList.RemoveAt(i);
		}
		else
		{
			//删除唯一的状态图标
			//减小角色数量记录
			pBattleMenu->m_enermyCardInfoList[i].enermyNb -= 1;
			for (int32 j=0; j<deleteEnermyStateList.Num(); j++)
			{
				if (allStatesExcludeDeleteEnermy.Contains(deleteEnermyStateList[j])) continue;
				pBattleMenu->m_enermyCardInfoList[i].pEnermyCard->RemoveState(deleteEnermyStateList[j]);
			}
		}
		break;
	}
}*/

UTemplateCharacterStatus* UWidgetBlueprintFunctionLibrary::CreateCharacterStatusMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UTemplateCharacterStatus* pMenu = CreateWidget<UTemplateCharacterStatus>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["CharacterStatus"]);
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();

	return pMenu;
}

UTemplateRunesMenu* UWidgetBlueprintFunctionLibrary::CreateRuneMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, 
	FString chSkillDomainTitle, FString skillDomainTitle, FString chWormDomainTitle, FString wormDomainTitle, 
	FString chCombineDomainTitle, FString combineDomainTitle, FString chNumericDomainTitle, FString numericDomainTitle)
{
	if (!pWidgetManager || !pWidgetManager->m_widgetClassMap.Contains("RuneMenu")) return NULL;
	UTemplateRunesMenu* pMenu = CreateWidget<UTemplateRunesMenu>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["RuneMenu"]);
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();
	
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_runeMenu);
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGameInstance);
	pMenu->InitialTitleTexts();
	pMenu->UpdateAttributeValue();
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	int32 keyNb = 0;
	int32 curSlotNb = 0;
	int32 curMentalityNb = 0;
	for (TMap<int32, int32>::TConstIterator iter = pSPGM->m_skillSlotNbMap.CreateConstIterator(); iter; ++iter)
	{
		if (pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["Mentality"] >= iter->Key && keyNb < pSPGM->m_skillSlotNbMap.Num() - 1)
		{
			keyNb += 1;
			continue;
		}
		curSlotNb = iter->Value;
		curMentalityNb = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["Mentality"];
		break;
	}
	pMenu->m_pCurMentalityNbText->SetText(FText::FromString(FString::FromInt(curMentalityNb)));
	pMenu->m_pCurAvailableSkillSlotNbText->SetText(FText::FromString(FString::FromInt(curSlotNb)));
	pMenu->m_targetDomain = 1;
	pMenu->SwitchDomain();
	return pMenu;
}

UTCardCombineListMenu* UWidgetBlueprintFunctionLibrary::CreateCardCombineListMenu(UWidgetManager* pWidgetManager, FString chExploreTitle, FString enExploreTitle, FString chCommunicationTitle, FString enCommunicationTitle, FString chForgeTitle, FString enForgeTitle, FString chResearchTitle, FString enResearchTitle,
	FString consumeTitle, FString lifeTitle, FString energyTitle, FString activityTitle, FString darknessTitle, FString mentalityTitle, FString moneyTitle,
	FString suppressionTitle, FString flameTitle, FString sunTitle, FString chconsumeTitle, FString chlifeTitle, FString chenergyTitle, FString chactivityTitle, FString chdarknessTitle, FString chmentalityTitle, FString chmoneyTitle,
	FString chsuppressionTitle, FString chflameTitle, FString chsunTitle)
{
	if (!pWidgetManager || !pWidgetManager->m_widgetClassMap.Contains("CardCombineList")) return NULL;
	UTCardCombineListMenu* pMenu = CreateWidget<UTCardCombineListMenu>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["CardCombineList"]);
	pMenu->NotifyInitial();
	pMenu->m_pWidgetManager = pWidgetManager;
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_cardCombineListMenu);
	if (pWidgetManager->m_language == "English")
	{
		pMenu->m_pConsumeTitle->SetText(FText::FromString(consumeTitle));
		pMenu->m_pLifeTitle->SetText(FText::FromString(lifeTitle));
		pMenu->m_pEnergyTitle->SetText(FText::FromString(energyTitle));
		pMenu->m_pActivityTitle->SetText(FText::FromString(activityTitle));
		pMenu->m_pDarknessTitle->SetText(FText::FromString(darknessTitle));
		pMenu->m_pMentalityTitle->SetText(FText::FromString(mentalityTitle));
		pMenu->m_pMoneyTitle->SetText(FText::FromString(moneyTitle));
		pMenu->m_pSuppressionTitle->SetText(FText::FromString(suppressionTitle));
		pMenu->m_pFlameFaithTitle->SetText(FText::FromString(flameTitle));
		pMenu->m_pSunFaithTitle->SetText(FText::FromString(sunTitle));
	}
	else 
	{
		pMenu->m_pConsumeTitle->SetText(FText::FromString(chconsumeTitle));
		pMenu->m_pLifeTitle->SetText(FText::FromString(chlifeTitle));
		pMenu->m_pEnergyTitle->SetText(FText::FromString(chenergyTitle));
		pMenu->m_pActivityTitle->SetText(FText::FromString(chactivityTitle));
		pMenu->m_pDarknessTitle->SetText(FText::FromString(chdarknessTitle));
		pMenu->m_pMentalityTitle->SetText(FText::FromString(chmentalityTitle));
		pMenu->m_pMoneyTitle->SetText(FText::FromString(chmoneyTitle));
		pMenu->m_pSuppressionTitle->SetText(FText::FromString(chsuppressionTitle));
		pMenu->m_pFlameFaithTitle->SetText(FText::FromString(chflameTitle));
		pMenu->m_pSunFaithTitle->SetText(FText::FromString(chsunTitle));
	}
	pMenu->LoadShadowActorCards();

	//pMenu->m_domain = 0;
	//pMenu->SwitchDomain(0);
	return pMenu;
}

UTemplateLoginMenu* UWidgetBlueprintFunctionLibrary::CreateLoginMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	UTemplateLoginMenu* pMenu = CreateWidget<UTemplateLoginMenu>(pGameInstance, pWidgetManager->m_widgetClassMap["LoginMenu"]);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->NotifyInitial();
	for (int32 i = 0; i < pMenu->m_buttonFunctions.Num(); i++)
	{
		UTemplateRuneElement* pSimpleButton = CreateWidget<UTemplateRuneElement>(UGameplayStatics::GetGameInstance(pWidgetManager), pWidgetManager->m_widgetClassMap["LoginMenuButton"]);
		pSimpleButton->NotifyInitial();
		pSimpleButton->m_buttonFunction = pMenu->m_buttonFunctions[i];
		if (pWidgetManager->m_language == "Chinese")
			pSimpleButton->m_pRuneName->SetText(FText::FromString(pMenu->m_chButtonTexts[i]));
		else
			pSimpleButton->m_pRuneName->SetText(FText::FromString(pMenu->m_buttonTexts[i]));
		pMenu->m_pButtons.Add(pSimpleButton);
		UPanelSlot* pSlot = pMenu->m_pVBox->AddChild(pSimpleButton);
		UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVSlot->SetPadding(pMenu->m_buttonMargin);
	}
	//ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_loginMenu);

	return pMenu;
}

void UWidgetBlueprintFunctionLibrary::AddStateElementToCharacterInfoBar(UObject* pWorldContextObject, UTemplateCharacterInfo* pInfo, FString stateName)
{
	if (!pWorldContextObject || !pInfo || !pInfo->m_pStateHorizontalBox) return;
	UTemplateCharacterStateElement* pElement = CreateWidget<UTemplateCharacterStateElement>(UGameplayStatics::GetGameInstance(pWorldContextObject), pInfo->m_characterStateElementClass);
	if (!pElement) return;
	pElement->m_stateName = stateName;
	pElement->NotifyInitial();
	pElement->LoadStateImage();
	//ApplyThemeToElement(pWidgetManager, pElement, EWidgetType::WidgetType_runeElement);
	pInfo->m_pStateHorizontalBox->AddChild(pElement);
	pInfo->m_pStateElements.Add(pElement);
}

void UWidgetBlueprintFunctionLibrary::RemoveStateElementFromCharacterInfoBar(UTemplateCharacterInfo* pInfo, FString stateName)
{
	if (!pInfo || !pInfo->m_pStateHorizontalBox) return;
	for (int32 i=0; i<pInfo->m_pStateElements.Num(); i++)
	{
		if (!pInfo->m_pStateElements[i] || pInfo->m_pStateElements[i]->m_stateName != stateName) continue;
		UWidget* pChildWidget = pInfo->m_pStateElements[i];
		pInfo->m_pStateElements.RemoveAt(i);
		pInfo->m_pStateHorizontalBox->RemoveChild(pChildWidget);
		if (pChildWidget && pChildWidget->IsValidLowLevel()) pChildWidget->ConditionalBeginDestroy();
		break;
	}
}
/*

UTemplateItemSystem* UWidgetBlueprintFunctionLibrary::CreateItemMenu(UObject* pObject, UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pObject);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("ItemMenu")) return NULL;
	TSubclassOf<class UUserWidget> itemMenuClass = pWidgetManager->m_widgetClassMap["ItemMenu"];
	UTemplateItemSystem* pMenu = CreateWidget<UTemplateItemSystem>(pGameInstance, itemMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->m_chineseTitle = chineseTitle;
	pMenu->m_englishTitle = englishTitle;
	pMenu->NotifyInitial();
	pMenu->m_pWidgetManager->SetTheme(EWidgetTheme::WT_normal);
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_ItemMenu);
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pObject);
	if (!pGameMode) return pMenu;
	ACWBaseGameMode* pCWGameMode = Cast<ACWBaseGameMode>(pGameMode);
	if (!pCWGameMode) return pMenu;
	pMenu->m_itemMenuButtonClickDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::ButtonClickCallback);
	pMenu->m_itemMenuFadeOutDoneDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::MenuFadeOutDoneCallback);
	for (int32 i=0; i<pMenu->m_maxItemRow; i++)
	{
		for (int32 j=0; j<pMenu->m_maxItemCol; j++)
		{
			TSubclassOf<class UUserWidget> itemElementClass = pWidgetManager->m_widgetClassMap["ItemElement"];
			UTemplateItemElement* pElement = CreateWidget<UTemplateItemElement>(pGameInstance, itemElementClass);
			pElement->NotifyInitial();
			pElement->m_domain = "ItemMenu";
			pElement->m_row = i;
			pElement->m_col = j;
			UGridSlot* pGridSlot = pMenu->m_pItemListGridPanel->AddChildToGrid(pElement);
			pGridSlot->SetRow(i);
			pGridSlot->SetColumn(j);
			pElement->m_buttonClickDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::ItemElementButtonClickCallback);
			pMenu->m_pAllItemElement.Add(pElement);
		}
	}
	/ *for (int32 i=0; i<pMenu->m_pCombineElementList.Num(); i++)
	{
		FString functionName = "Button_CombineElement_" + FString::FromInt(i);
		pMenu->m_pCombineElementList[i]->m_buttonFunction = functionName;
		pMenu->m_pCombineElementList[i]->m_buttonClickDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::ButtonClickCallback);
	}* /
	return pMenu;
}*/

UTBattleLineMenu* UWidgetBlueprintFunctionLibrary::CreateBattleLineMenu(UObject* pObject, UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pObject);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("BattleLineMenu")) return NULL;
	TSubclassOf<class UUserWidget> battleLineMenuClass = pWidgetManager->m_widgetClassMap["BattleLineMenu"];
	UTBattleLineMenu* pMenu = CreateWidget<UTBattleLineMenu>(pGameInstance, battleLineMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->m_chineseTitle = chineseTitle;
	pMenu->m_englishTitle = englishTitle;
	pMenu->NotifyInitial();
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_BattleLineMenu);

	for (int32 i=0; i<pMenu->m_skillCardColNb; i++)
	{
		UTemplateRuneElement* pDiceSkillCard = CreateWidget<UTemplateRuneElement>(pGameInstance, pWidgetManager->m_widgetClassMap["FCSkillInfo"]);
		pDiceSkillCard->NotifyInitial();
		/*UMaterialInstanceDynamic* pDMI = pDiceSkillCard->m_pRuneImage->GetDynamicMaterial();
		pDMI->SetTextureParameterValue(FName("ButtonTexture"), pSPPC->m_allDiceBattleSkillInfos[diceSkillName].pTexture);*/
		UPanelSlot* pSkillSlot = pMenu->m_pAppendSkillGridPanel->AddChild(pDiceSkillCard);
		UGridSlot* pGridSlot = Cast<UGridSlot>(pSkillSlot);
		pGridSlot->SetRow(i);
		pGridSlot->SetPadding(pMenu->m_appendSkillMargin);
		pMenu->m_pAllDiceSkillDemoCards.Add(pDiceSkillCard, -1);
		pDiceSkillCard->SetVisibility(ESlateVisibility::Hidden);
	}
	
	//pMenu->LoadAvailableSkills();
	return pMenu;
}

UTDecipherMenu* UWidgetBlueprintFunctionLibrary::CreateDecipherMenu(UObject* pObject, UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pObject);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("DecipherMenu")) return NULL;
	TSubclassOf<class UUserWidget> decipherMenuClass = pWidgetManager->m_widgetClassMap["DecipherMenu"];
	UTDecipherMenu* pMenu = CreateWidget<UTDecipherMenu>(pGameInstance, decipherMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->m_chineseTitle = chineseTitle;
	pMenu->m_englishTitle = englishTitle;
	pMenu->NotifyInitial();
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_DecipherMenu);
	pMenu->InitialDecipherMenu();

	for (int32 i = 0; i < pMenu->m_skillCardColNb; i++)
	{
		UTemplateRuneElement* pDecipherSkillCard = CreateWidget<UTemplateRuneElement>(pGameInstance, pWidgetManager->m_widgetClassMap["FCSkillInfo"]);
		pDecipherSkillCard->NotifyInitial();
		/*UMaterialInstanceDynamic* pDMI = pDiceSkillCard->m_pRuneImage->GetDynamicMaterial();
		pDMI->SetTextureParameterValue(FName("ButtonTexture"), pSPPC->m_allDiceBattleSkillInfos[diceSkillName].pTexture);*/
		UPanelSlot* pSkillSlot = pMenu->m_pSkillDemoCardGridPanel->AddChild(pDecipherSkillCard);
		UGridSlot* pGridSlot = Cast<UGridSlot>(pSkillSlot);
		pGridSlot->SetRow(i);
		pGridSlot->SetPadding(pMenu->m_appendSkillMargin);
		pMenu->m_pAllTheorizeSkillDemoCards.Add(pDecipherSkillCard, -1);
		pDecipherSkillCard->SetVisibility(ESlateVisibility::Hidden);
	}

	return pMenu;
}

UTCardSelectMenu* UWidgetBlueprintFunctionLibrary::CreateCardSelectMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pWidgetManager->m_widgetClassMap.Contains("CardSelectMenu") || !pWidgetManager->m_widgetClassMap.Contains("ActionCard")) return NULL;
	TSubclassOf<class UUserWidget> cardSelectMenuClass = pWidgetManager->m_widgetClassMap["CardSelectMenu"];
	UTCardSelectMenu* pMenu = CreateWidget<UTCardSelectMenu>(pGameInstance, cardSelectMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGI->m_language;
	pMenu->NotifyInitial();

	return pMenu;
}

UTemplateSingleProgressMenu* UWidgetBlueprintFunctionLibrary::CreateSingleProgressMenu(UObject* pObject, UWidgetManager* pWidgetManager, 
	FString durabilityNbTitle, FString chDurabilityNbTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pObject);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("SingleprogressMenu")) return NULL;
	TSubclassOf<class UUserWidget> singleprogressMenuClass = pWidgetManager->m_widgetClassMap["SingleprogressMenu"];
	UTemplateSingleProgressMenu* pMenu = CreateWidget<UTemplateSingleProgressMenu>(pGameInstance, singleprogressMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->NotifyInitial();

	return pMenu;
}

UTCardInfoMenu* UWidgetBlueprintFunctionLibrary::CreateCardInfoMenu(UWidgetManager* pWidgetManager, FString chineseTitle, FString englishTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("CardInfoMenu")) return NULL;
	TSubclassOf<class UUserWidget> cardInfoMenuClass = pWidgetManager->m_widgetClassMap["CardInfoMenu"];
	UTCardInfoMenu* pMenu = CreateWidget<UTCardInfoMenu>(pGameInstance, cardInfoMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;
	pMenu->NotifyInitial();
	if (pCWGameInstance->m_language == "Chinese")
		pMenu->m_pTitleText->SetText(FText::FromString(chineseTitle));
	else
		pMenu->m_pTitleText->SetText(FText::FromString(englishTitle));
	ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_CardInfoMenu);

	return pMenu;
}
/*

void UWidgetBlueprintFunctionLibrary::AddSkillIconToCardInfoMenu(UTCardInfoMenu* pCardInfoMenu, UTexture* pTexture, FString chineseText, FString englishText, FVector2D loc, FString iconName)
{
	if (!pCardInfoMenu) return;
	if (!pCardInfoMenu->m_pWidgetManager->m_widgetClassMap.Contains("SkillTreeIcon")) return;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pCardInfoMenu->m_pWidgetManager);
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	TSubclassOf<class UUserWidget> skillTreeIconClass = pCardInfoMenu->m_pWidgetManager->m_widgetClassMap["SkillTreeIcon"];
	UTSkillTreeIcon* pSkillTreeIcon = CreateWidget<UTSkillTreeIcon>(pGameInstance, skillTreeIconClass);
	pSkillTreeIcon->m_chineseText = chineseText;
	pSkillTreeIcon->m_englishText = englishText;
	pSkillTreeIcon->m_skillIconName = iconName;
	pSkillTreeIcon->NotifyInitial();
	//设置文字
	if (pCardInfoMenu->m_pWidgetManager->m_language == "Chinese")
		pSkillTreeIcon->m_pContentTextBox->SetText(FText::FromString(pSkillTreeIcon->m_chineseText));
	else
		pSkillTreeIcon->m_pContentTextBox->SetText(FText::FromString(pSkillTreeIcon->m_englishText));
	//设置按键图片
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pCardInfoMenu->m_pWidgetManager, pCardInfoMenu->m_pWidgetManager->m_pSkillIconButtonMat);
	pMI->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pTexture);
	pSkillTreeIcon->m_pSkillImage->Brush.SetResourceObject(pMI);
	ApplyThemeToElement(pCardInfoMenu->m_pWidgetManager, pSkillTreeIcon, EWidgetType::WidgetType_skillTreeIcon);
	UPanelSlot* pSlot = pCardInfoMenu->m_pCanvasPanel->AddChild(pSkillTreeIcon);
	UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
	FAnchors anchor;
	anchor.Maximum = FVector2D(0.5, 0.5);
	anchor.Minimum = FVector2D(0.5, 0.5);
	pCanvasSlot->SetAnchors(anchor);
	pCanvasSlot->SetAlignment(FVector2D(0.5, 0.5));
	pCanvasSlot->SetPosition(loc);
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pCardInfoMenu->m_pWidgetManager);
	if (!pGameMode) return;
	ACWBaseGameMode* pCWGameMode = Cast<ACWBaseGameMode>(pGameMode);
	if (!pCWGameMode) return;
	pSkillTreeIcon->m_buttonClickDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::ButtonClickCallback);
}*/

UTActionPanel* UWidgetBlueprintFunctionLibrary::CreateActionPanel(UWidgetManager* pWidgetManager, UEventNodeManager* pEventNodeManager, uint8 actionType)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pWidgetManager->m_widgetClassMap.Contains("ActionPanel")) return NULL;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pWidgetManager, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	TSubclassOf<class UUserWidget> actionPanelClass = pWidgetManager->m_widgetClassMap["ActionPanel"];
	UTActionPanel* pMenu = CreateWidget<UTActionPanel>(pGameInstance, actionPanelClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);

	pMenu->NotifyInitial();
	//这是有大量故事性文字的逻辑代码，现在改成只有一句
	//pMenu->UpdateActionPanelInfo(pEventNodeManager);
	if (pWidgetManager->m_language == "Chinese")
	{
		if (pSPGM->m_actionDescription.Contains(actionType) && pSPGM->m_actionDescription[actionType].chDescriptions.Num() > 0)
		{
			int32 randNb = FMath::RandRange(0, pSPGM->m_actionDescription[actionType].chDescriptions.Num() - 1);
			pMenu->ShowActionWords(pSPGM->m_actionDescription[actionType].chDescriptions[randNb]);
		}
	}
	else
	{
		if (pSPGM->m_actionDescription.Contains(actionType) && pSPGM->m_actionDescription[actionType].enDescriptions.Num() > 0)
		{
			int32 randNb = FMath::RandRange(0, pSPGM->m_actionDescription[actionType].enDescriptions.Num() - 1);
			pMenu->ShowActionWords(pSPGM->m_actionDescription[actionType].enDescriptions[randNb]);
		}
	}

	return pMenu;
}

UTShopMenu* UWidgetBlueprintFunctionLibrary::CreateShopMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pGameInstance) return NULL;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return NULL;
	if (!pWidgetManager->m_widgetClassMap.Contains("ShopMenu")) return NULL;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pWidgetManager, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	TSubclassOf<class UUserWidget> shopMenuClass = pWidgetManager->m_widgetClassMap["ShopMenu"];
	UTShopMenu* pMenu = CreateWidget<UTShopMenu>(pGameInstance, shopMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->m_pWidgetManager->m_language = pCWGameInstance->m_language;

	pMenu->NotifyInitial();
	if (pCWGameInstance->m_language == "Chinese")
	{
		pMenu->m_pTitle->SetText(FText::FromString(chTitle));
		//pMenu->m_pEnsureButtonText->SetText(FText::FromString(chEnsureButtonText));
	}
	else
	{
		pMenu->m_pTitle->SetText(FText::FromString(enTitle));
		//pMenu->m_pEnsureButtonText->SetText(FText::FromString(ensureButtonText));
	}
	//ApplyThemeToElement(pWidgetManager, pMenu, EWidgetType::WidgetType_ActionPanel);
	if (!pSPPC->m_pCurSelectEventCard) return pMenu;
	TArray<FString> shopCardList = pSPPC->m_pCurSelectEventCard->m_eventCardInfo.m_cardShopInfo.possibleShopCards;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	for (int32 i=0; i<shopCardList.Num(); i++)
	{
		UTActionCard* pActionCard = CreateWidget<UTActionCard>(pPC, pWidgetManager->m_widgetClassMap["ShopCard"]);
		pActionCard->NotifyInitial();
		pActionCard->InitialActionCard(-1, 5, shopCardList[i], NULL);
		pActionCard->m_pNbText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		if (pSPGM->m_pPlayCardTextureMap.Contains(shopCardList[i]))
		{
			if (pMenu->m_pWidgetManager->m_language == "Chinese")
				pActionCard->m_pNbText->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[shopCardList[i]].chCardName));
			else
				pActionCard->m_pNbText->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[shopCardList[i]].cardName));
		}
		UPanelSlot* pPanelSlot = pMenu->m_pVContentBox->AddChild(pActionCard);
		UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pPanelSlot);
		pVBoxSlot->SetPadding(pMenu->m_margin);
		pMenu->m_pActionCards.Add(pActionCard);
	}

	//pMenu->WriteTradeInfoIntoMenu(inputNb);
	
	pMenu->m_pMoneyText->SetText(FText::FromString(FString::FromInt(pSPGM->m_curMoney)));
	return pMenu;
}

TArray<UTexture2D*> UWidgetBlueprintFunctionLibrary::LoadTexture2D(FString path)
{
	TArray<FString> fileNames;
	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	ThePath = ThePath.Append(path);
	UWidgetBlueprintFunctionLibrary::ScanDirectory(fileNames, ThePath);
	TArray<UTexture2D*> pTextures;
	for (int32 i = 0; i < fileNames.Num(); i++)
	{
		UTexture2D* Texture = nullptr;
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fileNames[i])) continue;
		TArray<uint8> RawFileData;
		if (!FFileHelper::LoadFileToArray(RawFileData, *fileNames[i])) continue;
		IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		IImageWrapperPtr ImageWrapper = imageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8>* UncompressedRGBA = nullptr;
			if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);
				if (Texture != nullptr)
				{
					void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(TextureData, UncompressedRGBA->GetData(), UncompressedRGBA->Num());
					Texture->PlatformData->Mips[0].BulkData.Unlock();
					Texture->UpdateResource();
				}
			}
		}
		if (!Texture) continue;
		pTextures.Add(Texture);
	}
	return pTextures;
}

UTShadowModeMenu* UWidgetBlueprintFunctionLibrary::CreateShadowModeMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, FString chDeleteButtonStr,
	FString enDeleteButtonStr, FString lifeSlopeTitle, FString energySlopeTitle, FString activitySlopeTitle, FString darknessSlopeTitle, FString flameSlopeTitle,
	FString mentalitySlopeTitle, FString moneySlopeTitle, FString sunSlopeTitle, FString suppressionSlopeTitle, FString lifeMaxTitle, FString energyMaxTitle,
	FString activityMaxTitle, FString darknessMaxTitle, FString flameMaxTitle, FString mentalityMaxTitle, FString moneyMaxTitle, FString sunMaxTitle, FString suppressionMaxTitle,
	FString chlifeSlopeTitle, FString chenergySlopeTitle, FString chactivitySlopeTitle, FString chdarknessSlopeTitle, FString chflameSlopeTitle,
	FString chmentalitySlopeTitle, FString chmoneySlopeTitle, FString chsunSlopeTitle, FString chsuppressionSlopeTitle, FString chlifeMaxTitle, FString chenergyMaxTitle,
	FString chactivityMaxTitle, FString chdarknessMaxTitle, FString chflameMaxTitle, FString chmentalityMaxTitle, FString chmoneyMaxTitle, FString chsunMaxTitle, FString chsuppressionMaxTitle,
	FString changeIntervalTitle, FString chChangeIntervalTitle)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pWidgetManager->m_widgetClassMap.Contains("ShadowModeMenu")) return NULL;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pWidgetManager, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	TSubclassOf<class UUserWidget> shadowModeMenuClass = pWidgetManager->m_widgetClassMap["ShadowModeMenu"];
	UTShadowModeMenu* pMenu = CreateWidget<UTShadowModeMenu>(pGI, shadowModeMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;

	pMenu->NotifyInitial();
	pMenu->SetTextBlockTexts();
	pMenu->ReadAllShadowCards();
	
	return pMenu;
}

void UWidgetBlueprintFunctionLibrary::ScanDirectory(TArray<FString>& Files, FString FilePath)
{
	FString orignPath = FilePath;
	FString SearchedFiles = FilePath.Append(TEXT("*.png"));
	TArray<FString> FindedFiles;

	IFileManager::Get().FindFiles(FindedFiles, *SearchedFiles, true, false);

	FString SearchFile = "";

	for (int i = 0; i < FindedFiles.Num(); i++)
	{
		SearchFile = orignPath + FindedFiles[i];
		Files.Add(SearchFile);

		//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, SearchFile);
	}
}

UTEndMenu* UWidgetBlueprintFunctionLibrary::CreateEndMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pWidgetManager->m_widgetClassMap.Contains("EndMenu")) return NULL;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pWidgetManager, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	TSubclassOf<class UUserWidget> endMenuClass = pWidgetManager->m_widgetClassMap["EndMenu"];
	UTEndMenu* pMenu = CreateWidget<UTEndMenu>(pGI, endMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;

	pMenu->NotifyInitial();
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pWidgetManager->m_language == "Chinese")
		pMenu->m_demoText = pSPGM->m_endInfo.chTexts;
	else
		pMenu->m_demoText = pSPGM->m_endInfo.enTexts;

	return pMenu;
}

UDialogTextMenu* UWidgetBlueprintFunctionLibrary::CreateTutorialMenu(UWidgetManager* pWidgetManager, uint8 state)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	pWidgetManager->m_language = pCWGI->m_language;
	if (!pWidgetManager->m_widgetClassMap.Contains("TutorialMenu")) return NULL;
	TSubclassOf<class UUserWidget> endMenuClass = NULL;
	if (state == 0)
		endMenuClass = pWidgetManager->m_widgetClassMap["TutorialMenu"];
	else
		endMenuClass = pWidgetManager->m_widgetClassMap["TutorialMenu_Battle"];
	UDialogTextMenu* pMenu = CreateWidget<UDialogTextMenu>(pGI, endMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();
	pMenu->m_gameState = state;
	return pMenu;
}

UTCalendarMenu* UWidgetBlueprintFunctionLibrary::CreateCalendarMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pWidgetManager->m_widgetClassMap.Contains("EventMenu")) return NULL;
	TSubclassOf<class UUserWidget> eventMenuClass = pWidgetManager->m_widgetClassMap["EventMenu"];
	UTCalendarMenu* pMenu = CreateWidget<UTCalendarMenu>(pGI, eventMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();
	/*if (pWidgetManager->m_language == "Chinese")
	{
		pMenu->m_pActivityTargetTitle->SetText(FText::FromString(chactivityTitle));
		pMenu->m_pMentalityTargetTitle->SetText(FText::FromString(chmentalityTitle));
		pMenu->m_pSuppressionTargetTitle->SetText(FText::FromString(chsuppressionTitle));
		pMenu->m_pFlameFaithTargetTitle->SetText(FText::FromString(chflameFaithTitle));
		pMenu->m_pSunFaithTargetTitle->SetText(FText::FromString(chsuppressionTitle));
		pMenu->m_pDarknessTargetTitle->SetText(FText::FromString(chdarknessTitle));
	}
	else
	{
		pMenu->m_pActivityTargetTitle->SetText(FText::FromString(activityTitle));
		pMenu->m_pMentalityTargetTitle->SetText(FText::FromString(mentalityTitle));
		pMenu->m_pSuppressionTargetTitle->SetText(FText::FromString(suppressionTitle));
		pMenu->m_pFlameFaithTargetTitle->SetText(FText::FromString(flameFaithTitle));
		pMenu->m_pSunFaithTargetTitle->SetText(FText::FromString(suppressionTitle));
		pMenu->m_pDarknessTargetTitle->SetText(FText::FromString(darknessTitle));
	}
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	pMenu->m_pActivityTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.activity)));
	pMenu->m_pMentalityTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.mentality)));
	pMenu->m_pSuppressionTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.suppression)));
	pMenu->m_pFlameFaithTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.flameFaith)));
	pMenu->m_pSunFaithTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.sunFaith)));
	pMenu->m_pDarknessTargetNb->SetText(FText::FromString(FString::FromInt(pSPGM->m_curOverallIndex.darkness)));*/
	//pMenu->m_gameState = state;
	return pMenu;
}

UTSkillSelectMenu* UWidgetBlueprintFunctionLibrary::CreateSkillSelectMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pWidgetManager, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (!pWidgetManager->m_widgetClassMap.Contains("SkillSelectMenu")) return NULL;
	TSubclassOf<class UUserWidget> skillSelectMenuClass = pWidgetManager->m_widgetClassMap["SkillSelectMenu"];
	UTSkillSelectMenu* pMenu = CreateWidget<UTSkillSelectMenu>(pPC, skillSelectMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();

	int32 curRow = 0;
	int32 curCol = 0;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FString characterName = pCWGI->m_curPlayerSPInfo.characterName;
	if (characterName == "" || characterName == "NULL") characterName = "Lucian";
	pSPPC->ReadPlayerCharacterSkills(characterName);
	int32 curSlotNb = 0;
	for (int32 i=0; i< pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Num(); i++)
	{
		/*if (!pSPPC->m_playerSkillInfos[i].isInitial && !pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(pSPPC->m_playerSkillInfos[i].skillName))
			continue;*/
		for (int32 j=0; j< pSPPC->m_playerSkillInfos.Num(); j++)
		{
			if (pSPPC->m_playerSkillInfos[j].skillName != pCWGI->m_curPlayerSPInfo.availableExtraSkillList[i]) continue;
			TSubclassOf<class UUserWidget> skillSelectButtonClass = pWidgetManager->m_widgetClassMap["SkillSelectButton"];
			UTemplateRuneElement* pSkillSelectButton = CreateWidget<UTemplateRuneElement>(pPC, skillSelectButtonClass);
			pSkillSelectButton->NotifyInitial();
			UObject* pObject = pSkillSelectButton->m_pRuneImage->Brush.GetResourceObject();
			UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
			pMI->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pSPPC->m_playerSkillInfos[j].pTexture);
			pSkillSelectButton->m_buttonFunction = "SkillSelectButton_" + pCWGI->m_curPlayerSPInfo.availableExtraSkillList[i];
			UPanelSlot* pSlot = pMenu->m_pSkillGridPanel->AddChild(pSkillSelectButton);
			UGridSlot* pGridSlot = Cast<UGridSlot>(pSlot);
			pGridSlot->SetPadding(pMenu->m_gridMargin);
			pGridSlot->SetColumn(curCol);
			pGridSlot->SetRow(curRow);
			curCol += 1;
			if (curCol >= pMenu->m_maxCol)
			{
				curRow += 1;
				curCol = 0;
			}
			pMenu->m_pAllAvailableSkills.Add(curSlotNb, pSkillSelectButton);
			curSlotNb += 1;
			break;
		}
	}

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pWidgetManager);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("Mentality"))
		pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("Mentality", 0);
	int32 keyNb = 0;
	for (TMap<int32, int32>::TConstIterator iter = pSPGM->m_skillSlotNbMap.CreateConstIterator(); iter; ++iter)
	{
		if (pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["Mentality"] >= iter->Key && keyNb < pSPGM->m_skillSlotNbMap.Num() - 1)
		{
			keyNb += 1;
			continue;
		}
		pMenu->m_skillCapacity = iter->Value;
		pMenu->UpdateSkillCapacityText();
		break;
	}
	return pMenu;
}

UTRewardMenu* UWidgetBlueprintFunctionLibrary::CreateRewardMenu(UWidgetManager* pWidgetManager)
{
	if (!pWidgetManager) return NULL;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pWidgetManager);
	if (!pWidgetManager->m_widgetClassMap.Contains("RewardMenu")) return NULL;
	TSubclassOf<class UUserWidget> rewardMenuClass = pWidgetManager->m_widgetClassMap["RewardMenu"];
	UTRewardMenu* pMenu = CreateWidget<UTRewardMenu>(pGI, rewardMenuClass);
	//对一般变量进行赋值
	pMenu->m_pWidgetManager = pWidgetManager;
	pMenu->NotifyInitial();
	return pMenu;
}

