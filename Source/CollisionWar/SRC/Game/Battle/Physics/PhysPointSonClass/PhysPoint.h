// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/BasePhysGeo.h"
#include "../../../Character/BaseCharacter.h"
#include "PhysPoint.generated.h"



UCLASS()
class COLLISIONWAR_API APhysPoint : public ABasePhysGeo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
public:	

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill = true) override;

	void InitialPoint(ABaseCharacter* pHost, int32 campFlag, int32 movePertick);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Physics")
	void OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Physics")
	void OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent);

	/************************************************************************/
	/* 蓝图生成属性
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	UParticleSystemComponent* m_pMutationPSComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	float m_maxLifeTime = 4.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Physics")
	int32 m_pointRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	USoundBase* m_pHitSound;
	/************************************************************************/
	/* 计算属性
	/************************************************************************/

	//virtual void SetMutationPS() override;

	UPROPERTY()
	float m_curLifeTime;

	UPROPERTY()
		TArray<ABasePhysGeo*> m_pOverlapGeos;
	
	bool m_hitSolid = false;
};
