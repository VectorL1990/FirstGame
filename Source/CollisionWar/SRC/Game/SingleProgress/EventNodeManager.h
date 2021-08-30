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
	//��¼ÿ����Ŷ�Ӧ�ж��İ�������
	//0 - ������ս����
	//1 - ������һ������ս����
	//2 - ���¿��ơ�
	//3 - �����俨�ơ�
	//4 - ���¼���
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FChAndEnDescriptionList> m_actionSupplementStrs;

	//��¼��ʾ�ı������硰ǰ·�������Ҹе��е���ã�����������ʣ�����Ҫ�Ͽ���������.��
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
