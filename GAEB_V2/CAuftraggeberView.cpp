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
	//m_font.CreatePointFont(110, _T("Segoe UI")); 
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_edit_small;
	::ZeroMemory(&lf_edit_small, sizeof(LOGFONT));
	lf_edit_small.lfHeight = 16;
	lf_edit_small.lfWeight = FW_NORMAL;
	_tcscpy_s(lf_edit_small.lfFaceName, _T("Segoe UI"));
	m_font_edit.CreateFontIndirect(&lf_edit_small);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 18; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

	CRect m_rec2(CPoint(20, 20), CSize(920, 320));
	m_groupbox_Adressdaten = new CButton();
	m_groupbox_Adressdaten->Create(_T("Adressdaten"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX, m_rec2, this, 1006);
	m_groupbox_Adressdaten->SetFont(&m_font);

	m_staticText_Name1_AG.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 60), CSize(80, 20)), this, 1001);
	m_staticText_Strasse_AG.Create(_T("Strasse"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 180), CSize(80, 20)), this, 1001);
	m_staticText_PLZ_AG.Create(_T("PLZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 220), CSize(80, 20)), this, 1001);
	m_staticText_Ort_AG.Create(_T("Ort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 260), CSize(80, 20)), this, 1001);
	m_staticText_Land_AG.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 300), CSize(80, 20)), this, 1001);
	//minipage
	m_staticText_Ansprechpartner_AG.Create(_T("Ansprechpartner"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 60), CSize(120, 20)), this, 1001);
	m_staticText_Telefon_AG.Create(_T("Telefon"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 100), CSize(120, 20)), this, 1001);
	m_staticText_FAX_AG.Create(_T("Fax"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 140), CSize(120, 20)), this, 1001);
	m_staticText_Email_AG.Create(_T("Email"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 180), CSize(120, 20)), this, 1001);
	m_staticText_IL_Num_AG.Create(_T("IL-Nummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 220), CSize(120, 20)), this, 1001);
	m_staticText_Steuer_AG.Create(_T("UmsatzsteuerID"), WS_CHILD | WS_VISIBLE, CRect(CPoint(450, 260), CSize(120, 20)), this, 1001);


	m_edit_Name1_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(120, 60), CSize(250, 20)), this, 1002);
	m_edit_Name2_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 100), CSize(250, 20)), this, 1002);
	m_edit_Name3_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 140), CSize(250, 20)), this, 1002);
	m_edit_Srasse_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 180), CSize(250, 20)), this, 1002);
	m_edit_PLZ_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 220), CSize(125, 20)), this, 1002);
	m_edit_Ort_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 260), CSize(250, 20)), this, 1002);
	m_edit_Land_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 300), CSize(250, 20)), this, 1002);
	
	m_edit_Ansprechpartner_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 60), CSize(250, 20)), this, 1002);
	m_edit_Tel_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 100), CSize(250, 20)), this, 1002);
	m_edit_Fax_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 140), CSize(250, 20)), this, 1002);
	m_edit_Email_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 180), CSize(250, 20)), this, 1002);
	m_edit_IL_Num_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 220), CSize(250, 20)), this, 1002);
	m_edit_Steuer_AG.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(610, 260), CSize(250, 20)), this, 1002);

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
	CEdit* editControls[] = {
	& m_edit_Name1_AG,
	& m_edit_Name2_AG,
	& m_edit_Name3_AG,
	& m_edit_Srasse_AG,
	& m_edit_PLZ_AG,
	& m_edit_Ort_AG,
	& m_edit_Land_AG,
	& m_edit_Ansprechpartner_AG,
	& m_edit_Tel_AG,
	& m_edit_Fax_AG,
	& m_edit_Email_AG,
	& m_edit_IL_Num_AG,
	& m_edit_Steuer_AG,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
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
