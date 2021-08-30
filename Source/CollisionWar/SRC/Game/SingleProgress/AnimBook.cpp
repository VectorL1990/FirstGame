// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "AnimBook.h"


// Sets default values
AAnimBook::AAnimBook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimBook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimBook::BookConstruction(UMaterialInstance* pPageMaskMI, UMaterialInstance* pPageEdgeMI, UMaterialInstance* pPageMI, UMaterialInstance* pPaperEndSheet)
{
	m_pBookCoverFront->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_pBookCoverBack->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_pSpineBack->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	m_pCoverMaterial = m_pCoverMaterials[m_MISerialInfo.coverMaterialNb];

	m_pPageFront_DMI = m_pPageFront->CreateDynamicMaterialInstance(0, pPageMaskMI);
	m_pPageFront_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pPageFront_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pPageFront_DMI->SetScalarParameterValue("Roughness", m_paperPageRoughness[m_MISerialInfo.paperPageRoughnessNb]);
	m_pPageFront_DMI->SetScalarParameterValue("DirtStrength", m_paperDirtStrength);
	m_pPageFront->SetMaterial(1, m_pPageFront_DMI);

	m_pPageBack_DMI = m_pPageBack->CreateDynamicMaterialInstance(0, pPageMaskMI);
	m_pPageBack_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pPageBack_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pPageBack_DMI->SetScalarParameterValue("Roughness", m_paperPageRoughness[m_MISerialInfo.paperPageRoughnessNb]);
	m_pPageBack_DMI->SetScalarParameterValue("DirtStrength", m_paperDirtStrength);
	m_pPageBack->SetMaterial(1, m_pPageBack_DMI);

	m_pBlockFrontEdge_DMI = m_pBlockFront->CreateDynamicMaterialInstance(3, pPageEdgeMI);
	m_pBlockFrontEdge_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pBlockFrontEdge_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pBlockFrontEdge_DMI->SetScalarParameterValue("XscaleOffset", 0.24);

	m_pBlockBackEdge_DMI = m_pBlockBack->CreateDynamicMaterialInstance(3, pPageEdgeMI);
	m_pBlockBackEdge_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pBlockBackEdge_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pBlockBackEdge_DMI->SetScalarParameterValue("XscaleOffset", 0.16);

	m_pBlockFront_DMI = m_pBlockFront->CreateDynamicMaterialInstance(1, pPageMI);
	m_pBlockFront_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pBlockFront_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pBlockFront_DMI->SetScalarParameterValue("Roughness", m_paperPageRoughness[m_MISerialInfo.paperPageRoughnessNb]);
	m_pBlockFront_DMI->SetScalarParameterValue("WidgetRotation", 0.5);
	m_pBlockFront_DMI->SetScalarParameterValue("DirtStrength", m_paperDirtStrength);
	m_pBlockFront->SetMaterial(0, m_pBlockFront_DMI);

	m_pBlockBack_DMI = m_pBlockBack->CreateDynamicMaterialInstance(1, pPageMI);
	m_pBlockBack_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pBlockBack_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pBlockBack_DMI->SetScalarParameterValue("Roughness", m_paperPageRoughness[m_MISerialInfo.paperPageRoughnessNb]);
	m_pBlockBack_DMI->SetScalarParameterValue("DirtStrength", m_paperDirtStrength);
	m_pBlockBack->SetMaterial(0, m_pBlockBack_DMI);

	m_pEndpapers_DMI = m_pBookCoverBack->CreateDynamicMaterialInstance(1, pPaperEndSheet);
	m_pSpineBack->SetMaterial(1, m_pEndpapers_DMI);
	m_pBookCoverFront->SetMaterial(1, m_pEndpapers_DMI);
	m_pBlockFront->SetMaterial(2, m_pEndpapers_DMI);
	m_pBlockBack->SetMaterial(2, m_pEndpapers_DMI);
	m_pEndpapers_DMI->SetTextureParameterValue("TextureMap", m_pPaperTypeTexture[m_MISerialInfo.pageTextureMapNb]);
	m_pEndpapers_DMI->SetTextureParameterValue("NormalMap", m_pPaperTypeNormals[m_MISerialInfo.pageNormalMapNb]);
	m_pEndpapers_DMI->SetScalarParameterValue("DirtStrength", m_paperDirtStrength);

	m_pBlockFrontEdge_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pBlockBackEdge_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pPageBack_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pPageFront_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pBlockFront_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pBlockBack_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);
	m_pEndpapers_DMI->SetTextureParameterValue("DirtMap", m_pDirtMapTexture[m_MISerialInfo.dirtMapTextureNb]);

	m_pBlockFrontEdge_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pBlockBackEdge_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pPageBack_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pPageFront_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pBlockFront_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pBlockBack_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);
	m_pEndpapers_DMI->SetTextureParameterValue("DirtMask", m_pDirtMapMask[m_MISerialInfo.dirtMapMaskNb]);

	m_pPreviewLayoutBack->SetMaterial(0, m_pBlockBackEdge_DMI);
	m_pPreviewLayoutFront->SetMaterial(0, m_pBlockFrontEdge_DMI);
	m_pPreviewLayoutBack->SetMaterial(3, m_pBlockBackEdge_DMI);
	m_pPreviewLayoutFront->SetMaterial(3, m_pBlockFrontEdge_DMI);
	m_pPreviewLayoutBack->SetMaterial(1, m_pBlockBack_DMI);
	m_pPreviewLayoutFront->SetMaterial(1, m_pBlockFront_DMI);
	m_pPreviewLayoutBack->SetMaterial(2, m_pEndpapers_DMI);
	m_pPreviewLayoutFront->SetMaterial(2, m_pEndpapers_DMI);

	m_pCoverFront_DMI = m_pBookCoverFront->CreateDynamicMaterialInstance(0, m_pCoverMaterial);
	m_pBookCoverBack->SetMaterial(0, m_pCoverFront_DMI);
	m_pSpineBack->SetMaterial(0, m_pCoverFront_DMI);
	m_pCoverFront_DMI->SetScalarParameterValue("Metallic", m_coverDetailingMetallic);
	m_pCoverFront_DMI->SetScalarParameterValue("DirtStrength", 1 - m_coverDirtStrength);

	m_pPageFront_DMI->SetTextureParameterValue("Text", m_pWidget_PageFront->GetRenderTarget());
	m_pPageBack_DMI->SetTextureParameterValue("Text", m_pWidget_PageBack->GetRenderTarget());
	m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
	m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
	m_pPageFront_DMI->SetTextureParameterValue("Text", m_pWidget_PageFront->GetRenderTarget());
	m_pPageBack_DMI->SetTextureParameterValue("Text", m_pWidget_PageFront->GetRenderTarget());

	//m_pPageBack->SetMaterial(m_pPageBack_DMI);

	//////////////////////////////////////////////////////////////////////////
	float scaleX = GetActorScale3D().X;
	float scaleY = GetActorScale3D().Y;
	float scaleZ = GetActorScale3D().Z;
	int32 option = 0;
	if (scaleX == scaleY && scaleX == scaleZ) option = 3;
	else if (scaleX != scaleY && scaleX == scaleZ) option = 1;
	else if (scaleX == scaleY && scaleX != scaleZ) option = 2;
	else option = 0;
	if (option == 0 || option == 3) SetActorScale3D(FVector(scaleX, scaleX, scaleX));
	else if (option == 1) SetActorScale3D(FVector(scaleY, scaleY, scaleY));
	else SetActorScale3D(FVector(scaleZ, scaleZ, scaleZ));

	float spineBackScaleY = ((1 - m_bookThickness)*0.15 + m_bookThickness)*1.15*m_pSpineBack->RelativeScale3D.Y;
	m_pSpineBack->SetRelativeScale3D(FVector(m_bookProportions, spineBackScaleY, m_coverThickness));

	float bookCoverScaleY = 1.f / m_pSpineBack->RelativeScale3D.Y;
	m_pBookCoverFront->SetRelativeScale3D(FVector(1, bookCoverScaleY, 1));
	m_pBookCoverBack->SetRelativeScale3D(FVector(1, bookCoverScaleY, 1));

	m_pPageFront->SetRelativeScale3D(FVector(m_bookProportions, 1, m_bookThickness));
	m_pPageBack->SetRelativeScale3D(FVector(m_bookProportions, 1, m_bookThickness));
	m_pBlockFront->SetRelativeScale3D(FVector(m_bookProportions, 1, m_bookThickness));
	m_pBlockBack->SetRelativeScale3D(FVector(m_bookProportions, 1, m_bookThickness));

	//////////////////////////////////////////////////////////////////////////
	m_pWidget_CoverFront->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));
	m_pWidget_CoverBack->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));
	m_pWidget_BlockFront->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));
	m_pWidget_BlockBack->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));
	m_pWidget_PageFront->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));
	m_pWidget_PageBack->SetRelativeScale3D(FVector(0.001, 0.001, 0.001));

	m_pWidget_BlockFront->SetDrawSize(FVector2D(m_pageResolution, m_pageResolution*1.4142*m_bookProportions));
	m_pWidget_BlockBack->SetDrawSize(FVector2D(m_pageResolution, m_pageResolution*1.4142*m_bookProportions));
	m_pWidget_PageFront->SetDrawSize(FVector2D(m_pageResolution, m_pageResolution*1.4142*m_bookProportions));
	m_pWidget_PageBack->SetDrawSize(FVector2D(m_pageResolution, m_pageResolution*1.4142*m_bookProportions));

	m_pWidget_CoverFront->SetDrawSize(FVector2D(m_pageResolution*m_coverResolutionMultiplier, m_pageResolution*m_coverResolutionMultiplier*m_bookProportions));
	m_pWidget_CoverBack->SetDrawSize(FVector2D(m_pageResolution*m_coverResolutionMultiplier, m_pageResolution*m_coverResolutionMultiplier*m_bookProportions));

	m_pWidget_CoverFront->SetCastShadow(false);
	m_pWidget_CoverBack->SetCastShadow(false);
	m_pWidget_BlockFront->SetCastShadow(false);
	m_pWidget_BlockBack->SetCastShadow(false);
	m_pWidget_PageFront->SetCastShadow(false);
	m_pWidget_PageBack->SetCastShadow(false);

	TallyPages(true);

	//////////////////////////////////////////////////////////////////////////
	m_pBlockBack->SetVisibility(false);
	m_pBlockFront->SetVisibility(false);
	m_pPreviewLayoutFront->SetVisibility(true);
	m_pPreviewLayoutBack->SetVisibility(true);

	float bookBreakClamp = FMath::Clamp<float>(m_whereDoesSpineBreak, m_bookBreakClampMin, m_bookBreakClampMax);
	float averagePageThickness = (m_bookThickness + 4)*0.2;

	m_pPreviewLayoutBack->SetRelativeScale3D(FVector(1, 1, averagePageThickness*(1 - bookBreakClamp)));
	m_pPreviewLayoutFront->SetRelativeScale3D(FVector(1, 1, averagePageThickness*bookBreakClamp));

	float frontCenterZ = FMath::Lerp(-0.7*2.4*averagePageThickness*(0.5 - bookBreakClamp), 0.2 + 2*bookBreakClamp*averagePageThickness, m_bookOpenTargetAmount);
	m_pBlockFrontCenter->SetRelativeLocation(FVector(0, -7.58, frontCenterZ));

	float backCenterZ = FMath::Lerp(2.4*averagePageThickness*(0.5 - bookBreakClamp), 0.2 + 2 * (1-bookBreakClamp)*averagePageThickness, m_bookOpenTargetAmount);
	m_pBlockBackCenter->SetRelativeLocation(FVector(0, -7.58, backCenterZ));

	m_pWidget_CoverFront->SetVisibility(true);
	m_pWidget_CoverBack->SetVisibility(true);

	m_bookOpenCurrentAmount = m_bookOpenTargetAmount;
	m_coverOpenAmount = m_bookOpenCurrentAmount;

	//////////////////////////////////////////////////////////////////////////
	m_pCoverFront_DMI->SetTextureParameterValue("DirtLayer", m_pCoverDirtTexture[m_MISerialInfo.coverDirtTextNb]);

	NotifyAddAttachMesh();
}

