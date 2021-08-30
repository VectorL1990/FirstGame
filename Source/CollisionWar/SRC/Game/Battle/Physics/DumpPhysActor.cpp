// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../BattleLevelGameModeBase.h"
#include "Components/SplineMeshComponent.h"
#include "DumpPhysActor.h"


// Sets default values
ADumpPhysActor::ADumpPhysActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADumpPhysActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADumpPhysActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADumpPhysActor::InitialDumpActor()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleGameMode || !pBattleGameMode->m_pRecastDetourObject) return;
	if (m_isBoundaryActor)
	{
		
		if (!m_pBasicComponent) return;
		if (m_pBasicComponent->GetClass() == UBoxComponent::StaticClass())
		{
			UBoxComponent* pBoxComponent = Cast<UBoxComponent>(m_pBasicComponent);
			FVector center = pBoxComponent->GetComponentLocation();
			FVector extent = pBoxComponent->GetScaledBoxExtent();
			float bmin[3];
			bmin[0] = (center.Y - extent.Y) / 100.f;
			bmin[1] = (center.Z - extent.Z) / 100.f;
			bmin[2] = (center.X - extent.X) / 100.f;
			float bmax[3];
			bmax[0] = (center.Y + extent.Y) / 100.f;
			bmax[1] = (center.Z + extent.Z) / 100.f;
			bmax[2] = (center.X + extent.X) / 100.f;
			pBattleGameMode->m_pRecastDetourObject->HandleAddTempBoxObstacle(bmin, bmax, 0);
		}
		else if (m_pBasicComponent->GetClass() == UCapsuleComponent::StaticClass())
		{
			UCapsuleComponent* pCapsuleComponent = Cast<UCapsuleComponent>(m_pBasicComponent);
			float pos[3];
			pos[0] = GetActorLocation().Y / 100.f;
			pos[1] = GetActorLocation().Z / 100.f;
			pos[2] = GetActorLocation().X / 100.f;
			pBattleGameMode->m_pRecastDetourObject->HandleAddTempObstacle(pos, pCapsuleComponent->GetScaledCapsuleRadius() / 100.f, 
				pCapsuleComponent->GetUnscaledCapsuleHalfHeight() * 2.f / 100.f);
		}
		else if (m_pBasicComponent->GetClass() == USphereComponent::StaticClass())
		{
			USphereComponent* pSphereComponent = Cast<USphereComponent>(m_pBasicComponent);
			float pos[3];
			pos[0] = GetActorLocation().Y / 100.f;
			pos[1] = GetActorLocation().Z / 100.f;
			pos[2] = GetActorLocation().X / 100.f;
			pBattleGameMode->m_pRecastDetourObject->HandleAddTempObstacle(pos, pSphereComponent->GetScaledSphereRadius() / 100.f,
				pSphereComponent->GetScaledSphereRadius() * 2.f / 100.f);
		}
		TArray<UActorComponent*> pMeshes = GetComponentsByClass(UStaticMeshComponent::StaticClass());
		TArray<UActorComponent*> pSplineMeshes = GetComponentsByClass(USplineMeshComponent::StaticClass());
		for (int32 i=0; i<pMeshes.Num(); i++)
		{
			if (!pMeshes[i]->ComponentHasTag(FName("Boundary")))
				pMeshes[i]->ComponentTags.Add(FName("Boundary"));
		}
		for (int32 i=0; i<pSplineMeshes.Num(); i++)
		{
			if (!pSplineMeshes[i]->ComponentHasTag(FName("Boundary")))
				pSplineMeshes[i]->ComponentTags.Add(FName("Boundary"));
		}
	}
}

void ADumpPhysActor::SetBasicComponent(UPrimitiveComponent* pComponent)
{
	if (!pComponent) return;
	m_pBasicComponent = pComponent;
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("DumpActor")));
}

void ADumpPhysActor::OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (otherActor && otherActor == this) return;
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
		{
			ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);

			if (pGeo->m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
			{
				if (!m_timeDilationParams.Contains(pGeo))
				{
					for (int32 i = 0; i < pGeo->m_effectParamList.Num(); i++)
					{
						if (pGeo->m_effectParamList[i].effectName != "TimeDilation") continue;
						m_timeDilationParams.Add(pGeo, pGeo->m_effectParamList[i].duration);
						if (CustomTimeDilation >= ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f)
							CustomTimeDilation = ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f;
						break;
					}
				}
			}

		}
	}
}

void ADumpPhysActor::OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo) return;
		//这里要将时间膨胀的顺序理清
		if (m_timeDilationParams.Contains(pGeo))
		{
			//
			float minTimeDilation = 1.f;
			for (TMap<ABasePhysGeo*, float>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
			{
				if (pGeo == iter->Key) continue;
				if (iter->Value <= minTimeDilation) minTimeDilation = iter->Value;
			}
			CustomTimeDilation = minTimeDilation;
			m_timeDilationParams.Remove(pGeo);
		}
	}
}

