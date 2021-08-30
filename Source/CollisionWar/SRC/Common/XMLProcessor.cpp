// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "XMLProcessor.h"




bool UXMLProcessor::ReadAndInitialXML(const FString& pathName, const FString& docName)
{
	FString _xmlpath = FPaths::GameDir() + pathName + docName;
	char* charPath = TCHAR_TO_ANSI(*_xmlpath);
	m_pDoc = new XMLDocument();
	XMLError loadResult = m_pDoc->LoadFile(charPath);
	if (loadResult != XML_SUCCESS)
	{
		delete m_pDoc;
		return false;
	}
	m_pRootNode = m_pDoc->RootElement();
	if (!m_pRootNode)
	{
		delete m_pDoc;
		return false;
	}
	return true;
}

void UXMLProcessor::GetXMLNodeByAttributeFromRoot(FString targetNodeName, FString targetNodeAttribute, FString attributeValue)
{
	if (!m_pRootNode) return;
	m_pCurSearchNode = UCollisionWarBpFunctionLibrary::SearchXMLNodeByAttribute(m_pRootNode, targetNodeName, targetNodeAttribute, attributeValue);
}

void UXMLProcessor::GetXMLNodeByContentFromRoot(FString targetNodeName, FString content)
{
	if (!m_pRootNode) return;
	m_pCurSearchNode = UCollisionWarBpFunctionLibrary::SearchXMLNodeByContent(m_pRootNode, targetNodeName, content);
}

bool UXMLProcessor::GetXMLTableUnderCurWorksheetNode()
{
	if (!m_pCurWorksheetNode)
	{
		return false;
	}
	if (!m_pCurWorksheetNode->FirstChildElement())
	{
		return false;
	}
	m_pCurTableNode = m_pCurWorksheetNode->FirstChildElement();
	return true;
}

void UXMLProcessor::GetXMLFirstWorksheetNode()
{
	if (!m_pRootNode) return;
	XMLElement* pCurChildNode = m_pRootNode->FirstChildElement();
	if (!pCurChildNode) return;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == TEXT("Worksheet"))
		{
			m_pCurWorksheetNode = pCurChildNode;
			return;
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	m_pCurWorksheetNode = NULL;
}

void UXMLProcessor::GetXMLFirstTableNode()
{
	if (!m_pRootNode) return;
	XMLElement* pCurChildNode = m_pRootNode->FirstChildElement();
	if (!pCurChildNode) return;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == TEXT("Worksheet"))
		{
			m_pCurTableNode = pCurChildNode->FirstChildElement();
			return;
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	m_pCurTableNode = NULL;
}

void UXMLProcessor::GetXMLFirstTableUnderCurWorksheet()
{
	if (!m_pCurWorksheetNode && !m_pCurWorksheetNode->FirstChildElement()) return;
	m_pCurTableNode = m_pCurWorksheetNode->FirstChildElement();
}

void UXMLProcessor::GetXMLRowByContentFromTableNode(FString content)
{
	if (!m_pCurTableNode) return;
	XMLElement* pCurChildNode = m_pCurTableNode->FirstChildElement();
	if (!pCurChildNode) return;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == "Row")
		{
			XMLElement* pCellNode = pCurChildNode->FirstChildElement();
			while (pCellNode)
			{
				XMLElement* pDataNode = pCellNode->FirstChildElement();
				if (pDataNode)
				{
					const char* nodeDataChar = pDataNode->GetText();
					FString nodeData = ANSI_TO_TCHAR(nodeDataChar);
					if (nodeData == content)
					{
						m_pCurRowNodeInTable = pCurChildNode;
						return;
					}
				}
				pCellNode = pCellNode->NextSiblingElement();
			}
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	m_pCurRowNodeInTable = NULL;
}

void UXMLProcessor::GetXMLEndRowByContentFromTableNode(FString content)
{
	if (!m_pCurTableNode) return;
	XMLElement* pCurChildNode = m_pCurTableNode->FirstChildElement();
	if (!pCurChildNode) return;
	while (pCurChildNode)
	{
		const char* nodeNameChar = pCurChildNode->Name();
		FString nodeName = ANSI_TO_TCHAR(nodeNameChar);
		if (nodeName == "Row")
		{
			XMLElement* pCellNode = pCurChildNode->FirstChildElement();
			while (pCellNode)
			{
				XMLElement* pDataNode = pCellNode->FirstChildElement();
				if (pDataNode)
				{
					const char* nodeDataChar = pDataNode->GetText();
					FString nodeData = ANSI_TO_TCHAR(nodeDataChar);
					if (nodeData == content)
					{
						m_pEndNodeInTable = pCurChildNode;
						return;
					}
				}
				pCellNode = pCellNode->NextSiblingElement();
			}
		}
		pCurChildNode = pCurChildNode->NextSiblingElement();
	}
	m_pEndNodeInTable = NULL;
}

void UXMLProcessor::GetNextWorksheetNode()
{
	if (!m_pCurWorksheetNode) return;
	m_pCurWorksheetNode = m_pCurWorksheetNode->NextSiblingElement();
}

void UXMLProcessor::GetNextCellNode()
{
	if (!m_pCurCellNodeInTable) return;
	m_pCurCellNodeInTable = m_pCurCellNodeInTable->NextSiblingElement();
}

void UXMLProcessor::GetNextRowNode()
{
	if (!m_pCurRowNodeInTable) return;
	m_pCurRowNodeInTable = m_pCurRowNodeInTable->NextSiblingElement();
}

bool UXMLProcessor::IsCurRowReachEndRow()
{
	XMLElement* pFirstCellNode1 = m_pCurRowNodeInTable->FirstChildElement()->FirstChildElement();
	XMLElement* pFirstCellNode2 = m_pEndNodeInTable->FirstChildElement()->FirstChildElement();
	const char* nodeDataChar1 = pFirstCellNode1->GetText();
	FString nodeData1 = ANSI_TO_TCHAR(nodeDataChar1);
	const char* nodeDataChar2 = pFirstCellNode2->GetText();
	FString nodeData2 = ANSI_TO_TCHAR(nodeDataChar2);
	if (nodeData1 == nodeData2)
	{
		return true;
	}
	else return false;
}

void UXMLProcessor::GetFirstCellNodeInCurRow()
{
	if (!m_pCurRowNodeInTable) return;
	m_pCurCellNodeInTable = m_pCurRowNodeInTable->FirstChildElement();
}

bool UXMLProcessor::IsCurWorksheetNodeValid()
{
	if (m_pCurWorksheetNode) return true;
	else return false;
}

bool UXMLProcessor::IsCurCellNodeValid()
{
	if (m_pCurCellNodeInTable) return true;
	else return false;
}

FString UXMLProcessor::GetCurCellNodeContent()
{
	const char* contentChar = m_pCurCellNodeInTable->FirstChildElement()->GetText();
	FString contentString = ANSI_TO_TCHAR(contentChar);
	return contentString;
}

void UXMLProcessor::CloseXMLDoc()
{
	m_pCurCellNodeInTable = NULL;
	m_pCurRowNodeInTable = NULL;
	m_pCurSearchNode = NULL;
	m_pCurTableNode = NULL;
	m_pEndNodeInTable = NULL;
	m_pRootNode = NULL;
	delete m_pDoc;
}