void AAnimBook::InitialBook()
{
	if (!m_preview)
	{
		NotifyReadAllTexture();
		m_pBlockBackCenter->SetRelativeLocation(FVector(0, -7.25, 0));
		m_pBlockFrontCenter->SetRelativeLocation(FVector(0, -7.25, 0));
		m_pBlockBack->SetVisibility(true);
		m_pBlockFront->SetVisibility(true);
		m_pPageBack->SetVisibility(false, true);
		m_pPageFront->SetVisibility(false, true);
	}
	SetBlockAngle(m_bookOpenCurrentAmount, false);
	if (!m_preview) UpdateMorphTargets(m_bookOpenCurrentAmount, 1, false, false);
	OrientToGround();
	OrientToGround();
	SetEdgeTextureOffset(m_whereDoesSpineBreak, m_whereDoesSpineBreak + 0.2);
	ApplyTypographySettings();
	UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
	UpdatePageWidget(m_pW_BlockBack, m_currentPage, false);
	UpdatePageWidget(m_pW_CoverFront, 0, true);
	if (m_pWidget_BlockFront->IsVisible() || m_pWidget_BlockBack->IsVisible())
	{
		if (!m_preview)
		{
			if (!m_pWidget_BlockFront->GetRenderTarget() || !m_pWidget_BlockBack->GetRenderTarget())
			{
				GetWorldTimerManager().SetTimer(m_drawBlockRTTimerHandler, this, &AAnimBook::WaitToDrawBlockRT, 0.1, false);
				return;
			}
			/*if (!m_pWidget_BlockFront->GetRenderTarget() || !m_pWidget_BlockBack->GetRenderTarget())
			{
				NotifyDelay(0.0f, 1);
				return;
			}*/
			WaitToDrawBlockRT();
			
		}
		else
		{
			m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
			m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
			if (!m_preview)
			{
				/*if (!m_pWidget_CoverFront->GetRenderTarget())
				{
					FLatentActionInfo latenInfo;
					latenInfo.UUID = 5;
					latenInfo.CallbackTarget = this;
					latenInfo.ExecutionFunction = "WaitToDrawCoverRT";
					latenInfo.Linkage = 0;
					UKismetSystemLibrary::Delay(this, 0.0, latenInfo);
				}*/
				if (!m_pWidget_CoverFront->GetRenderTarget())
				{
					GetWorldTimerManager().SetTimer(m_drawCoverRTTimerHandler, this, &AAnimBook::WaitToDrawCoverRT, 0.1, false);
					return;
				}
				WaitToDrawCoverRT();
				
			}
			else
			{
				m_pCoverFront_DMI->SetTextureParameterValue("Text", m_pWidget_CoverFront->GetRenderTarget());
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetXoffset", 0);
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetXScale", 1);
				m_pCoverFront_DMI->SetScalarParameterValue("TextRoughness", 1 - m_coverLetteringGloss);
				m_pCoverFront_DMI->SetScalarParameterValue("TextMetallic", m_coverLetteringMetallic);
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetAlpha", 0);
				m_initInProgress = false;
			}
		}
	}
}

