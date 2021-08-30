// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "PlanSpawnPoint.generated.h"

UCLASS()
class COLLISIONWAR_API APlanSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	FLogicVec2D m_spawnPointLoc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_spawnPointWidth;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_spawnYaw;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	FString m_className;
};
