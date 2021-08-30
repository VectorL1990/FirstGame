// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "VerticalBoxSlot.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "UniformGridSlot.h"
#include "TSkillSelectIcon.h"



void UTSkillSelectIcon::NotifyInitial_Implementation()
{

}

void UTSkillSelectIcon::ButtonClick()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (pSPPC->m_pSPMenu)
	{
		if (m_domain == 0)
		{
			//属于普通按钮
			UMaterialInstanceDynamic* pMID = m_pDynaRotator->GetDynamicMaterial();
			pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 10, 10, 1));
			if (pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon != this && pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon)
			{
				UMaterialInstanceDynamic* pMID = pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon->m_pDynaRotator->GetDynamicMaterial();
				pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 20, 20, 1));
			}
			pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon = this;
			if (!pSPPC->m_pSPMenu->m_isSkillTreeShown)
			{
				TSubclassOf<class UUserWidget> skillTreeClass = pSPPC->m_pWidgetManager->m_widgetClassMap["SkillTree"];
				UTSkillTree* pMenu = CreateWidget<UTSkillTree>(pPC, skillTreeClass);
				//对一般变量进行赋值
				pSPPC->m_pSPMenu->m_pSizeBox->AddChild(pMenu);
				pMenu->NotifyInitial();
				pSPPC->m_pSPMenu->m_pSkillTree = pMenu;
				UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
				UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
				int32 curCol = 0;
				int32 curRow = 0;
				//载入所有对应技能
				for (int32 i = 0; i < pSPPC->m_playerSkillInfos.Num(); i++)
				{
					if (pSPPC->m_playerSkillInfos[i].skillType == m_skillType &&
						(pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(pSPPC->m_playerSkillInfos[i].skillName)))
					{
						TSubclassOf<class UUserWidget> skillSelectIconClass = pSPPC->m_pWidgetManager->m_widgetClassMap["SkillSelectIcon"];
						UTSkillSelectIcon* pSkillSelectIcon = CreateWidget<UTSkillSelectIcon>(pPC, skillSelectIconClass);
						pSkillSelectIcon->NotifyInitial();
						pSkillSelectIcon->m_domain = 1;
						pSkillSelectIcon->m_skillName = pSPPC->m_playerSkillInfos[i].skillName;
						pSkillSelectIcon->m_skillType = pSPPC->m_playerSkillInfos[i].skillType;
						UMaterialInstanceDynamic* pSkillMID = pSkillSelectIcon->m_pSkillImage->GetDynamicMaterial();
						pSkillMID->SetTextureParameterValue(FName("Front"), pSPPC->m_playerSkillInfos[i].pTexture);
						for (int32 j=0; j<pSPPC->m_playerSkillInfos[i].attributeList.Num(); j++)
						{
							if (pSPPC->m_playerSkillInfos[i].mutationType == pSPPC->m_playerSkillInfos[i].attributeList[j])
							{
								UTEnergyBall* pAttributeBall = CreateWidget<UTEnergyBall>(pSPPC, pSPPC->m_pWidgetManager->m_widgetClassMap["AttributeBall"]);
								pAttributeBall->NotifyInitial();
								if (pSPPC->m_pWidgetManager->m_pAttributeTextureMap.Contains(pSPPC->m_playerSkillInfos[i].attributeList[j]))
								{
									pAttributeBall->m_pImage->SetBrushFromTexture(pSPPC->m_pWidgetManager->m_pAttributeTextureMap[pSPPC->m_playerSkillInfos[i].attributeList[j]]);
									m_pAttributeVerticalBox->AddChild(pAttributeBall);
									break;
								}
							}
						}
						UPanelSlot* pSlot = pSPPC->m_pSPMenu->m_pSkillTree->m_pSkillGridPanel->AddChild(pSkillSelectIcon);
						UUniformGridSlot* pGridSlot = Cast<UUniformGridSlot>(pSlot);
						if (curCol >= pSPPC->m_pSPMenu->m_pSkillTree->m_maxColPerRow)
						{
							curRow += 1;
							curCol = 0;
						}
						pGridSlot->SetRow(curRow);
						pGridSlot->SetColumn(curCol);
						curCol += 1;
					}
				}

				pMenu->NotifyFadeIn();
				
			}
		}
		else
		{
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			//属于在skilltree里的按钮
			for (int32 i=0; i<pSPPC->m_playerSkillInfos.Num(); i++)
			{
				if (pSPPC->m_playerSkillInfos[i].skillName != m_skillName) continue;

				if (pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(pSPPC->m_playerSkillInfos[i].skillName))
				{
					//如果其他按钮和所选按钮相同，切换图标
					bool isRepeatSkill = false;
					if (m_skillType == 2)
					{
						for (int32 j = 0; j < pSPPC->m_pSPMenu->m_pNormalSkillIcons.Num(); j++)
						{
							if (pSPPC->m_pSPMenu->m_pNormalSkillIcons[j]->m_skillName == pSPPC->m_playerSkillInfos[i].chSkillName)
							{
								FString repeatSkillIconName = pSPPC->m_pSPMenu->m_pNormalSkillIcons[j]->m_skillName;
								UMaterialInstanceDynamic* pRepeatSkillIconMID = pSPPC->m_pSPMenu->m_pNormalSkillIcons[j]->m_pSkillImage->GetDynamicMaterial();
								FMaterialParameterInfo MPI("Front", EMaterialParameterAssociation::GlobalParameter, 0);
								UTexture* pRepeatTexture = NULL;
								pRepeatSkillIconMID->GetTextureParameterValue(MPI, pRepeatTexture);
								UMaterialInstanceDynamic* pMID = pSPPC->m_pSPMenu->m_pNormalSkillIcons[j]->m_pSkillImage->GetDynamicMaterial();
								pMID->SetTextureParameterValue("Front", pRepeatTexture);
								pSPPC->m_pSPMenu->m_pNormalSkillIcons[j]->m_skillName = repeatSkillIconName;
								isRepeatSkill = true;
								break;
							}
						}
					}
					UMaterialInstanceDynamic* pMID = pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon->m_pSkillImage->GetDynamicMaterial();
					pMID->SetTextureParameterValue("Front", pSPPC->m_playerSkillInfos[i].pTexture);
					//如非重复指定技能，先将原有的技能删除，然后添加新的技能
					if (m_skillType == 0)
					{
						pCWGI->m_curPlayerSPInfo.selectSkillInfo.chopSkillName = pSPPC->m_playerSkillInfos[i].skillName;
					}
					else if (m_skillType == 1)
					{
						pCWGI->m_curPlayerSPInfo.selectSkillInfo.blockSkillName = pSPPC->m_playerSkillInfos[i].skillName;
					}
					else if (m_skillType == 2)
					{
						pCWGI->m_curPlayerSPInfo.selectSkillInfo.dodgeSkillName = pSPPC->m_playerSkillInfos[i].skillName;
					}
					else
					{
						if (!isRepeatSkill)
						{
							pCWGI->m_curPlayerSPInfo.selectSkillInfo.normalSkillNames.Remove(pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon->m_skillName);
							pCWGI->m_curPlayerSPInfo.selectSkillInfo.normalSkillNames.Add(pSPPC->m_playerSkillInfos[i].skillName);
						}
					}
					pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon->m_skillName = pSPPC->m_playerSkillInfos[i].skillName;

					pSPPC->m_pSPMenu->m_pSkillTree->RemoveFromParent();
					if (pSPPC->m_pSPMenu->m_pSkillTree->IsValidLowLevel())
						pSPPC->m_pSPMenu->m_pSkillTree->ConditionalBeginDestroy();
					pSPPC->m_pSPMenu->m_pSkillTree = NULL;
				}
				
				break;
			}
		}
		
	}
}

