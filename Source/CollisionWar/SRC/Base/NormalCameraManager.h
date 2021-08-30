// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "NormalCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ANormalCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base")
	FVector m_POVLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base")
	FRotator m_POVRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base")
	FVector m_buildPOVLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Base")
	FRotator m_buildPOVRotation;
};