void AAnimBook::SetBlockAngle(float bookOpenAmount, bool pageOrBlock)
{
	float fullyOpenOffset = 0.f;
	float blendPreventPagesThrough = 5.5*m_bookThickness + (0.5 - (FMath::Abs(0.5 - m_whereDoesSpineBreak) + m_bookThickness * 0.1))*4 - (1.f - m_coverThickness);
	/*FVector2D inRange(0, 1);
	FVector2D outRange(90, blendPreventPagesThrough);*/
	float clampValue = UKismetMathLibrary::MapRangeClamped(bookOpenAmount, 0.f, 1.f, 90.f, blendPreventPagesThrough);
	//float clampValue = FMath::GetMappedRangeValueClamped(inRange, outRange, bookOpenAmount);

	float t = (0.6 - FMath::Abs(0.6 - m_bookOpenCurrentAmount))*0.4*(0.5 - m_whereDoesSpineBreak);

	FRotator rot(0,0,clampValue + t);
	FRotator rotBack(0, 180, clampValue - t);
	if (pageOrBlock)
	{
		m_pPageFront->SetRelativeRotation(rot, false, nullptr, ETeleportType::TeleportPhysics);
		m_pPageBack->SetRelativeRotation(rotBack, false, nullptr, ETeleportType::TeleportPhysics);
	}
	else
	{
		m_pBlockFront->SetRelativeRotation(rot, false, nullptr, ETeleportType::TeleportPhysics);
		m_pBlockBack->SetRelativeRotation(rotBack, false, nullptr, ETeleportType::TeleportPhysics);
	}

}

void AAnimBook::UpdateSceneCoords(float bookOpenAmount, USceneComponent* pPageScene, bool backOrFront)
{
	float t1 = 0.f;
	float t2 = 0.f;
	if (backOrFront)
	{
		t1 = m_whereDoesSpineBreak;
		t2 = 1 - m_whereDoesSpineBreak;
	}
	else
	{
		t1 = 1 - m_whereDoesSpineBreak;
		t2 = m_whereDoesSpineBreak;
	}
	FRotator newRot(0, 0, bookOpenAmount*m_bookThickness*(t1 + 0.5)*(-7.88));
	float t3 = ((t2 - 0.5)*0.71 + 0.18 - 0.02*m_bookThickness)*bookOpenAmount;
	float t4 = 0.5*bookOpenAmount - 7.25 - 0.14*m_bookThickness;
	FVector newLoc(0, t4, t3);
	pPageScene->SetRelativeLocationAndRotation(newLoc, newRot, false, nullptr, ETeleportType::TeleportPhysics);
}

void AAnimBook::GetBlockEdgeLocation(USceneComponent* pTrackingPoint, float openAmount, float spineBreak)
{
	float t1 = FMath::Clamp(FMath::Abs<float>(m_whereDoesSpineBreak - 0.5), 1.f - m_bookThickness, 0.5f);
	m_thinPageOffset = FMath::Clamp((float)(t1 * 2 * (1.2 - m_bookThickness)), 0.0f, 1.0f)*m_coverThickness*(-0.5);
	float t2 = FMath::Lerp(FMath::Abs(spineBreak - 0.4)*0.4 + 0.1, (1 - spineBreak)*0.5 - 0.9, openAmount);
	float t3 = (spineBreak + 0.07)*(-1.87) - (-0.3)*openAmount*spineBreak + m_thinPageOffset;
	FVector newLoc(0, t2, t3);
	pTrackingPoint->SetRelativeLocation(newLoc);
}

void AAnimBook::SetEdgeTextureOffset(float pageCurrentlyOpenBack, float pageCurrentlyOpenFront)
{
	m_pBlockBackEdge_DMI->SetScalarParameterValue(FName(TEXT("Xscale")), 1.2 - pageCurrentlyOpenBack);
	m_pBlockFrontEdge_DMI->SetScalarParameterValue(FName(TEXT("Xscale")), pageCurrentlyOpenFront);
}

