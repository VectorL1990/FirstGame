// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayCard.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "EventCard.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FDescriptionAndChoice
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString descriptions;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString chDescriptions;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> choiceStrs;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> chChoiceStrs;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> choices;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDescriptionTreeNode
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FDescriptionAndChoice descriptionAndChoice;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<int32> childrenNodeNbs;
};



USTRUCT(BlueprintType, Blueprintable)
struct FEventFunctionList
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<FEventFunction> list;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString cardName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString chCardName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString SAName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FDescriptionTreeNode> allNodes;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 rootNodeNb;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FDiceBattleInfo diceInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FTheorizeInfo theorizeInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FDrawCardInfo m_drawCardInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FCardShopInfo m_cardShopInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FBattleInfo battleInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<FString, FEventFunctionList> actionChoiceMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 defaultActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 level;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventCardInfoList
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEventCardInfo> eventCardInfoList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FChAndEnDescriptionList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enDescriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> chDescriptions;

};

USTRUCT()
struct FActionNodeBriefInfo
{
	GENERATED_USTRUCT_BODY()
public:
	uint8 actionType;

	FString nodeName;

	uint8 rewardType;
};

USTRUCT()
struct FActionNodeBriefInfoList
{
	GENERATED_USTRUCT_BODY()
public:
	TArray<FActionNodeBriefInfo> actionNodeBriefInfoList;
};

UCLASS()
class COLLISIONWAR_API AEventCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitialCard();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupPlayCard(UStaticMeshComponent* pCardImageMesh, UStaticMeshComponent* pCardMesh,UStaticMeshComponent* pCardRoundCircle, UStaticMeshComponent* pRewardMesh);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateWarp(float percent);

	void InitialPlayCard(uint8 cardType);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void StartWarpIn();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void WarpInEnd();
	
	UPROPERTY()
	UStaticMeshComponent* m_pCardImageMesh;

	UPROPERTY()
		UStaticMeshComponent* m_pCardMesh;

	UPROPERTY()
		UStaticMeshComponent* m_pCardImageRoundCircle;

	UPROPERTY()
		UStaticMeshComponent* m_pRewardMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystem* m_pWarpPS;

	uint8 m_cardType;

	UPROPERTY()
	FEventCardInfo m_eventCardInfo;

	UPROPERTY()
	FString m_nodeName;

	uint8 m_rewardType;

	UPROPERTY()
	FDescriptionTreeNode m_curTreeNode;

	FString m_choiceSelectStr;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isFlip = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_tolerance = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_rotateSpeed = 15.f;
};
