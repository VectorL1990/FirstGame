// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "MapGenerator.h"




void UMapGenerator::InitialMapGeneratorFromBlueprint_Implementation(uint8 curProgress)
{

}

bool UMapGenerator::GenerateRandomMap(const TArray<FString>& specifiedLandBlockList)
{
	if (m_specifiedLandBlockNameList.Num() > m_bigTileHeightNb * m_bigTileWidthNb) return false;
	int32 totalTileNb = m_bigTileWidthNb * m_bigTileHeightNb*m_bigTileWidth*m_bigTileHeight;
	int32 specialLandBlockAmount = (int32)(totalTileNb*m_specialLandBlockDensity/100);
	int32 totalTileWidth = m_bigTileWidth * m_bigTileWidthNb;
	int32 totalTileHeight = m_bigTileHeight * m_bigTileHeightNb;
	TArray<int32> unOccupyBigTileNbList;
	TArray<ULandBlockTile*> pSpecialTileList;
	TArray<ULandBlockTile*> pJunctionList;
	//生成大方块数组
	for (int32 i=0; i<m_bigTileHeightNb; i++)
	{
		for (int32 j=0; j<m_bigTileWidthNb; j++)
		{
			unOccupyBigTileNbList.Add(i * m_bigTileWidthNb + j);
			FBigLandBlockTile bigTile;
			bigTile.X = j;
			bigTile.Y = i;
			bigTile.isOccupiedBySpecialLandBlock = false;
			m_bigTiles.Add(bigTile);
		}
	}
	//将小方块放到大方块中
	TArray<int32> unOccupyTileNbList;
	for (int32 i = 0; i<totalTileHeight; i++)
	{
		for (int32 j=0; j<totalTileWidth; j++)
		{
			unOccupyTileNbList.Add(i * totalTileWidth + j);
			ULandBlockTile* pNewTile = NewObject<ULandBlockTile>();
			pNewTile->X = j;
			pNewTile->Y = i;
			pNewTile->m_isOccupied = false;
			m_pTiles.Add(pNewTile);
			int32 bigTileXNb = j / m_bigTileWidth;
			int32 bigTileYNb = i / m_bigTileHeight;
			int32 bigTileNb = bigTileXNb + bigTileYNb * m_bigTileWidthNb;
			if (bigTileNb >= m_bigTiles.Num()) continue;
			m_bigTiles[bigTileNb].pSonTiles.Add(pNewTile);
		}
	}
	//将一些指定的模块物体随机放到一个大方块中
	for (int32 i=0; i<specifiedLandBlockList.Num(); i++)
	{
		//UClass* landBlockClass = UCollisionWarBpFunctionLibrary::GetLandBlockBlueprintClassDyanmic(m_specialLandBlockNameList[i]);
		//if (!landBlockClass) continue;
		if (specifiedLandBlockList[i] == "" ||
			!m_allSpecifiedLandBlockNameList.Contains(specifiedLandBlockList[i])) continue;
		int32 randBigTileNb = FMath::RandRange(0, unOccupyBigTileNbList.Num()-1);
		int32 randSonTileNb = (int32)FMath::RandRange(0, m_bigTileWidth*m_bigTileHeight-1);
		m_bigTiles[randBigTileNb].pSonTiles[randSonTileNb]->m_landBlockName = specifiedLandBlockList[i];
		m_bigTiles[randBigTileNb].pSonTiles[randSonTileNb]->m_isOccupied = true;
		pSpecialTileList.Add(m_bigTiles[randBigTileNb].pSonTiles[randSonTileNb]);
		pSpecialTileList.Last()->m_landBlockType = "specified";
		unOccupyBigTileNbList.RemoveAt(randBigTileNb);
		unOccupyTileNbList.RemoveAt(m_bigTiles[randBigTileNb].pSonTiles[randSonTileNb]->X + m_bigTiles[randBigTileNb].pSonTiles[randSonTileNb]->Y*totalTileWidth);
	}
	//根据指定的特殊小方块数量，随机填充到方块中
	int32 leftSpecialLandBlockNb = specialLandBlockAmount - specifiedLandBlockList.Num();
	if (leftSpecialLandBlockNb <= 0) return true;
	for (int32 i=0; i<leftSpecialLandBlockNb; i++)
	{
		int32 randSpecialLandBlockInfoNb = FMath::RandRange(0, m_allSpecialLandBlockNameList.Num()-1);
		int32 randTileNb = FMath::RandRange(0, unOccupyTileNbList.Num()-1);
		m_pTiles[unOccupyTileNbList[randTileNb]]->m_landBlockName = m_allSpecialLandBlockNameList[randSpecialLandBlockInfoNb];
		m_pTiles[unOccupyTileNbList[randTileNb]]->m_isOccupied = true;
		pSpecialTileList.Add(m_pTiles[unOccupyTileNbList[randTileNb]]);
		pSpecialTileList.Last()->m_landBlockType = "special";
		unOccupyTileNbList.RemoveAt(randTileNb);
	}
	//随机生成岔路点
	TArray<FIsometricBlockList> isometricBlockList;
	int32 junctionBlockNb = totalTileNb * m_junctionBlockPercentage / 100;
	for (int32 i=0; i<junctionBlockNb; i++)
	{
		int32 randJunctionLandBlockInfoNb = FMath::RandRange(0, m_allJunctionBlockNameList.Num() - 1);
		int32 randTileNb = FMath::RandRange(0, unOccupyTileNbList.Num() - 1);
		m_pTiles[unOccupyTileNbList[randTileNb]]->m_landBlockName = m_allJunctionBlockNameList[randJunctionLandBlockInfoNb];
		m_pTiles[unOccupyTileNbList[randTileNb]]->m_isOccupied = true;
		m_pTiles[unOccupyTileNbList[randTileNb]]->m_landBlockType = "junction";
		pJunctionList.Add(m_pTiles[unOccupyTileNbList[randTileNb]]);
		FIsometricBlockList newBlock;
		newBlock.pBasicJunctionBlock = m_pTiles[unOccupyTileNbList[randTileNb]];
		isometricBlockList.Add(newBlock);
		unOccupyTileNbList.RemoveAt(randTileNb);
	}
	//遍历所有特殊地块，找到最近的岔路点并用路径地块连接起来
	for (int32 i=0; i<pSpecialTileList.Num(); i++)
	{
		int32 minDis = 0;
		int32 minDisJunctionNb = 0;
		for (int32 j=0; j<isometricBlockList.Num(); j++)
		{
			int32 xDisToJunction = FMath::Abs(isometricBlockList[j].pBasicJunctionBlock->X - pSpecialTileList[i]->X);
			int32 yDisToJunction = FMath::Abs(isometricBlockList[j].pBasicJunctionBlock->Y - pSpecialTileList[i]->Y);
			if (j == 0 || (xDisToJunction + yDisToJunction) <= minDis)
			{
				minDis = xDisToJunction + yDisToJunction;
				minDisJunctionNb = j;
			}
		}
		//连接该特殊地块与岔路地块
		SetTilesToBlockAsConnecting(isometricBlockList[minDisJunctionNb].pBasicJunctionBlock,totalTileWidth,totalTileHeight,
			isometricBlockList[minDisJunctionNb].pElementTiles, pSpecialTileList[i]);
	}
	//先将所有不属于第一个Block的地块全都放在一个数组中
	if (isometricBlockList.Num() == 0) return false;
	TArray<ULandBlockTile*> pIsoTileList;
	for (int32 i=1; i<isometricBlockList.Num(); i++)
	{
		for (int32 j=0; j<isometricBlockList[i].pElementTiles.Num(); j++)
		{
			pIsoTileList.Add(isometricBlockList[i].pElementTiles[j]);
		}
	}

	TArray<ULandBlockTile*> pConnectTiles;
	while (pIsoTileList.Num() > 0)
	{
		//遍历所有iso地块与首个block的地块，找到距离最近的一对地块
		int32 minDis = -1;
		ULandBlockTile* pBaseMinDisTile = NULL;
		ULandBlockTile* pIsoMinDisTile = NULL;
		for (int32 i = 0; i < pIsoTileList.Num(); i++)
		{
			if (isometricBlockList[0].pElementTiles.Num() > 0)
			{
				for (int32 j = 0; j < isometricBlockList[0].pElementTiles.Num(); j++)
				{
					int32 xDis = FMath::Abs(isometricBlockList[0].pElementTiles[j]->X - pIsoTileList[i]->X);
					int32 yDis = FMath::Abs(isometricBlockList[0].pElementTiles[j]->Y - pIsoTileList[i]->Y);
					if (minDis == -1 || minDis >= (xDis + yDis))
					{
						minDis = xDis + yDis;
						pBaseMinDisTile = isometricBlockList[0].pElementTiles[j];
						pIsoMinDisTile = pIsoTileList[i];
					}
				}
			}
			else
			{
				int32 xDis = FMath::Abs(isometricBlockList[0].pBasicJunctionBlock->X - pIsoTileList[i]->X);
				int32 yDis = FMath::Abs(isometricBlockList[0].pBasicJunctionBlock->Y - pIsoTileList[i]->Y);
				if (minDis == -1 || minDis >= (xDis + yDis))
				{
					minDis = xDis + yDis;
					pBaseMinDisTile = isometricBlockList[0].pBasicJunctionBlock;
					pIsoMinDisTile = pIsoTileList[i];
				}
			}
		}
		//找到这个距离最近的iso地块所属block，然后将这个block和首个block归并
		for (int32 i=1; i<isometricBlockList.Num(); i++)
		{
			if (isometricBlockList[i].pElementTiles.Contains(pIsoMinDisTile))
			{
				for (int32 j = 0; j<isometricBlockList[i].pElementTiles.Num(); j++)
				{
					if (!isometricBlockList[0].pElementTiles.Contains(isometricBlockList[i].pElementTiles[j]))
						isometricBlockList[0].pElementTiles.Add(isometricBlockList[i].pElementTiles[j]);
					if (pIsoTileList.Contains(isometricBlockList[i].pElementTiles[j]))
						pIsoTileList.Remove(isometricBlockList[i].pElementTiles[j]);
				}
				if (!isometricBlockList[0].pElementTiles.Contains(isometricBlockList[i].pBasicJunctionBlock))
					isometricBlockList[0].pElementTiles.Add(isometricBlockList[i].pBasicJunctionBlock);
				isometricBlockList.RemoveAt(i);
				break;
			}
		}
		//连接两个分离的block
		SetTilesToBlockAsConnecting(pIsoMinDisTile,totalTileWidth, totalTileHeight, pConnectTiles, pBaseMinDisTile);
	}

	for (int32 i=0; i<m_pTiles.Num(); i++)
	{
		if (m_pTiles[i]->m_landBlockType == "connect")
		{
			int32 randConnectLandBlockInfoNb = FMath::RandRange(0, m_allConnectBlockNameList.Num() - 1);
			m_pTiles[i]->m_landBlockName = m_allConnectBlockNameList[randConnectLandBlockInfoNb];
			m_pTiles[i]->m_isOccupied = true;
			unOccupyTileNbList.Remove(m_pTiles[i]->Y*totalTileWidth + m_pTiles[i]->X);
		}
	}
	
	for (int32 i=0; i<unOccupyTileNbList.Num(); i++)
	{
		int32 randBarrierLandBlockInfoNb = FMath::RandRange(0, m_allBarrierBlockNameList.Num() - 1);
		m_pTiles[unOccupyTileNbList[i]]->m_landBlockName = m_allBarrierBlockNameList[randBarrierLandBlockInfoNb];
		m_pTiles[unOccupyTileNbList[i]]->m_landBlockType = "Barrier";
	}

	SpawnActorsInTiles();
	//在空白方块上放置APlanSpawnPoint
	//设置角色与staticMesh碰撞
	//将有Boundary标签的物体添加tempObstacle到RecastNav中
	return true;
}