void AAnimBook::UpdateMorphTargets(float bookOpenAmount, float pageOpenAmount, bool pageOrBlock, bool updateInvisiblePage)
{
	float t1 = 0.f;
	if (pageOrBlock)
	{
		t1 = bookOpenAmount * pageOpenAmount;
		m_pPageBack->SetMorphTarget(FName(TEXT("Open_thick")), t1, false);
		m_pPageBack->SetMorphTarget(FName(TEXT("Open_thin")), t1*m_whereDoesSpineBreak*m_thinBoost, false);
		float t2 = 1 - t1;
		float t3 = 0;
		if (1 - m_whereDoesSpineBreak >= 0.5) t3 = (1 - m_whereDoesSpineBreak - 0.5) * 2 * t2;
		else t3 = 0;
		m_pPageBack->SetMorphTarget(FName(TEXT("Closed_thick")), t3, false);
		m_pPageBack->SetMorphTarget(FName(TEXT("Closed_thin")), t2*m_whereDoesSpineBreak*1.25, false);

		m_pPageFront->SetMorphTarget(FName(TEXT("Open_thick")), t1, false);
		m_pPageFront->SetMorphTarget(FName(TEXT("Open_thin")), t1*(1 - m_whereDoesSpineBreak)*m_thinBoost, false);
		t3 = 0;
		if (1 - m_whereDoesSpineBreak >= 0.5) t3 = 0;
		else t3 = 1 - (1 - m_whereDoesSpineBreak) * 2;
		m_pPageFront->SetMorphTarget(FName(TEXT("Closed_thick")), t2*t3, false);
		m_pPageFront->SetMorphTarget(FName(TEXT("Closed_thin")), t2*(1 - m_whereDoesSpineBreak)*1.25, false);
		if (updateInvisiblePage || m_pPageFront->bVisible != 0) UpdateSceneCoords(t1, m_pPageFrontCenter, false);
		if (updateInvisiblePage || m_pPageBack->bVisible != 0) UpdateSceneCoords(t1, m_pPageBackCenter, true);
	}
	else
	{
		t1 = bookOpenAmount;

		m_pBlockBack->SetMorphTarget(FName(TEXT("Open_thick")), t1, false);
		m_pBlockBack->SetMorphTarget(FName(TEXT("Open_thin")), t1*m_whereDoesSpineBreak*m_thinBoost, false);
		float t2 = 1 - t1;
		float t3 = 0;
		if (1 - m_whereDoesSpineBreak >= 0.5) t3 = (1 - m_whereDoesSpineBreak - 0.5) * 2 * t2;
		else t3 = 0;
		m_pBlockBack->SetMorphTarget(FName(TEXT("Closed_thick")), t3, false);
		m_pBlockBack->SetMorphTarget(FName(TEXT("Closed_thin")), t2*m_whereDoesSpineBreak*1.25, false);

		m_pBlockFront->SetMorphTarget(FName(TEXT("Open_thick")), t1, false);
		m_pBlockFront->SetMorphTarget(FName(TEXT("Open_thin")), t1*(1 - m_whereDoesSpineBreak)*m_thinBoost, false);
		t3 = 0;
		if (1 - m_whereDoesSpineBreak >= 0.5) t3 = 0;
		else t3 = 1 - (1 - m_whereDoesSpineBreak) * 2;
		m_pBlockFront->SetMorphTarget(FName(TEXT("Closed_thick")), t2*t3, false);
		m_pBlockFront->SetMorphTarget(FName(TEXT("Closed_thin")), t2*(1 - m_whereDoesSpineBreak)*1.25, false);

		GetBlockEdgeLocation(m_pSpineAttachPointFront, t1, m_whereDoesSpineBreak);
		GetBlockEdgeLocation(m_pSpineAttachPointBack, t1, 1 - m_whereDoesSpineBreak);
		UpdateSceneCoords(t1, m_pBlockFrontCenter, false);
		UpdateSceneCoords(t1, m_pBlockBackCenter, true);
	}
}

void AAnimBook::UpdateTurnThePage(float pageTurn, float noDamping, float progress)
{
	if (m_dampedPageTurns) m_pageOpenAmount = pageTurn;
	else m_pageOpenAmount = noDamping;

	if (m_pageTurnBackwards) m_whereDoesSpineBreak = m_whereDoesSpineBreak_Scratch - (progress - 1) / (float)m_totalPages * 2;
	else m_whereDoesSpineBreak = m_whereDoesSpineBreak_Scratch - progress / (float)m_totalPages * 2;

	UpdateMorphTargets(m_bookOpenCurrentAmount, m_whereDoesSpineBreak, false, false);
	float pageCurrentlyOpenBack = 0;
	float pageCurrentlyOpenFront = 0;
	if (m_pageTurnBackwards) pageCurrentlyOpenBack = m_whereDoesSpineBreak - (FMath::Clamp<float>(progress - 0.5, 0.f, 1.f) * 2 - 1) / (float)m_totalPages * 2;
	else pageCurrentlyOpenBack = m_whereDoesSpineBreak - FMath::Clamp<float>(progress - 0.5, 0, 1) * 2 / (float)m_totalPages * 2;
	if (m_pageTurnBackwards) pageCurrentlyOpenFront = m_whereDoesSpineBreak - (FMath::Clamp<float>(0.5 - progress, 0, 1) * (-2) - 1) / (float)m_totalPages * 2;
	else pageCurrentlyOpenFront = m_whereDoesSpineBreak - FMath::Clamp<float>(0.5 - progress, 0, 1) * (-2) / (float)m_totalPages * 2;
	SetEdgeTextureOffset(pageCurrentlyOpenBack, pageCurrentlyOpenFront);
	SetBlockAngle(m_bookOpenCurrentAmount*m_pageOpenAmount, true);
	UpdateMorphTargets(m_bookOpenCurrentAmount, m_pageOpenAmount, true, false);
	SetBlockAngle(m_bookOpenCurrentAmount, false);
	OrientToGround();
}

