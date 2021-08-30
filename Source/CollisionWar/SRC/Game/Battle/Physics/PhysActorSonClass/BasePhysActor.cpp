// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../../BattleLevelGameModeBase.h"
#include "../../../../Base/Widget/TPhysActorPopMenu.h"
#include "../../../../Common/WidgetBlueprintFunctionLibrary.h"
#include "Components/SplineMeshComponent.h"
#include "BasePhysActor.h"

// Sets default values
ABasePhysActor::ABasePhysActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pFixComponent = CreateDefaultSubobject<USphereComponent>(TEXT("FixComponent"));
	m_pFixComponent->SetSimulatePhysics(false);
	m_pFixComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	m_pFixComponent->bGenerateOverlapEvents = true;
	m_pFixComponent->SetSphereRadius(10);
	RootComponent = m_pFixComponent;
	m_physGeoType = EPhysGeoType::PGT_Actor;
	m_physActorLifeTime = 0;
	m_isCollectable = true;
	m_pAttachEquipInfo = NULL;
}

void ABasePhysActor::Tick(float DeltaSeconds)
{
	if (m_pWaitReactionGeos.Num() <= 0 || !m_pPhysCalculator) return;
	for (int32 i = 0; i < m_pWaitReactionGeos.Num(); i++)
	{
		if (m_pWaitReactionGeos[i]->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(m_pWaitReactionGeos[i]))
			continue;
		GeoReaction(m_pWaitReactionGeos[i]);
	}
	m_pWaitReactionGeos.Empty();
}

// Called when the game starts or when spawned
void ABasePhysActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePhysActor::DecreaseLifeTime(float dT)
{

}

void ABasePhysActor::SetWidgetComponent(UWidgetComponent* pWidget)
{
	if (!pWidget) return;
	m_pWidget = pWidget;
	/*if (m_pWidget)
	{
		UTPhysActorPopMenu* pPhysActorPopMenu = Cast<UTPhysActorPopMenu>(m_pWidget->GetUserWidgetObject());
		if (!pPhysActorPopMenu) return;
		pPhysActorPopMenu->NotifyInitial();
		pPhysActorPopMenu->m_pInfoButton->m_physActorID = m_entityID;
		pPhysActorPopMenu->m_pBuildButton->m_physActorID = m_entityID;
		AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
		if (!pGameMode) return;
		ACWBaseGameMode* pCWGameMode = Cast<ACWBaseGameMode>(pGameMode);
		pPhysActorPopMenu->m_pBuildButton->m_physPopButtonDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::PhysActorPopButtonClickCallback);
		pPhysActorPopMenu->m_pInfoButton->m_physPopButtonDelegate.AddDynamic(pCWGameMode, &ACWBaseGameMode::PhysActorPopButtonClickCallback);
	}*/
}

void ABasePhysActor::PopPhysActorWidget()
{
	if (!m_pWidget) return;
	UUserWidget* pWidget = m_pWidget->GetUserWidgetObject();
	UTPhysActorPopMenu* pPhysActorPopMenu = Cast<UTPhysActorPopMenu>(pWidget);
	if (!pPhysActorPopMenu || !pPhysActorPopMenu->m_pCanvasPanel) return;
	pPhysActorPopMenu->m_pCanvasPanel->SetRenderOpacity(1.f);
	pPhysActorPopMenu->m_pInfoButton->m_physActorID = m_entityID;
	pPhysActorPopMenu->m_pBuildButton->m_physActorID = m_entityID;
}

void ABasePhysActor::HidePhysActorWidget()
{
	if (!m_pWidget) return;
	UUserWidget* pWidget = m_pWidget->GetUserWidgetObject();
	UTPhysActorPopMenu* pPhysActorPopMenu = Cast<UTPhysActorPopMenu>(pWidget);
	if (!pPhysActorPopMenu || !pPhysActorPopMenu->m_pCanvasPanel) return;
	pPhysActorPopMenu->m_pCanvasPanel->SetRenderOpacity(0.f);
}

void ABasePhysActor::OnBaseComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (otherActor && otherActor == this) return;
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			if (!m_pOverlapCharacters.Contains(pCharacter))
				m_pOverlapCharacters.Add(pCharacter);
		}
		if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
		{
			ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);

			if (pGeo->m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
			{
				if (!m_timeDilationParams.Contains(GetName()))
				{
					for (int32 i = 0; i < pGeo->m_effectParamList.Num(); i++)
					{
						if (pGeo->m_effectParamList[i].effectName != "TimeDilation" ||
							(pGeo->m_effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == m_campFlag)) continue;
						m_timeDilationParams.Add(pGeo->GetName(), pGeo->m_effectParamList[i].duration);
						if (CustomTimeDilation >= ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f)
							CustomTimeDilation = ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f;
						break;
					}
				}
			}

			if (!pGeo || !pGeo->m_isGeoValid || OtherComp->ComponentHasTag(FName(TEXT("PhysPolygon"))) || OtherComp->ComponentHasTag(FName(TEXT("PhysPoint")))
				|| (m_isOneTimeReaction && m_hasTriggerReaction) || (pGeo->m_isOneTimeReaction && pGeo->m_hasTriggerReaction)) return;

			m_pWaitReactionGeos.Add(pGeo);
		}
	}
}

