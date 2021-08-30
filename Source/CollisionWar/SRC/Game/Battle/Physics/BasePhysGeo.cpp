// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "BasePhysGeo.h"
#include "../../../Common/CollisionWarSingleton.h"
#include "PhysCalculator.h"


// Sets default values
ABasePhysGeo::ABasePhysGeo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pBasicComponent = NULL;
}

// Called when the game starts or when spawned
void ABasePhysGeo::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePhysGeo::SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill)
{
	
}

/*
void ABasePhysGeo::AddReactionInfo(FReactionInfo reactionInfo)
{
	m_reactionInfos.Add(reactionInfo);
}*/

void ABasePhysGeo::SetAttachEquipment(UCharacterEquipInfo* pEquipInfo)
{
	m_pAttachEquipInfo = pEquipInfo;
	for (int32 i=0; i<pEquipInfo->m_actorTags.Num(); i++)
	{
		if (!m_pBasicComponent->ComponentHasTag(pEquipInfo->m_actorTags[i]))
			m_pBasicComponent->ComponentTags.Add(pEquipInfo->m_actorTags[i]);
	}
}

void ABasePhysGeo::DoSomethingToCoverCharacter_Implementation()
{

}
/*

void ABasePhysGeo::AddPreOverlapGeoPair(ABasePhysGeo* pGeo)
{
	bool hasAddPair = false;
	for (int32 j = 0; j < pGeo->m_reactionInfos.Num(); j++)
	{
		if (m_pBasicComponent->ComponentHasTag(pGeo->m_reactionInfos[j].reactionTag))
		{
			m_preReactionPairs.Add(FPreReactionPair(pGeo->m_entityID, m_entityID));
			hasAddPair = true;
			break;
		}
	}
	if (!hasAddPair)
	{
		for (int32 j = 0; j < m_reactionInfos.Num(); j++)
		{
			if (pGeo->m_pBasicComponent->ComponentHasTag(m_reactionInfos[j].reactionTag))
			{
				m_preReactionPairs.Add(FPreReactionPair(m_entityID, pGeo->m_entityID));
				break;
			}
		}
	}
}
*/

void ABasePhysGeo::InitialEquipmentInfo()
{
	m_pAttachEquipInfo = NewObject<UCharacterEquipInfo>(this, m_attchEquipClass);
}