void AAnimBook::OrientToGround()
{
	FVector centerLoc = m_pCenter->GetComponentLocation();
	FVector spineAttachPointFrontLoc = m_pSpineAttachPointFront->GetComponentLocation();
	FVector spineAttachPointBackLoc = m_pSpineAttachPointBack->GetComponentLocation();
	m_pDirectionReference->SetWorldLocation(centerLoc + spineAttachPointFrontLoc - spineAttachPointBackLoc);
	m_pSpineBack->SetWorldLocation((spineAttachPointFrontLoc + spineAttachPointBackLoc) / 2);
	FVector centerRot = m_pCenter->RelativeLocation;
	FVector DRRot = m_pDirectionReference->RelativeLocation;
	FRotator findLookRot = UKismetMathLibrary::FindLookAtRotation(centerRot, DRRot);
	m_spineAngle = findLookRot.Pitch;
	m_pSpineBack->SetRelativeRotation(FRotator(0, 0, m_spineAngle));
	FTransform transform(GetActorRotation(), (spineAttachPointFrontLoc + spineAttachPointBackLoc) / 2, GetActorScale3D());
	m_pIKSpineCenter->SetRelativeLocation(UKismetMathLibrary::InverseTransformLocation(transform, centerLoc));

	FVector bookCoverFrontLoc = m_pBookCoverFront->GetComponentLocation();
	FVector bookCoverBackLoc = m_pBookCoverBack->GetComponentLocation();
	FVector groundScale = m_pGround->GetComponentScale();

	FVector inverseBookCoverFront = UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), bookCoverFrontLoc);
	FVector inverseBookCoverBack = UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), bookCoverBackLoc);

	float t1 = FMath::Clamp<float>(m_bookOpenCurrentAmount * 4, 0, 1);
	float t2 = (groundScale.X*inverseBookCoverFront.Z - m_coverThickness * 0.25*groundScale.X)*t1;
	float atan2Result = UKismetMathLibrary::Atan2(t2, 14.8*groundScale.X);
	m_pBookCoverFront->SetRelativeRotation(FRotator(180, 0, m_spineAngle - 90 * (1 - m_coverOpenAmount) + atan2Result));
	float t3 = (groundScale.X*inverseBookCoverBack.Z - m_coverThickness * 0.25*groundScale.X)*t1;
	float atan2Result2 = UKismetMathLibrary::Atan2(t3, 14.8*groundScale.X);
	m_pBookCoverBack->SetRelativeRotation(FRotator(180, 0, -atan2Result2 + 90 * (1 - m_coverOpenAmount) - (180 - m_spineAngle)));
}

void AAnimBook::UpdatePageWidget(UTPage* pWidget, int32 pagetoOpento, bool isCover)
{
	if (m_preview) return;
	FPageInfo pageInfo;
	if (isCover) pageInfo = m_coverPageInfo;
	else
	{
		if (m_individualPages.Num() >= pagetoOpento && pagetoOpento >= 1) pageInfo = m_individualPages[pagetoOpento - 1];
		//else m_individualPages.Add(pageInfo);
	}
	if (m_pPlayCardTextureMap.Contains(pageInfo.cardName))
	{
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, m_pBookTextureMat);
		pMI->SetTextureParameterValue("BaseTexture", m_pPlayCardTextureMap[pageInfo.cardName]);
		pWidget->m_pImage->SetBrushFromMaterial(pMI);
		pWidget->m_pImage->Brush.ImageSize = m_pagePictureDrawSize * m_pictureSize;
		//pWidget->m_pImage->Brush.SetResourceObject(pageInfo.pTexture);
	}
	else
		pWidget->m_pImage->SetVisibility(ESlateVisibility::Collapsed);
	pWidget->m_pBodyText->SetText(FText::FromString(pageInfo.bodyStr));
	
	/*for (int32 i=0; i<pageInfo.optionStrs.Num(); i++)
	{
		UTemplateRuneElement* pChoice = CreateWidget<UTemplateRuneElement>(GetGameInstance(), m_pChoiceButtonClass);
		pChoice->NotifyInitial();
		pChoice->m_pRuneName->SetText(FText::FromString(pageInfo.optionStrs[i]));
		pChoice->m_buttonFunction = "ChoiceButton_" + pageInfo.choices[i];
		pWidget->m_pChoiceElements.Add(pChoice);
		pWidget->m_pVBox->AddChild(pChoice);
	}*/
}

void AAnimBook::TurnThePage(bool backwards, float howQuickly)
{
	if ((m_currentPage <= 2 && backwards) || (m_currentPage >= m_numberofViewablePages && !backwards))
	{

	}
	else
	{
		m_isTurningPage = true;
		float pageTurnSpeed = 0.f;
		if (howQuickly <= 0) pageTurnSpeed = 0.05;
		else pageTurnSpeed = howQuickly;
		if (m_pageTurnInProgress)
		{
			if (!m_allowPageTurnsMidTurn) return;
			m_pPageTurn->SetPlayRate(m_pPageTurn->GetPlayRate()*2.2);
			m_pageTurnQueued = true;
			m_pageTurnDirectionQueued = backwards;
			m_pageTurnSpeedQueued = pageTurnSpeed;
		}
		else
		{
			m_pageTurnBackwards = backwards;
			m_pPageTurn->SetPlayRate(1 / pageTurnSpeed);
			m_pageOpenAmount = 1.f;
			m_pWidget_PageFront->SetVisibility(true, false);
			m_pWidget_PageBack->SetVisibility(true, false);
			m_pPageFront->SetVisibility(m_pageTurnBackwards);
			m_pPageBack->SetVisibility(!m_pageTurnBackwards);
			m_pPageBackRevCenter->SetRelativeRotation(FRotator(180, 0, 0));
			if (m_pageTurnBackwards)
			{
				UpdatePageWidget(m_pW_PageBack, m_currentPage - 2, false);
				UpdatePageWidget(m_pW_PageFront, m_currentPage - 1, false);
			}
			else
			{
				UpdatePageWidget(m_pW_PageBack, m_currentPage, false);
				UpdatePageWidget(m_pW_PageFront, m_currentPage + 1, false);
			}
			SetBlockAngle(m_bookOpenCurrentAmount, true);
			UpdateMorphTargets(m_bookOpenCurrentAmount, m_pageOpenAmount, true, true);
			GetWorldTimerManager().SetTimer(m_turnDelayActionTimerHandler, this, &AAnimBook::TurnDelayAction, m_renderDelay + 0.1, false);
			//TurnDelayAction();
			/*FLatentActionInfo latenInfo;
			latenInfo.UUID = 0;
			latenInfo.CallbackTarget = this;
			latenInfo.ExecutionFunction = "TurnDelayAction";
			latenInfo.Linkage = 0;
			UKismetSystemLibrary::Delay(this, m_renderDelay + 0.1, latenInfo);*/
			//NotifyDelay(m_renderDelay + 0.1, 0);
		}
	}
}

