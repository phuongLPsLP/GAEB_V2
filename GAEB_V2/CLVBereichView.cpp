// CLVBereichView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLVBereichView.h"


// CLVBereichView

IMPLEMENT_DYNCREATE(CLVBereichView, CView)

CLVBereichView::CLVBereichView()
{

}

CLVBereichView::~CLVBereichView()
{
}

BEGIN_MESSAGE_MAP(CLVBereichView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLVBereichView drawing

void CLVBereichView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CLVBereichView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255,255,200));

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

	m_staticText_LV_Bereich.Create(_T("LV-Bereich"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(200, 30)), this, 1001);

	m_staticText_OZ.Create(_T("GAEB-OZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 50), CSize(80, 20)), this, 1001);
	m_staticText_PosArt.Create(_T("Positionsart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 90), CSize(200, 20)), this, 1001);
	m_statticText_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 130), CSize(200, 30)), this, 1001);


	m_edit_oz.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200,50),CSize(120,20)), this, 1002);
	m_combobox_posArt.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		CRect(CPoint(200, 90), CSize(120, 20)), this, 1004);
	m_edit_bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(200,130), CSize(1000,100)), this, 1005);


	m_groupbox_Summe = new CButton();
	m_groupbox_Summe->Create(_T("Summe"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 250), CSize(600, 300)), this, 1006);
	m_groupbox_Summe->SetFont(&m_font);

	m_staticText_Summe.Create(_T("LV-Summe"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 290), CSize(80, 20)), this, 1001);
	m_staticText_Nachlass_Anteil.Create(_T("Nachlass [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 330), CSize(120, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass [Euro]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(350, 330), CSize(120, 20)), this, 1001);
	m_staticText_Summe_nach_Nachlass.Create(_T("Zwischensumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 370), CSize(120, 20)), this, 1001);
	m_staticText_Pauschalsumme.Create(_T("Pauschalsumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 410), CSize(120, 20)), this, 1001);
	m_StaticText_Ust.Create(_T("Umsatzsteuer [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 450), CSize(120, 20)), this, 1001);
	m_staticText_Summe_LV_Bereich.Create(_T("Bruttosumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 490), CSize(120, 20)), this, 1001);

	m_edit_summe.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 290), CSize(120, 20)), this, 1002);
	m_edit_nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 330), CSize(120, 20)), this, 1002);
	m_edit_nachlass_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(490, 330), CSize(120, 20)), this, 1002);
	m_edit_summe_nach_nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 370), CSize(120, 20)), this, 1002);
	m_edit_pauschal.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 410), CSize(120, 20)), this, 1002);
	m_edit_ust.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 450), CSize(120, 20)), this, 1002);
	m_edit_summe_bereich.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(200, 490), CSize(120, 20)), this, 1002);




	CStatic* staticControls_bold[] = {
	&m_staticText_LV_Bereich,
	};

	for (CStatic* pStatic : staticControls_bold)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font_bold);
	}
	CStatic* staticControls_normal[] = {
	&m_staticText_OZ,
	&m_staticText_PosArt,
	&m_statticText_Bezeichnung,
	&m_staticText_Summe,
	&m_staticText_Nachlass_Anteil,
	&m_staticText_Nachlass,
	&m_staticText_Summe_nach_Nachlass,
	&m_staticText_Pauschalsumme,
	&m_StaticText_Ust,
	&m_staticText_Summe_LV_Bereich,
	};

	for (CStatic* pStatic : staticControls_normal)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}


	CEdit* editControls[] = {
	&m_edit_summe,
	&m_edit_nachlass_anteil,
	&m_edit_nachlass,
	&m_edit_summe_nach_nachlass,
	&m_edit_pauschal,
	&m_edit_ust,
	&m_edit_summe_bereich,
	&m_edit_oz,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
	}

	m_edit_bezeichnung.SetFont(&m_font);
}


// CLVBereichView diagnostics

#ifdef _DEBUG
void CLVBereichView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLVBereichView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLVBereichView message handlers

HBRUSH CLVBereichView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	}*/
	//Edit box
	if (ctrlID == 1005)
	{
		pDC->SetBkColor(RGB(255, 255, 180));
		// Return the brush for background color
		return m_brush_edit_bg_color;

	}

	return hbr;
}