void ABasePhysGeo::GeoReaction(ABasePhysGeo* pHitGeo)
{
	if (pHitGeo->m_hierachy == 1 || m_hierachy == 1) return;
	/*for (int32 i = 0; i < m_pPhysCalculator->m_reactionPairs.Num(); i++)
	{
		if ((m_pPhysCalculator->m_reactionPairs[i].geoID1 == m_entityID && m_pPhysCalculator->m_reactionPairs[i].geoID2 == pHitGeo->m_entityID) ||
			(m_pPhysCalculator->m_reactionPairs[i].geoID2 == m_entityID && m_pPhysCalculator->m_reactionPairs[i].geoID1 == pHitGeo->m_entityID))
			return;
	}*/
	for (int32 i = 0; i < m_pPhysCalculator->m_reactionPairs.Num(); i++)
	{
		if ((m_pPhysCalculator->m_reactionPairs[i].pGeo1 == this && m_pPhysCalculator->m_reactionPairs[i].pGeo2 == pHitGeo) ||
			(m_pPhysCalculator->m_reactionPairs[i].pGeo2 == this && m_pPhysCalculator->m_reactionPairs[i].pGeo1 == pHitGeo))
			return;
	}
	int32 reactionType = -1;
	FReactionPair reactionPair;
	TArray<FString> reactionTags;
	TArray<FString> hitGeoReactionTags;
	for (int32 i=0; i<m_attributeList.Num(); i++)
	{
		FString attributeTag = "Attribute_" + FString::FromInt((int32)m_attributeList[i]);
		reactionTags.Add(attributeTag);
	}
	for (int32 i=0; i<m_pBasicComponent->ComponentTags.Num(); i++)
	{
		reactionTags.Add(m_pBasicComponent->ComponentTags[i].ToString());
	}

	for (int32 i = 0; i < pHitGeo->m_attributeList.Num(); i++)
	{
		FString attributeTag = "Attribute_" + FString::FromInt((int32)pHitGeo->m_attributeList[i]);
		hitGeoReactionTags.Add(attributeTag);
	}
	for (int32 i = 0; i < pHitGeo->m_pBasicComponent->ComponentTags.Num(); i++)
	{
		hitGeoReactionTags.Add(pHitGeo->m_pBasicComponent->ComponentTags[i].ToString());
	}

	//反应中本物体和触发的物体只管自己的反应，免得造成冲突
	for (int32 i=0; i<hitGeoReactionTags.Num(); i++)
	{
		if (!m_reactionMap.Contains(hitGeoReactionTags[i])) continue;

		reactionPair.reactionName1 = m_reactionMap[hitGeoReactionTags[i]];
		reactionType = 0;
		break;
	}

	for (int32 i = 0; i < reactionTags.Num(); i++)
	{
		if (!pHitGeo->m_reactionMap.Contains(reactionTags[i])) continue;

		reactionPair.reactionName2 = pHitGeo->m_reactionMap[reactionTags[i]];

		if (reactionType == 0) reactionType = 2;
		else if (reactionType == -1) reactionType = 1;
		break;
	}
	if (reactionType == -1) return;
	m_hasTriggerReaction = true;
	pHitGeo->m_hasTriggerReaction = true;
	reactionPair.reactionLoc1 = GetActorLocation();
	reactionPair.reactionRot1 = GetActorRotation();
	reactionPair.reactionLoc2 = pHitGeo->GetActorLocation();
	reactionPair.reactionRot2 = pHitGeo->GetActorRotation();
	//reactionPair.geoID1 = m_entityID;
	//reactionPair.geoID2 = pHitGeo->m_entityID;
	reactionPair.pGeo1 = this;
	reactionPair.pGeo2 = pHitGeo;
	reactionPair.reactionType = reactionType;
	if (!m_pRootGeos.Contains(pHitGeo)) m_pRootGeos.Add(pHitGeo);
	if (!pHitGeo->m_pRootGeos.Contains(this)) pHitGeo->m_pRootGeos.Add(this);
	if (!m_isInitial || !pHitGeo->m_isInitial) reactionPair.isInitial = false;
	m_pPhysCalculator->m_reactionPairs.Add(reactionPair);
}

void ABasePhysGeo::AppendEnhanceParticle(uint8 enhanceType)
{
	if (!m_enhancePS.Contains(enhanceType)) return;
	/*UGameplayStatics::SpawnEmitterAttached(m_enhancePS[enhanceType].pPS, GetRootComponent(), FName(""), m_enhancePS[enhanceType].relativeLoc,
		m_enhancePS[enhanceType].relativeRot, EAttachLocation::KeepRelativeOffset);*/
	UGameplayStatics::SpawnEmitterAttached(m_enhancePS[enhanceType].pPS, GetRootComponent());
}

void ABasePhysGeo::AddEnhanceEffectToOverlapCharacters(int32 enhanceType)
{
	//if (!m_enhanceEffectParamList.Contains(enhanceType)) return;
	//m_pPhysCalculator->PolygonEffectPreCalculate(this, m_enhanceEffectParamList[enhanceType].effectParamList);
	for (int32 i = 0; i < m_pOverlapCharacters.Num(); i++)
	{
		TArray<FActiveAttributeReactionInfo> flashEffects;
		TArray<uint8> enhanceAtkAttributeList;
		enhanceAtkAttributeList.Add(enhanceType);
		m_pPhysCalculator->CalCharacterAttributeReaction(m_pOverlapCharacters[i], enhanceAtkAttributeList, flashEffects);
		bool isHit = false;
		m_pPhysCalculator->AddEnhanceEffectToCharacter(this, m_pOverlapCharacters[i], enhanceType);
		if (m_campFlag != m_pOverlapCharacters[i]->m_campFlag && isHit)
		{
			m_pPhysCalculator->PlayHitParticle(this, m_pOverlapCharacters[i]->GetActorLocation());
			//UGameplayStatics::PlaySoundAtLocation(this, m_pPolygons[i]->m_pHitSound, m_pPolygons[i]->m_pOverlapCharacters[j]->GetActorLocation());
		}
	}
}

/*
void ABasePhysGeo::SetMutationPS()
{
	
}*/

void ABasePhysGeo::GeoHitCharacter_Implementation(ABaseCharacter* pCharacter)
{

}




