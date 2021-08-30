// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/CWBaseGameMode.h"
#include "../CollisionWarGameInstance.h"
#include "TemplateProgressSlider.h"




void UTemplateProgressSlider::NotifyInitial_Implementation()
{

}

void UTemplateProgressSlider::SliderChange(float value)
{
	if (m_function.Contains("ChangeVolume_"))
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);

		pCWGM->NotifyChangeSoundClassVolume(m_function, value);

		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (pCWGI->m_sliderOptionPercent.Contains(m_function))
			pCWGI->m_sliderOptionPercent[m_function] = value;
	}

	/*if (m_function.Contains("ChangeBGSFX"))
		UGameplayStatics::SetSoundMixClassOverride(this, pCWGM->m_pSoundMix, pCWGM->m_pSoundMix->m_pBGSFXClass, value);
	else if (m_function.Contains("ChangeBGM"))
		UGameplayStatics::SetSoundMixClassOverride(this, pCWGM->m_pSoundMix, pCWGM->m_pSoundMix->m_pBGMClass, value);
	else if (m_function.Contains("ChangeSFX"))
		UGameplayStatics::SetSoundMixClassOverride(this, pCWGM->m_pSoundMix, pCWGM->m_pSoundMix->m_pSFXClass, value);*/
}