void ABasePhysActor::OnBaseComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent)
{
	if (!m_isGeoValid || !otherActor || !otherComponent) return;
	if (otherComponent->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo) return;

		//这里要将时间膨胀的顺序理清
		if (m_timeDilationParams.Contains(pGeo->GetName()))
		{
			//
			float minTimeDilation = 1.f;
			for (TMap<FString, float>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
			{
				if (pGeo->GetName() == iter->Key) continue;
				if (iter->Value <= minTimeDilation) minTimeDilation = iter->Value;
			}
			CustomTimeDilation = minTimeDilation;
			m_timeDilationParams.Remove(pGeo->GetName());
		}

		if (m_pPreOverlapGeos.Contains(pGeo)) m_pPreOverlapGeos.Remove(pGeo);
	}
	else if (otherComponent->ComponentHasTag(FName(TEXT("BaseCharacter"))))
	{
		ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
		if (!pCharacter) return;
		if (m_pOverlapCharacters.Contains(pCharacter)) m_pOverlapCharacters.Remove(pCharacter);
	}
}

void ABasePhysActor::SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill)
{
	m_pBasicComponent = pComponent;
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("BasePhysGeo")));
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("BasePhysActor")));
	if (m_pBasicComponent)
	{
		for (int32 i = 0; i < m_attributeTags.Num(); i++)
		{
			if (!m_pBasicComponent->ComponentHasTag(m_attributeTags[i]))
				m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
		}
	}
	m_pBasicComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ABasePhysActor::SetParticleComponent(UParticleSystemComponent* pParticleComponent)
{
	m_pParticleComponent = pParticleComponent;
	if (m_pParticleComponent) m_pParticleComponent->SetAutoActivate(false);
}

void ABasePhysActor::InitialPhysActor(int32 campFlag, ABaseCharacter* pCharacter, int32 defaultHeight)
{
	m_defaultHeight = defaultHeight;
	m_campFlag = campFlag;
	
	if (m_isBoundaryActor)
	{
		if (!m_pBasicComponent) return;
		AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
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

		/*float pos[3];
		pos[0] = GetActorLocation().Y / 100.f;
		pos[1] = GetActorLocation().Z / 100.f;
		pos[2] = GetActorLocation().X / 100.f;
		pBattleGameMode->m_pRecastDetourObject->HandleAddTempObstacle(pos, m_obtacleRadius / 100.f, m_obtacleHeight / 100.f);*/
		TArray<UActorComponent*> pMeshes = GetComponentsByClass(UStaticMeshComponent::StaticClass());
		TArray<UActorComponent*> pSplineMeshes = GetComponentsByClass(USplineMeshComponent::StaticClass());
		for (int32 i = 0; i < pMeshes.Num(); i++)
		{
			if (!pMeshes[i]->ComponentHasTag(FName("Boundary")))
				pMeshes[i]->ComponentTags.Add(FName("Boundary"));
		}
		for (int32 i = 0; i < pSplineMeshes.Num(); i++)
		{
			if (!pSplineMeshes[i]->ComponentHasTag(FName("Boundary")))
				pSplineMeshes[i]->ComponentTags.Add(FName("Boundary"));
		}
	}
	//m_curRandTarget = m_logicPos2D;
	m_pHost = pCharacter;

	/*if (!m_pHost) return;
	if (m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
	{
		if (!m_pHost->m_timeDilationParams.Contains(GetName())) return;
		int32 minTimeDilation = 100;
		for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = m_pHost->m_timeDilationParams.CreateConstIterator(); iter; ++iter)
		{
			if (GetName() == iter->Key) continue;
			if (iter->Value.timeDilationPercent <= minTimeDilation) minTimeDilation = iter->Value.timeDilationPercent;
		}

		m_pHost->CustomTimeDilation = (float)minTimeDilation / 100.f;
		m_pHost->m_speedRatePercent = minTimeDilation;
		m_pHost->m_timeDilationParams.Remove(GetName());
	}*/
}

void ABasePhysActor::DeleteTempObstacleFromRecastNav()
{
	if (m_pBasicComponent)
	{
		bool isBoundary = false;
		for (int32 i = 0; i < m_pBasicComponent->ComponentTags.Num(); i++)
		{
			if (m_pBasicComponent->ComponentTags[i] == "Boundary")
			{
				isBoundary = true;
				break;
			}
		}
		if (isBoundary)
		{
			AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
			ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
			float pos[3];
			pos[0] = GetActorLocation().Y / 100.f;
			pos[1] = GetActorLocation().Z / 100.f;
			pos[2] = GetActorLocation().X / 100.f;
			pBattleGameMode->m_pRecastDetourObject->HandleRemoveTempObstacle(pos);
		}
	}
}
