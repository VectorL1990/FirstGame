// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Slider.h"
#include "TemplateProgressSlider.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FSliderDefaultInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString sliderTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chsliderTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString sliderFunction;
};

UCLASS()
class COLLISIONWAR_API UTemplateProgressSlider : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent , Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SliderChange(float value);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USlider* m_pSlider;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_function;

};
