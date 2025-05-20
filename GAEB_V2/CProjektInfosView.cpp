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
	m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font

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
