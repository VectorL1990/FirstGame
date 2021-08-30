// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "DumpPhysActor.generated.h"

class ABasePhysGeo;

UCLASS()
class COLLISIONWAR_API ADumpPhysActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADumpPhysActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitialDumpActor();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetBasicComponent(UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UPROPERTY()
		UPrimitiveComponent* m_pBasicComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "CollisionWar")
	FString m_className;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar")
	int32 m_obtacleRadius = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar")
	int32 m_obtacleHeight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar")
	int32 m_actorRadius = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_isBoundaryActor = false;

	/*UPROPERTY()
	FLogicVec2D m_logicPos2D;*/

	/*UPROPERTY()
	FLogicVec2D m_logicForwardDir;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_relativeHeight;

	TMap<ABasePhysGeo*, float> m_timeDilationParams;
};
