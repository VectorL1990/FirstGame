// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TEndMenu.h"




void UTEndMenu::NotifyInitial_Implementation()
{

}

void UTEndMenu::DemoTextTick()
{
	if (m_demoText.Num() == 0 || !m_canTick) return;
	if (m_curTick == 0)
	{
		m_pDemoText->SetText(FText::FromString(m_demoText[m_curTextNb]));
		NotifyPlaySwitchTextAnimation();
		m_curTick += 1;
	}
	else
	{
		if (m_curTick >= m_switchTextInterval)
		{
			m_curTextNb += 1;
			if (m_curTextNb >= m_demoText.Num())
			{
				m_canTick = false;
				ClearSwitchTextTimer();
				NotifyFadeOut();
				SetBackToLoginMenuTimer();
				return;
			}
			m_pDemoText->SetText(FText::FromString(m_demoText[m_curTextNb]));
			NotifyPlaySwitchTextAnimation();
			m_curTick = 0;
		}
		else m_curTick += 1;
	}
}

void UTEndMenu::OpenLoginLevel()
{
	UGameplayStatics::OpenLevel(this, FName("LoginMap"));
}

void UTEndMenu::SetBackToLoginMenuTimer_Implementation()
{

}

void UTEndMenu::NotifyFadeOut_Implementation()
{

}

void UTEndMenu::ClearSwitchTextTimer_Implementation()
{

}

void UTEndMenu::ActivateSwitchTextTick_Implementation()
{

}

void UTEndMenu::NotifyPlaySwitchTextAnimation_Implementation()
{

}
