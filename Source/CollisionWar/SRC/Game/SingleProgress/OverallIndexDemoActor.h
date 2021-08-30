// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverallIndexDemoActor.generated.h"

UCLASS()
class COLLISIONWAR_API AOverallIndexDemoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverallIndexDemoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDemoOverallIndexWords(const FString& demoWords);
	
	UParticleSystemComponent* m_pDemoPS;

	float m_curTick = 0;
};
