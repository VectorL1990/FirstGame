// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BattlePlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ABattlePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base/Battle")
	FVector m_POVLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base/Battle")
	FRotator m_POVRotation;
};
