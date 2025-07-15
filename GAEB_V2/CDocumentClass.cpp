// CDocumentClass.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CDocumentClass.h"


// CDocumentClass

IMPLEMENT_DYNCREATE(CDocumentClass, CDocument)

CDocumentClass::CDocumentClass()
{
}

BOOL CDocumentClass::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDocumentClass::~CDocumentClass()
{
}


BEGIN_MESSAGE_MAP(CDocumentClass, CDocument)
END_MESSAGE_MAP()


// CDocumentClass diagnostics

#ifdef _DEBUG
void CDocumentClass::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDocumentClass::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDocumentClass serialization

void CDocumentClass::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// CDocumentClass commands
