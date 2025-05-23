// CVergabeinfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVergabeinfosView.h"


// CVergabeinfosView

IMPLEMENT_DYNCREATE(CVergabeinfosView, CView)

CVergabeinfosView::CVergabeinfosView()
{

}

CVergabeinfosView::~CVergabeinfosView()
{
}

BEGIN_MESSAGE_MAP(CVergabeinfosView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CVergabeinfosView drawing

void CVergabeinfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CVergabeinfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
	m_groupbox_Ausführung = new CButton();
	m_groupbox_Gewährleistung = new CButton();
	m_groupbox_Burgschaften = new CButton();
	m_groupbox_Ausführung->Create(_T("Voraussichtliche Ausführung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20,300), CSize(1000,80)), this, 1003);
	m_groupbox_Ausführung->SetFont(&m_font);
	m_groupbox_Gewährleistung->Create(_T("Gewährleistung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 400), CSize(1000, 80)), this, 1003);
	m_groupbox_Gewährleistung->SetFont(&m_font);
	m_groupbox_Burgschaften->Create(_T("Bürgschaften"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 500), CSize(1000, 80)), this, 1003);
	m_groupbox_Burgschaften->SetFont(&m_font);

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
	

	m_staticText_Vergabeart.Create(_T("Vergabeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 50), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung_vergabeinfos.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 90), CSize(120, 20)), this, 1001);
	m_staticText_Angebotsdatum.Create(_T("Angebotsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 130), CSize(120, 20)), this, 1001);
	m_staticText_Abnahmedatum.Create(_T("Abnahmedatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 170), CSize(120, 20)), this, 1001);
	m_staticText_Auftragsdatum.Create(_T("Auftragsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 210), CSize(120, 20)), this, 1001);
	m_staticText_Sonderart.Create(_T("Sonderart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(120, 20)), this, 1001);
	m_staticText_Abgabeort.Create(_T("Abgabeort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(120, 20)), this, 1001);
	m_staticText_Angebotszeit.Create(_T("Angebotszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 130), CSize(120, 20)), this,1001);
	m_staticText_Zuschlagsfrist.Create(_T("Zuschlagsfrist"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 170), CSize(120, 20)), this,1001);
	m_staticText_Abnahmeart.Create(_T("Abnahmeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 210), CSize(120, 20)), this,1001);
	m_staticText_Auftragsnummer.Create(_T("Auftragsnummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 250), CSize(120, 20)), this,1001);


	m_combobox_Vergabeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER| ES_MULTILINE | CBS_DROPDOWNLIST, CRect(CPoint(200, 50), CSize(200, 20)), this, 1002);
	m_edit_Waehrung_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 90), CSize(50, 20)), this, 1002);
	m_edit_Bez_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(280, 90), CSize(120, 20)), this, 1002);
	m_edit_Angebotsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 130), CSize(100, 20)), this, 1002);
	m_edit_Abnahmedatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 170), CSize(200, 20)), this, 1002);
	m_edit_Auftragsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 210), CSize(200, 20)), this, 1002);
	m_combobox_Sonderart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST, CRect(CPoint(650, 50), CSize(200, 20)), this, 1002);
	m_edit_Abgabeort.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 90), CSize(200, 20)), this, 1002);
	m_edit_Angebotszeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 130), CSize(200, 20)), this, 1002);
	m_edit_Zuschlagsfrist.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 170), CSize(200, 20)), this, 1002);
	m_edit_Abnahmeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 210), CSize(200, 20)), this, 1002);
	m_edit_Auftragsnummer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 250), CSize(200, 20)), this, 1002);

	m_staticText_Beginn.Create(_T("Beginn"), WS_CHILD | WS_VISIBLE , CRect(CPoint(50, 340), CSize(120, 20)), this, 1001);
	m_staticText_End_Ausführung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 340), CSize(200, 20)), this, 1001);
	m_staticText_Dauer.Create(_T("Dauer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 440), CSize(200, 20)), this, 1001);
	m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 440), CSize(50, 20)), this, 1001);
	m_staticText_End_Gewährleistung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 440), CSize(200, 20)), this, 1001);
	m_staticText_Ausführung_Anteil.Create(_T("Ausführung [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(50, 540), CSize(200, 20)), this, 1001);
	m_staticText_Gewährleist.Create(_T("Gewährleist. [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 540), CSize(200, 20)), this, 1001);

	m_edit_beginn.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 340), CSize(200, 20)), this, 1002);
	m_edit_end_ausführung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 340), CSize(200, 20)), this, 1002);
	m_edit_dauer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 440), CSize(50, 20)), this, 1002);
	m_edit_einheit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(340, 440), CSize(60, 20)), this, 1002);
	m_edit_ende_gewährleistung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 440), CSize(200, 20)), this, 1002);
	m_edit_ausführung_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(200, 540), CSize(200, 20)), this, 1002);
	m_edit_gewährleist_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(650, 540), CSize(200, 20)), this, 1002);

	m_button_heute.Create( _T("heute"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(330,130), CSize(70,20)), this, 1004);
	m_button_Zusatztext.Create(_T("Zusatztext"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(50, 610), CSize(100, 30)), this, 1004);

	m_button_heute.SetFont(&m_font_button);
	m_button_Zusatztext.SetFont(&m_font_button);

	CStatic* staticControls[] = {
	&m_staticText_Vergabeart,
	&m_staticText_Waehrung_vergabeinfos,
	&m_staticText_Angebotsdatum,
	&m_staticText_Abnahmedatum,
	&m_staticText_Auftragsdatum,
	&m_staticText_Sonderart,
	&m_staticText_Abgabeort,
	&m_staticText_Angebotszeit,
	&m_staticText_Zuschlagsfrist,
	&m_staticText_Abnahmeart,
	&m_staticText_Auftragsnummer,
	&m_staticText_Beginn,
	&m_staticText_End_Ausführung,
	&m_staticText_Dauer,
	&m_staticText_Einheit,
	&m_staticText_End_Gewährleistung,
	&m_staticText_Ausführung_Anteil,
	&m_staticText_Gewährleist,
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}

}


// CVergabeinfosView diagnostics

#ifdef _DEBUG
void CVergabeinfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVergabeinfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVergabeinfosView message handlers

HBRUSH CVergabeinfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
