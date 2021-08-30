// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "WidgetBlueprintLibrary.h"
#include "TFlipImage.h"




void UTFlipImage::InitialFlipImage(UImage* pFlipImage, UImage* pAlternateImage)
{
	if (m_textureList.pTextures.Num() == 0 || !pFlipImage) return;
	m_pImage = pFlipImage;
	m_pAlternateImage = pAlternateImage;
	//初始化笔刷列表
	//m_brushes.Empty();
	/*int32 keyNb = m_textureList.pTextureList.Num();
	for (int32 i=0; i<keyNb; i++)
	{
		if (!m_textureList.pTextureList[i]) continue;
		FSlateBrush brush = UWidgetBlueprintLibrary::MakeBrushFromTexture(m_textureList.pTextureList[i], 0, 0);
		brush.TintColor = m_imageColor;
		m_brushes.Add(brush);
	}*/
	//设置初始画面
	if (m_textureList.pTextures.Num() <= 0 || m_startFrame >= m_textureList.pTextures.Num()) return;
	UMaterialInstanceDynamic* pDMI = m_pImage->GetDynamicMaterial();
	if (!pDMI) return;
	pDMI->SetVectorParameterValue(FName("Color"), m_color);
	pDMI->SetTextureParameterValue(FName("Texture"), m_textureList.pTextures[m_startFrame]);
	if (m_useRedChannelAsAlpha)
		pDMI->SetScalarParameterValue(FName("UseRedAsTransparent"), 1.f);
	else
		pDMI->SetScalarParameterValue(FName("UseRedAsTransparent"), 0.f);

	UMaterialInstanceDynamic* pAlternateDMI = m_pAlternateImage->GetDynamicMaterial();
	if (!pAlternateDMI) return;
	pAlternateDMI->SetVectorParameterValue(FName("Color"), m_color);
	//pAlternateDMI->SetTextureParameterValue(FName("Texture"), m_brushes[m_startFrame]);
	if (m_useRedChannelAsAlpha)
		pAlternateDMI->SetScalarParameterValue(FName("UseRedAsTransparent"), 1.f);
	else
		pAlternateDMI->SetScalarParameterValue(FName("UseRedAsTransparent"), 0.f);
	//m_pImage->SetBrush(m_brushes[m_startFrame]);

	//初始化计时器
	/*float dTPerFrame = 1.f / m_framesPerSecond;
	float updateInterval = dTPerFrame / m_playRate;
	GetWorldTimerManager().SetTimer(m_timerHandle, this, &UTFlipImage::FlipbookTick, updateInterval, true);*/
}

