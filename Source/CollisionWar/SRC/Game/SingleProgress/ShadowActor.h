// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShadowActor.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexSlopeInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 extraEnergyIncreasePerT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 mentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 suppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 activity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 darkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 flameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 sunFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		float changeInterval;

};

USTRUCT(BlueprintType, Blueprintable)
struct FRangeOverallIndexSlopeInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minExtraEnergyIncreasePerT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxExtraEnergyIncreasePerT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minFlameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxFlameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minSunFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxSunFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		float changeInterval;
};

USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexValueInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 mentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 suppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 activity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 darkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 flameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 sunFaith;

	void Reset()
	{
		life = 0;
		energy = 0;
		money = 0;
		mentality = 0;
		suppression = 0;
		activity = 0;
		darkness = 0;
		flameFaith = 0;
		sunFaith = 0;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FRangeOverallIndexValueInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minFlameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxFameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minSunFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxSunFaith;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSAEventFunction
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString functionName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<int32> values;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSAOverallIndexSlopInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString SAName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FOverallIndexSlopeInfo info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FOverallIndexValueInfo limitChangeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FSAEventFunction> eventFunctionInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString chDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString enDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 level;

	/** 标记是什么时候起作用
	* 0. 主动作用，即一放下即发动
	* 1. 被动作用，即被动触发
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 exertType = 0;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventOverallIndexSlopInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FOverallIndexSlopeInfo info;

	UPROPERTY()
		FOverallIndexValueInfo limitChangeInfo;

	UPROPERTY()
		float maxInterval;

	UPROPERTY()
		float curInterval;

	UPROPERTY()
	float curSlopeTick = 0;
};

UCLASS()
class COLLISIONWAR_API AShadowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadowActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnBeginOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnEndOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FOverallIndexSlopeInfo m_overallIndexModificationInfo;*/
	bool m_isSet = false;

	FString m_SAName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isOverlapSA = false;

	TArray<AActor*> m_pOverlapSAs;

	int32 m_idx;
};
