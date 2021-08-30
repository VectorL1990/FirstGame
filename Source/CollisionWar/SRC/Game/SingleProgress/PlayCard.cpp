// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "SingleProgressGameMode.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "../../Base/SingleProgress/SingleProgressPlayerController.h"
#include "PlayCard.h"


// Sets default values
APlayCard::APlayCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayCard::Tick(float DeltaTime)
{
	//if (!m_canTick) return;
	Super::Tick(DeltaTime);
	if (m_isMove)
	{
		FVector offset = m_targetLoc - GetActorLocation();
		if (offset.Size() > m_tolerance)
		{
			FVector stepLoc = FMath::VInterpTo(GetActorLocation(), m_targetLoc, DeltaTime, m_moveSpeed);
			SetActorLocation(stepLoc);
		}
		else
		{
			m_isMove = false;
			//m_loc = GetActorLocation();
		}
	}
	
	if (m_isFlip)
	{
		//说明目标是正面朝上
		if (GetActorRotation().Equals(FRotator(0,0,0), m_tolerance)) return;
		else
		{
			FRotator stepRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 0, 0), DeltaTime, m_rotateSpeed);
			SetActorRotation(stepRot);
		}
		if (m_isInSkillState)
		{
			if (m_skillCountDown <= 0) TurnCard();
			else
			{
				m_skillCountDown -= DeltaTime;
			}
		}
	}
	else
	{
		//说明目标是背面朝上
		if (GetActorRotation().Equals(FRotator(0, 0, 180), m_tolerance)) return;
		else
		{
			FRotator stepRot = FMath::RInterpTo(GetActorRotation(), FRotator(0, 0, 180), DeltaTime, m_rotateSpeed);
			SetActorRotation(stepRot);
		}
	}
}

void APlayCard::NotifyInitialCard_Implementation(const FString& cardType,const FString& cardName, int32 cardNb)
{

}

void APlayCard::SetupPlayCard(UStaticMeshComponent* pBaseMesh, UTextRenderComponent* pText, UStaticMeshComponent* pCardImageMesh,
	UStaticMeshComponent* pColorImageMesh, UTextRenderComponent* pNbText)
{
	m_pBaseMesh = pBaseMesh;
	m_pCardName = pText;
	m_pCardImageMesh = pCardImageMesh;
	m_pColorImageMesh = pColorImageMesh;
	m_pCardNbText = pNbText;
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);*/
	
}

void APlayCard::InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName)
{
	m_cardName = cardName;
	m_cardType = cardType;
	m_pBaseMesh->ComponentTags.Add(FName(TEXT("PlayCard")));
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (nb == -1 && m_pCardName)
	{
		m_pCardName->SetText(cardName);
		/*if (pSPGM->m_pPlayCardTextureMap.Contains(cardName))
		{
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			if (pSPPC->m_pWidgetManager->m_language == "Chinese")
				m_pCardName->SetText(pSPGM->m_pPlayCardTextureMap[cardName].chCardName);
			else
				m_pCardName->SetText(cardName);
		}
		else
			m_pCardName->SetText(cardName);*/
	}
	if (m_pCardImageMesh)
	{
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pSurfaceMatRoundButton);
		m_pCardImageMesh->SetMaterial(0, pMI);
		if (!pSPGM->m_pPlayCardTextureMap.Contains(m_cardName)) return;
		UTexture* pTexture = pSPGM->m_pPlayCardTextureMap[m_cardName].pTexture;
		pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
		for (int32 i=0; i< pSPGM->m_pPlayCardTextureMap[m_cardName].tags.Num(); i++)
		{
			m_pBaseMesh->ComponentTags.Add(FName(*(pSPGM->m_pPlayCardTextureMap[m_cardName].tags[i])));
			m_tags.Add(pSPGM->m_pPlayCardTextureMap[m_cardName].tags[i]);
		}
		m_cardFunction = pSPGM->m_pPlayCardTextureMap[m_cardName].applyFunction;
		m_functionValues = pSPGM->m_pPlayCardTextureMap[m_cardName].functionValues;
		m_durability = pSPGM->m_pPlayCardTextureMap[m_cardName].durability;
	}
	if (m_pColorImageMesh)
	{
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pMatCardAttachment);
		if (pSPGM->m_pColorTextureMap.Contains(color))
			pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pSPGM->m_pColorTextureMap[color]);
		m_pColorImageMesh->SetMaterial(0, pMI);
		m_color = color;
	}
	if (nb != -1)
	{
		if (m_pCardNbText)
		{
			m_pCardNbText->SetText(FText::FromString(FString::FromInt(nb)));
		}
		m_nb = nb;
	}

}

void APlayCard::MoveToLocation(FVector loc, bool isFlip)
{
	m_isMove = true;
	m_isFlip = isFlip;
	m_targetLoc = loc;
}

void APlayCard::CardDisappear_Implementation()
{

}

void APlayCard::TurnCard()
{
	if (m_isFlip) m_isFlip = false;
	else m_isFlip = true;
}

void APlayCard::HideCard()
{
	m_pBaseMesh->SetVisibility(false);
	if (m_pCardImageMesh) m_pCardImageMesh->SetVisibility(false);
	if (m_pCardName) m_pCardName->SetVisibility(false);
}

void APlayCard::ReadCardName_Implementation(const FString& enName)
{

}

void APlayCard::NotifyChangeState_Implementation(uint8 state)
{

}

bool APlayCard::IsSatisfyTags(TArray<FString> tags)
{
	for (int32 i=0; i<tags.Num(); i++)
	{
		if (!m_tags.Contains(tags[i])) return false;
	}
	return true;
}

void APlayCard::CardShowUp_Implementation(FVector targetLoc, bool isFlip)
{

}

