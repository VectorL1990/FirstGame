// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/CWBaseGameMode.h"
#include "../../Common/CollisionWarSingleton.h"
#include "../../Base/Login/LoginPlayerController.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ALoginGameModeBase : public ACWBaseGameMode
{
	GENERATED_BODY()
	
public:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Login")
	void OpenSPLevel();

	void FadeToSPLevel();

	void FadeOutDone();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Login")
	void ReadCharacterPrefixSkills(const FString& characterName);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_cameraFadeTime;

	FTimerHandle m_cameraFadeTimerHandle;

	UCollisionWarSingleton* m_pCWSingleton;

	ALoginPlayerController* m_pLPC;

	bool m_canTick = false;

	bool m_hasApplyAsyncLoad = false;

	uint8 m_type = 0;
};
