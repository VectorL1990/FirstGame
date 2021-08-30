// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/SingleProgress/PlayCard.h"
#include "NumericCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ANumericCard : public APlayCard
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupNumericCard(UStaticMeshComponent* pBaseMesh, UStaticMeshComponent* pColorMesh1, UStaticMeshComponent* pColorMesh2, UTextRenderComponent* pNb);

	virtual void InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName) override;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pColorMesh1;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pColorMesh2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextRenderComponent* m_pNbRender;

	
};
