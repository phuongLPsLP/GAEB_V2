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
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CProjektInfosView drawing

void CProjektInfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CProjektInfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
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


	m_staticText_Name.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(80, 20)), this, 1001);
	m_staticText_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 60), CSize(120, 20)), this, 1001);
	m_staticText_Beschreibung.Create(_T("Beschreibung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 160), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 330), CSize(120, 20)), this, 1001);
	m_staticText_Leistungsbreich.Create(_T("Leistungsbereich"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 370), CSize(120, 20)), this, 1001);

	m_edit_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 20), CSize(120, 20)), this, 1002);
	m_edit_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 60), CSize(250, 80)), this, 1002);
	m_edit_Beschreibung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 160), CSize(250, 150)), this, 1002);
	m_edit_Bez.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 330), CSize(50, 20)), this, 1002);
	m_edit_Waehrung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(270,330), CSize(160, 20)), this, 1002);
	m_edit_Leistungsbreich.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 370), CSize(80, 20)), this, 1002);
	
	m_button_Zusatztext.Create(_T("Zusatztext"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(330, 370), CSize(100, 20)), this, 1003);

	CStatic* staticControls[] =
	{
		&m_staticText_Name,
		&m_staticText_Bezeichnung,
		&m_staticText_Beschreibung,
		&m_staticText_Waehrung,
		&m_staticText_Leistungsbreich,
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}
	CEdit* editControls[] = {
	&m_edit_Name,
	&m_edit_Bezeichnung,
	&m_edit_Beschreibung,
	&m_edit_Waehrung,
	&m_edit_Bez,
	&m_edit_Leistungsbreich,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
	}
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
#endif
#endif //_DEBUG


// CProjektInfosView message handlers

HBRUSH CProjektInfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