void AAnimBook::TurnDelayAction()
{
	m_pPageFront_DMI->SetTextureParameterValue("Text", m_pWidget_PageFront->GetRenderTarget());
	m_pPageBack_DMI->SetTextureParameterValue("Text", m_pWidget_PageBack->GetRenderTarget());
	if (m_pageTurnBackwards)
	{
		m_pPageFront_DMI->SetScalarParameterValue("WidgetRotation", 0.5);
		m_pPageBack_DMI->SetScalarParameterValue("WidgetRotation", 0.5);
		m_pPageFront_DMI->SetScalarParameterValue("Invert", 1);
		m_pPageBack_DMI->SetScalarParameterValue("Invert", -1);
		m_currentPage = m_currentPage - 2;
	}
	else
	{
		m_pPageFront_DMI->SetScalarParameterValue("WidgetRotation", 0);
		m_pPageBack_DMI->SetScalarParameterValue("WidgetRotation", 0);
		m_pPageFront_DMI->SetScalarParameterValue("Invert", -1);
		m_pPageBack_DMI->SetScalarParameterValue("Invert", 1);
		m_currentPage = m_currentPage + 2;
	}
	m_pPageFront_DMI->SetScalarParameterValue("OpacityMask", 1);
	m_pPageBack_DMI->SetScalarParameterValue("OpacityMask", 1);
	m_whereDoesSpineBreak_Scratch = ((float)(m_currentPage + m_nonViewableExtraPagesAtFront)) / (float)((float)(m_totalPages + 1) / 2.0 * 2.0);
	m_halfwayMarkReached = false;
	NotifyPageTurnPlayTimeLine(m_pageTurnBackwards);
	GetWorldTimerManager().ClearTimer(m_turnDelayActionTimerHandler);
}

void AAnimBook::NotifyOpentoPagePlayTimeLine_Implementation()
{

}

void AAnimBook::TurnPageFinish()
{
	m_whereDoesSpineBreak = ((float)(m_currentPage + m_nonViewableExtraPagesAtFront)) / (float)((float)(m_totalPages + 1) / 2.0 * 2.0);
	if (m_pageTurnBackwards)
	{
		UpdatePageWidget(m_pW_BlockBack, m_currentPage - 1, false);
		m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
	}
	else
	{
		UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
		m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
	}
	m_pPageFront_DMI->SetScalarParameterValue("OpacityMask", 0);
	m_pPageBack_DMI->SetScalarParameterValue("OpacityMask", 0);
	m_pPageFront->SetVisibility(false);
	m_pPageBack->SetVisibility(false);
	m_pWidget_PageFront->SetVisibility(false);
	m_pWidget_PageBack->SetVisibility(false);
	m_pageTurnInProgress = false;
	m_isTurningPage = false;
	if (!m_pageTurnQueued) return;

	TurnThePage(m_pageTurnDirectionQueued, m_pageTurnSpeedQueued);
	m_pageTurnQueued = false;
}

void AAnimBook::Turn1_9Damped()
{
	if (!m_dampedPageTurns) return;
	if (m_halfwayMarkReached)
	{
		if (m_pageTurnBackwards)
		{
			UpdatePageWidget(m_pW_BlockBack, m_currentPage, false);
			m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
		}
		else
		{
			UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
			m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
		}
	}
	else
	{
		if (m_pageTurnBackwards)
		{
			UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
			m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
		}
		else
		{
			UpdatePageWidget(m_pW_BlockBack, m_currentPage, false);
			m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
		}
	}
}

void AAnimBook::TurnHalfMark()
{
	m_halfwayMarkReached = true;
	if (m_pageTurnBackwards)
	{
		m_pPageFront_DMI->SetScalarParameterValue("Invert", -1);
		m_pPageBack_DMI->SetScalarParameterValue("Invert", 1);
		m_pPageFront->SetVisibility(false);
		m_pPageBack->SetVisibility(true);
		m_pPageFront_DMI->SetScalarParameterValue("WidgetRotation", 0);
		m_pPageBack_DMI->SetScalarParameterValue("WidgetRotation", 0);
	}
	else
	{
		m_pPageFront_DMI->SetScalarParameterValue("Invert", 1);
		m_pPageBack_DMI->SetScalarParameterValue("Invert", -1);
		m_pPageFront->SetVisibility(true);
		m_pPageBack->SetVisibility(false);
		m_pPageFront_DMI->SetScalarParameterValue("WidgetRotation", 0.5);
		m_pPageBack_DMI->SetScalarParameterValue("WidgetRotation", 0.5);
	}
}

void AAnimBook::OpenToPage(float openHowWide, float openHowQuickly, int32 pageToOpen)
{
	//WaitToDrawBlockRT();
	if (m_bookOpeningInProgress && m_coversOpenAheadOfPagesSlightly) return;
	m_isTurningPage = true;
	m_bookOpeningInProgress = true;
	m_bookOpenTargetAmount = openHowWide;
	if (openHowQuickly <= 0) m_pOpenTheBook->SetPlayRate(1.f / 0.001);
	else m_pOpenTheBook->SetPlayRate(1.f / openHowQuickly);
	int32 currentPage = 0;
	if (pageToOpen >= 0 && pageToOpen <= m_numberofViewablePages)
	{
		m_currentPage = (pageToOpen + 2) / 2 * 2;
		currentPage = (pageToOpen + 2) / 2 * 2;
	}
	else
	{
		currentPage = m_currentPage;
	}
	m_whereDoesSpineBreak = ((float)(currentPage + m_nonViewableExtraPagesAtFront)) / (float)((float)(m_totalPages + 1) / 2.0 * 2.0);

	m_bookOpenStart = m_bookOpenCurrentAmount;
	m_multiplier = m_bookOpenTargetAmount - m_bookOpenCurrentAmount;
	if (!m_pageTurnInProgress)
	{
		UpdatePageWidget(m_pW_BlockBack, m_currentPage, false);
		UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
	}
	m_pWidget_BlockBack->SetVisibility(true);
	m_pWidget_BlockFront->SetVisibility(true);
	if (m_bookOpenTargetAmount <= 0) m_bookOpeningStyle = 2;
	else if (m_bookOpenTargetAmount <= 1) m_bookOpeningStyle = 0;
	else m_bookOpeningStyle = 1;
	NotifyOpentoPagePlayTimeLine();
}