void UMapGenerator::ReadRoguelikeSMMap_Implementation()
{

}

void UMapGenerator::SpawnActorsInTiles()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(this);
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	for (int32 i=0; i<m_pTiles.Num(); i++)
	{
		ReadBlockInfoByName(pCWGameInstance->m_curPlayerSPInfo.curProgress, m_pTiles[i]->m_landBlockName, m_pTiles[i]);
		int32 tileLocXInWorldSpace = m_leftDownCornerCoord.X + m_pTiles[i]->X * m_tileWidth + m_tileWidth / 2;
		int32 tileLocYInWorldSpace = m_leftDownCornerCoord.Y + m_pTiles[i]->Y * m_tileHeight + m_tileHeight / 2;
		FLogicVec2D tileLocInWorldSpace(tileLocXInWorldSpace, tileLocYInWorldSpace);
		//m_pTiles[i]->m_actorSpawnYaw = FMath::RandRange(0, 180);
		for (int32 j=0; j<m_pTiles[i]->m_physActorSpawnLocs.Num(); j++)
		{
			FLogicVec2D locInRelativeSpace = m_pTiles[i]->m_physActorSpawnLocs[j];
			FLogicVec2D locInWorldSpace = locInRelativeSpace + tileLocInWorldSpace;
			m_pTiles[i]->m_physActorSpawnLocInWorldSpace.Add(locInWorldSpace);
			//m_pTiles[i]->m_physActorSpawnYaws[j] += m_pTiles[i]->m_actorSpawnYaw;
		}
		for (int32 j=0; j<m_pTiles[i]->m_dumpActorSpawnLocs.Num(); j++)
		{
			FLogicVec2D locInRelativeSpace = m_pTiles[i]->m_dumpActorSpawnLocs[j];
			FLogicVec2D locInWorldSpace = locInRelativeSpace + tileLocInWorldSpace;
			m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace.Add(locInWorldSpace);
			//m_pTiles[i]->m_dumpActorSpawnYaws[j] += m_pTiles[i]->m_actorSpawnYaw;
		}
		for (int32 j = 0; j < m_pTiles[i]->m_planSpawnPointLocs.Num(); j++)
		{
			FLogicVec2D locInRelativeSpace = m_pTiles[i]->m_planSpawnPointLocs[j];
			FLogicVec2D locInWorldSpace = locInRelativeSpace + tileLocInWorldSpace;
			m_pTiles[i]->m_planSpawnPointLocInWorldSpace.Add(locInWorldSpace);
			//m_pTiles[i]->m_dumpActorSpawnYaws[j] += m_pTiles[i]->m_actorSpawnYaw;
		}
		for (int32 j = 0; j < m_pTiles[i]->m_staticMeshLocs.Num(); j++)
		{
			FLogicVec2D locInRelativeSpace(m_pTiles[i]->m_staticMeshLocs[j].X, m_pTiles[i]->m_staticMeshLocs[j].Y);
			FLogicVec2D locInWorldSpace = locInRelativeSpace + tileLocInWorldSpace;
			//FLogicVec3D locInWorldSpace3D(locInWorldSpace.X, locInWorldSpace.Y, m_pTiles[i]->m_staticMeshLocs[j].Z);
			m_pTiles[i]->m_staticMeshLocInWorldSpace.Add(locInWorldSpace);
			//m_pTiles[i]->m_dumpActorSpawnYaws[j] += m_pTiles[i]->m_actorSpawnYaw;
		}
	}
}

