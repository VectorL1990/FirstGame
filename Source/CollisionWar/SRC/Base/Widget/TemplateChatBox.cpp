// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "TemplateChatBox.h"




void UTemplateChatBox::NotifyInitial_Implementation()
{

}

void UTemplateChatBox::InitialChatBox(UImage* pChatBoxBG, UButton* pChatBoxButton, UImage* pChatBoxTopDivision, 
	UImage* pChatBoxBottomDivision, UScrollBox* pMessageScrollBox, UImage* pMiddleDivision, UScrollBox* pFriendListScrollBox, 
	UImage* pLowDivision, UButton* pSendMessageButton, UEditableTextBox* pInputTextBox)
{
	m_pChatBoxBG = pChatBoxBG;
	m_pChatBoxButton = pChatBoxButton;
	m_pChatBoxTopDivision = pChatBoxTopDivision;
	m_pChatBoxBottomDivision = pChatBoxBottomDivision;
	m_pMessageScrollBox = pMessageScrollBox;
	m_pMiddleDivision = pMiddleDivision;
	m_pFriendListScrollBox = pFriendListScrollBox;
	m_pLowDivision = pLowDivision;
	m_pSendMessageButton = pSendMessageButton;
	m_pInputTextBox = pInputTextBox;
}

void UTemplateChatBox::SwitchCustomFriend(FString buttonFunction)
{
	for (int32 i=0; i<m_pFriendButtonList.Num(); i++)
	{
		if (!m_pFriendButtonList[i]) continue;
		if (m_pFriendButtonList[i]->m_buttonFunction == buttonFunction)
		{
			if (m_pCurSelectFriendButton == m_pFriendButtonList[i]) return;
			m_pCurSelectFriendButton->SetDeactive();
			m_pFriendButtonList[i]->SetActive();
			m_pCurSelectFriendButton = m_pFriendButtonList[i];
		}
	}
}

void UTemplateChatBox::RefreshFriendList()
{
	if (!m_pWidgetManager || !m_pWidgetManager->m_BPInvisibleButtonClass || !m_pFriendListScrollBox) return;
	while (m_pFriendButtonList.Num() > 0)
	{
		UTemplateInvisibleButton* pFriendButton = m_pFriendButtonList.Last();
		if (!pFriendButton)
		{
			m_pFriendButtonList.Pop();
			continue;
		}
		pFriendButton->RemoveFromParent();
		m_pFriendButtonList.Pop();
		if (!pFriendButton->IsValidLowLevel()) continue;
		pFriendButton->ConditionalBeginDestroy();
	}
	for (int32 i=0; i<m_friendNameList.Num(); i++)
	{
		UTemplateInvisibleButton* pTemplateButton = CreateWidget<UTemplateInvisibleButton>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_BPInvisibleButtonClass);
		if (!pTemplateButton) continue;
		pTemplateButton->m_caption = m_friendNameList[i];
		pTemplateButton->m_buttonFunction = TEXT("Friend_") + m_friendNameList[i];
		pTemplateButton->m_lineHeight = m_invisibleButtonHeight;
		pTemplateButton->NotifyInitial();
		UWidgetBlueprintFunctionLibrary::ApplyThemeToElement(m_pWidgetManager, pTemplateButton, EWidgetType::WidgetType_invisibleButton);
		UHorizontalBoxSlot* pLeftSpacerSlot = Cast<UHorizontalBoxSlot>(pTemplateButton->m_pLeftSpacer->Slot);
		UHorizontalBoxSlot* pRightSpacerSlot = Cast<UHorizontalBoxSlot>(pTemplateButton->m_pRightSpacer->Slot);
		FSlateChildSize leftSlotSize;
		FSlateChildSize rightSlotSize;
		switch (m_hMessageAlignment)
		{
		case HAlign_Fill:
			leftSlotSize.Value = 0.0f;
			leftSlotSize.SizeRule = ESlateSizeRule::Automatic;
			rightSlotSize.Value = 0.0f;
			rightSlotSize.SizeRule = ESlateSizeRule::Automatic;
			pLeftSpacerSlot->SetSize(leftSlotSize);
			pRightSpacerSlot->SetSize(rightSlotSize);
			break;
		case HAlign_Left:
			leftSlotSize.Value = 0.0f;
			leftSlotSize.SizeRule = ESlateSizeRule::Automatic;
			pLeftSpacerSlot->SetSize(leftSlotSize);
			rightSlotSize.Value = 1.0f;
			rightSlotSize.SizeRule = ESlateSizeRule::Fill;
			pRightSpacerSlot->SetSize(rightSlotSize);
			break;
		case HAlign_Right:
			leftSlotSize.Value = 1.0f;
			leftSlotSize.SizeRule = ESlateSizeRule::Fill;
			pLeftSpacerSlot->SetSize(leftSlotSize);
			rightSlotSize.Value = 0.0f;
			rightSlotSize.SizeRule = ESlateSizeRule::Automatic;
			pRightSpacerSlot->SetSize(rightSlotSize);
			break;
		case HAlign_Center:
			leftSlotSize.Value = 1.0f;
			leftSlotSize.SizeRule = ESlateSizeRule::Fill;
			pLeftSpacerSlot->SetSize(leftSlotSize);
			rightSlotSize.Value = 1.0f;
			rightSlotSize.SizeRule = ESlateSizeRule::Fill;
			pRightSpacerSlot->SetSize(rightSlotSize);
			break;
		}
		m_pFriendButtonList.Add(pTemplateButton);
		m_pFriendListScrollBox->AddChild(pTemplateButton);
	}
}

void UTemplateChatBox::ClickSendMessageButton()
{
	m_sendMessageDelegate.Broadcast(m_pCurSelectFriendButton->m_caption, m_inputMessage);
}
