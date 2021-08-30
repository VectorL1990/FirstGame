// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LandBlock.h"
#include "LandBlockTile.h"
#include "MapGenerator.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELandBlockType : uint8
{
	LBT_NULL,
	LBT_Specified,
	LBT_Special,
};

USTRUCT(BlueprintType, Blueprintable)
struct FBigLandBlockTile
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		bool isOccupiedBySpecialLandBlock = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<ULandBlockTile*> pSonTiles;
};

USTRUCT(BlueprintType, Blueprintable)
struct FIsometricBlockList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<ULandBlockTile*> pElementTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	ULandBlockTile* pBasicJunctionBlock;
};


UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UMapGenerator : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void InitialMapGeneratorFromBlueprint(uint8 curProgress);

	bool GenerateRandomMap(const TArray<FString>& specifiedLandBlockList);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadBlockInfoByName(uint8 curLevelProgress, const FString& blockName, ULandBlockTile* pTile);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadRoguelikeSMMap();

	void SpawnActorsInTiles();

	void SetTilesToBlockAsConnecting(ULandBlockTile* pMergeTile, int32 totalTileWidth, int32 totalTileHeight, TArray<ULandBlockTile*>& pMergeTileList, ULandBlockTile* pTargetTile);
	
	bool GetBuildTileListByCoords(int32 x, int32 y, int32 LExtend, int32 RExtent, int32 UExtent, int32 DExtent, TArray<FLogicVec2D>& gridList);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_bigTileWidthNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_bigTileHeightNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_bigTileWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_bigTileHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_specialLandBlockDensity;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_junctionBlockPercentage;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FLogicVec2D m_leftDownCornerCoord;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_tileWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_tileHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_buildTileWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_spawnEnermySampleDis;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_spawnEnermySampleExtent;

	FString m_mapName;

	TArray<FString> m_specifiedLandBlockNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_allSpecifiedLandBlockNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_allSpecialLandBlockNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_allJunctionBlockNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_allConnectBlockNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_allBarrierBlockNameList;

	TArray<FBigLandBlockTile> m_bigTiles;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<ULandBlockTile*> m_pTiles;

	TArray<ALandBlock*> m_pLandBlocks;

	TArray<int32> m_alreadyOccupiedBuildTiles;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UStaticMesh*> m_pAllLandBlockSMs;
};
