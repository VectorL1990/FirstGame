// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../../Common/CollisionWarBpFunctionLibrary.h"
#include "ConstructionSite.generated.h"

UCLASS()
class COLLISIONWAR_API AConstructionSite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructionSite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TSubclassOf<class AActor> m_foundationClass;

	UPROPERTY()
	FFoundationCharacterOccupyInfo m_occupyInfo;

	UPROPERTY()
	FLogicVec3D m_logicLoc3D;

	int32 m_constructTime;
	
	int32 m_curConstructTime;

	UPROPERTY()
	UParticleSystem* m_pParticleTemplate;
};
