// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowActor.h"
#include "NumericCard.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "ActionPanel.generated.h"

UCLASS()
class COLLISIONWAR_API AActionPanel : public AShadowActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/************************************************************************/
	/* »ù´¡ÐÅÏ¢
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void InitialPanel();

	bool PutPlayCardInArray(ANumericCard* pPlayCard);

	bool RemovePlayCardOutArray(ANumericCard* pPlayCard);

	void ResetPanel();
	
	FLogicVec2D m_loc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FLogicVec2D> m_cardArrayLocs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FRotator> m_cardArrayRots;

	TArray<ANumericCard*> m_pPlayCards;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UStaticMeshComponent* m_pSkillDemoPlane;

	TArray<FOutputCardInfo> m_skillCardList;

	bool m_isActivate = false;

	FString m_skillName;
};
