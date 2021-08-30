// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "RecastDetourObject.h"
#include "Sample_TempObstacles.h"
#include "../../../ThirdParty/Filelist.h"
#include "../../../ThirdParty/SampleInterfaces.h"
#include "../../../ThirdParty/DetourCrowd.h"
#include "../../../ThirdParty/DetourCommon.h"


struct SampleItem
{
	Sample* (*create)();
	const string name;
};
Sample* createTempObstacle() { return new Sample_TempObstacles(); }
static SampleItem g_samples[] =
{
	{ createTempObstacle, "Temp Obstacles" },
};

void URecastDetourObject::InitialBuild(const FString& levelName)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return;

	m_targetPack = NewObject<UVectorPack>();
	m_posPack = NewObject<UVectorPack>();
	m_velPack = NewObject<UVectorPack>();
	m_playerVelPack = NewObject<UVectorPack>();

	//string sampleName = "Choose Sample...";
	vector<string> files;
	FString navMeshDir = FPaths::GameDir() + "Meshes";
	std::string navMeshStdString(TCHAR_TO_UTF8(*navMeshDir));
	const string meshesFolder = navMeshStdString;
	//const string meshesFolder = "D:/UEProject/CollisionWar/Meshes";
	string meshName = "Choose Mesh...";
	InputGeom* geom = 0;
	BuildContext ctx;
	//handle scan mesh and build mesh
	/************************************************************************/
	scanDirectory(meshesFolder, ".obj", files);
	scanDirectoryAppend(meshesFolder, ".gset", files);
	/************************************************************************/


	//handle model build
	/************************************************************************/
	vector<string>::const_iterator fileIter = files.begin();
	vector<string>::const_iterator fileEnd = files.end();
	for (; fileIter != fileEnd; ++fileIter)
	{
		FString fileIterFString = fileIter->c_str();
		int32 dotPos = fileIterFString.Find(".");
		fileIterFString = fileIterFString.Left(dotPos);
		if (fileIterFString == levelName)
		{
			meshName = *fileIter;
			break;
		}
	}
	if (meshName == "Choose Mesh...") return;
	string path = meshesFolder + "/" + meshName;
	geom = new InputGeom;
	if (!geom->load(&ctx, path))
	{
		delete geom;
		geom = 0;
		// Destroy the sample if it already had geometry loaded, as we've just deleted it!
		if (m_pSample.IsValid() && m_pSample->getInputGeom())
		{
			m_pSample.Reset();
			m_pSample = 0;
		}
	}
	/************************************************************************/


	//handle sample build
	/************************************************************************/
	TSharedPtr<Sample> newSample;
	newSample = MakeShareable(new Sample_TempObstacles());
	//if (newSample) sampleName = g_samples[0].name;
	if (newSample.IsValid())
	{
		m_pSample.Reset();
		m_pSample = newSample;
		m_pSample->setContext(&ctx);
		if (geom)
		{
			m_pSample->handleMeshChanged(geom);
		}
	}
	/************************************************************************/


	//build navmesh
	/************************************************************************/
	if (geom && m_pSample.IsValid())
	{
		m_pSample->handleSettings(m_cellSize,m_cellHeight,m_agentHeight,m_agentRadius,m_agentMaxClimb,m_agentMaxSlope,
			m_regionMinSize,m_regionMergeSize,m_edgeMaxLen,m_edgeMaxError,m_vertsPerPoly,m_detailSampleDist,m_detailSampleMaxError,
			m_agentPlacementXCoe,m_agentPlacementYCoe,m_agentPlacementZCoe);
		m_pSample->handleBuild();

	}
	/************************************************************************/
	m_isRunMainTick = true;
}

void URecastDetourObject::SetRunMainTick(bool flag)
{
	m_isRunMainTick = flag;
}

void URecastDetourObject::MainTick(float dT)
{
	/*float t = 0.0f;
	float timeAcc = 0.0f;
	Uint32 prevFrameTime = SDL_GetTicks();*/

	if (m_isRunMainTick)
	{
		FetchAllAgentsMoveTarget();
		FetchAllAgentsNewPos();
		FetchAllPlayerAgentsNewVel();
		m_pSample->handleUpdate(dT);
		CollectAllAgentsNewVel();
		//handle Event
		/************************************************************************/

		/************************************************************************/
		/*Uint32 time = SDL_GetTicks();
		float dt = (time - prevFrameTime) / 1000.0f;
		prevFrameTime = time;
		t += dt;*/

		//update sample simulation, deal handleupdating
		/************************************************************************/
		/*const float SIM_RATE = 20;
		const float DELTA_TIME = 1.0f / SIM_RATE;
		timeAcc = rcClamp(timeAcc + dt, -1.0f, 1.0f);
		int simIter = 0;
		while (timeAcc > DELTA_TIME)
		{
			timeAcc -= DELTA_TIME;
			if (simIter < 5 && m_pSample)
			{
				ConvertUEPosToRCDPos();
				m_pSample->handleUpdate(DELTA_TIME);
			}
			simIter++;
		}

		// Clamp the framerate so that we do not hog all the CPU.
		const float MIN_FRAME_TIME = 1.0f / 40.0f;
		if (dt < MIN_FRAME_TIME)
		{
			int ms = (int)((MIN_FRAME_TIME - dt) * 1000.0f);
			if (ms > 10) ms = 10;
			if (ms >= 0) SDL_Delay(ms);
		}*/
		
		/************************************************************************/

	}
}

