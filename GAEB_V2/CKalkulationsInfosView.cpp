// CKalkulationsInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CKalkulationsInfosView.h"


// CKalkulationsInfosView

IMPLEMENT_DYNCREATE(CKalkulationsInfosView, CView)

CKalkulationsInfosView::CKalkulationsInfosView()
{

}

CKalkulationsInfosView::~CKalkulationsInfosView()
{
}

BEGIN_MESSAGE_MAP(CKalkulationsInfosView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CKalkulationsInfosView drawing

void CKalkulationsInfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CKalkulationsInfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
	m_groupbox_LV_Summe = new CButton();
	m_groupbox_LV_Summe->Create(_T("Adressdaten"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 20), CSize(90, 100)), this, 1003);
	m_groupbox_LV_Summe->SetFont(&m_font);
	m_groupbox_Bez_EP_Anteil = new CButton();
	m_groupbox_Bez_EP_Anteil->Create(_T("Adressdaten"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(70, 70), CSize(920, 320)), this, 1003);
	m_groupbox_Bez_EP_Anteil->SetFont(&m_font);




	CStatic* staticControls[] = {
	&m_staticText_Anzahl_LVInfos,
	&m_staticText_LV_Summe_Net,
	&m_staticText_Nachlass,
	&m_staticText_Pauschal,
	&m_staticText_Zwischensumme,
	&m_staticText_USt_Anteil,
	&m_staticText_Brutto_Summe,
	&m_staticText_EP_Anteil_1,
	&m_staticText_EP_Anteil_2,
	&m_staticText_EP_Anteil_3,
	&m_staticText_EP_Anteil_4,
	&m_staticText_EP_Anteil_5,
	&m_staticText_EP_Anteil_6,
	&m_staticText_Skontosatz_Anteil,
	&m_staticText_Skonto_Tage,
	&m_staticText_Zeit_Anteil,
	&m_staticText_Ausführungszeit,
	&m_staticText_EP_Nachkomma,
	&m_staticText_Nachlasswert,
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}
}


// CKalkulationsInfosView diagnostics

#ifdef _DEBUG
void CKalkulationsInfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CKalkulationsInfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CKalkulationsInfosView message handlers

HBRUSH CKalkulationsInfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
