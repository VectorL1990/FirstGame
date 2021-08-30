// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Base/Widget/TemplateCharacterInfo.h"
#include "Image.h"
#include "VerticalBox.h"
#include "TFCInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTFCInfo : public UTemplateCharacterInfo
{
	GENERATED_BODY()
public:

	void UpdateFCInfo();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pSkillVBox;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_skillMaterialCardMargin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FMargin m_skillCardMargin;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_skillHBoxMargin;
};
