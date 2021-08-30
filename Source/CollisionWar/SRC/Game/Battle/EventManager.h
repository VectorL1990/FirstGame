// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "EventManager.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UEventManager : public UObject
{
	GENERATED_BODY()
public:

	void GenerateRandCode();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> m_curRandCode;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FHistoryEvent> events;
};