void UTSkillSelectIcon::AddAttributeIcon(uint8 attribute)
{

}

void UTSkillSelectIcon::OnHoverBeginEnter()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (pSPPC->m_pSPMenu)
	{
		if (m_domain == 0)
		{
			if (pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon != this)
			{
				UMaterialInstanceDynamic* pMID = m_pDynaRotator->GetDynamicMaterial();
				pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 10, 10, 1));
			}
		}
		else
		{
			if (pSPPC->m_pSPMenu->m_pSkillTree)
			{
				pSPPC->m_pSPMenu->m_pSkillTree->m_pCurHighLightSelectIcon = this;
				UMaterialInstanceDynamic* pMID = m_pDynaRotator->GetDynamicMaterial();
				pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 10, 10, 1));
			}
		}
	}
}

void UTSkillSelectIcon::OnHoverEndEnd()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (pSPPC->m_pSPMenu)
	{
		if (m_domain == 0)
		{
			if (pSPPC->m_pSPMenu->m_pCurHighLightSkillSelectIcon != this)
			{
				UMaterialInstanceDynamic* pMID = m_pDynaRotator->GetDynamicMaterial();
				pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 20, 20, 1));
			}
		}
		else
		{
			UMaterialInstanceDynamic* pMID = m_pDynaRotator->GetDynamicMaterial();
			pMID->SetVectorParameterValue(FName("baseColor"), FLinearColor(20, 20, 20, 1));
		}
	}
}