void URecastDetourObject::CollectAllAgentsNewVel()
{
	dtCrowdTP* pCrowd = 0;
	if (m_pSample.IsValid()) pCrowd = m_pSample->getCrowd();
	if (!m_pSample.IsValid() || !pCrowd || !m_pSample->m_pCrowdTool) return;
	dtCrowdAgent** agents = pCrowd->m_activeAgents;
	int nagents = pCrowd->getActiveAgents(agents, pCrowd->getAgentCount());
	for (int i = 0; i < nagents; i++)
	{
		dtCrowdAgent* ag = agents[i];
		if (!ag) continue;
		float rcdVel[3];
		dtVset(rcdVel, ag->vel[0], ag->vel[1], ag->vel[2]);
		int mark = ag->m_agentMark;
		for (int j=0; j<m_velPack->m_vec.Num(); j++)
		{
			if (m_velPack->m_vec[j]->agentMark == mark)
			{
				if (!ag->m_isPlayerAgent &&
					(rcdVel[0] == m_velPack->m_vec[j]->x && rcdVel[1] == m_velPack->m_vec[j]->y && rcdVel[2] == m_velPack->m_vec[j]->z))
					break;
				m_velPack->m_vec[j]->x = rcdVel[0];
				m_velPack->m_vec[j]->y = rcdVel[1];
				m_velPack->m_vec[j]->z = rcdVel[2];
				m_velPack->m_vec[j]->state = ag->state;
				m_velPack->m_vec[j]->targetState = ag->targetState;
				break;
			}
		}
	}
}

void URecastDetourObject::FetchAllAgentsNewPos()
{
	dtCrowdTP* pCrowd = m_pSample->getCrowd();
	if (!pCrowd) return;
	for (int i=0; i<m_posPack->m_vec.Num(); i++)
	{
		dtCrowdAgent** agents = pCrowd->m_activeAgents;
		int nagents = pCrowd->getActiveAgents(agents, pCrowd->getAgentCount());
		int mark = m_posPack->m_vec[i]->agentMark;
		for (int j = 0; j < nagents; j++)
		{
			dtCrowdAgent* ag = agents[j];
			if (!ag) break;
			if (mark == ag->m_agentMark)
			{
				dtVset(ag->npos, m_posPack->m_vec[i]->x, m_posPack->m_vec[i]->y, m_posPack->m_vec[i]->z);
				break;
			}
		}
	}
}

void URecastDetourObject::FetchAllPlayerAgentsNewVel()
{
	dtCrowdTP* pCrowd = m_pSample->getCrowd();
	if (!pCrowd) return;
	for (int i = 0; i < m_playerVelPack->m_vec.Num(); i++)
	{
		dtCrowdAgent** agents = pCrowd->m_activeAgents;
		int nagents = pCrowd->getActiveAgents(agents, pCrowd->getAgentCount());
		int mark = m_playerVelPack->m_vec[i]->agentMark;
		for (int j = 0; j < nagents; j++)
		{
			dtCrowdAgent* ag = agents[j];
			if (!ag) break;
			if (mark == ag->m_agentMark)
			{
				dtVset(ag->vel, m_playerVelPack->m_vec[i]->x, m_playerVelPack->m_vec[i]->y, m_playerVelPack->m_vec[i]->z);
				break;
			}
		}
	}
}

void URecastDetourObject::HandleAddAgent(const float* p, int agentMark, bool isPlayerAgent, float radius, float height, float maxV, float maxAcc)
{
	m_pSample->m_pCrowdTool->HandleAddAgent(p, agentMark,isPlayerAgent, radius, height, maxV, maxAcc);
}

