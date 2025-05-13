// CProjektInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CProjektInfosView.h"


// CProjektInfosView

IMPLEMENT_DYNCREATE(CProjektInfosView, CView)

CProjektInfosView::CProjektInfosView()
{

}

CProjektInfosView::~CProjektInfosView()
{
}

BEGIN_MESSAGE_MAP(CProjektInfosView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CProjektInfosView drawing

void CProjektInfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CProjektInfosView diagnostics

#ifdef _DEBUG
void CProjektInfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjektInfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
int CProjektInfosView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//OnCreate_FirstView(lpCreateStruct); // Create the first view
}
int CProjektInfosView::OnCreate_ProjecktInfos_View(LPCREATESTRUCT lpCreateStruct)
{
	m_staticText_Name.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(80, 20)), this, 1001);
	m_staticText_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 90), CSize(120, 20)), this, 1001);
	m_staticText_Beschreibung.Create(_T("Beschreibung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 190), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 360), CSize(120, 20)), this, 1001);
	m_staticText_Leistungsbreich.Create(_T("Leistungsbereich"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 400), CSize(120, 20)), this, 1001);

	m_edit_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 50), CSize(150, 20)), this, 1002);
	m_edit_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 90), CSize(300, 80)), this, 1002);
	m_edit_Beschreibung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 190), CSize(300, 150)), this, 1002);
	m_edit_Waehrung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 360), CSize(50, 20)), this, 1002);
	m_edit_Bez.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(300, 360), CSize(200, 20)), this, 1002);
	m_edit_Leistungsbreich.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 400), CSize(100, 20)), this, 1002);

	return 0;
}
#endif
#endif //_DEBUG


// CProjektInfosView message handlers
