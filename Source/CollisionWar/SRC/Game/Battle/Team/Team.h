// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../../Character/BaseCharacter.h"
#include "../../Character/KingCharacter/King.h"
#include "MarchSquad.h"
#include "Team.generated.h"


UCLASS()
class COLLISIONWAR_API ATeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeam();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SortCharacterCW(TArray<int32> posList, int32 pos, int32 maxPos, int32 preDifPos, int32& returnPos, int32& difPos);

	void SortCharacterCCW(TArray<int32> posList, int32 pos, int32 maxPos, int32 preDifPos, int32& returnPos, int32& difPos);

	UFUNCTION()
	void CharactersFormation();

	UPROPERTY()
	int32 m_campFlag = 0;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	TArray<ABaseCharacter*> m_pCharacters;

	UPROPERTY()
	TArray<UMarchSquad*> m_pMarchSquads;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int32 m_minCharacterSurroundNb = 6;
};
