// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/BasePhysGeo.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../../Common/CollisionWarBpFunctionLibrary.h"
#include "PhysPolygon.generated.h"

UCLASS()
class COLLISIONWAR_API APhysPolygon : public ABasePhysGeo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysPolygon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:	

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySpawnPolygon = true) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Physics")
	virtual void OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Physics")
	void OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent);
	UFUNCTION()
	void InitialPolygon(ABaseCharacter* pHost,int32 campFlag, int32 defaultHeight);
	UFUNCTION()
	void UpdatePolygon();
	/************************************************************************/
	/* 蓝图生成属性
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	UParticleSystemComponent* m_pMutationPSComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	float m_maxLifeTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle/Physics")
	USphereComponent* m_pFixComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	USoundBase* m_pSpawnSound;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	USoundBase* m_pHitSound;
	/************************************************************************/
	/* 计算属性
	/************************************************************************/

	UPROPERTY()
	float m_curLifeTime;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pOverlapGeos;

	bool m_hasSpawnSonGeo = false;
};
