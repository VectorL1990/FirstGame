// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "ShadowActor.h"


// Sets default values
AShadowActor::AShadowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AShadowActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> pComponents = GetComponentsByClass(USkeletalMeshComponent::StaticClass());
	for (int32 i = 0; i < pComponents.Num(); i++)
	{
		USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
		pSMComponent->bGenerateOverlapEvents = true;
		pSMComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		pSMComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
		//pSMComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Overlap);
		pSMComponent->OnComponentBeginOverlap.AddDynamic(this, &AShadowActor::OnBeginOverlap);
		pSMComponent->OnComponentEndOverlap.AddDynamic(this, &AShadowActor::OnEndOverlap);
	}

	TArray<UActorComponent*> pStaticComponents = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (int32 i = 0; i < pStaticComponents.Num(); i++)
	{
		UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticComponents[i]);
		pSMComponent->bGenerateOverlapEvents = true;
		pSMComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		pSMComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
		//pSMComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Overlap);
		pSMComponent->OnComponentBeginOverlap.AddDynamic(this, &AShadowActor::OnBeginOverlap);
		pSMComponent->OnComponentEndOverlap.AddDynamic(this, &AShadowActor::OnEndOverlap);
	}
}

// Called every frame
void AShadowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShadowActor::OnBeginOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_isSet || OtherActor == this) return;
	if (!OtherComp) return;
	if (OtherComp->ComponentHasTag(FName("ShadowActor")))
		m_pOverlapSAs.Add(OtherActor);
}

void AShadowActor::OnEndOverlap(class UPrimitiveComponent* OverlapedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_isSet || !OtherActor) return;
	if (m_pOverlapSAs.Contains(OtherActor)) m_pOverlapSAs.Remove(OtherActor);
}

