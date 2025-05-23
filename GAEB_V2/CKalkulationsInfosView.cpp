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

	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(70, 280);
	pDC->LineTo(330, 280);

	pDC->SelectObject(pOldPen);
}

void CKalkulationsInfosView::OnInitialUpdate()
{

	//StaticText 1001
	//Edit 1002
	//Groupbox 1003
	
	CView::OnInitialUpdate();
	Invalidate();
	UpdateWindow();
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

	m_font_button.CreateFont(
		18,                        // Height
		0,                         // Width
		0,                         // Escapement
		0,                         // Orientation
		FW_NORMAL,                  // Weight
		FALSE,                    // Italic
		FALSE,                    // Underline
		0,                        // StrikeOut
		ANSI_CHARSET,             // Charset
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, // Pitch and Family
		_T("Segoe UI")            // Font name
	);

	m_staticText_LV_Name.Create(_T("LV-Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(80, 20)), this, 1001);
	m_staticText_LV_Datum.Create(_T("LV-Datum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(300, 50), CSize(80, 20)), this,1001 );
	m_staticText_LV_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 90), CSize(100, 20)), this, 1001);
	m_staticText_LV_AnzahlPos.Create(_T("Anzahl der Positionen"), WS_CHILD | WS_VISIBLE, CRect(CPoint(600, 50), CSize(150, 20)), this, 1001);

	m_edit_LV_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(150, 50), CSize(80, 20)), this, 1002);
	m_edit_LV_Datum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(400, 50), CSize(80, 20)), this, 1002);
	m_edit_LV_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(150, 90), CSize(700, 20)), this, 1002);
	m_edit_LV_AnzahlPos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(770, 50), CSize(80, 20)), this, 1002);
	m_button_heute_LVInfos.Create(_T("heute"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_FLAT,
		CRect(CPoint(500, 50), CSize(50, 20)), this, 1003);
	m_button_heute_LVInfos.SetFont(&m_font_button);

	m_groupbox_LV_Summe = new CButton();
	m_groupbox_LV_Summe->Create(_T("LV-Summen"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(50,130), CSize(300,280)), this, 1003);
	m_groupbox_LV_Summe->SetFont(&m_font);

	m_staticText_LV_Summe_Net.Create(_T("LV-Summe netto"), WS_CHILD | WS_VISIBLE, 
		CRect(CPoint(70, 170), CSize(80, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 210), CSize(80, 20)), this, 1001);
	m_staticText_Pauschal.Create(_T("oder Pauschal"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 250), CSize(120, 20)), this, 1001);
	m_staticText_Zwischensumme.Create(_T("Zwischensumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 290), CSize(120, 20)), this, 1001);
	m_staticText_USt_Anteil.Create(_T("USt-Satz [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 330), CSize(120, 20)), this, 1001);
	m_staticText_Brutto_Summe.Create(_T("Bruttosumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 370), CSize(120, 20)), this, 1001);

	m_edit_LV_Summe_Net.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(250, 170), CSize(80, 20)), this, 1002);
	m_edit_Nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(250, 210), CSize(80, 20)), this, 1002);
	m_edit_Pauschal.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(250, 250), CSize(80, 20)), this, 1002);
	m_edit_Zwischensumme.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(250, 290), CSize(80, 20)), this, 1002);
	m_edit_USt_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(290, 330), CSize(40, 20)), this, 1002);
	m_edit_Brutto_Summe.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(250, 370), CSize(80, 20)), this, 1002);

	m_groupbox_Bez_EP_Anteil = new CButton();
	m_groupbox_Bez_EP_Anteil->Create(_T("Bezeichnung der EP-Anteile"), WS_CHILD|WS_VISIBLE|BS_LEFT |BS_GROUPBOX,
		CRect(CPoint(370,130),CSize(300,280)), this, 1003);
	m_groupbox_Bez_EP_Anteil->SetFont(&m_font);


	m_staticText_Anzahl_LVInfos.Create(_T("Anzahl"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 170), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_1.Create(_T("EP-Anteil 1"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 220), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_2.Create(_T("EP-Anteil 2"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 250), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_3.Create(_T("EP-Anteil 3"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 280), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_4.Create(_T("EP-Anteil 4"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 310), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_5.Create(_T("EP-Anteil 5"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 340), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_6.Create(_T("EP-Anteil 6"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 370), CSize(80, 20)), this, 1001);

	m_comboBox_Anzahl_LVInfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST, 
		CRect(CPoint(530, 170), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil1.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 220), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil2.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 250), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil3.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 280), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil4.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 310), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil5.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 340), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil6.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 370), CSize(120, 20)), this, 1003);

	m_button_Gliederung.Create(_T("LV-Gliederung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT |BS_FLAT,
		CRect(CPoint(690, 140), CSize(120, 40)), this, 1003);
	m_button_Gliederung.SetFont(&m_font_button);

	m_groupbox_2 = new CButton();
	m_groupbox_2->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFT | BS_GROUPBOX,
		CRect(CPoint(50, 430), CSize(620, 100)), this, 1003);
	m_groupbox_2->SetFont(&m_font);

	m_staticText_Skontosatz_Anteil.Create(_T("Skontosatz [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 450), CSize(120, 20)), this, 1001);
	m_staticText_Skonto_Tage.Create(_T("Skonto-Tage"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 490), CSize(120, 20)), this, 1001);
	m_staticText_Zeit_Anteil.Create(_T("Zeitanteil"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 450), CSize(80, 20)), this, 1001);
	m_staticText_Ausführungszeit.Create(_T("Ausführungszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 490), CSize(120, 20)), this, 1001);

	m_edit_Skontosatz_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(290, 450), CSize(40, 20)), this, 1002);
	m_edit_Skonto_Tage.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(290, 490), CSize(40, 20)), this, 1002);
	m_comboBox_Zeit_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(530, 450), CSize(120, 20)), this, 1003);
	m_edit_Ausführungszeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(530, 490), CSize(120, 20)), this, 1002);


	m_groupbox_3 = new CButton();
	m_groupbox_3->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFT | BS_GROUPBOX,
		CRect(CPoint(50, 550), CSize(620, 70)), this, 1003);
	m_groupbox_3->SetFont(&m_font);

	m_staticText_EP_Nachkomma.Create(_T("EP-Nachkommastellen"), WS_CHILD | WS_VISIBLE, CRect(CPoint(70, 570), CSize(150, 20)), this, 1001);
	m_staticText_Nachlasswert.Create(_T("Nachlasswert runden"), WS_CHILD | WS_VISIBLE, CRect(CPoint(390, 570), CSize(150, 20)), this, 1001);

	m_comboBox_EP_Nachkomma.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(290, 570), CSize(40, 20)), this, 1003);
	m_checkbox_Nachlass.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(CPoint(630,570),CSize(20,20)), this, 1003);

	CStatic* staticControls[] = {
	&m_staticText_LV_Name,
	&m_staticText_LV_Datum,
	&m_staticText_LV_Bezeichnung,
	&m_staticText_LV_AnzahlPos,
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
