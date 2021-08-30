// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../CollisionWarGameInstance.h"
#include "WidgetManager.h"




void UWidgetManager::MenuFadeOutDone(FString menuName)
{

}

void UWidgetManager::ButtonClickCallback(FString buttonFunction)
{

}

void UWidgetManager::GetInputTextStyle(FSlateBrush& normalBrush, FSlateBrush& hoveredBrush, FSlateBrush& pressedBrush, FSlateBrush& disableBrush, FMargin& padding, FSlateFontInfo& font, FSlateColor& foreGroundColor, FSlateFontInfo& captionFont, FSlateColor& captionColor)
{
	//set normal brush
	normalBrush.ImageSize = m_inputTextInfo.size;
	hoveredBrush.ImageSize = m_inputTextInfo.size;
	pressedBrush.ImageSize = m_inputTextInfo.size;
	disableBrush.ImageSize = m_inputTextInfo.size;
	normalBrush.Margin = m_inputTextInfo.imageMargin;
	hoveredBrush.Margin = m_inputTextInfo.imageMargin;
	pressedBrush.Margin = m_inputTextInfo.imageMargin;
	disableBrush.Margin = m_inputTextInfo.imageMargin;
	normalBrush.TintColor = m_basicInfo.themeColorNormal;
	hoveredBrush.TintColor = m_basicInfo.themeColorHover;
	pressedBrush.TintColor = m_basicInfo.themeColorExtra;
	disableBrush.TintColor = m_basicInfo.themeColorDisable;
	if (m_inputTextInfo.pBGTexture)
	{
		normalBrush.SetResourceObject(m_inputTextInfo.pBGTexture);
		hoveredBrush.SetResourceObject(m_inputTextInfo.pBGTexture);
		pressedBrush.SetResourceObject(m_inputTextInfo.pBGTexture);
		disableBrush.SetResourceObject(m_inputTextInfo.pBGTexture);
	}
	switch (m_inputTextInfo.drawAs)
	{
	case EDrawType::DT_Null:
		normalBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		hoveredBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		pressedBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		disableBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		break;
	case EDrawType::DT_Box:
		normalBrush.DrawAs = ESlateBrushDrawType::Box;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Box;
		pressedBrush.DrawAs = ESlateBrushDrawType::Box;
		disableBrush.DrawAs = ESlateBrushDrawType::Box;
		break;
	case EDrawType::DT_Border :
		normalBrush.DrawAs = ESlateBrushDrawType::Border;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Border;
		pressedBrush.DrawAs = ESlateBrushDrawType::Border;
		disableBrush.DrawAs = ESlateBrushDrawType::Border;
		break;
	case EDrawType::DT_Image :
		normalBrush.DrawAs = ESlateBrushDrawType::Image;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Image;
		pressedBrush.DrawAs = ESlateBrushDrawType::Image;
		disableBrush.DrawAs = ESlateBrushDrawType::Image;
		break;
	default:
		break;
	}

	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (pCWGameInstance->m_language == "Chinese")
	{
		font = m_basicInfo.textChineseElementFont;
		captionFont = m_basicInfo.textAndCaptionChineseFont;
	}
	else
	{
		font = m_basicInfo.textElementFont;
		captionFont = m_basicInfo.textAndCaptionFont;
	}
	padding = m_inputTextInfo.padding;
	foreGroundColor = m_basicInfo.textElementColor;
	captionColor = m_basicInfo.textAndCaptionColor;
}

