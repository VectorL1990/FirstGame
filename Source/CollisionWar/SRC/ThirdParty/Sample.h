//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef RECASTSAMPLE_H
#define RECASTSAMPLE_H

#include "Recast.h"
#include "DetourTileCache.h"
#include "SampleInterfaces.h"


/// Tool types.
enum SampleToolType
{
	TOOL_NONE = 0,
	TOOL_TILE_EDIT,
	TOOL_TILE_HIGHLIGHT,
	TOOL_TEMP_OBSTACLE,
	TOOL_NAVMESH_TESTER,
	TOOL_NAVMESH_PRUNE,
	TOOL_OFFMESH_CONNECTION,
	TOOL_CONVEX_VOLUME,
	TOOL_CROWD,
	MAX_TOOLS
};

/// These are just sample areas to use consistent values across the samples.
/// The use should specify these base on his needs.
enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK		= 0x01,		// Ability to walk (ground, grass, road)
	SAMPLE_POLYFLAGS_SWIM		= 0x02,		// Ability to swim (water).
	SAMPLE_POLYFLAGS_DOOR		= 0x04,		// Ability to move through doors.
	SAMPLE_POLYFLAGS_JUMP		= 0x08,		// Ability to jump.
	SAMPLE_POLYFLAGS_DISABLED	= 0x10,		// Disabled polygon
	SAMPLE_POLYFLAGS_ALL		= 0xffff	// All abilities.
};

enum SamplePartitionType
{
	SAMPLE_PARTITION_WATERSHED,
	SAMPLE_PARTITION_MONOTONE,
	SAMPLE_PARTITION_LAYERS,
};

struct SampleTool
{
	virtual ~SampleTool() {}
	virtual int type() = 0;
	virtual void init(class Sample* sample, float agentPlacementXCoe, float agentPlacementYCoe, float agentPlacementZCoe) = 0;
	virtual void reset() = 0;
	virtual void handleMenu() = 0;
	virtual void handleClick(const float* s, const float* p, bool shift) = 0;
	virtual void handleRender() = 0;
	virtual void handleRenderOverlay(double* proj, double* model, int* view) = 0;
	virtual void handleToggle() = 0;
	virtual void handleStep() = 0;
	virtual void handleUpdate(const float dt) = 0;
	virtual void HandleAddAgent(const float* p,int agentMark, bool isPlayerAgent, float radius, float height, float maxV, float maxAcc) {};
	virtual void HandleDeleteAgent(int agentMark) {};
	virtual void HandleRemoveAgent(int i) {};
	virtual void HandleSetAgentMoveTarget(int mark, const float* des) {};
};

struct SampleToolState {
	virtual ~SampleToolState() {}
	virtual void init(class Sample* sample, float agentPlacementXCoe, float agentPlacementYCoe, float agentPlacementZCoe) = 0;
	virtual void reset() = 0;
	virtual void handleRender() = 0;
	virtual void handleRenderOverlay(double* proj, double* model, int* view) = 0;
	virtual void handleUpdate(const float dt) = 0;
};

class COLLISIONWAR_API Sample
{
public:
	class InputGeom* m_geom;
	class dtNavMeshTP* m_navMesh;
	class dtNavMeshQueryTP* m_navQuery;
	class dtCrowdTP* m_crowd;

	float m_cellSize;
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;
	int m_partitionType;

	bool m_filterLowHangingObstacles;
	bool m_filterLedgeSpans;
	bool m_filterWalkableLowHeightSpans;
	
	SampleToolState* m_toolStates[MAX_TOOLS];
	BuildContext* m_ctx;
	
	dtNavMeshTP* loadAll(const char* path);
	void saveAll(const char* path, const dtNavMeshTP* mesh);

public:
	SampleTool * m_pCrowdTool;
	SampleTool* m_pTempObstacleTool;
	float m_agentPlacementXCoe = 2.0f;
	float m_agentPlacementYCoe = 100.0f;
	float m_agentPlacementZCoe = 2.0f;

	Sample();
	virtual ~Sample();
	
	void setTool(SampleTool* CrowdTool, SampleTool* ObstacleTool);
	SampleToolState* getToolState(int type) { return m_toolStates[type]; }
	void setToolState(int type, SampleToolState* s) { m_toolStates[type] = s; }
	void setContext(BuildContext* ctx) { m_ctx = ctx; }

	virtual void handleSettings(float cellSize,float cellHeight, float agentHeight, float agentRadius, float agentMaxClimb,
		float agentMaxSlope, float regionMinSize, float regionMergetSize, float edgeMaxLen, float edgetMaxError,
		float vertsPerPoly, float detailSampleDist, float detailSampleMaxError, float agentPlacementXCoe,
		float agentPlacementYCoe, float agentPlacementZCoe);
	virtual void handleTools();
	virtual void handleDebugMode();
	virtual void handleMeshChanged(class InputGeom* geom);
	virtual bool handleBuild();
	virtual void handleUpdate(const float dt);
	virtual void HandleAddTempObstacle(const float* p, float radius, float height) {};
	virtual void HandleAddTempBoxObstacle(const float* bmin, const float* bmax, float height) {};
	virtual void HandleRemoveTempObstacle(const float* p) {};
	virtual void collectSettings(struct BuildSettings& settings);

	virtual class InputGeom* getInputGeom() { return m_geom; }
	virtual class dtNavMeshTP* getNavMesh() { return m_navMesh; }
	virtual class dtNavMeshQueryTP* getNavMeshQuery() { return m_navQuery; }
	virtual class dtCrowdTP* getCrowd() { return m_crowd; }
	virtual float getAgentRadius() { return m_agentRadius; }
	virtual float getAgentHeight() { return m_agentHeight; }
	virtual float getAgentClimb() { return m_agentMaxClimb; }

	void updateToolStates(const float dt);
	void initToolStates(Sample* sample);
	void resetToolStates();

	void resetCommonSettings();
	void handleCommonSettings(float cellSize, float cellHeight, float agentHeight, float agentRadius, float agentMaxClimb,
		float agentMaxSlope, float regionMinSize, float regionMergetSize, float edgeMaxLen, float edgetMaxError,
		float vertsPerPoly, float detailSampleDist, float detailSampleMaxError, float agentPlacementXCoe,
		float agentPlacementYCoe, float agentPlacementZCoe);
private:
	// Explicitly disabled copy constructor and copy assignment operator.
	Sample(const Sample&);
	Sample& operator=(const Sample&);
};


#endif // RECASTSAMPLE_H
