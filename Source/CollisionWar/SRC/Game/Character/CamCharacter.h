// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "CamCharacter.generated.h"

UCLASS()
class COLLISIONWAR_API ACamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetParticleBySceneType(uint8 type);


	void UpdateDayNight(float dT);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void ReadDayNightDLYaw(uint8 levelNb);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystemComponent* m_pPSComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FAppendPSInfo> m_pAppendPS;

	uint8 m_domain = 0;

	UPROPERTY()
	ACharacter* m_pTargetCharacter;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		ADirectionalLight* m_pDirectionLight;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		ASkyLight* m_pSkyLight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FVector2D m_dayNightLightRotTarget;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FVector2D m_dayNightLightSkyLightIntensityTarget;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FVector2D m_dayNightLightDLIntensityTarget;

	bool m_isDayOrNight = true;

	bool m_shouldRotatorDayNight = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_DLSpinVelocity;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_DLInterSpeed = 1.f;

};
