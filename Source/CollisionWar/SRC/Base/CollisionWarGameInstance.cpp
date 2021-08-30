// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Engine.h"
#include "../Game/BattleLevelGameModeBase.h"
#include "CollisionWarGameInstance.h"


UCollisionWarGameInstance::UCollisionWarGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	m_cosExpandList.Add(10000);
	m_cosExpandList.Add(9998);
	m_cosExpandList.Add(9994);
	m_cosExpandList.Add(9986);
	m_cosExpandList.Add(9976);
	m_cosExpandList.Add(9962);
	m_cosExpandList.Add(9945);
	m_cosExpandList.Add(9925);
	m_cosExpandList.Add(9903);
	m_cosExpandList.Add(9877);
	m_cosExpandList.Add(9848);
	m_cosExpandList.Add(9816);
	m_cosExpandList.Add(9781);
	m_cosExpandList.Add(9744);
	m_cosExpandList.Add(9703);
	m_cosExpandList.Add(9659);
	m_cosExpandList.Add(9613);
	m_cosExpandList.Add(9563);
	m_cosExpandList.Add(9511);
	m_cosExpandList.Add(9455);
	m_cosExpandList.Add(9397);
	m_cosExpandList.Add(9336);
	m_cosExpandList.Add(9272);
	m_cosExpandList.Add(9205);
	m_cosExpandList.Add(9135);
	m_cosExpandList.Add(9063);
	m_cosExpandList.Add(8988);
	m_cosExpandList.Add(8910);
	m_cosExpandList.Add(8829);
	m_cosExpandList.Add(8746);
	m_cosExpandList.Add(8660);
	m_cosExpandList.Add(8572);
	m_cosExpandList.Add(8480);
	m_cosExpandList.Add(8387);
	m_cosExpandList.Add(8290);
	m_cosExpandList.Add(8192);
	m_cosExpandList.Add(8090);
	m_cosExpandList.Add(7986);
	m_cosExpandList.Add(7880);
	m_cosExpandList.Add(7771);
	m_cosExpandList.Add(7660);
	m_cosExpandList.Add(7547);
	m_cosExpandList.Add(7431);
	m_cosExpandList.Add(7314);
	m_cosExpandList.Add(7193);
	m_cosExpandList.Add(7071);
	m_cosExpandList.Add(6947);
	m_cosExpandList.Add(6820);
	m_cosExpandList.Add(6691);
	m_cosExpandList.Add(6561);
	m_cosExpandList.Add(6428);
	m_cosExpandList.Add(6293);
	m_cosExpandList.Add(6157);
	m_cosExpandList.Add(6018);
	m_cosExpandList.Add(5878);
	m_cosExpandList.Add(5736);
	m_cosExpandList.Add(5592);
	m_cosExpandList.Add(5446);
	m_cosExpandList.Add(5299);
	m_cosExpandList.Add(5150);
	m_cosExpandList.Add(5000);
	m_cosExpandList.Add(4848);
	m_cosExpandList.Add(4695);
	m_cosExpandList.Add(4540);
	m_cosExpandList.Add(4384);
	m_cosExpandList.Add(4226);
	m_cosExpandList.Add(4067);
	m_cosExpandList.Add(3907);
	m_cosExpandList.Add(3746);
	m_cosExpandList.Add(3584);
	m_cosExpandList.Add(3420);
	m_cosExpandList.Add(3256);
	m_cosExpandList.Add(3090);
	m_cosExpandList.Add(2924);
	m_cosExpandList.Add(2756);
	m_cosExpandList.Add(2588);
	m_cosExpandList.Add(2419);
	m_cosExpandList.Add(2250);
	m_cosExpandList.Add(2079);
	m_cosExpandList.Add(1908);
	m_cosExpandList.Add(1736);
	m_cosExpandList.Add(1564);
	m_cosExpandList.Add(1392);
	m_cosExpandList.Add(1219);
	m_cosExpandList.Add(1045);
	m_cosExpandList.Add(872);
	m_cosExpandList.Add(698);
	m_cosExpandList.Add(523);
	m_cosExpandList.Add(349);
	m_cosExpandList.Add(175);
	m_cosExpandList.Add(0);


	m_intSqrtList = {
		0,    16,  22,  27,  32,  35,  39,  42,  45,  48,  50,  53,  55,  57,
		59,   61,  64,  65,  67,  69,  71,  73,  75,  76,  78,  80,  81,  83,
		84,   86,  87,  89,  90,  91,  93,  94,  96,  97,  98,  99, 101, 102,
		103, 104, 106, 107, 108, 109, 110, 112, 113, 114, 115, 116, 117, 118,
		119, 120, 121, 122, 123, 124, 125, 126, 128, 128, 129, 130, 131, 132,
		133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 144, 145,
		146, 147, 148, 149, 150, 150, 151, 152, 153, 154, 155, 155, 156, 157,
		158, 159, 160, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168,
		169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 178,
		179, 180, 181, 181, 182, 183, 183, 184, 185, 185, 186, 187, 187, 188,
		189, 189, 190, 191, 192, 192, 193, 193, 194, 195, 195, 196, 197, 197,
		198, 199, 199, 200, 201, 201, 202, 203, 203, 204, 204, 205, 206, 206,
		207, 208, 208, 209, 209, 210, 211, 211, 212, 212, 213, 214, 214, 215,
		215, 216, 217, 217, 218, 218, 219, 219, 220, 221, 221, 222, 222, 223,
		224, 224, 225, 225, 226, 226, 227, 227, 228, 229, 229, 230, 230, 231,
		231, 232, 232, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238,
		239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246,
		246, 247, 247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253,
		253, 254, 254, 255
	};
}

void UCollisionWarGameInstance::ServerTravelByLevelName(FString levelName)
{
	FString levelPath = TEXT("/Game/TopDown/Maps/");
	levelPath += levelName;
	levelPath += TEXT("?Listen");
	GetWorld()->ServerTravel(levelPath, false);
}



