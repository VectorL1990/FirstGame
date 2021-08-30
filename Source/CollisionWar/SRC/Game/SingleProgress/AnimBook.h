// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetComponent.h"
#include "../../Base/Widget/TPage.h"
#include "../../Base/Widget/TemplateRuneElement.h"
#include "EventCard.h"
#include "AnimBook.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FPageInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString cardName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString bodyStr;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> SANames;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> optionStrs;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> choices;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBookMaterialSerial
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 pageTextureMapNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 pageNormalMapNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 dirtMapTextureNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 dirtMapMaskNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 paperPageRoughnessNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 coverMaterialNb = 0;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 coverDirtTextNb = 0;
};




UCLASS()
class COLLISIONWAR_API AAnimBook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimBook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
		void BookConstruction(UMaterialInstance* pPageMaskMI, UMaterialInstance* pPageEdgeMI, UMaterialInstance* pPageMI, UMaterialInstance* pPaperEndSheet);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void InitialBook();

	void SetBlockAngle(float bookOpenAmount, bool pageOrBlock);

	void UpdateSceneCoords(float bookOpenAmount, USceneComponent* pPageScene, bool backOrFront);

	void GetBlockEdgeLocation(USceneComponent* pTrackingPoint, float openAmount, float spineBreak);

	void SetEdgeTextureOffset(float pageCurrentlyOpenBack, float pageCurrentlyOpenFront);

	void UpdateMorphTargets(float bookOpenAmount, float pageOpenAmount, bool pageOrBlock, bool updateInvisiblePage);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void UpdateTurnThePage(float pageTurn, float noDamping, float progress);

	void OrientToGround();

	void UpdatePageWidget(UTPage* pWidget, int32 pagetoOpento, bool isCover);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void TurnThePage(bool backwards, float howQuickly);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void TurnDelayAction();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPageTurnPlayTimeLine(bool pageTurnBackwards);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyOpentoPagePlayTimeLine();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void TurnPageFinish();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void Turn1_9Damped();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void TurnHalfMark();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void OpenToPage(float openHowWide, float openHowQuickly, int32 pageToOpen);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void UpdateOpenToPage(float p1, float p2, float p3, float cover, float coverReverse);

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void OpenToPageFinish();

	void ApplyTypographySettings();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void WaitToDrawBlockRT();

	UFUNCTION(BlueprintCallable, Category = "ColllisionWar")
	void WaitToDrawCoverRT();

	void TallyPages(bool isBookConstruction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyAddAttachMesh();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDelay(float delayTime, uint8 functionID);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyReadAllTexture();

	void RefreshPages(int32 targetPage);

	void ResetBook();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pGround;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pDirectionReference;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pIKSpineCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pGroundOffset;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USkeletalMeshComponent* m_pBlockFront;	
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USceneComponent* m_pBlockFrontCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UStaticMeshComponent* m_pPreviewLayoutFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USceneComponent* m_pSpineAttachPointFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USkeletalMeshComponent* m_pBlockBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pBlockBackCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pPreviewLayoutBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pSpineAttachPointBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USkeletalMeshComponent* m_pPageFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pPageFrontCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pPageFrontRevCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USkeletalMeshComponent* m_pPageBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pPageBackCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		USceneComponent* m_pPageBackRevCenter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pSpineBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pBookCoverBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetComponent* m_pWidget_CoverFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetComponent* m_pWidget_BlockBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetComponent* m_pWidget_PageFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetComponent* m_pWidget_PageBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetComponent* m_pWidget_BlockFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UWidgetComponent* m_pWidget_CoverBack;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UStaticMeshComponent* m_pBookCoverFront;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTimelineComponent* m_pPageTurn;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTimelineComponent* m_pOpenTheBook;
	/************************************************************************/
	/* Book Construction
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_bookThickness = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_coverThickness = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_dampedPageTurns = true;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_totalPages = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_allowPageTurnsMidTurn = true;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_coversOpenAheadOfPagesSlightly = true;

	float m_bookOpenTargetAmount = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_bookProportions = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_pageResolution = 1024;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_coverResolutionMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_bookBreakClampMin = 0.1;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_bookBreakClampMax = 0.8;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_pageToOpenTo = 4;

	FString m_language;
	/************************************************************************/
	/* Book Pages
	/************************************************************************/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FPageInfo> m_individualPages;

	int32 m_nonViewableExtraPagesAtFront=0;

	int32 m_nonViewableExtraPagesAtBack=0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_paperDirtStrength = 1;

	/************************************************************************/
	/* Book Cover
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_coverLetteringGloss = 0.8;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_coverLetteringMetallic = 0.9;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_coverDetailingMetallic = 0.7;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_coverDirtStrength = 1;

	/************************************************************************/
	/* “ª∞„±‰¡ø
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FBookMaterialSerial m_MISerialInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_whereDoesSpineBreak_Scratch = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_whereDoesSpineBreak = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_bookOpenCurrentAmount = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_thinPageOffset = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_thinBoost = 1.25;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_pageOpenAmount = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_spineAngle = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_coverOpenAmount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_pageTurnBackwards = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_currentPage = 2;

	int32 m_curActionPanelShowPage = 0;

	int32 m_numberofViewablePages = 0;

	UPROPERTY()
	UTPage* m_pW_BlockFront;

	UPROPERTY()
	UTPage* m_pW_BlockBack;

	UPROPERTY()
		UTPage* m_pW_PageFront;

	UPROPERTY()
		UTPage* m_pW_PageBack;

	UPROPERTY()
		UTPage* m_pW_CoverFront;

	bool m_pageTurnInProgress = false;

	bool m_pageTurnQueued = false;

	bool m_pageTurnDirectionQueued = false;

	float m_pageTurnSpeedQueued = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_renderDelay = 0.f;

	bool m_halfwayMarkReached = false;

	bool m_bookOpeningInProgress = false;

	float m_bookOpenStart = 0.f;

	float m_multiplier = 0.f;

	int32 m_bookOpeningStyle = 0;

	bool m_jumpingToPage = false;

	float m_queuedBookOpenAmount = 0.f;

	int32 m_queuedPage = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_preview = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_initInProgress = false;

	float m_pageturnThickness = 0;

	FVector2D m_pagePictureDrawSize;

	FVector2D m_coverPictureDrawSize;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FPageInfo m_coverPageInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pPageFront_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pPageBack_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockBackEdge_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockFrontEdge_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockFrontBinding_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockBackBinding_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockBack_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pBlockFront_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pEndpapers_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstanceDynamic* m_pCoverFront_DMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<UMaterialInstance*> m_pCoverMaterials;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstance* m_pCoverMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UMaterialInstance* m_pBackCoverMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<UTexture*> m_pPaperTypeTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<UTexture*> m_pPaperTypeNormals;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<UTexture*> m_pDirtMapTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<UTexture*> m_pDirtMapMask;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<UTexture*> m_pCoverDirtTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<float> m_paperPageRoughness;

	UPROPERTY()
	FTimerHandle m_turnDelayActionTimerHandler;

	UPROPERTY()
	FTimerHandle m_drawBlockRTTimerHandler;

	UPROPERTY()
	FTimerHandle m_drawCoverRTTimerHandler;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTemplateRuneElement> m_pChoiceButtonClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pBookTextureMat;

	UPROPERTY()
	FEventCardInfo m_eventCardInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_pictureSize;

	UPROPERTY()
	FDescriptionTreeNode m_curTreeNode;

	FString m_choiceSelectStr;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, UTexture*> m_pPlayCardTextureMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FChAndEnDescriptionList> m_actionButtonStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FChAndEnDescriptionList> m_actionSupplementStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FChAndEnDescriptionList m_rootNodeBodyStrList;

	bool m_isVirtualNodeState = false;

	bool m_isTurningPage = false;
};
