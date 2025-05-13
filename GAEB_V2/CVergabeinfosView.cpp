// CVergabeinfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVergabeinfosView.h"


// CVergabeinfosView

IMPLEMENT_DYNCREATE(CVergabeinfosView, CView)

CVergabeinfosView::CVergabeinfosView()
{

}

CVergabeinfosView::~CVergabeinfosView()
{
}

BEGIN_MESSAGE_MAP(CVergabeinfosView, CView)
END_MESSAGE_MAP()


// CVergabeinfosView drawing

void CVergabeinfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CVergabeinfosView diagnostics

#ifdef _DEBUG
void CVergabeinfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVergabeinfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
int CVergabeinfosView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
}
int CVergabeinfosView::OnCreate_Vergabeninfos_View(LPCREATESTRUCT lpCreateStruct)
{

	m_staticText_Vergabeart.Create(_T("Vergabeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50,50),CSize(80,20)), this, 1001);
	m_combobox_Vergabeart.Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | CBS_DROPDOWNLIST, CRect(CPoint(200, 50), CSize(200, 20)), this, 1002);

	m_staticText_Waehrung_vergabeinfos.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 90), CSize(120, 20)), this, 1001);

	m_staticText_Angebotsdatum.Create(_T("Angebotsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 130), CSize(80, 20)), this, 1001);

	m_staticText_Abnahmedatum.Create(_T("Abnahmedatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 170), CSize(80, 20)), this, 1001);

	m_staticText_Auftragsdatum.Create(_T("Auftragsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 210), CSize(80, 20)), this, 1001);

	m_staticText_Sonderart.Create(_T("Sonderart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(80, 20)), this, 1001);

	m_staticText_Abgabeort.Create(_T("Abgabeort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(80, 20)), this, 1001);

	//m_staticText_Angebotszeit.Create(_T("Angebotszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(300, 130), CSize(80, 20)), this);

	//m_staticText_Zuschlagsfrist.Create(_T("Zuschlagsfrist"), WS_CHILD | WS_VISIBLE, CRect(CPoint(300, 170), CSize(80, 20)), this);

	//m_staticText_Abnahmeart.Create(_T("Abnahmeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(300, 210), CSize(80, 20)), this);

	//m_staticText_Auftragsnummer.Create(_T("Auftragsnummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 250), CSize(80, 20)), this);
	return 0;
}
#endif
#endif //_DEBUG


// CVergabeinfosView message handlers
