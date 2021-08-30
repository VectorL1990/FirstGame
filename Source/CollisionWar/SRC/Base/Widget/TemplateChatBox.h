// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBox.h"
#include "Image.h"
#include "ScrollBox.h"
#include "EditableTextBox.h"
#include "HorizontalBox.h"
#include "HorizontalBoxSlot.h"
#include "TemplateInvisibleButton.h"
#include "TemplateTextLine.h"
#include "WidgetManager.h"
#include "TemplateChatBox.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSendMessageDelegate, FString, friendName, FString, message);

UCLASS()
class COLLISIONWAR_API UTemplateChatBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialChatBox(UImage* pChatBoxBG, UButton* pChatBoxButton, UImage* pChatBoxTopDivision, UImage* pChatBoxBottomDivision,
		UScrollBox* pMessageScrollBox, UImage* pMiddleDivision, UScrollBox* pFriendListScrollBox, UImage* pLowDivision,
		UButton* pSendMessageButton, UEditableTextBox* pInputTextBox);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SwitchCustomFriend(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void RefreshFriendList();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickSendMessageButton();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pChatBoxBG;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pChatBoxButton;

	/** Content box components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pChatBoxTopDivision;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pChatBoxBottomDivision;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pMessageScrollBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pMiddleDivision;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pFriendListScrollBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pLowDivision;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pSendMessageButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UEditableTextBox* m_pInputTextBox;

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	bool m_isShow = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_maxMessageNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_messageTextLineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_invisibleButtonHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_divisionWidth;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	EHorizontalAlignmentType m_hMessageAlignment;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FString> m_friendNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTemplateInvisibleButton* m_pCurSelectFriendButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_hintText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_inputMessage;

	/** Elements
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateInvisibleButton*> m_pFriendButtonList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateTextLine*> m_pMessageTextLines;

	/** Logic members
	*/
	UPROPERTY()
	FSendMessageDelegate m_sendMessageDelegate;
};