void AAnimBook::UpdateOpenToPage(float p1, float p2, float p3, float cover, float coverReverse)
{
	float t1 = 0;
	if (m_bookOpeningStyle == 0) t1 = p1;
	else if (m_bookOpeningStyle == 1) t1 = p2;
	else t1 = p3;
	m_bookOpenCurrentAmount = t1 * m_multiplier + m_bookOpenStart;
	if (!m_jumpingToPage)
	{
		if (m_coversOpenAheadOfPagesSlightly)
		{
			if (m_multiplier <= 0) m_coverOpenAmount = coverReverse * m_multiplier + m_bookOpenStart;
			else m_coverOpenAmount = cover * m_multiplier + m_bookOpenStart;
		}
		else m_coverOpenAmount = m_bookOpenCurrentAmount;
	}
	if (m_pageTurnInProgress) return;
	SetBlockAngle(m_bookOpenCurrentAmount, false);
	UpdateMorphTargets(m_bookOpenCurrentAmount, 0.f, false, false);
	SetEdgeTextureOffset(m_whereDoesSpineBreak, m_whereDoesSpineBreak + 0.2);
	OrientToGround();
}

void AAnimBook::OpenToPageFinish()
{
	if (m_bookOpenCurrentAmount < 0.05)
	{
		m_pWidget_PageFront->SetVisibility(false);
		m_pWidget_PageBack->SetVisibility(false);
		m_pWidget_BlockFront->SetVisibility(false);
		m_pWidget_BlockBack->SetVisibility(false);
		m_pPageFront->SetVisibility(false);
		m_pPageBack->SetVisibility(false);
	}
	m_isTurningPage = false;
	m_bookOpeningInProgress = false;
	if (m_jumpingToPage)
	{
		if (m_bookOpenTargetAmount > 0) m_jumpingToPage = false;
		else
		{
			OpenToPage(m_queuedBookOpenAmount, 1.f / m_pOpenTheBook->GetPlayRate(), m_queuedPage);
			return;
		}
	}
	if (!m_pageTurnQueued) return;
	TurnThePage(m_pageTurnDirectionQueued, m_pageTurnSpeedQueued);
	m_pageTurnQueued = false;
}

void AAnimBook::ApplyTypographySettings()
{
	float blockFrontDrawSizeX = m_pWidget_BlockFront->GetDrawSize().X;
	float coverFrontDrawSizeX = m_pWidget_CoverFront->GetDrawSize().X;

	m_pagePictureDrawSize.X = blockFrontDrawSizeX;
	m_pagePictureDrawSize.Y = blockFrontDrawSizeX;

	m_coverPictureDrawSize.X = 0.75*coverFrontDrawSizeX;
	m_coverPictureDrawSize.Y = 0.75*coverFrontDrawSizeX;

	m_pW_BlockFront = Cast<UTPage>(m_pWidget_BlockFront->GetUserWidgetObject());
	m_pW_BlockBack = Cast<UTPage>(m_pWidget_BlockBack->GetUserWidgetObject());
	m_pW_PageFront = Cast<UTPage>(m_pWidget_PageFront->GetUserWidgetObject());
	m_pW_PageBack = Cast<UTPage>(m_pWidget_PageBack->GetUserWidgetObject());
	m_pW_CoverFront = Cast<UTPage>(m_pWidget_CoverFront->GetUserWidgetObject());

	m_pW_BlockFront->NotifyInitial();
	m_pW_BlockBack->NotifyInitial();
	m_pW_PageFront->NotifyInitial();
	m_pW_PageBack->NotifyInitial();
	m_pW_CoverFront->NotifyInitial();
}

void AAnimBook::WaitToDrawBlockRT()
{
	/*if (!m_pWidget_BlockFront->GetRenderTarget() || m_pWidget_BlockBack->GetRenderTarget())
	{
		FLatentActionInfo latenInfo;
		latenInfo.UUID = 5;
		latenInfo.CallbackTarget = this;
		latenInfo.ExecutionFunction = "WaitToDrawBlockRT";
		latenInfo.Linkage = 0;
		UKismetSystemLibrary::Delay(this, 0.0, latenInfo);
		return;
	}*/
	/*if (!m_pWidget_BlockFront->GetRenderTarget() || !m_pWidget_BlockBack->GetRenderTarget())
	{
		GetWorldTimerManager().SetTimer(m_drawBlockRTTimerHandler, this, &AAnimBook::WaitToDrawBlockRT, 0.1, false);
		return;
	}*/
	m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
	m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
	GetWorldTimerManager().ClearTimer(m_drawBlockRTTimerHandler);
	if (!m_preview)
	{
		/*if (!m_pWidget_CoverFront->GetRenderTarget())
		{
			FLatentActionInfo latenInfo;
			latenInfo.UUID = 2;
			latenInfo.CallbackTarget = this;
			latenInfo.ExecutionFunction = "WaitToDrawCoverRT";
			latenInfo.Linkage = 0;
			UKismetSystemLibrary::Delay(this, 0.0, latenInfo);
		}*/
		if (!m_pWidget_CoverFront->GetRenderTarget())
		{
			GetWorldTimerManager().SetTimer(m_drawCoverRTTimerHandler, this, &AAnimBook::WaitToDrawCoverRT, 0.1, false);
			return;
		}
		WaitToDrawCoverRT();
	}
	else
	{
		m_pCoverFront_DMI->SetTextureParameterValue("Text", m_pWidget_CoverFront->GetRenderTarget());
		m_pCoverFront_DMI->SetScalarParameterValue("WidgetXoffset", 0);
		m_pCoverFront_DMI->SetScalarParameterValue("WidgetXScale", 1);
		m_pCoverFront_DMI->SetScalarParameterValue("TextRoughness", 1 - m_coverLetteringGloss);
		m_pCoverFront_DMI->SetScalarParameterValue("TextMetallic", m_coverLetteringMetallic);
		m_pCoverFront_DMI->SetScalarParameterValue("WidgetAlpha", 0);
		m_initInProgress = false;
	}
}

