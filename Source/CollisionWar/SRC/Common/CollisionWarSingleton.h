// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CollisionWarSingleton.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FItem
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		FString itemName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		int32 num;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TArray<int32> codeList;

	FItem()
	{
		itemName = "NULL";
		num = 0;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FCombineInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TMap<FString, int32> itemMap;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		FItem combineInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	TSubclassOf<class UObject> equipmentInfoClass;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBuildWorkShopInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TArray<FItem> itemList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPhysActorPopMenuInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TSubclassOf<class UUserWidget> widgetClass;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	float drawSizeX;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	float drawSizeY;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAsyncLoadClassAndPathInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TSubclassOf<class UObject> asyncLoadClass;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString path;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSoftObjectPathList
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<FSoftObjectPath> itemtoStream;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBaseCharacterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TSubclassOf<class UObject> pCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 grade;
};

UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UCollisionWarSingleton : public UObject
{
	GENERATED_BODY()
public:
	UCollisionWarSingleton(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	TSubclassOf<class UObject> FindEffectClassByName(FString effectName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	UParticleSystem* FindJudgeParticleByNb(int32 nb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	UParticleSystem* FindHitParticleByName(FString effectName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyReadSingleprogressMeshAndMat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<int32> m_cosExpandList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<int32> m_intSqrtList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, TSubclassOf<class UObject> > m_effectClassMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, UParticleSystem*> m_judgeResultParticleMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, UParticleSystem*> m_hitParticleMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FCombineInfo> m_combineInfoList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, FBuildWorkShopInfo> m_buildWorkShopInfoMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, UTexture2D*> m_itemTextureMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FPhysActorPopMenuInfo m_physActorPopMenuInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UStaticMesh*> m_pStaticMeshMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UMaterialInstance*> m_pMatMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_detonationMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UParticleSystem*> m_attachPSMap;
	/************************************************************************/
	/* 人物升级部分固定参数
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_playerAtkRollRate = 1.06;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_playerDfcRollRate = 1.04;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_playerHpRollRate = 1.025;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_enermyAtkRollRate = 1.06;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_enermyDfcRollRate = 1.025;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_enermyHpRollRate = 1.025;
	/************************************************************************/
	/* Asyncload
	/************************************************************************/
	
	void ReqAsynLoad(int32 infoNb);

	UFUNCTION()
		void AsynLoadCharacterDone();

	UFUNCTION()
	void AsyncLoadDumpActorDone();

	UFUNCTION()
		void AsyncLoadPhysGeoDone();

	UFUNCTION()
		void AsyncLoadSADone();

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FAsyncLoadClassAndPathInfo> m_asyncLoadClassAndPathInfos;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<int32, FSoftObjectPathList> m_softObjectPathMap;

	FStreamableManager m_streamableManager;

	UPROPERTY()
	TMap<FString, UClass*> m_allCharacterInfo;

	UPROPERTY()
		TMap<FString, UClass*> m_dumpActorClassMap;

	UPROPERTY()
		TMap<FString, UClass*> m_physGeoClassMap;

	UPROPERTY()
		TMap<FString, UClass*> m_SAClassMap;

	TArray<uint8> m_asyncLoadStateDone;

	UObjectLibrary* m_pCharacterObjectLibrary;

	UObjectLibrary* m_pDumpActorObjectLibrary;

	UObjectLibrary* m_pPhysGeoObjectLibrary;

	UObjectLibrary* m_pSAObjectLibrary;
};
