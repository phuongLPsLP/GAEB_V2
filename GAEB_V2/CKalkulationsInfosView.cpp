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
	m_groupbox_Bez_EP_Anteil = new CButton();
	m_groupbox_Bez_EP_Anteil->Create(_T("Bezeichnung der EP-Anteile"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(), CSize()), this, 1003);
	m_groupbox_Bez_EP_Anteil->SetFont(&m_font);
	m_groupbox_2 = new CButton();
	m_groupbox_2->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(), CSize()), this, 1003);
	m_groupbox_2->SetFont(&m_font);
	m_groupbox_3 = new CButton();
	m_groupbox_3->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(), CSize()), this, 1003);
	m_groupbox_3->SetFont(&m_font);



	m_staticText_LV_Name.Create(_T("LV-Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(80, 20)), this, 1001);
	m_staticText_LV_Datum.Create(_T("LV-Datum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(250, 50), CSize(80, 20)), this, 1001);
	m_staticText_LV_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 90), CSize(80, 20)), this, 1001);
	m_staticText_LV_AnzahlPos.Create(_T("Anzahl der Positionen"), WS_CHILD | WS_VISIBLE, CRect(CPoint(530, 50), CSize(190, 20)), this, 1001);

	m_edit_LV_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(150, 50), CSize(80, 20)), this, 1002);
	m_edit_LV_Datum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(350, 50), CSize(80, 20)), this, 1002);
	m_edit_LV_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(150, 90), CSize(700, 20)), this, 1002);
	m_edit_LV_AnzahlPos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(740, 50), CSize(50, 20)), this, 1002);
	m_button_heute_LVInfos.Create(_T("heute"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT,
		CRect(CPoint(450, 50), CSize(50, 20)), this, 1003);

	m_groupbox_LV_Summe = new CButton();
	m_groupbox_LV_Summe->Create(_T("LV-Summen"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(50,130), CSize(400,300)), this, 1003);
	m_groupbox_LV_Summe->SetFont(&m_font);

	m_staticText_LV_Summe_Net.Create(_T("LV-Summe netto"), WS_CHILD | WS_VISIBLE, 
		CRect(CPoint(50, 170), CSize(80, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 210), CSize(80, 20)), this, 1001);
	m_staticText_Pauschal.Create(_T("oder Pauschal"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 250), CSize(80, 20)), this, 1001);
	m_staticText_Zwischensumme.Create(_T("Zwischensumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 290), CSize(80, 20)), this, 1001);
	m_staticText_USt_Anteil.Create(_T("USt-Satz [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 330), CSize(80, 20)), this, 1001);
	m_staticText_Brutto_Summe.Create(_T("Bruttosumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 370), CSize(80, 20)), this, 1001);





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
