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

	m_groupbox_Ausführung = new CButton();
	m_groupbox_Gewährleistung = new CButton();
	m_groupbox_Burgschaften = new CButton();
	m_groupbox_Ausführung->Create(_T("Voraussichtliche Ausführung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20,260), CSize(900,80)), this, 1006);
	m_groupbox_Ausführung->SetFont(&m_font);
	m_groupbox_Gewährleistung->Create(_T("Gewährleistung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 360), CSize(900, 80)), this, 1006);
	m_groupbox_Gewährleistung->SetFont(&m_font);
	m_groupbox_Burgschaften->Create(_T("Bürgschaften"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20, 460), CSize(900, 80)), this, 1006);
	m_groupbox_Burgschaften->SetFont(&m_font);

	/*m_font_button.CreateFont(
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
	);*/
	

	m_staticText_Vergabeart.Create(_T("Vergabeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung_vergabeinfos.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 60), CSize(120, 20)), this, 1001);
	m_staticText_Angebotsdatum.Create(_T("Angebotsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 100), CSize(120, 20)), this, 1001);
	m_staticText_Abnahmedatum.Create(_T("Abnahmedatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 140), CSize(120, 20)), this, 1001);
	m_staticText_Auftragsdatum.Create(_T("Auftragsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 180), CSize(120, 20)), this, 1001);
	
	m_staticText_Sonderart.Create(_T("Sonderart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 20), CSize(120, 20)), this, 1001);
	m_staticText_Abgabeort.Create(_T("Abgabeort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 60), CSize(120, 20)), this, 1001);
	m_staticText_Angebotszeit.Create(_T("Angebotszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 100), CSize(120, 20)), this,1001);
	m_staticText_Zuschlagsfrist.Create(_T("Zuschlagsfrist"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 140), CSize(120, 20)), this,1001);
	m_staticText_Abnahmeart.Create(_T("Abnahmeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 180), CSize(120, 20)), this,1001);
	m_staticText_Auftragsnummer.Create(_T("Auftragsnummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 220), CSize(120, 20)), this,1001);


	m_combobox_Vergabeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER| ES_MULTILINE | CBS_DROPDOWNLIST, 
		CRect(CPoint(180, 20), CSize(250, 20)), this, 1007);
	m_edit_Waehrung_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(180, 60), CSize(50, 20)), this, 1002);
	m_edit_Bez_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(250, 60), CSize(180, 20)), this, 1002);
	m_edit_Angebotsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(180, 100), CSize(120, 20)), this, 1002);
	m_edit_Abnahmedatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(180, 140), CSize(250, 20)), this, 1002);
	m_edit_Auftragsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(180, 180), CSize(250, 20)), this, 1002);
	
	m_combobox_Sonderart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST, 
		CRect(CPoint(670, 20), CSize(250, 20)), this, 1007);
	m_edit_Abgabeort.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(670, 60), CSize(250, 20)), this, 1002);
	m_edit_Angebotszeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(670, 100), CSize(250, 20)), this, 1002);
	m_edit_Zuschlagsfrist.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(670, 140), CSize(250, 20)), this, 1002);
	m_edit_Abnahmeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(670, 180), CSize(250, 20)), this, 1002);
	m_edit_Auftragsnummer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(670, 220), CSize(250, 20)), this, 1002);

	m_staticText_Beginn.Create(_T("Beginn"), WS_CHILD | WS_VISIBLE , CRect(CPoint(30, 300), CSize(120, 20)), this, 1001);
	m_staticText_End_Ausführung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 300), CSize(120, 20)), this, 1001);

	m_staticText_Dauer.Create(_T("Dauer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 400), CSize(120, 20)), this, 1001);
	m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 400), CSize(80, 20)), this, 1001);
	m_staticText_End_Gewährleistung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 400), CSize(120, 20)), this, 1001);

	m_staticText_Ausführung_Anteil.Create(_T("Ausführung [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 500), CSize(120, 20)), this, 1001);
	m_staticText_Gewährleist.Create(_T("Gewährleist. [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 500), CSize(120, 20)), this, 1001);

	m_edit_beginn.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 300), CSize(250, 20)), this, 1002);
	m_edit_end_ausführung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 300), CSize(250, 20)), this, 1002);
	
	m_edit_dauer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 400), CSize(50, 20)), this, 1002);
	m_edit_einheit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(350, 400), CSize(80, 20)), this, 1002);
	m_edit_ende_gewährleistung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 400), CSize(250, 20)), this, 1002);
	
	m_edit_ausführung_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 500), CSize(250, 20)), this, 1002);
	m_edit_gewährleist_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 500), CSize(250, 20)), this, 1002);

	m_button_heute.Create( _T("heute"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(350,100), CSize(80,20)), this, 1004);
	m_button_Zusatztext.Create(_T("Zusatztext"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(20, 570), CSize(120, 20)), this, 1004);

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

	CEdit* editControls[] = {
	&m_edit_Waehrung_vergabeinfos,
	&m_edit_Bez_vergabeinfos,
	&m_edit_Angebotsdatum,
	&m_edit_Abnahmedatum,
	&m_edit_Auftragsdatum,
	&m_edit_Abgabeort,
	&m_edit_Angebotszeit,
	&m_edit_Zuschlagsfrist,
	&m_edit_Abnahmeart,
	&m_edit_Auftragsnummer,
	&m_edit_beginn,
	&m_edit_end_ausführung,
	&m_edit_dauer,
	&m_edit_einheit,
	&m_edit_ende_gewährleistung,
	&m_edit_ausführung_anteil,
	&m_edit_gewährleist_anteil,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
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
