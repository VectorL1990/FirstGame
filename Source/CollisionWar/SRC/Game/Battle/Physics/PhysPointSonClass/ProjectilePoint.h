// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/PhysPointSonClass/PhysPoint.h"
#include "ProjectilePoint.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API AProjectilePoint : public APhysPoint
{
	GENERATED_BODY()
public:
	//AProjectilePoint();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialProjectilePoint(const FVector& initialLoc);

	void UpdateProjectileMovement(float dT);

	void CalculateHorizontalVel(FVector targetLoc);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UProjectileMovementComponent* m_pProjectileComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_upliftV;

	FVector m_velocity;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_acc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FDetonationInfo m_detonationInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TSubclassOf<class ABasePhysGeo> m_mutateGeoClass;

	//uint8 m_detonationState = 0;

	float m_curDetonationTime = 0;
};