void UWidgetManager::GetButtonStyle(FSlateBrush& normalBrush, FSlateBrush& hoveredBrush, FSlateBrush& pressedBrush, FSlateBrush& disableBrush, 
	FSlateBrush& borderBrush, FMargin& normalPadding, FMargin& pressedPadding, FSlateFontInfo& buttonTextFont, FSlateColor& buttonTextColor)
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	normalBrush.ImageSize = m_buttonInfo.size;
	hoveredBrush.ImageSize = m_buttonInfo.size;
	pressedBrush.ImageSize = m_buttonInfo.size;
	disableBrush.ImageSize = m_buttonInfo.size;
	normalBrush.Margin = m_buttonInfo.imageMargin;
	hoveredBrush.Margin = m_buttonInfo.imageMargin;
	pressedBrush.Margin = m_buttonInfo.imageMargin;
	disableBrush.Margin = m_buttonInfo.imageMargin;
	normalBrush.TintColor = m_basicInfo.themeColorNormal;
	hoveredBrush.TintColor = m_basicInfo.themeColorHover;
	pressedBrush.TintColor = m_basicInfo.themeColorExtra;
	disableBrush.TintColor = m_basicInfo.themeColorDisable;
	if (m_buttonInfo.pBGTexture)
	{
		normalBrush.SetResourceObject(m_buttonInfo.pBGTexture);
		hoveredBrush.SetResourceObject(m_buttonInfo.pBGTexture);
		pressedBrush.SetResourceObject(m_buttonInfo.pBGTexture);
		disableBrush.SetResourceObject(m_buttonInfo.pBGTexture);
	}
	if (m_buttonInfo.drawAs == EDrawType::DT_Null)
	{
		normalBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		hoveredBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		pressedBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
		disableBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
	}
	else if (m_buttonInfo.drawAs == EDrawType::DT_Box)
	{
		normalBrush.DrawAs = ESlateBrushDrawType::Box;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Box;
		pressedBrush.DrawAs = ESlateBrushDrawType::Box;
		disableBrush.DrawAs = ESlateBrushDrawType::Box;
	}
	else if (m_buttonInfo.drawAs == EDrawType::DT_Image)
	{
		normalBrush.DrawAs = ESlateBrushDrawType::Image;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Image;
		pressedBrush.DrawAs = ESlateBrushDrawType::Image;
		disableBrush.DrawAs = ESlateBrushDrawType::Image;
	}
	else if (m_buttonInfo.drawAs == EDrawType::DT_Border)
	{
		normalBrush.DrawAs = ESlateBrushDrawType::Border;
		hoveredBrush.DrawAs = ESlateBrushDrawType::Border;
		pressedBrush.DrawAs = ESlateBrushDrawType::Border;
		disableBrush.DrawAs = ESlateBrushDrawType::Border;
	}
	normalPadding = m_buttonInfo.normalPadding;
	pressedPadding = m_buttonInfo.pressedPadding;
	if (pCWGameInstance->m_language == "Chinese")
		buttonTextFont = m_basicInfo.textChineseElementFont;
	else
		buttonTextFont = m_basicInfo.textElementFont;
	buttonTextColor = m_basicInfo.textElementColor;
	if (m_buttonInfo.pBorderTexture)
	{
		borderBrush.SetResourceObject(m_buttonInfo.pBorderTexture);
	}
}

