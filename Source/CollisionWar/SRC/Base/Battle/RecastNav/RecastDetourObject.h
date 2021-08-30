// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../../ThirdParty/Recast.h"
#include "InputGeom.h"
#include "../../../ThirdParty/SDL/include/SDL.h"
#include "../../../ThirdParty/Sample.h"
#include "../../../ThirdParty/DetourNavMesh.h"
#include "../../../ThirdParty/DetourCrowd.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "VectorPack.h"
#include <string>
#include "RecastDetourObject.generated.h"

using namespace std;
/**
 * 
 */

UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API URecastDetourObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "RecastDetour")
	bool m_isRunMainTick = false;

	UPROPERTY()
	UVectorPack* m_velPack;

	UPROPERTY()
	UVectorPack* m_playerVelPack;

	UPROPERTY()
	UVectorPack* m_posPack;

	UPROPERTY()
	UVectorPack* m_targetPack;

	TSharedPtr<Sample> m_pSample = 0;

	float m_defaultArenaHeight = 190.f;

	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_cellSize = 0.3;//imguiSlider("Cell Size", &m_cellSize, 0.1f, 1.0f, 0.01f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_cellHeight = 0.2;//("Cell Height", &m_cellHeight, 0.1f, 1.0f, 0.01f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentHeight = 2.0f;// imguiSlider("Height", &m_agentHeight, 0.1f, 5.0f, 0.1f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentRadius = 0.5f;// imguiSlider("Radius", &m_agentRadius, 0.0f, 5.0f, 0.1f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentMaxClimb = 0.9f;// imguiSlider("Max Climb", &m_agentMaxClimb, 0.1f, 5.0f, 0.1f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentMaxSlope = 45.0f;// imguiSlider("Max Slope", &m_agentMaxSlope, 0.0f, 90.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_regionMinSize = 8.0f;// imguiSlider("Min Region Size", &m_regionMinSize, 0.0f, 150.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_regionMergeSize = 20.0f;// imguiSlider("Merged Region Size", &m_regionMergeSize, 0.0f, 150.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_edgeMaxLen = 12.0f;// imguiSlider("Max Edge Length", &m_edgeMaxLen, 0.0f, 50.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_edgeMaxError = 1.3f;// imguiSlider("Max Edge Error", &m_edgeMaxError, 0.1f, 3.0f, 0.1f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_vertsPerPoly = 6.0f;// imguiSlider("Verts Per Poly", &m_vertsPerPoly, 3.0f, 12.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_detailSampleDist = 6.0f;// imguiSlider("Sample Distance", &m_detailSampleDist, 0.0f, 16.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_detailSampleMaxError = 1.0f;// imguiSlider("Max Sample Error", &m_detailSampleMaxError, 0.0f, 16.0f, 1.0f);
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentPlacementXCoe = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentPlacementYCoe = 100.0f;
	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	float m_agentPlacementZCoe = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "RecastNav")
	FString m_defaultRoguelikeMapName = "RogueLikeMap";

	void InitialBuild(const FString& levelName);

	UFUNCTION(BlueprintCallable, Category = "RecastDetour")
	void SetRunMainTick(bool flag);

	UFUNCTION(BlueprintCallable, Category = "RecastDetour")
	void MainTick(float dT);

	void CollectAllAgentsNewVel();

	void FetchAllAgentsNewPos();

	void FetchAllPlayerAgentsNewVel();
	
	void HandleAddAgent(const float* p, int agentMark, bool isPlayerAgent, float radius, float height, float maxV, float maxAcc);

	void HandleAddAgent_Int(const FVector& p, int32 agentMark, uint8 characterType, int32 radius, int32 height, int32 maxV, int32 maxAcc);

	void HandleDeleteAgent(int32 agentMark, uint8 characterType);

	void HandleAddTempObstacle(const float* p, float radius, float height);

	void HandleAddTempBoxObstacle(const float* bmin, const float* bmax, float height);

	void HandleRemoveTempObstacle(const float* p);

	void HandleRemoveAgent(int i);

	void FetchAllAgentsMoveTarget();

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_relativeDebugLineHeight = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_relativeDebugLineTime = 5;

	//void DrawDebug();
};