void URecastDetourObject::HandleAddAgent_Int(const FVector& p, int32 agentMark, uint8 characterType, int32 radius, int32 height, int32 maxV, int32 maxAcc)
{
	float pos[3];
	pos[0] = (float)p.Y / 100.f;
	//pos[1] = (float)m_defaultArenaHeight / 100.f;
	pos[1] = 150.f / 100.f;
	pos[2] = (float)p.X / 100.f;
	bool foundCharacter = false;
	for (int32 i = 0; i < m_posPack->m_vec.Num(); i++)
	{
		if (m_posPack->m_vec[i]->agentMark == agentMark)
		{
			foundCharacter = true;
			break;
		}
	}
	if (!foundCharacter)
	{
		if (characterType == 0 || characterType == 2)
		{
			UVectorAndMarkAndUpdate* pNewTargetVec = NewObject<UVectorAndMarkAndUpdate>();
			pNewTargetVec->agentMark = agentMark;
			m_targetPack->m_vec.Add(pNewTargetVec);
		}
		else
		{
			UVectorAndMarkAndUpdate* pNewPlayerVelVec = NewObject<UVectorAndMarkAndUpdate>();
			pNewPlayerVelVec->agentMark = agentMark;
			m_playerVelPack->m_vec.Add(pNewPlayerVelVec);
		}
		UVectorAndMarkAndUpdate* pNewPosVec = NewObject<UVectorAndMarkAndUpdate>();
		pNewPosVec->agentMark = agentMark;
		pNewPosVec->x = (float)p.Y / 100.f;
		pNewPosVec->y = (float)m_defaultArenaHeight / 100.f;
		pNewPosVec->z = (float)p.X / 100.f;
		m_posPack->m_vec.Add(pNewPosVec);

		UVectorAndMarkAndUpdate* pNewVelVec = NewObject<UVectorAndMarkAndUpdate>();
		pNewVelVec->agentMark = agentMark;
		m_velPack->m_vec.Add(pNewVelVec);
	}
	
	if (!m_pSample.IsValid()) return;
	if (characterType == 0 || characterType == 2)
		m_pSample->m_pCrowdTool->HandleAddAgent(pos, agentMark, false, (float)radius / 100.f, (float)height / 100.f, (float)maxV/100.f, (float)maxAcc / 10.f);
	else
		m_pSample->m_pCrowdTool->HandleAddAgent(pos, agentMark, true, (float)radius / 100.f, (float)height / 100.f, (float)maxV / 100.f, (float)maxAcc / 10.f);
}

void URecastDetourObject::HandleDeleteAgent(int32 agentMark, uint8 characterType)
{
	for (int32 i = 0; i < m_posPack->m_vec.Num(); i++)
	{
		if (m_posPack->m_vec[i]->agentMark == agentMark)
		{
			UVectorAndMarkAndUpdate* pPos = m_posPack->m_vec[i];
			m_posPack->m_vec.RemoveAt(i);
			pPos->ConditionalBeginDestroy();
			break;
		}
	}
	for (int32 i = 0; i < m_velPack->m_vec.Num(); i++)
	{
		if (m_velPack->m_vec[i]->agentMark == agentMark)
		{
			UVectorAndMarkAndUpdate* pVel = m_velPack->m_vec[i];
			m_velPack->m_vec.RemoveAt(i);
			pVel->ConditionalBeginDestroy();
			break;
		}
	}
	if (characterType == 0 || characterType == 2)
	{
		for (int32 i = 0; i < m_targetPack->m_vec.Num(); i++)
		{
			if (m_targetPack->m_vec[i]->agentMark == agentMark)
			{
				UVectorAndMarkAndUpdate* pTarget = m_targetPack->m_vec[i];
				m_targetPack->m_vec.RemoveAt(i);
				pTarget->ConditionalBeginDestroy();
				break;
			}
		}
	}
	else
	{
		for (int32 i = 0; i < m_playerVelPack->m_vec.Num(); i++)
		{
			if (m_playerVelPack->m_vec[i]->agentMark == agentMark)
			{
				UVectorAndMarkAndUpdate* pVel = m_playerVelPack->m_vec[i];
				m_playerVelPack->m_vec.RemoveAt(i);
				pVel->ConditionalBeginDestroy();
				break;
			}
		}
	}
	m_pSample->m_pCrowdTool->HandleDeleteAgent(agentMark);
}

void URecastDetourObject::HandleAddTempObstacle(const float* p, float radius, float height)
{
	m_pSample->HandleAddTempObstacle(p, radius, height);
}

void URecastDetourObject::HandleAddTempBoxObstacle(const float* bmin, const float* bmax, float height)
{
	m_pSample->HandleAddTempBoxObstacle(bmin, bmax, height);
}

void URecastDetourObject::HandleRemoveTempObstacle(const float* p)
{
	m_pSample->HandleRemoveTempObstacle(p);
}

void URecastDetourObject::HandleRemoveAgent(int i)
{
	m_pSample->m_pCrowdTool->HandleRemoveAgent(i);
}


