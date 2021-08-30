// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "CamCharacter.h"


// Sets default values
ACamCharacter::ACamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_domain == 0 || !m_pTargetCharacter) return;
	SetActorLocation(m_pTargetCharacter->GetActorLocation());
}

// Called to bind functionality to input
void ACamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACamCharacter::SetParticleBySceneType(uint8 type)
{
	if (!m_pAppendPS.Contains(type)) return;
	m_pPSComponent = UGameplayStatics::SpawnEmitterAttached(m_pAppendPS[type].pPS, GetCapsuleComponent(), FName("PSSocket"), m_pAppendPS[type].relativeLoc, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
}

void ACamCharacter::UpdateDayNight(float dT)
{
	if (m_isDayOrNight && m_shouldRotatorDayNight)
	{
		float curPitch = m_pDirectionLight->GetActorRotation().Pitch;
		if (curPitch <= m_dayNightLightRotTarget.X && m_pSkyLight->GetLightComponent()->Intensity >= m_dayNightLightSkyLightIntensityTarget.X)
		{
			m_shouldRotatorDayNight = false;
			return;
		}
		else
		{
			FRotator deltaSpin(-m_DLSpinVelocity, 0, 0);
			if (m_pDirectionLight->GetActorRotation().Pitch > m_dayNightLightRotTarget.X)
				m_pDirectionLight->AddActorLocalRotation(deltaSpin);
			float curSkyLightIntensity = FMath::FInterpTo(m_pSkyLight->GetLightComponent()->Intensity, m_dayNightLightSkyLightIntensityTarget.X,
				dT, m_DLInterSpeed);
			if (curSkyLightIntensity >= m_dayNightLightSkyLightIntensityTarget.X) return;
			else m_pSkyLight->GetLightComponent()->SetIntensity(curSkyLightIntensity);

			float curDLIntensity = FMath::FInterpTo(m_pDirectionLight->GetLightComponent()->Intensity, m_dayNightLightDLIntensityTarget.X,
				dT, m_DLInterSpeed);
			if (curDLIntensity >= m_dayNightLightDLIntensityTarget.X) return;
			else m_pDirectionLight->GetLightComponent()->SetIntensity(curDLIntensity);
		}
	}
	else if (!m_isDayOrNight && m_shouldRotatorDayNight)
	{
		float curPitch = m_pDirectionLight->GetActorRotation().Pitch;
		if (curPitch >= m_dayNightLightRotTarget.Y && m_pSkyLight->GetLightComponent()->Intensity <= m_dayNightLightSkyLightIntensityTarget.Y)
		{
			m_shouldRotatorDayNight = false;
			return;
		}
		else
		{
			FRotator deltaSpin(m_DLSpinVelocity, 0, 0);
			if (m_pDirectionLight->GetActorRotation().Pitch < m_dayNightLightRotTarget.X)
				m_pDirectionLight->AddActorLocalRotation(deltaSpin);
			float curSkyLightIntensity = FMath::FInterpTo(m_pSkyLight->GetLightComponent()->Intensity, m_dayNightLightSkyLightIntensityTarget.Y,
				dT, m_DLInterSpeed);
			if (curSkyLightIntensity <= m_dayNightLightSkyLightIntensityTarget.Y) return;
			else m_pSkyLight->GetLightComponent()->SetIntensity(curSkyLightIntensity);

			float curDLIntensity = FMath::FInterpTo(m_pDirectionLight->GetLightComponent()->Intensity, m_dayNightLightDLIntensityTarget.Y,
				dT, m_DLInterSpeed);
			if (curDLIntensity <= m_dayNightLightDLIntensityTarget.Y) return;
			else m_pDirectionLight->GetLightComponent()->SetIntensity(curDLIntensity);
		}
	}
}

void ACamCharacter::ReadDayNightDLYaw_Implementation(uint8 levelNb)
{

}

