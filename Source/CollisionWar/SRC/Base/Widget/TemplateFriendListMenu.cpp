// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "TemplateFriendListMenu.h"




void UTemplateFriendListMenu::NotifyInitial_Implementation()
{

}

void UTemplateFriendListMenu::InitialFriendListMenu(UImage* pDarkBG, USizeBox* pContentSizeBox, UImage* pContentBoxBG, 
	UBorder* pContentBoxBorder1, UScrollBox* pContentScrollBox1, UTextBlock* pContentBoxHeaderText1, UBorder* pContentBoxBorder2, 
	UScrollBox* pContentScrollBox2, UTextBlock* pContentBoxHeaderText2, UVerticalBox* pDetailVBox, UBorder* pPlayerStateBorder, 
	UHorizontalBox* pSearchHBox, UTextBlock* pSearchBoxCaption, UEditableTextBox* pSearchEditBox, UButton* pSearchButton, 
	UHorizontalBox* pSearchResultHBox, UTextBlock* pSearchResultText, UButton* pAddFriendButton, UButton* pResumeButton, 
	UTextBlock* pResumeButtonCaption)
{
	m_pDarkBG = pDarkBG;
	m_pContentSizeBox = pContentSizeBox;
	m_pContentBoxBG = pContentBoxBG;
	m_pContentBoxBorder1 = pContentBoxBorder1;
	m_pContentScrollBox1 = pContentScrollBox1;
	m_pContentBoxHeaderText1 = pContentBoxHeaderText1;
	m_pContentBoxBorder2 = pContentBoxBorder2;
	m_pContentScrollBox2 = pContentScrollBox2;
	m_pContentBoxHeaderText2 = pContentBoxHeaderText2;
	m_pDetailVBox = pDetailVBox;
	m_pPlayerStateBorder = pPlayerStateBorder;
	m_pSearchHBox = pSearchHBox;
	m_pResumeButtonCaption = pSearchBoxCaption;
	m_pSearchEditBox = pSearchEditBox;
	m_pSearchButton = pSearchButton;
	m_pSearchResultHBox = pSearchResultHBox;
	m_pSearchResultText = pSearchResultText;
	m_pAddFriendButton = pAddFriendButton;
	m_pResumeButton = pResumeButton;
	m_pResumeButtonCaption = pResumeButtonCaption;
	//设置UI尺寸
	if (m_pContentSizeBox)
	{
		FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
		float sizeX = FMath::Clamp(m_size.X, 0.0f, 1.0f);
		float scaleSizeX = sizeX * viewportSize.X;
		float sizeY = FMath::Clamp(m_size.Y, 0.0f, 1.0f);
		float scaleSizeY = sizeY * viewportSize.Y;
		float viewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
		FVector2D scaleSize(scaleSizeX / viewportScale, scaleSizeY / viewportScale);
		UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(m_pContentSizeBox->Slot);
		pCanvasSlot->SetSize(scaleSize);
	}
	//设置scrollbox之间的间距
	if (m_pContentBoxBorder1 && m_pContentBoxBorder2)
	{
		UWidgetBlueprintFunctionLibrary::SetPad(m_pContentBoxBorder1, ESlotType::ST_HSlot, 0.0f, 0.0f, m_scrollBoxSpacing, 0.0f);
		UWidgetBlueprintFunctionLibrary::SetPad(m_pContentBoxBorder2, ESlotType::ST_HSlot, 0.0f, 0.0f, m_scrollBoxSpacing, 0.0f);
	}
	//设置背景
	if (m_pBGTexture && m_pContentBoxBG)
	{
		FSlateBrush bgBrush;
		bgBrush.ImageSize = FVector2D(32.0f, 32.0f);
		bgBrush.SetResourceObject(m_pBGTexture);
		m_pContentBoxBG->SetBrush(bgBrush);
	}
}

void UTemplateFriendListMenu::FriendListMenuFadeOutDone()
{
	m_friendListMenuFadeOutDoneDelegate.Broadcast(m_menuName);
}

void UTemplateFriendListMenu::SwitchPlayerInfo(FString buttonFunction)
{
	FString chopPlayerName;
	FString totalWinNb;
	if (m_pCurPlayerTag)
	{
		for (int32 i = 0; i < m_playerTagInfos.Num(); i++)
		{
			chopPlayerName = buttonFunction.RightChop(17);
			if (chopPlayerName == m_playerTagInfos[i].playerName)
			{
				m_pCurPlayerTag->SetDeactive();
				break;
			}
		}
	}
	
	for (int32 i = 0; i < m_playerTagInfos.Num(); i++)
	{
		chopPlayerName = buttonFunction.RightChop(17);
		if (chopPlayerName == m_playerTagInfos[i].playerName)
		{
			m_pCurPlayerTag = m_pPlayerTags[i];
			m_pCurPlayerTag->SetActive();
			totalWinNb = FString::FromInt(m_playerTagInfos[i].totalWinNb);
			break;
		}
	}
	if (m_pPlayerDetailWidget)
	{
		m_pPlayerDetailWidget->m_playerName = chopPlayerName;
		m_pPlayerDetailWidget->m_playerTotalWinNbText = totalWinNb;
	}
}

void UTemplateFriendListMenu::ClickResumeButton()
{
	m_friendListMenuResumeButtonClickDelegate.Broadcast("Button_FriendList_Resume");
}

void UTemplateFriendListMenu::ClickSearchButton()
{
	m_friendListMenuSearchClickDelegate.Broadcast("Button_FriendList_SearchPlayer");
}

void UTemplateFriendListMenu::ClickAddFriendButton()
{
	m_friendListMenuAddFriendClickDelegate.Broadcast("Button_FriendList_AddFriend");
}

void UTemplateFriendListMenu::AskMenuFadeOut_Implementation()
{

}