void URecastDetourObject::FetchAllAgentsMoveTarget()
{
	dtCrowdTP* pCrowd = 0;
	if (m_pSample.IsValid()) pCrowd = m_pSample->getCrowd();
	if (!m_pSample.IsValid() || !pCrowd || !m_pSample->m_pCrowdTool) return;
	for (int i=0; i<m_targetPack->m_vec.Num(); i++)
	{
		int mark = m_targetPack->m_vec[i]->agentMark;
		float des[3];
		des[0] = m_targetPack->m_vec[i]->x;
		des[1] = m_targetPack->m_vec[i]->y;
		des[2] = m_targetPack->m_vec[i]->z;
		m_pSample->m_pCrowdTool->HandleSetAgentMoveTarget(mark, des);
	}
}

/*
void URecastDetourObject::DrawDebug()
{
	if (!m_pSample) return;
	//const dtNavMesh& navMesh = *(m_pSample->m_navMesh);
	int32 maxTileNb = (*m_pSample->m_navMesh).getMaxTiles();
	float maxX = 0;
	float minX = 0;
	float maxY = 0;
	float minY = 0;
	for (int i = 0; i < maxTileNb; ++i)
	{
		const dtMeshTile* tile = (*m_pSample->m_navMesh).getTile(i);
		if (!tile->header) continue;
		for (int j = 0; j < tile->header->polyCount; ++j)
		{
			const dtPoly* p = &tile->polys[j];
			if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION)	// Skip off-mesh links.
				continue;

			const dtPolyDetail* pd = &tile->detailMeshes[j];

			for (int k = 0; k < pd->triCount; ++k)
			{
				const unsigned char* t = &tile->detailTris[(pd->triBase + k) * 4];
				if (t[0] >= p->vertCount || t[1] >= p->vertCount || t[2] >= p->vertCount) return;
				float* ptRaw1 = &tile->verts[p->verts[t[0]] * 3];
				float* ptRaw2 = &tile->verts[p->verts[t[1]] * 3];
				float* ptRaw3 = &tile->verts[p->verts[t[2]] * 3];
				FVector pt1(ptRaw1[0]*100, ptRaw1[2] * 100, ptRaw1[1] + m_relativeDebugLineHeight + 150);
				FVector pt2(ptRaw2[0] * 100, ptRaw2[2] * 100, ptRaw2[1] + m_relativeDebugLineHeight + 150);
				FVector pt3(ptRaw3[0] * 100, ptRaw3[2] * 100, ptRaw3[1] + m_relativeDebugLineHeight + 150);
				FString pt1Str = FString::SanitizeFloat(pt1.X) + "," + FString::SanitizeFloat(pt1.Y) + "," + FString::SanitizeFloat(pt1.Z);
				FString pt2Str = FString::SanitizeFloat(pt2.X) + "," + FString::SanitizeFloat(pt2.Y) + "," + FString::SanitizeFloat(pt2.Z);
				FString pt3Str = FString::SanitizeFloat(pt3.X) + "," + FString::SanitizeFloat(pt3.Y) + "," + FString::SanitizeFloat(pt3.Z);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt1Str);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt2Str);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt3Str);
				DrawDebugLine(GetWorld(), pt1, pt2, FColor::Cyan, false, m_relativeDebugLineTime, 0, 10);
				DrawDebugLine(GetWorld(), pt2, pt3, FColor::Cyan, false, m_relativeDebugLineTime, 0, 10);
				DrawDebugLine(GetWorld(), pt3, pt1, FColor::Cyan, false, m_relativeDebugLineTime, 0, 10);
				DrawDebugPoint(GetWorld(), pt1, 5, FColor::Cyan, false, 5, 0);
				DrawDebugPoint(GetWorld(), pt2, 5, FColor::Cyan, false, 5, 0);
				DrawDebugPoint(GetWorld(), pt3, 5, FColor::Cyan, false, 5, 0);
				if (pt1.X >= maxX) maxX = pt1.X;
				if (pt1.X <= minX) minX = pt1.X;
				if (pt1.Y >= maxY) maxY = pt1.Y;
				if (pt1.Y <= minY) minY = pt1.Y;

				if (pt2.X >= maxX) maxX = pt2.X;
				if (pt2.X <= minX) minX = pt2.X;
				if (pt2.Y >= maxY) maxY = pt2.Y;
				if (pt2.Y <= minY) minY = pt2.Y;

				if (pt3.X >= maxX) maxX = pt3.X;
				if (pt3.X <= minX) minX = pt3.X;
				if (pt3.Y >= maxY) maxY = pt3.Y;
				if (pt3.Y <= minY) minY = pt3.Y;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(minX));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(maxX));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(minY));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(maxY));
}
*/
