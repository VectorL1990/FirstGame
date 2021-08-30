// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/SingleProgress/PlayCard.h"
#include "../../Base/Widget/TActionCardInfo.h"
#include "ActionCard.generated.h"

UCLASS()
class COLLISIONWAR_API AActionCard : public APlayCard
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupActionCard(UStaticMeshComponent* pBaseMesh, UTextRenderComponent* pCardName);

	virtual void InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName) override;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitialWidget();
	
	FString m_actionDescription;

	FString m_chActionDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UStaticMeshComponent* m_pActionTexture;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTActionCardInfo* m_pActionCardInfo;

	/** 标记行动种类
	* 0 - 行动合成
	* 1 - 探索
	* 2 - 交流
	* 3 - 锻造
	* 4 - 研究
	* 5 - 普通事件
	* 6 - 战斗事件
	*/
	uint8 m_actionType;

	FString m_actionName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_chActionName;

	float m_originLoadTime = 0;

	float m_curLoadTime = 0;

	/** 标记卡牌当前状态
	* 0 - 什么都没发生
	* 1 - 玩家按下了合成键，等待ActionPanel确认，然后正式开始倒计时或进行战斗计算等情景，如为选择情景，例如探索城镇，0代表旅馆，1代表酒吧等，
			此时需要将possibleOutputlist中以"/"为分隔的前缀tags作为subsidary判断，即此处进行特殊修改m_availableTransformInfos，短暂维持
	* 2 - 正在计时
	* 3 - 完成计时，但没被ActionPanel确认，短暂维持
	* 4 - 被ActionPanel确认，将倒计时等界面元素删除
	* 5 - 玩家按下了合成键，ActionPanel确认为选择情景，按下确认按钮后需要对m_availableTransformInfos进行剔除
	* 6 - 玩家在选择情景中选择完毕，回到正常放置卡牌的界面，放置完成后按下合成键，将状态转为1
	* 7 - ActionPanel确认为战斗计算情景，此时生成对应的Slot
	*/
	uint8 m_state;

	UPROPERTY()
	FCardTransformInfo m_curCardTransformInfo;

	UPROPERTY()
	FPossibleEventInfo m_eventInfo;
};
