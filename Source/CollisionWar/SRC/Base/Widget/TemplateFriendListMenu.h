// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "SizeBox.h"
#include "Border.h"
#include "ScrollBox.h"
#include "TextBlock.h"
#include "VerticalBox.h"
#include "HorizontalBox.h"
#include "EditableTextBox.h"
#include "Button.h"
#include "TemplatePlayerDetail.h"
#include "TemplatePlayerTag.h"
#include "WidgetManager.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "TemplateFriendListMenu.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFriendListMenuFadeOutDoneDelegate, FString, menuName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFriendListMenuResumeButtonClickDelegate,const FString&, buttonName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFriendListMenuSearchButtonClickDelegate,const FString&, buttonName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFriendListMenuAddFriendButtonClickDelegate,const FString&, buttonName);

UCLASS()
class COLLISIONWAR_API UTemplateFriendListMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialFriendListMenu(UImage* pDarkBG, USizeBox* pContentSizeBox, UImage* pContentBoxBG, UBorder* pContentBoxBorder1,
		UScrollBox* pContentScrollBox1, UTextBlock* pContentBoxHeaderText1, UBorder* pContentBoxBorder2, UScrollBox* pContentScrollBox2,
		UTextBlock* pContentBoxHeaderText2, UVerticalBox* pDetailVBox, UBorder* pPlayerStateBorder, UHorizontalBox* pSearchHBox,
		UTextBlock* pSearchBoxCaption, UEditableTextBox* pSearchEditBox, UButton* pSearchButton, UHorizontalBox* pSearchResultHBox,
		UTextBlock* pSearchResultText, UButton* pAddFriendButton, UButton* pResumeButton, UTextBlock* pResumeButtonCaption);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void FriendListMenuFadeOutDone();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SwitchPlayerInfo(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickResumeButton();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void ClickSearchButton();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void ClickAddFriendButton();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void AskMenuFadeOut();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pDarkBG;

	/** Content box components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pContentSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pContentBoxBG;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UBorder* m_pContentBoxBorder1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pContentScrollBox1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pContentBoxHeaderText1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UBorder* m_pContentBoxBorder2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pContentScrollBox2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pContentBoxHeaderText2;

	/** Player detail components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pDetailVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UBorder* m_pPlayerStateBorder;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTemplatePlayerDetail* m_pPlayerDetailWidget;

	/** Search box components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UHorizontalBox* m_pSearchHBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pSearchBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UEditableTextBox* m_pSearchEditBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pSearchButton;

	/** Search result components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UHorizontalBox* m_pSearchResultHBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pSearchResultText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pAddFriendButton;

	/** Resume button components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pResumeButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pResumeButtonCaption;

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_menuName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_hintText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	bool m_isInScrollBox1 = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTemplatePlayerTag* m_pCurPlayerTag;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FPlayerTagInfo> m_playerTagInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_searchFriendName;
	/** Appearance members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTexture* m_pBGTexture;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FVector2D m_size;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FMargin m_margin;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_scrollBoxSpacing;

	/** Elements
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplatePlayerTag*> m_pPlayerTags;


	FFriendListMenuFadeOutDoneDelegate m_friendListMenuFadeOutDoneDelegate;
	FFriendListMenuResumeButtonClickDelegate m_friendListMenuResumeButtonClickDelegate;
	FFriendListMenuAddFriendButtonClickDelegate m_friendListMenuAddFriendClickDelegate;
	FFriendListMenuSearchButtonClickDelegate m_friendListMenuSearchClickDelegate;
};
