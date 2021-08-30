// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/BasePhysGeo.h"
#include "../../../Character/BaseCharacter.h"
#include "../PhysPolySonClass/PhysPolygon.h"
#include "../PhysActorSonClass/BasePhysActor.h"
#include "PhysLine.generated.h"


UCLASS()
class COLLISIONWAR_API APhysLine : public ABasePhysGeo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void TickLine();

	void InitialLine(FLogicVec2D fixLoc, ABaseCharacter* pHost,int32 campFlag, FLogicVec2D dir, int32 lineHeight);

	void RefreshLine_Int(FLogicVec2D dir, FLogicVec2D startPt, int32 lineLength);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void UpdateLine_Int();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill = true) override;

	/************************************************************************/
	/* 蓝图生成属性
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int32 m_logicLineLength;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle/Physics")
	USphereComponent* m_pFixComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	bool m_isFixFlag;

	/************************************************************************/
	/* 计算属性
	/************************************************************************/
	UPROPERTY()
	FLogicVec2D m_logicStartPoint;

	UPROPERTY()
	FLogicVec2D m_logicEndPoint;

	UPROPERTY()
	FString m_cutStuffName;

	UPROPERTY()
	int32 m_logicCutLength;

	UPROPERTY()
	FString m_preHitActorName = "NULL";

	UPROPERTY()
	FString m_preHitComponentName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	ABaseCharacter* m_pHitCharacter;

	UPROPERTY()
	int32 m_preHitGeoID = -1;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pOverlapGeos;
	/************************************************************************/
	/* 校正临时属性
	/************************************************************************/
	UPROPERTY()
	int32 m_correctHitCharacterID;

	UPROPERTY()
	TArray<int32> m_correctOverlapGeoIDs;

	UPROPERTY()
	bool m_hasBroadcastDeleteFlag;

	UPROPERTY()
	TArray<int32> m_solidHitEntityIDs;
private:

	void LineTraceHitDetect_Int();

	bool IsLineLineIntercept(const FLogicVec2D& ownStartPoint, const FLogicVec2D& ownEndPoint, const FLogicVec2D& oppStartPoint, const FLogicVec2D& oppEndPoint);
	
	bool CutLine_Int(APhysLine* pLine, ABasePhysGeo* pCutGeo, FLogicVec2D interPt, FLogicVec2D reflectRefractDir2D, UPrimitiveComponent* pHitComponent, FReactionInfo reactionInfo);

	void BlockLine_Int(APhysLine* pLine, ABasePhysGeo* pBlockGeo, FLogicVec2D interPt, UPrimitiveComponent* pHitComponent, FReactionInfo reactionInfo);
	
};
