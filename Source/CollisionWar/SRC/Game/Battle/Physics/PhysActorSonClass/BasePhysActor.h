// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/Battle/Physics/BasePhysGeo.h"
#include "../../../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../../Character/BaseCharacter.h"
#include "../../Attachment/CharacterEquipInfo.h"
#include "WidgetComponent.h"
#include "BasePhysActor.generated.h"



UCLASS()
class COLLISIONWAR_API ABasePhysActor : public ABasePhysGeo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePhysActor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill = false) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetParticleComponent(UParticleSystemComponent* pParticleComponent);

	UFUNCTION()
	void InitialPhysActor(int32 campFlag, ABaseCharacter* pCharacter, int32 defaultHeight);

	UFUNCTION()
	void DeleteTempObstacleFromRecastNav();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void OnBaseComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void OnBaseComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent);

	virtual void DecreaseLifeTime(float dT);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetWidgetComponent(UWidgetComponent* pWidget);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void PopPhysActorWidget();

	void HidePhysActorWidget();

	/************************************************************************/
	/* 蓝图生成属性
	/************************************************************************/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle/Physics")
	USphereComponent* m_pFixComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	bool m_isBoundaryActor = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle/Physics")
	int32 m_actorRadius;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	bool m_isCollectable;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	int32 m_buildTime = 1;

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TSubclassOf<class AActor> m_producePhysActorClass;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FSkillIndependentFXInfo m_buildParticleInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FSkillIndependentFXInfo m_buildFinishParticleInfo;

	UParticleSystemComponent* m_pBuildParticleSystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetComponent* m_pWidget;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystemComponent* m_pParticleComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FString m_description;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FString m_chDescription;
	/************************************************************************/
	/* 计算属性
	/************************************************************************/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	int32 m_physActorLifeTime;

	UPROPERTY()
	int32 m_curLogicLifeTime;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pPreOverlapGeos;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pOverlapGeos;

	bool m_isBuilding = false;

	int32 m_curBuildingTick = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_produceCardName;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_possibleOutputCardList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_stockNb = 1;
	/************************************************************************/
	/* 校正临时属性
	/************************************************************************/
	UPROPERTY()
	TArray<int32> m_correctOverlapCharacterIDs;

	UPROPERTY()
	TArray<int32> m_correctPreOverlapCharacterIDs;

	UPROPERTY()
	TArray<int32> m_correctOverlapGeoIDs;

	UPROPERTY()
	TArray<int32> m_correctPreOverlapGeoIDs;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
