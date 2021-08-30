// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "ProducePhysActor.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API AProducePhysActor : public ABasePhysActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_goodsName;
};