void UTFlipImage::FlipbookTick()
{
	if (m_flipType == 0)
	{
		if (m_curFrame >= m_textureList.pTextures.Num())
		{
			if (m_isLoop)
			{
				if (m_textureList.pTextures.Num() == 0) return;
				m_curFrame = 0;
				UMaterialInstanceDynamic* pDMI = m_pImage->GetDynamicMaterial();
				if (!pDMI) return;
				pDMI->SetTextureParameterValue(FName("Texture"), m_textureList.pTextures[m_curFrame]);
				//m_pImage->SetBrush(m_brushes[m_curFrame]);
			}
			else
			{
				ClearFlipbookTimer();
			}
		}
		else
		{
			UMaterialInstanceDynamic* pDMI = m_pImage->GetDynamicMaterial();
			if (!pDMI) return;
			pDMI->SetTextureParameterValue(FName("Texture"), m_textureList.pTextures[m_curFrame]);
			//m_pImage->SetBrush(m_brushes[m_curFrame]);
			m_curFrame += 1;
		}
	}
	else
	{
		if (!m_pAlternateImage || m_textureList.pTextures.Num() == 0) return;
		if (!switchToAlternateImage)
		{
			if (m_curOriginImageTime >= m_alternateTextureInfo.alternatePeriod)
			{
				if (m_curSwitchImageTime == 0)
				{
					//如到了原图片切换同时切换图片计时为0，说明切换刚开始，此时切换图片，同时设置原图片的不透明度
					m_curFrame += 1;
					if (m_curFrame >= m_textureList.pTextures.Num()) m_curFrame = 0;
					m_pAlternateImage->SetOpacity(0);
					UMaterialInstanceDynamic* pDMI = m_pAlternateImage->GetDynamicMaterial();
					if (!pDMI) return;
					pDMI->SetTextureParameterValue(FName("Texture"), m_textureList.pTextures[m_curFrame]);
					//m_pAlternateImage->SetBrush(m_brushes[m_curFrame]);
					m_curSwitchImageTime += 1;
				}
				else
				{
					float switchOpacity = 0.f;
					if (m_curSwitchImageTime <= m_alternateTextureInfo.firstCornerTime)
						switchOpacity = (float)m_curSwitchImageTime / (float)m_alternateTextureInfo.firstCornerTime;
					else if (m_curSwitchImageTime <= m_alternateTextureInfo.fullInterval - m_alternateTextureInfo.rearCornerTime)
						switchOpacity = 1.f;
					else
						switchOpacity = (float)(m_alternateTextureInfo.fullInterval - m_curSwitchImageTime) / (float)m_alternateTextureInfo.rearCornerTime;
					m_pAlternateImage->SetOpacity(switchOpacity);
					m_curSwitchImageTime += 1;
				}
			}
			float originalOpacity = 0.f;
			if (m_curOriginImageTime <= m_alternateTextureInfo.firstCornerTime)
				originalOpacity = (float)m_curOriginImageTime / (float)m_alternateTextureInfo.firstCornerTime;
			else if (m_curOriginImageTime <= m_alternateTextureInfo.fullInterval - m_alternateTextureInfo.rearCornerTime)
				originalOpacity = 1.f;
			else
				originalOpacity = (float)(m_alternateTextureInfo.fullInterval - m_curOriginImageTime) / (float)m_alternateTextureInfo.rearCornerTime;

			m_pImage->SetOpacity(originalOpacity);
			m_curOriginImageTime += 1;
			if (m_curOriginImageTime > m_alternateTextureInfo.fullInterval)
			{
				m_curOriginImageTime = 0;
				switchToAlternateImage = true;
			}
		}
		else
		{
			if (m_curSwitchImageTime >= m_alternateTextureInfo.alternatePeriod)
			{
				if (m_curOriginImageTime == 0)
				{
					//如到了原图片切换同时切换图片计时为0，说明切换刚开始，此时切换图片，同时设置原图片的不透明度
					m_curFrame += 1;
					if (m_curFrame >= m_textureList.pTextures.Num()) m_curFrame = 0;
					m_pImage->SetOpacity(0);
					UMaterialInstanceDynamic* pDMI = m_pImage->GetDynamicMaterial();
					if (!pDMI) return;
					pDMI->SetTextureParameterValue(FName("Texture"), m_textureList.pTextures[m_curFrame]);
					//m_pImage->SetBrush(m_brushes[m_curFrame]);
					m_curOriginImageTime += 1;
				}
				else
				{
					float originOpacity = 0.f;
					if (m_curOriginImageTime <= m_alternateTextureInfo.firstCornerTime)
						originOpacity = (float)m_curOriginImageTime / (float)m_alternateTextureInfo.firstCornerTime;
					else if (m_curOriginImageTime <= m_alternateTextureInfo.fullInterval - m_alternateTextureInfo.rearCornerTime)
						originOpacity = 1.f;
					else
						originOpacity = (float)(m_alternateTextureInfo.fullInterval - m_curOriginImageTime) / (float)m_alternateTextureInfo.rearCornerTime;

					m_pImage->SetOpacity(originOpacity);
					m_curOriginImageTime += 1;
				}
			}
			float switchOpacity = 0.f;
			if (m_curSwitchImageTime <= m_alternateTextureInfo.firstCornerTime)
				switchOpacity = (float)m_curSwitchImageTime / (float)m_alternateTextureInfo.firstCornerTime;
			else if (m_curSwitchImageTime <= m_alternateTextureInfo.fullInterval - m_alternateTextureInfo.rearCornerTime)
				switchOpacity = 1.f;
			else
				switchOpacity = (float)(m_alternateTextureInfo.fullInterval - m_curSwitchImageTime) / (float)m_alternateTextureInfo.rearCornerTime;
			m_pAlternateImage->SetOpacity(switchOpacity);
			m_curSwitchImageTime += 1;
			if (m_curSwitchImageTime > m_alternateTextureInfo.fullInterval)
			{
				m_curSwitchImageTime = 0;
				switchToAlternateImage = false;
			}
		}
	}
}

void UTFlipImage::NotifyActivateManually_Implementation()
{

}

void UTFlipImage::ClearFlipbookTimer_Implementation()
{

}
