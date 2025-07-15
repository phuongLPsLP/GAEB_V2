#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CDocumentClass document

class CDocumentClass : public CDocument
{
	DECLARE_DYNCREATE(CDocumentClass)

public:
	CDocumentClass();
	virtual ~CDocumentClass();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award
protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
