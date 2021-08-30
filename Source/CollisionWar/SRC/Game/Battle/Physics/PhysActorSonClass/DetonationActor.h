// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "DetonationActor.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API ADetonationActor : public ABasePhysActor
{
	GENERATED_BODY()
public:
	ADetonationActor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void SetSMComponent(UStaticMeshComponent* pSMComponent);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void InitialDetonationActor();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		void ActivateDetonation(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
		virtual void OnBaseComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp) override;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
		FDetonationInfo m_detonationInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TSubclassOf<class ABasePhysGeo> m_mutateGeoClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle/Physics")
	UStaticMeshComponent* m_pBasicSMComponent;
	
	uint8 m_detonationState = 0;

	float m_curDetonationTime = 0;
};
