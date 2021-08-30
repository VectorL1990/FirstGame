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
#pragma once

#ifndef RECASTSAMPLETEMPOBSTACLE_H
#define RECASTSAMPLETEMPOBSTACLE_H

#include "../../../ThirdParty/Sample.h"
#include "../../../ThirdParty/DetourNavMesh.h"
#include "../../../ThirdParty/Recast.h"
#include "../../../ThirdParty/ChunkyTriMesh.h"


class COLLISIONWAR_API Sample_TempObstacles : public Sample
{
protected:
	bool m_keepInterResults;

	struct LinearAllocator* m_talloc;
	struct FastLZCompressor* m_tcomp;
	struct MeshProcess* m_tmproc;

	class dtTileCacheTP* m_tileCache;
	
	float m_cacheBuildTimeMs;
	int m_cacheCompressedSize;
	int m_cacheRawSize;
	int m_cacheLayerCount;
	int m_cacheBuildMemUsage;
	
	enum DrawMode
	{
		DRAWMODE_NAVMESH,
		DRAWMODE_NAVMESH_TRANS,
		DRAWMODE_NAVMESH_BVTREE,
		DRAWMODE_NAVMESH_NODES,
		DRAWMODE_NAVMESH_PORTALS,
		DRAWMODE_NAVMESH_INVIS,
		DRAWMODE_MESH,
		DRAWMODE_CACHE_BOUNDS,
		MAX_DRAWMODE
	};
	
	DrawMode m_drawMode;
	
	int m_maxTiles;
	int m_maxPolysPerTile;
	float m_tileSize;
	
public:
	Sample_TempObstacles();
	virtual ~Sample_TempObstacles();
	
	virtual void handleSettings(float cellSize, float cellHeight, float agentHeight, float agentRadius, float agentMaxClimb,
		float agentMaxSlope, float regionMinSize, float regionMergetSize, float edgeMaxLen, float edgetMaxError,
		float vertsPerPoly, float detailSampleDist, float detailSampleMaxError, float agentPlacementXCoe,
		float agentPlacementYCoe, float agentPlacementZCoe);
	virtual void handleTools();
	virtual void handleMeshChanged(class InputGeom* geom);
	virtual bool handleBuild();
	virtual void handleUpdate(const float dt);
	virtual void HandleAddTempObstacle(const float* p, float radius, float height) override;
	virtual void HandleAddTempBoxObstacle(const float* bmin, const float* bmax, float height) override;
	virtual void HandleRemoveTempObstacle(const float* p) override;

	void getTilePos(const float* pos, int& tx, int& ty);

	void addTempObstacle(const float* pos, float radius, float height);
	void addBoxObstacle(const float* bmin, const float* bmax);
	void removeTempObstacle(const float* sq);
	void clearAllTempObstacles();

	void saveAll(const char* path);
	void loadAll(const char* path);

private:
	// Explicitly disabled copy constructor and copy assignment operator.
	Sample_TempObstacles(const Sample_TempObstacles&);
	Sample_TempObstacles& operator=(const Sample_TempObstacles&);

	int rasterizeTileLayers(const int tx, const int ty, const rcConfig& cfg, struct TileCacheData* tiles, const int maxTiles);
};


class COLLISIONWAR_API TempObstacleCreateTool : public SampleTool
{
	Sample_TempObstacles* m_sample;

public:

	TempObstacleCreateTool() : m_sample(0)
	{
	}

	virtual ~TempObstacleCreateTool()
	{
	}

	virtual int type() { return TOOL_TEMP_OBSTACLE; }

	virtual void init(Sample* sample, float agentPlacementXCoe, float agentPlacementYCoe, float agentPlacementZCoe)
	{
		m_sample = (Sample_TempObstacles*)sample;
	}

	virtual void reset() {}

	virtual void handleMenu() {};

	virtual void handleClick(const float* s, const float* p, bool shift)
	{
		if (m_sample)
		{
			if (shift)
				m_sample->removeTempObstacle(p);
			else
				m_sample->addTempObstacle(p,1.0f, 2.0f);
		}
	}

	virtual void handleToggle() {}
	virtual void handleStep() {}
	virtual void handleUpdate(const float /*dt*/) {}
	virtual void handleRender() {}
	virtual void handleRenderOverlay(double* /*proj*/, double* /*model*/, int* /*view*/) { }
};

#endif // RECASTSAMPLETEMPOBSTACLE_H