void UMapGenerator::SetTilesToBlockAsConnecting(ULandBlockTile* pMergeTile, int32 totalTileWidth, int32 totalTileHeight, TArray<ULandBlockTile*>& pMergeTileList, ULandBlockTile* pTargetTile)
{
	if (!pTargetTile || !pMergeTile) return;
	if (!pMergeTileList.Contains(pTargetTile))
		pMergeTileList.Add(pTargetTile);
	if (pTargetTile->m_landBlockType == "")
		pTargetTile->m_landBlockType = "connect";
	int32 xDisToJunction = pMergeTile->X - pTargetTile->X;
	int32 yDisToJunction = pMergeTile->Y - pTargetTile->Y;
	bool horizontalOrVerticalFirst = FMath::RandBool();
	int32 curXTileNb = pTargetTile->X;
	int32 curYTileNb = pTargetTile->Y;
	if (horizontalOrVerticalFirst)
	{
		//先横方向前进，然后垂直方向
		if (xDisToJunction < 0)
		{
			if (curYTileNb != pMergeTile->Y)
				xDisToJunction -= 1;
			//说明岔路地块在特殊地块的左侧
			for (int32 j = 0; j < FMath::Abs(xDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + curYTileNb * totalTileWidth - 1];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//xDisToJunction += 1;
				curXTileNb -= 1;
			}
		}
		else
		{
			if (curYTileNb != pMergeTile->Y)
				xDisToJunction += 1;
			for (int32 j = 0; j < FMath::Abs(xDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + curYTileNb * totalTileWidth + 1];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//xDisToJunction -= 1;
				curXTileNb += 1;
			}
		}

		if (yDisToJunction < 0)
		{
			for (int32 j = 0; j < FMath::Abs(yDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + (curYTileNb - 1) * totalTileWidth];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//yDisToJunction += 1;
				curYTileNb -= 1;
			}
		}
		else
		{
			for (int32 j = 0; j < FMath::Abs(yDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + (curYTileNb + 1) * totalTileWidth];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//yDisToJunction -= 1;
				curYTileNb += 1;
			}
		}
	}
	else
	{
		if (yDisToJunction < 0)
		{
			if (curXTileNb != pMergeTile->X)
				yDisToJunction -= 1;
			for (int32 j = 0; j < FMath::Abs(yDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + (curYTileNb - 1) * totalTileWidth];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//yDisToJunction += 1;
				curYTileNb -= 1;
			}
		}
		else
		{
			if (curXTileNb != pMergeTile->X)
				yDisToJunction += 1;
			for (int32 j = 0; j < FMath::Abs(yDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + (curYTileNb + 1) * totalTileWidth];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//yDisToJunction -= 1;
				curYTileNb += 1;
			}
		}

		if (xDisToJunction < 0)
		{
			for (int32 j = 0; j < FMath::Abs(xDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + curYTileNb * totalTileWidth - 1];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//xDisToJunction += 1;
				curXTileNb -= 1;
			}
		}
		else
		{
			for (int32 j = 0; j < FMath::Abs(xDisToJunction) - 1; j++)
			{
				ULandBlockTile* pNextTile = m_pTiles[curXTileNb + curYTileNb * totalTileWidth + 1];
				if (!pMergeTileList.Contains(pNextTile))
					pMergeTileList.Add(pNextTile);
				if (pNextTile->m_landBlockType == "")
					pNextTile->m_landBlockType = "connect";
				//xDisToJunction -= 1;
				curXTileNb += 1;
			}
		}
	}
}

