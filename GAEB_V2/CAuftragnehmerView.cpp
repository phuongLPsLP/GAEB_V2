// CAuftragnehmerView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CAuftragnehmerView.h"


// CAuftragnehmerView

IMPLEMENT_DYNCREATE(CAuftragnehmerView, CView)

CAuftragnehmerView::CAuftragnehmerView()
{

}

CAuftragnehmerView::~CAuftragnehmerView()
{
}

BEGIN_MESSAGE_MAP(CAuftragnehmerView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CAuftragnehmerView drawing

void CAuftragnehmerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CAuftragnehmerView diagnostics

#ifdef _DEBUG
void CAuftragnehmerView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CAuftragnehmerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
int CAuftragnehmerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//OnCreate_FirstView(lpCreateStruct); // Create the first view
}
int CAuftragnehmerView::OnCreate_Auftragnehmer_View(LPCREATESTRUCT lpCreateStruct)
{
	CPoint pt(400, 430);
	CSize sz(70, 30);

	m_GroupBox_Adresse_Daten_AN.Create(_T("Adressedaten"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, CRect(CPoint(50, 40), CSize(1000, 500)), this);

	m_staticText_Name1_AN.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 50), CSize(80, 20)), this, 1001);
	m_edit_Name1_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(120, 50), CSize(250, 20)), this, 1002);
	m_edit_Name2_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 90), CSize(250, 20)), this, 1002);
	m_edit_Name3_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 130), CSize(250, 20)), this, 1002);



	m_staticText_Strasse_AN.Create(_T("Strasse"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 170), CSize(80, 20)), this, 1001);
	m_edit_Srasse_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 170), CSize(250, 20)), this, 1002);

	m_staticText_PLZ_AN.Create(_T("PLZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 210), CSize(80, 20)), this, 1001);
	m_edit_PLZ_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 210), CSize(150, 20)), this, 1002);


	m_staticText_Ort_AN.Create(_T("Ort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 250), CSize(80, 20)), this, 1001);
	m_edit_Ort_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 250), CSize(250, 20)), this, 1002);



	m_staticText_Land_AN.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 290), CSize(80, 20)), this, 1001);
	m_edit_Land_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 290), CSize(250, 20)), this, 1002);


	m_staticText_Ansprechpartner_AN.Create(_T("Ansprechpartner"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(120, 20)), this, 1001);
	m_edit_Ansprechpartner_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 50), CSize(250, 20)), this, 1002);



	m_staticText_Telefon_AN.Create(_T("Telefon"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(120, 20)), this, 1001);
	m_edit_Tel_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 90), CSize(250, 20)), this, 1002);



	m_staticText_Fax_AN.Create(_T("Fax"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 130), CSize(120, 20)), this, 1001);
	m_edit_Fax_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 130), CSize(250, 20)), this, 1002);


	m_staticText_Email_AN.Create(_T("Email"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 170), CSize(120, 20)), this, 1001);
	m_edit_Email_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 170), CSize(250, 20)), this, 1002);


	m_staticText_IL_Num_AN.Create(_T("IL-Nummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 210), CSize(120, 20)), this, 1001);
	m_edit_IL_Num_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 210), CSize(250, 20)), this, 1002);


	m_staticText_Steuer_AN.Create(_T("UmsatzsteuerID"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 250), CSize(120, 20)), this, 1001);
	m_edit_Steuer_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 250), CSize(250, 20)), this, 1002);


	return 0;
}
#endif
#endif //_DEBUG


// CAuftragnehmerView message handlers