void UWidgetManager::GetComboBoxStyle(FComboButtonStyle& comboButtonStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor)
{
	FSlateBrush normalBrush;
	FSlateBrush hoveredBrush;
	FSlateBrush pressBrush;
	FSlateBrush disableBrush;
	normalBrush.ImageSize = m_comboBoxInfo.bgImageSize;
	hoveredBrush.ImageSize = m_comboBoxInfo.bgImageSize;
	pressBrush.ImageSize = m_comboBoxInfo.bgImageSize;
	disableBrush.ImageSize = m_comboBoxInfo.bgImageSize;
	normalBrush.Margin = m_comboBoxInfo.bgMargin;
	hoveredBrush.Margin = m_comboBoxInfo.bgMargin;
	pressBrush.Margin = m_comboBoxInfo.bgMargin;
	disableBrush.Margin = m_comboBoxInfo.bgMargin;
	if (m_comboBoxInfo.pComboBGTexture)
	{
		normalBrush.SetResourceObject(m_comboBoxInfo.pComboBGTexture);
		hoveredBrush.SetResourceObject(m_comboBoxInfo.pComboBGTexture);
		pressBrush.SetResourceObject(m_comboBoxInfo.pComboBGTexture);
		disableBrush.SetResourceObject(m_comboBoxInfo.pComboBGTexture);
	}
	normalBrush.TintColor = m_basicInfo.themeColorNormal;
	hoveredBrush.TintColor = m_basicInfo.themeColorHover;
	pressBrush.TintColor = m_basicInfo.themeColorExtra;
	disableBrush.TintColor = m_basicInfo.themeColorDisable;
	FButtonStyle buttonStyle;
	buttonStyle.Normal = normalBrush;
	buttonStyle.Hovered = hoveredBrush;
	buttonStyle.Pressed = pressBrush;
	buttonStyle.Disabled = disableBrush;
	buttonStyle.NormalPadding = m_comboBoxInfo.normalPadding;
	buttonStyle.PressedPadding = m_comboBoxInfo.pressedPadding;

	FSlateBrush downArrowBrush;
	downArrowBrush.ImageSize = m_comboBoxInfo.arrowImageSize;
	downArrowBrush.Margin = m_comboBoxInfo.arrowMargin;
	if (m_comboBoxInfo.pArrowTexture)
	{
		downArrowBrush.SetResourceObject(m_comboBoxInfo.pArrowTexture);
	}
	if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Null)
		downArrowBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Box)
		downArrowBrush.DrawAs = ESlateBrushDrawType::Box;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Border)
		downArrowBrush.DrawAs = ESlateBrushDrawType::Border;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Image)
		downArrowBrush.DrawAs = ESlateBrushDrawType::Image;

	FSlateBrush borderBrush;
	borderBrush.ImageSize = m_comboBoxInfo.borderSize;
	borderBrush.Margin = m_comboBoxInfo.borderMargin;
	borderBrush.TintColor = m_basicInfo.themeColorNormal;
	if (m_comboBoxInfo.pBorderTexture)
	{
		borderBrush.SetResourceObject(m_comboBoxInfo.pBorderTexture);
	}
	if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Null)
		borderBrush.DrawAs = ESlateBrushDrawType::NoDrawType;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Box)
		borderBrush.DrawAs = ESlateBrushDrawType::Box;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Border)
		borderBrush.DrawAs = ESlateBrushDrawType::Border;
	else if (m_comboBoxInfo.arrowDrawAs == EDrawType::DT_Image)
		borderBrush.DrawAs = ESlateBrushDrawType::Image;

	comboButtonStyle.ButtonStyle = buttonStyle;
	comboButtonStyle.DownArrowImage = downArrowBrush;
	comboButtonStyle.MenuBorderBrush = borderBrush;
	comboButtonStyle.MenuBorderPadding = m_comboBoxInfo.menuBorderPadding;

	captionFont = m_basicInfo.textElementFont;
	captionColor = m_basicInfo.textElementColor;
}

