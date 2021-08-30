// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventCard.h"
#include "ShadowActor.h"
#include "EventNodeManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FEventChAndEnDescriptionList
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enDescriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> chDescriptions;

};

UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UEventNodeManager : public UObject
{
	GENERATED_BODY()
public:
	
	void ResetNodeManager();

	/************************************************************************/
	/* Event Node Message
	/************************************************************************/
	//记录每个编号对应行动的按键文字
	//0 - “进行战斗”
	//1 - “进行一场艰苦的战斗”
	//2 - “猜卡牌”
	//3 - “记忆卡牌”
	//4 - “事件”
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FChAndEnDescriptionList> m_actionSupplementStrs;

	//记录提示文本，例如“前路漫漫，我感到有点迷茫，但毫无疑问，我需要赶快作出抉择.”
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FChAndEnDescriptionList m_rootNodeBodyStrList;

	//Player has mutiple choice at each node step, this variable controls
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_multipleChoiceNb = 2;

	UPROPERTY()
	FEventCardInfo m_eventCardInfo;

	UPROPERTY()
	FDescriptionTreeNode m_curTreeNode;

	UPROPERTY()
	FString m_choiceSelectStr;

	FString m_language;

	bool m_isVirtualNodeState;

	TArray<AShadowActor*> m_pShadowActors;
};
