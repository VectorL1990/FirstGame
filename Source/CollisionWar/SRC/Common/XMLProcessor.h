// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ThirdParty/tinyxml2.h"
#include "CollisionWarBpFunctionLibrary.h"
#include "XMLProcessor.generated.h"

using namespace tinyxml2;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UXMLProcessor : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	bool ReadAndInitialXML(const FString& pathName, const FString& docName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLNodeByAttributeFromRoot(FString targetNodeName, FString targetNodeAttribute, FString attributeValue);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLNodeByContentFromRoot(FString targetNodeName, FString content);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	bool GetXMLTableUnderCurWorksheetNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLFirstTableNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLFirstWorksheetNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLFirstTableUnderCurWorksheet();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLRowByContentFromTableNode(FString content);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetXMLEndRowByContentFromTableNode(FString content);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetNextCellNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetNextRowNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetNextWorksheetNode();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	bool IsCurRowReachEndRow();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void GetFirstCellNodeInCurRow();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	bool IsCurCellNodeValid();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	bool IsCurWorksheetNodeValid();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	FString GetCurCellNodeContent();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	void CloseXMLDoc();

	XMLDocument* m_pDoc;

	XMLElement* m_pRootNode;

	XMLElement* m_pCurSearchNode;

	XMLElement* m_pCurRowNodeInTable;

	XMLElement* m_pCurCellNodeInTable;
	
	XMLElement* m_pCurTableNode;

	XMLElement* m_pCurWorksheetNode;

	XMLElement* m_pEndNodeInTable;
};
