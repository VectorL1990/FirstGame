// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AsyncLoadDataAsset.generated.h"

/**
 * 
 */
USTRUCT()
struct FAssetContentInfo
{
	GENERATED_USTRUCT_BODY()
public:
		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 ID;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TSoftObjectPtr<UObject> asset;

	FAssetContentInfo()
	{
		ID = 0;
		asset = FSoftObjectPath("");
	}
};

UCLASS()
class COLLISIONWAR_API UAsyncLoadDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FAssetContentInfo> m_assetList;
	
};