void UWidgetManager::GetCheckBoxStyle(FCheckBoxStyle& checkBoxStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor)
{
	checkBoxStyle.CheckBoxType = ESlateCheckBoxType::CheckBox;
	checkBoxStyle.UncheckedImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.UncheckedHoveredImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.UncheckedPressedImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.CheckedImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.CheckedHoveredImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.CheckedPressedImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.UndeterminedImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.UndeterminedHoveredImage.ImageSize = m_checkBoxInfo.size;
	checkBoxStyle.UndeterminedPressedImage.ImageSize = m_checkBoxInfo.size;

	checkBoxStyle.UncheckedImage.TintColor = m_basicInfo.themeColorNormal;
	checkBoxStyle.UncheckedHoveredImage.TintColor = m_basicInfo.themeColorHover;
	checkBoxStyle.UncheckedPressedImage.TintColor = m_basicInfo.themeColorExtra;
	checkBoxStyle.CheckedImage.TintColor = m_basicInfo.themeColorNormal;
	checkBoxStyle.CheckedHoveredImage.TintColor = m_basicInfo.themeColorHover;
	checkBoxStyle.CheckedPressedImage.TintColor = m_basicInfo.themeColorExtra;
	checkBoxStyle.UndeterminedImage.TintColor = m_basicInfo.themeColorNormal;
	checkBoxStyle.UndeterminedHoveredImage.TintColor = m_basicInfo.themeColorHover;
	checkBoxStyle.UndeterminedPressedImage.TintColor = m_basicInfo.themeColorExtra;

	checkBoxStyle.UncheckedImage.SetResourceObject(m_checkBoxInfo.pUncheckTexture);
	checkBoxStyle.UncheckedHoveredImage.SetResourceObject(m_checkBoxInfo.pUncheckTexture);
	checkBoxStyle.UncheckedPressedImage.SetResourceObject(m_checkBoxInfo.pUncheckTexture);
	checkBoxStyle.CheckedImage.SetResourceObject(m_checkBoxInfo.pCheckTexture);
	checkBoxStyle.CheckedHoveredImage.SetResourceObject(m_checkBoxInfo.pCheckTexture);
	checkBoxStyle.CheckedPressedImage.SetResourceObject(m_checkBoxInfo.pCheckTexture);
	checkBoxStyle.UndeterminedImage.SetResourceObject(m_checkBoxInfo.pUndetermineTexture);
	checkBoxStyle.UndeterminedHoveredImage.SetResourceObject(m_checkBoxInfo.pUndetermineTexture);
	checkBoxStyle.UndeterminedPressedImage.SetResourceObject(m_checkBoxInfo.pUndetermineTexture);

	if (m_checkBoxInfo.drawAs == EDrawType::DT_Null)
	{
		checkBoxStyle.UncheckedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.UncheckedHoveredImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.UncheckedPressedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.CheckedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.CheckedHoveredImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.CheckedPressedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.UndeterminedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.UndeterminedHoveredImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		checkBoxStyle.UndeterminedPressedImage.DrawAs = ESlateBrushDrawType::NoDrawType;
	}
	else if (m_checkBoxInfo.drawAs == EDrawType::DT_Box)
	{
		checkBoxStyle.UncheckedImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.UncheckedHoveredImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.UncheckedPressedImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.CheckedImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.CheckedHoveredImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.CheckedPressedImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.UndeterminedImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.UndeterminedHoveredImage.DrawAs = ESlateBrushDrawType::Box;
		checkBoxStyle.UndeterminedPressedImage.DrawAs = ESlateBrushDrawType::Box;
	}
	else if (m_checkBoxInfo.drawAs == EDrawType::DT_Border)
	{
		checkBoxStyle.UncheckedImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.UncheckedHoveredImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.UncheckedPressedImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.CheckedImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.CheckedHoveredImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.CheckedPressedImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.UndeterminedImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.UndeterminedHoveredImage.DrawAs = ESlateBrushDrawType::Border;
		checkBoxStyle.UndeterminedPressedImage.DrawAs = ESlateBrushDrawType::Border;
	}
	else if (m_checkBoxInfo.drawAs == EDrawType::DT_Image)
	{
		checkBoxStyle.UncheckedImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.UncheckedHoveredImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.UncheckedPressedImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.CheckedImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.CheckedHoveredImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.CheckedPressedImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.UndeterminedImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.UndeterminedHoveredImage.DrawAs = ESlateBrushDrawType::Image;
		checkBoxStyle.UndeterminedPressedImage.DrawAs = ESlateBrushDrawType::Image;
	}
	checkBoxStyle.ForegroundColor = m_checkBoxInfo.foregroundColor;
	checkBoxStyle.BorderBackgroundColor = m_checkBoxInfo.borderColor;
	checkBoxStyle.Padding = m_checkBoxInfo.padding;
	captionFont = m_basicInfo.textElementFont;
	captionColor = m_basicInfo.textElementColor;
}

