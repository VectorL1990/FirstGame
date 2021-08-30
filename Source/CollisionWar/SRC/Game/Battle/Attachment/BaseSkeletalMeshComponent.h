// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class COLLISIONWAR_API UBaseSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UBaseSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Attachment")
	FName m_attachPointName;
};
