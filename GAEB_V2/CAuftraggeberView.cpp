// CAuftraggeberView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CAuftraggeberView.h"


// CAuftraggeberView

IMPLEMENT_DYNCREATE(CAuftraggeberView, CView)

CAuftraggeberView::CAuftraggeberView()
{

}

CAuftraggeberView::~CAuftraggeberView()
{
}

BEGIN_MESSAGE_MAP(CAuftraggeberView, CView)
	ON_WM_CREATE()

END_MESSAGE_MAP()


// CAuftraggeberView drawing

void CAuftraggeberView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CAuftraggeberView diagnostics

#ifdef _DEBUG
void CAuftraggeberView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CAuftraggeberView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
int CAuftraggeberView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
}
int CAuftraggeberView::OnCreate_AuftragsgeberView(LPCREATESTRUCT lpCreateStruct)
{
	//m_GroupBox_Adresse_Daten_AG.Create(_T("Adressedaten"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, CRect(CPoint(50, 40), CSize(1000, 500)), this);

	m_staticText_Name1_AG.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(80, 20)), this, 1001);
	m_edit_Name1_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(120, 50), CSize(250, 20)), this, 1002);
	m_edit_Name2_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 90), CSize(250, 20)), this, 1002);
	m_edit_Name3_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 130), CSize(250, 20)), this, 1002);


	m_staticText_Strasse_AG.Create(_T("Strasse"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 170), CSize(80, 20)), this, 1001);
	m_edit_Srasse_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 170), CSize(250, 20)), this, 1002);


	m_staticText_PLZ_AG.Create(_T("PLZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 210), CSize(80, 20)), this, 1001);
	m_edit_PLZ_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 210), CSize(150, 20)), this, 1002);


	m_staticText_Ort_AG.Create(_T("Ort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 250), CSize(80, 20)), this, 1001);
	m_edit_Ort_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 250), CSize(250, 20)), this, 1002);

	m_staticText_Land_AG.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 290), CSize(80, 20)), this, 1001);
	m_staticText_Land_AG.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 290), CSize(80, 20)), this, 1001);

	m_staticText_Ansprechpartner_AG.Create(_T("Ansprechpartner"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(120, 20)), this, 1001);
	m_edit_Ansprechpartner_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 50), CSize(250, 20)), this, 1002);


	m_staticText_Telefon_AG.Create(_T("Telefon"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(120, 20)), this, 1001);
	m_edit_Tel_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 90), CSize(250, 20)), this, 1002);


	m_staticText_FAX_AG.Create(_T("Fax"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 130), CSize(120, 20)), this, 1001);
	m_edit_Fax_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 130), CSize(250, 20)), this, 1002);


	m_staticText_Email_AG.Create(_T("Email"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 170), CSize(120, 20)), this, 1001);
	m_edit_Email_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 170), CSize(250, 20)), this, 1002);


	m_staticText_IL_Num_AG.Create(_T("IL-Nummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 210), CSize(120, 20)), this, 1001);
	m_edit_IL_Num_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 210), CSize(250, 20)), this, 1002);


	m_staticText_Steuer_AG.Create(_T("UmsatzsteuerID"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 250), CSize(120, 20)), this, 1001);
	m_edit_Steuer_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 250), CSize(250, 20)), this, 1002);
	return 0;
}
#endif
#endif //_DEBUG


// CAuftraggeberView message handlers