void UWidgetManager::GetSliderStyle(FSliderStyle& sliderStyle, FSlateFontInfo& captionFont, FSlateColor& captionColor)
{
	sliderStyle.NormalBarImage.ImageSize = m_sliderInfo.barImageSize;
	sliderStyle.DisabledBarImage.ImageSize = m_sliderInfo.barImageSize;
	sliderStyle.NormalThumbImage.ImageSize = m_sliderInfo.thumbSize;
	sliderStyle.DisabledThumbImage.ImageSize = m_sliderInfo.thumbSize;

	sliderStyle.NormalBarImage.TintColor = m_sliderInfo.barNormalTint;
	sliderStyle.DisabledBarImage.TintColor = m_sliderInfo.barDisableTint;
	sliderStyle.NormalThumbImage.TintColor = m_sliderInfo.thumbNormalTint;
	sliderStyle.DisabledThumbImage.TintColor = m_sliderInfo.thumbDisableTint;

	sliderStyle.NormalBarImage.SetResourceObject(m_sliderInfo.pBarTexture);
	sliderStyle.DisabledBarImage.SetResourceObject(m_sliderInfo.pBarTexture);
	sliderStyle.NormalThumbImage.SetResourceObject(m_sliderInfo.pThumbTexture);
	sliderStyle.DisabledThumbImage.SetResourceObject(m_sliderInfo.pThumbTexture);

	if (m_sliderInfo.barDrawAs == EDrawType::DT_Null)
	{
		sliderStyle.NormalBarImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		sliderStyle.DisabledBarImage.DrawAs = ESlateBrushDrawType::NoDrawType;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Box)
	{
		sliderStyle.NormalBarImage.DrawAs = ESlateBrushDrawType::Box;
		sliderStyle.DisabledBarImage.DrawAs = ESlateBrushDrawType::Box;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Border)
	{
		sliderStyle.NormalBarImage.DrawAs = ESlateBrushDrawType::Border;
		sliderStyle.DisabledBarImage.DrawAs = ESlateBrushDrawType::Border;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Image)
	{
		sliderStyle.NormalBarImage.DrawAs = ESlateBrushDrawType::Image;
		sliderStyle.DisabledBarImage.DrawAs = ESlateBrushDrawType::Image;
	}

	if (m_sliderInfo.barDrawAs == EDrawType::DT_Null)
	{
		sliderStyle.NormalThumbImage.DrawAs = ESlateBrushDrawType::NoDrawType;
		sliderStyle.DisabledThumbImage.DrawAs = ESlateBrushDrawType::NoDrawType;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Box)
	{
		sliderStyle.NormalThumbImage.DrawAs = ESlateBrushDrawType::Box;
		sliderStyle.DisabledThumbImage.DrawAs = ESlateBrushDrawType::Box;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Border)
	{
		sliderStyle.NormalThumbImage.DrawAs = ESlateBrushDrawType::Border;
		sliderStyle.DisabledThumbImage.DrawAs = ESlateBrushDrawType::Border;
	}
	else if (m_sliderInfo.barDrawAs == EDrawType::DT_Image)
	{
		sliderStyle.NormalThumbImage.DrawAs = ESlateBrushDrawType::Image;
		sliderStyle.DisabledThumbImage.DrawAs = ESlateBrushDrawType::Image;
	}

	sliderStyle.BarThickness = m_sliderInfo.barThickness;

	captionColor = m_basicInfo.textElementColor;
	captionFont = m_basicInfo.textElementFont;
}

void UWidgetManager::GetElementTextStyle(FSlateFontInfo& font, FSlateColor& color)
{
	font = m_basicInfo.textElementFont;
	color = m_basicInfo.textElementColor;
}

void UWidgetManager::SetTheme(EWidgetTheme theme)
{
	for (int32 i=0; i<m_allThemeData.Num(); i++)
	{
		if (theme == m_allThemeData[i].theme)
		{
			m_basicInfo = m_allThemeData[i].basicTheme;
			m_buttonInfo = m_allThemeData[i].buttonInfo;
			m_checkBoxInfo = m_allThemeData[i].checkBoxInfo;
			m_comboBoxInfo = m_allThemeData[i].comboBoxInfo;
			m_inputTextInfo = m_allThemeData[i].inputTextInfo;
			m_sliderInfo = m_allThemeData[i].sliderInfo;
			break;
		}
	}
}

