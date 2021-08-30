// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VectorAndMarkAndUpdate.generated.h"


/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UVectorAndMarkAndUpdate : public UObject
{
	GENERATED_BODY()
public:
	UVectorAndMarkAndUpdate(const FObjectInitializer& ObjectInitializer);

	float x = 0;
	float y = 0;
	float z = 0;
	int agentMark = -1;
	unsigned char state = 0;
	unsigned char targetState = -1;
};