void AAnimBook::WaitToDrawCoverRT()
{
	/*if (!m_pWidget_CoverFront->GetRenderTarget())
	{
		FLatentActionInfo latenInfo;
		latenInfo.UUID = 3;
		latenInfo.CallbackTarget = this;
		latenInfo.ExecutionFunction = "WaitToDrawCoverRT";
		latenInfo.Linkage = 0;
		UKismetSystemLibrary::Delay(this, 0.0, latenInfo);
		return;
	}*/
	/*if (!m_pWidget_CoverFront->GetRenderTarget())
	{
		GetWorldTimerManager().SetTimer(m_drawCoverRTTimerHandler, this, &AAnimBook::WaitToDrawCoverRT, 0.1, false);
		return;
	}*/
	m_pCoverFront_DMI->SetTextureParameterValue("Text", m_pWidget_CoverFront->GetRenderTarget());
	m_pCoverFront_DMI->SetScalarParameterValue("WidgetXoffset", 0);
	m_pCoverFront_DMI->SetScalarParameterValue("WidgetXScale", 1);
	m_pCoverFront_DMI->SetScalarParameterValue("TextRoughness", 1 - m_coverLetteringGloss);
	m_pCoverFront_DMI->SetScalarParameterValue("TextMetallic", m_coverLetteringMetallic);
	m_pCoverFront_DMI->SetScalarParameterValue("WidgetAlpha", 0);
	m_initInProgress = false;
	GetWorldTimerManager().ClearTimer(m_drawCoverRTTimerHandler);
}

void AAnimBook::TallyPages(bool isBookConstruction)
{

	m_numberofViewablePages = m_individualPages.Num();
	m_totalPages = m_individualPages.Num() + m_nonViewableExtraPagesAtFront + m_nonViewableExtraPagesAtBack;
	/*FString debugStr = "TallyPages totalPages is: " + FString::FromInt(m_totalPages);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, debugStr);*/
	if (m_totalPages <= 0) m_pageturnThickness = m_bookThickness * 1.5;
	else m_pageturnThickness = m_bookThickness * (1.5 / (float)m_totalPages);
	if (isBookConstruction)
	{
		if (m_pageToOpenTo >= m_numberofViewablePages)
		{
			m_currentPage = m_numberofViewablePages;
			m_pageToOpenTo = m_currentPage - 1;
		}
		else
		{
			if (m_pageToOpenTo <= 0) m_currentPage = 2;
			else m_currentPage = m_pageToOpenTo + 1;
		}
	}
	else
	{

	}
	m_currentPage = (m_currentPage + 1) / 2 * 2;
	float t1 = (m_currentPage + 1) / 2 * 2;
	if (t1 == 0) t1 = 0.01;
	m_whereDoesSpineBreak = FMath::Clamp<float>((float)(m_currentPage + m_nonViewableExtraPagesAtFront) / t1, 0, 1);
}

void AAnimBook::RefreshPages(int32 targetPage)
{
	TallyPages(false);
	/*FString testText = "RefreshPages test curnodeText:" + m_curTreeNode.descriptionAndChoice.chDescriptions;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, testText);*/
	if (targetPage <= m_currentPage && targetPage >= m_currentPage - 1)
	{
		UpdatePageWidget(m_pW_BlockFront, m_currentPage - 1, false);
		UpdatePageWidget(m_pW_BlockBack, m_currentPage, false);
	}
	UpdatePageWidget(m_pW_CoverFront, 0, true);
	/*testText = "RefreshPages test curnodeText:" + m_curTreeNode.descriptionAndChoice.chDescriptions;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, testText);*/
	if (m_pWidget_BlockFront->IsVisible() || m_pWidget_BlockBack->IsVisible())
	{
		if (!m_preview)
		{
			if (!m_pWidget_BlockFront->GetRenderTarget() || !m_pWidget_BlockBack->GetRenderTarget())
			{
				GetWorldTimerManager().SetTimer(m_drawBlockRTTimerHandler, this, &AAnimBook::WaitToDrawBlockRT, 0.1, false);
				return;
			}
			/*if (!m_pWidget_BlockFront->GetRenderTarget() || !m_pWidget_BlockBack->GetRenderTarget())
			{
				NotifyDelay(0.0f, 1);
				return;
			}*/
			WaitToDrawBlockRT();

		}
		else
		{
			m_pBlockFront_DMI->SetTextureParameterValue("Text", m_pWidget_BlockFront->GetRenderTarget());
			m_pBlockBack_DMI->SetTextureParameterValue("Text", m_pWidget_BlockBack->GetRenderTarget());
			if (!m_preview)
			{
				/*if (!m_pWidget_CoverFront->GetRenderTarget())
				{
					FLatentActionInfo latenInfo;
					latenInfo.UUID = 5;
					latenInfo.CallbackTarget = this;
					latenInfo.ExecutionFunction = "WaitToDrawCoverRT";
					latenInfo.Linkage = 0;
					UKismetSystemLibrary::Delay(this, 0.0, latenInfo);
				}*/
				if (!m_pWidget_CoverFront->GetRenderTarget())
				{
					GetWorldTimerManager().SetTimer(m_drawCoverRTTimerHandler, this, &AAnimBook::WaitToDrawCoverRT, 0.1, false);
					return;
				}
				WaitToDrawCoverRT();

			}
			else
			{
				m_pCoverFront_DMI->SetTextureParameterValue("Text", m_pWidget_CoverFront->GetRenderTarget());
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetXoffset", 0);
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetXScale", 1);
				m_pCoverFront_DMI->SetScalarParameterValue("TextRoughness", 1 - m_coverLetteringGloss);
				m_pCoverFront_DMI->SetScalarParameterValue("TextMetallic", m_coverLetteringMetallic);
				m_pCoverFront_DMI->SetScalarParameterValue("WidgetAlpha", 0);
				m_initInProgress = false;
			}
		}
	}
	/*FString testText = "RefreshPages test curnodeText:" + m_curTreeNode.descriptionAndChoice.chDescriptions;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, testText);*/
}


void AAnimBook::ResetBook()
{
	m_individualPages.Empty();
	m_totalPages = 0;
	/*FString debugStr = "ResetBook totalPages is: " + FString::FromInt(m_totalPages);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, debugStr);*/
	m_curActionPanelShowPage = 0;
	m_numberofViewablePages = 0;
	m_pageToOpenTo = 4;
	m_currentPage = 2;
	m_choiceSelectStr = "";
}

void AAnimBook::NotifyReadAllTexture_Implementation()
{

}

void AAnimBook::NotifyDelay_Implementation(float delayTime, uint8 functionID)
{

}

void AAnimBook::NotifyAddAttachMesh_Implementation()
{

}

void AAnimBook::NotifyPageTurnPlayTimeLine_Implementation(bool pageTurnBackwards)
{

}

