// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "OverallIndexDemoActor.h"


// Sets default values
AOverallIndexDemoActor::AOverallIndexDemoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOverallIndexDemoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverallIndexDemoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverallIndexDemoActor::NotifyDemoOverallIndexWords_Implementation(const FString& demoWords)
{

}

