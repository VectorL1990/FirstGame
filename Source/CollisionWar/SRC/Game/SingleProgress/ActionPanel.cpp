// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "SingleProgressGameMode.h"
#include "../../Base/SingleProgress/SingleProgressPlayerController.h"
#include "ActionPanel.h"


// Sets default values
AActionPanel::AActionPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActionPanel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActionPanel::InitialPanel_Implementation()
{

}

bool AActionPanel::PutPlayCardInArray(ANumericCard* pPlayCard)
{
	if (!pPlayCard) return false;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	int32 playCardNb = 0;
	if (m_pPlayCards.Contains(pPlayCard))
		playCardNb = m_pPlayCards.Find(pPlayCard);
	else
		playCardNb = m_pPlayCards.Num();
	if (playCardNb >= m_cardArrayLocs.Num()) return false;
	
	FVector skillPanelLoc = GetActorLocation();
	skillPanelLoc.Z = 0.f;
	FVector cardLoc(m_cardArrayLocs[playCardNb].X + skillPanelLoc.X, m_cardArrayLocs[playCardNb].Y + skillPanelLoc.Y, pSPGM->m_diceCardZ);
	pPlayCard->SetActorLocation(cardLoc);
	m_pPlayCards.Add(pPlayCard);
	return true;
}

bool AActionPanel::RemovePlayCardOutArray(ANumericCard* pPlayCard)
{
	if (!m_pPlayCards.Contains(pPlayCard)) return false;
	m_pPlayCards.Remove(pPlayCard);
	return true;
}

void AActionPanel::ResetPanel()
{
	
	m_skillCardList.Empty();
	m_isActivate = false;
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		if (m_pPlayCards[i] && m_pPlayCards[i]->IsValidLowLevel())
		{
			m_pPlayCards[i]->ConditionalBeginDestroy();
			m_pPlayCards[i]->Destroy();
		}
	}
	m_pPlayCards.Empty();
}