bool UMapGenerator::GetBuildTileListByCoords(int32 x, int32 y, int32 LExtend, int32 RExtent, int32 UExtent, int32 DExtent, TArray<FLogicVec2D>& gridList)
{
	//GetWorld()->OverlapMultiByChannel()
	int32 centralTileX = x / m_buildTileWidth;
	int32 centralTileY = y / m_buildTileWidth;
	int32 gridCentralX = centralTileX * m_buildTileWidth + m_buildTileWidth / 2;
	int32 gridCentralY = centralTileY * m_buildTileWidth + m_buildTileWidth / 2;
	bool canBuild = true;
	int32 tileNbPerRow = (m_bigTileWidthNb * m_bigTileWidth*m_tileWidth - m_leftDownCornerCoord.X)/m_buildTileWidth;
	for (int32 i=0; i<LExtend; i++)
	{
		for (int32 j=0; j<=UExtent; j++)
		{
			int32 gridX = gridCentralX - i * m_buildTileWidth;
			int32 gridY = gridCentralY + j * m_buildTileWidth;
			if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
				gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
				canBuild = false;
			else
			{
				int32 tileNb = centralTileX + (centralTileY + j) * tileNbPerRow - i;
				if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
			}
			gridList.Add(FLogicVec2D(gridX, gridY));
		}
		for (int32 j = 1; j <= DExtent; j++)
		{
			int32 gridX = gridCentralX - i * m_buildTileWidth;
			int32 gridY = gridCentralY - j * m_buildTileWidth;
			if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
				gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
				canBuild = false;
			else
			{
				int32 tileNb = centralTileX + (centralTileY - j) * tileNbPerRow - i;
				if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
			}
			gridList.Add(FLogicVec2D(gridX, gridY));
		}
	}
	for (int32 i = 0; i < RExtent; i++)
	{
		for (int32 j = 0; j <= UExtent; j++)
		{
			int32 gridX = gridCentralX + i * m_buildTileWidth;
			int32 gridY = gridCentralY + j * m_buildTileWidth;
			if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
				gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
				canBuild = false;
			else
			{
				int32 tileNb = centralTileX + (centralTileY + j) * tileNbPerRow + i;
				if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
			}
			gridList.Add(FLogicVec2D(gridX, gridY));
		}
		for (int32 j = 1; j <= DExtent; j++)
		{
			int32 gridX = gridCentralX + i * m_buildTileWidth;
			int32 gridY = gridCentralY - j * m_buildTileWidth;
			if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
				gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
				canBuild = false;
			else
			{
				int32 tileNb = centralTileX + (centralTileY - j) * tileNbPerRow + i;
				if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
			}
			gridList.Add(FLogicVec2D(gridX, gridY));
		}
	}
	for (int32 i=0; i<UExtent; i++)
	{
		int32 gridX = gridCentralX;
		int32 gridY = gridCentralY + i * m_buildTileWidth;
		if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
			gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
			canBuild = false;
		else
		{
			int32 tileNb = centralTileX + (centralTileY + i) * tileNbPerRow;
			if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
		}
		gridList.Add(FLogicVec2D(gridX, gridY));
	}
	for (int32 i=1; i<=DExtent; i++)
	{
		int32 gridX = gridCentralX;
		int32 gridY = gridCentralY - i * m_buildTileWidth;
		if (gridX < m_leftDownCornerCoord.X || gridX > m_leftDownCornerCoord.X + m_bigTileWidthNb * m_bigTileWidth*m_tileWidth ||
			gridY < m_leftDownCornerCoord.Y || gridY > m_leftDownCornerCoord.Y + m_bigTileHeightNb * m_bigTileHeight*m_tileHeight)
			canBuild = false;
		else
		{
			int32 tileNb = centralTileX + (centralTileY - i) * tileNbPerRow;
			if (m_alreadyOccupiedBuildTiles.Contains(tileNb)) canBuild = false;
		}
		gridList.Add(FLogicVec2D(gridX, gridY));
	}
	
	if (canBuild)
	{
		float ldCornerX = centralTileX - (float)m_buildTileWidth / 2.f - LExtend * m_buildTileWidth;
		float ldCornerY = centralTileY - (float)m_buildTileWidth / 2.f - DExtent * m_buildTileWidth;
		float rtCornerX = centralTileX + (float)m_buildTileWidth / 2.f + RExtent * m_buildTileWidth;
		float rtCornerY = centralTileY + (float)m_buildTileWidth / 2.f + UExtent * m_buildTileWidth;
		FVector overlapTestCenter((ldCornerX + rtCornerX) / 2.f, (ldCornerY + rtCornerY) / 2.f, 100);
		FVector collisionBoxHalfExtent((rtCornerX - ldCornerX) / 2.f, (rtCornerY - ldCornerY) / 2.f, 200.f);
		TArray<FOverlapResult> overlapResults;
		GetWorld()->OverlapMultiByChannel(overlapResults, overlapTestCenter, FQuat::Identity, ECollisionChannel::ECC_Visibility,
			FCollisionShape::MakeBox(collisionBoxHalfExtent));
		for (int32 i = 0; i < overlapResults.Num(); i++)
		{
			if (!overlapResults[i].GetActor())
				continue;
			if (overlapResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysActor"))) ||
				overlapResults[i].GetComponent()->ComponentHasTag(FName(TEXT("DumpActor"))))
			{
				canBuild = false;
				break;
			}
		}
	}
	

	return canBuild;
}

void UMapGenerator::ReadBlockInfoByName_Implementation(uint8 curLevelProgress, const FString& blockName, ULandBlockTile* pTile)
{

}

