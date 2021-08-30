// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VectorAndMarkAndUpdate.h"
#include "VectorPack.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UVectorPack : public UObject
{
	GENERATED_BODY()
public:
	UVectorPack(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	TArray<UVectorAndMarkAndUpdate*> m_vec;

	bool isUpdate = false;
};
