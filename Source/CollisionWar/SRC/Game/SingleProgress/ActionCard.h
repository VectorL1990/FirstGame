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

	/** ����ж�����
	* 0 - �ж��ϳ�
	* 1 - ̽��
	* 2 - ����
	* 3 - ����
	* 4 - �о�
	* 5 - ��ͨ�¼�
	* 6 - ս���¼�
	*/
	uint8 m_actionType;

	FString m_actionName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_chActionName;

	float m_originLoadTime = 0;

	float m_curLoadTime = 0;

	/** ��ǿ��Ƶ�ǰ״̬
	* 0 - ʲô��û����
	* 1 - ��Ұ����˺ϳɼ����ȴ�ActionPanelȷ�ϣ�Ȼ����ʽ��ʼ����ʱ�����ս��������龰����Ϊѡ���龰������̽������0�����ùݣ�1����ưɵȣ�
			��ʱ��Ҫ��possibleOutputlist����"/"Ϊ�ָ���ǰ׺tags��Ϊsubsidary�жϣ����˴����������޸�m_availableTransformInfos������ά��
	* 2 - ���ڼ�ʱ
	* 3 - ��ɼ�ʱ����û��ActionPanelȷ�ϣ�����ά��
	* 4 - ��ActionPanelȷ�ϣ�������ʱ�Ƚ���Ԫ��ɾ��
	* 5 - ��Ұ����˺ϳɼ���ActionPanelȷ��Ϊѡ���龰������ȷ�ϰ�ť����Ҫ��m_availableTransformInfos�����޳�
	* 6 - �����ѡ���龰��ѡ����ϣ��ص��������ÿ��ƵĽ��棬������ɺ��ºϳɼ�����״̬תΪ1
	* 7 - ActionPanelȷ��Ϊս�������龰����ʱ���ɶ�Ӧ��Slot
	*/
	uint8 m_state;

	UPROPERTY()
	FCardTransformInfo m_curCardTransformInfo;

	UPROPERTY()
	FPossibleEventInfo m_eventInfo;
};
