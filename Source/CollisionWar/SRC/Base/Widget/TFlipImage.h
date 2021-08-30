// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TFlipImage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FTextureList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<UTexture2D*> pTextureList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTexture*> pTextures;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAlternateTextureInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 firstCornerTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 rearCornerTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 fullInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 alternatePeriod;
};

UCLASS()
class COLLISIONWAR_API UTFlipImage : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialFlipImage(UImage* pFlipImage, UImage* pAlternateImage);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FlipbookTick();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ClearFlipbookTimer();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyActivateManually();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_flipType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FAlternateTextureInfo m_alternateTextureInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool m_isLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool m_isAutoPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool m_existAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float m_playRate;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTimerHandle m_timerHandle;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FSlateColor m_imageColor;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FLinearColor m_color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 m_startFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FTextureList m_textureList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 m_framesPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool m_useRedChannelAsAlpha = false;

	UPROPERTY()
	TArray<FSlateBrush> m_brushes;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pAlternateImage;

	int32 m_curFrame;

	int32 m_curOriginImageTime;

	int32 m_curSwitchImageTime;

	bool switchToAlternateImage = false;

	
};
