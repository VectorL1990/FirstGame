// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../Base/Animation/BaseAnimInstance.h"
#include "DemoCharacter.generated.h"

UCLASS()
class COLLISIONWAR_API ADemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Character")
	void SetupItemComponentList(USkeletalMeshComponent* pBaseMesh, const TArray<FCharacterSKComponentInfo>& pSMComponents);

	void TriggerDemoAnim(FString motionName);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCharacterSKComponentInfo> m_pItemComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, USkeletalMeshComponent*> m_pItemComponentMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, uint8> m_itemComponentType;

	UBaseAnimInstance* m_pAnimInstance;
};
