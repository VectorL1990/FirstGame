// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../../Common/CollisionWarBpFunctionLibrary.h"
#include "BaseTrigger.generated.h"


UCLASS()
class COLLISIONWAR_API ABaseTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialTrigger(FLogicVec2D logicLoc, FString spawnGroupName, bool isAutoGenerate);

	UPROPERTY()
	bool m_isTriggerOnFlag = false;

	UPROPERTY()
	int32 m_onCampFlag = 0;

	UPROPERTY()
	FLogicVec2D m_logicTriggerLoc;

	UPROPERTY()
	FString m_trigType;

	UPROPERTY()
	bool m_isAutoGenerate = false;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Physics")
	void OverlapTrigger(class AActor* otherActor, class UPrimitiveComponent* OtherComp);
};
