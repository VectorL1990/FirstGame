// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBox.h"
#include "SizeBox.h"
#include "TemplateScrollBoxWrapper.h"
#include "TemplateScrollBox.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScrollBoxFadeOutDelegate, FString, caption);

UCLASS()
class COLLISIONWAR_API UTemplateScrollBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent , Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable , Category = "CollisionWar/Widget")
	void InitialTemplateScrollBox(UScrollBox* pScrollBox, USizeBox* pSizeBox);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyFadeIn();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ScrollBoxFadeOutDone();

	/** components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox * m_pScrollBox;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_scrollBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UWidget*> m_pElements;

	FScrollBoxFadeOutDelegate m_scrollBoxFadeOutDoneDelegate;
};
