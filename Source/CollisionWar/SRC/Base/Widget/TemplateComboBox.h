// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "ComboBoxString.h"
#include "TemplateComboBox.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FComboBoxDefaultInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString comboboxTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chcomboboxTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		TArray<FString> comboboxOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chcomboboxFunction;
};

UCLASS()
class COLLISIONWAR_API UTemplateComboBox : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ComboSelectionChange(FString selectItem);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UComboBoxString * m_pComboBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCaption;

	FString m_function;
};
