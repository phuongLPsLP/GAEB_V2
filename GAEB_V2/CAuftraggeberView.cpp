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
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAuftraggeberView drawing

void CAuftraggeberView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CAuftraggeberView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
	CRect m_rec2(CPoint(20, 20), CSize(920, 320));
	m_groupbox_Adressdaten = new CButton();
	m_groupbox_Adressdaten->Create(_T("Adressdaten"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX, m_rec2, this, 1003);
	m_groupbox_Adressdaten->SetFont(&m_font);

	m_staticText_Name1_AG.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(80, 20)), this, 1001);
	m_staticText_Strasse_AG.Create(_T("Strasse"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 170), CSize(80, 20)), this, 1001);
	m_staticText_PLZ_AG.Create(_T("PLZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 210), CSize(80, 20)), this, 1001);
	m_staticText_Ort_AG.Create(_T("Ort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 250), CSize(80, 20)), this, 1001);
	m_staticText_Land_AG.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 290), CSize(80, 20)), this, 1001);
	m_staticText_Ansprechpartner_AG.Create(_T("Ansprechpartner"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(120, 20)), this, 1001);
	m_staticText_Telefon_AG.Create(_T("Telefon"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(120, 20)), this, 1001);
	m_staticText_FAX_AG.Create(_T("Fax"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 130), CSize(120, 20)), this, 1001);
	m_staticText_Email_AG.Create(_T("Email"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 170), CSize(120, 20)), this, 1001);
	m_staticText_IL_Num_AG.Create(_T("IL-Nummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 210), CSize(120, 20)), this, 1001);
	m_staticText_Steuer_AG.Create(_T("UmsatzsteuerID"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 250), CSize(120, 20)), this, 1001);


	m_edit_Name1_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(120, 50), CSize(250, 20)), this, 1002);
	m_edit_Name2_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 90), CSize(250, 20)), this, 1002);
	m_edit_Name3_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 130), CSize(250, 20)), this, 1002);
	m_edit_Srasse_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 170), CSize(250, 20)), this, 1002);
	m_edit_PLZ_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 210), CSize(150, 20)), this, 1002);
	m_edit_Ort_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 250), CSize(250, 20)), this, 1002);
	m_edit_Land_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 290), CSize(250, 20)), this, 1002);
	m_edit_Ansprechpartner_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 50), CSize(250, 20)), this, 1002);
	m_edit_Tel_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 90), CSize(250, 20)), this, 1002);
	m_edit_Fax_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 130), CSize(250, 20)), this, 1002);
	m_edit_Email_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 170), CSize(250, 20)), this, 1002);
	m_edit_IL_Num_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 210), CSize(250, 20)), this, 1002);
	m_edit_Steuer_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 250), CSize(250, 20)), this, 1002);

	CStatic* staticControls[] = {
	&m_staticText_Name1_AG,
	&m_staticText_Strasse_AG,
	&m_staticText_PLZ_AG,
	&m_staticText_Ort_AG,
	&m_staticText_Land_AG,
	&m_staticText_Ansprechpartner_AG,
	&m_staticText_Telefon_AG,
	&m_staticText_FAX_AG,
	&m_staticText_Email_AG,
	&m_staticText_IL_Num_AG,
	&m_staticText_Steuer_AG
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}
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
#endif
#endif //_DEBUG

HBRUSH CAuftraggeberView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();
	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	//Combobox

	/*if (ctrlID == 1003)
	{
		if (nCtlColor == CTLCOLOR_LISTBOX) // ListBox (Dropdown area)
		{
			pDC->SetBkColor(RGB(200, 220, 255)); // Light Blue Background
			pDC->SetTextColor(RGB(255, 0, 0));     // Black Text
			return m_brush_combobox;
		}

		else if (nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_STATIC) // ComboBox text area
		{
			pDC->SetBkColor(RGB(255, 255, 180)); // Light Yellow
			pDC->SetTextColor(RGB(0, 0, 0));   // Black text
			return m_brush_combobox;
		}
		return CView::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	//Edit box
	if (ctrlID == 1002)
	{
		m_textColor_editbox = RGB(0, 0, 0);
		pDC->SetTextColor(m_textColor_editbox);       // Black text
		pDC->SetBkColor(RGB(255, 255, 180));
		// Return the brush for background color
		return m_brush_editbox;

	}*/

	return hbr;
}
