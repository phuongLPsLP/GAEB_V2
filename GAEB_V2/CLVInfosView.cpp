// CKalkulationsInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLVInfosView.h"


// CKalkulationsInfosView

IMPLEMENT_DYNCREATE(CLVInfosView, CView)

CLVInfosView::CLVInfosView()
{

}

CLVInfosView::~CLVInfosView()
{
}

BEGIN_MESSAGE_MAP(CLVInfosView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CKalkulationsInfosView drawing

void CLVInfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	//pDC->MoveTo(30, 250);
	//pDC->LineTo(220, 250);

	//pDC->SelectObject(pOldPen);
}

void CLVInfosView::OnInitialUpdate()
{

	//StaticText 1001
	//Edit 1002
	//Groupbox 1003

	CView::OnInitialUpdate();
	Invalidate();
	UpdateWindow();
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect);
	CClientDC dc(this);

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
	lf_bold.lfHeight = 20; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

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

	/*m_staticText_LV_Name.Create(_T("LV-Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(80, 20)), this, 1001);
	m_staticText_LV_Datum.Create(_T("LV-Datum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(260, 20), CSize(80, 20)), this,1001 );
	m_staticText_LV_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 60), CSize(120, 20)), this, 1001);
	m_staticText_LV_AnzahlPos.Create(_T("Anzahl der Positionen"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 20), CSize(130, 20)), this, 1001);

	m_edit_LV_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 20), CSize(80, 20)), this, 1002);
	m_edit_LV_Datum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(320, 20), CSize(80, 20)), this, 1002);
	m_edit_LV_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 60), CSize(580, 20)), this, 1002);
	m_edit_LV_AnzahlPos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(640, 20), CSize(80, 20)), this, 1002);
	m_button_heute_LVInfos.Create(_T("heute"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_FLAT,
		CRect(CPoint(410, 20), CSize(50, 20)), this, 1003);
	m_button_heute_LVInfos.SetFont(&m_font_button);

	m_groupbox_LV_Summe = new CButton();
	m_groupbox_LV_Summe->Create(_T("LV-Summen"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
		CRect(CPoint(20,100), CSize(220,280)), this, 1006);
	m_groupbox_LV_Summe->SetFont(&m_font);

	m_staticText_LV_Summe_Net.Create(_T("LV-Summe netto"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(30, 140), CSize(80, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 180), CSize(80, 20)), this, 1001);
	m_staticText_Pauschal.Create(_T("oder Pauschal"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 220), CSize(120, 20)), this, 1001);
	m_staticText_Zwischensumme.Create(_T("Zwischensumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 260), CSize(120, 20)), this, 1001);
	m_staticText_USt_Anteil.Create(_T("USt-Satz [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 300), CSize(120, 20)), this, 1001);
	m_staticText_Brutto_Summe.Create(_T("Bruttosumme"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 340), CSize(120, 20)), this, 1001);

	m_edit_LV_Summe_Net.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 140), CSize(80, 20)), this, 1002);
	m_edit_Nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 180), CSize(80, 20)), this, 1002);
	m_edit_Pauschal.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 220), CSize(80, 20)), this, 1002);
	m_edit_Zwischensumme.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 260), CSize(80, 20)), this, 1002);
	m_edit_USt_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(170, 300), CSize(50, 20)), this, 1002);
	m_edit_Brutto_Summe.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(140, 340), CSize(80, 20)), this, 1002);

	m_groupbox_Bez_EP_Anteil = new CButton();
	m_groupbox_Bez_EP_Anteil->Create(_T("Bezeichnung der EP-Anteile"), WS_CHILD|WS_VISIBLE|BS_LEFT |BS_GROUPBOX,
		CRect(CPoint(260,100),CSize(260,280)), this, 1006);
	m_groupbox_Bez_EP_Anteil->SetFont(&m_font);


	m_staticText_Anzahl_LVInfos.Create(_T("Anzahl"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 140), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_1.Create(_T("EP-Anteil 1"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 190), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_2.Create(_T("EP-Anteil 2"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 220), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_3.Create(_T("EP-Anteil 3"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 250), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_4.Create(_T("EP-Anteil 4"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 280), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_5.Create(_T("EP-Anteil 5"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 310), CSize(80, 20)), this, 1001);
	m_staticText_EP_Anteil_6.Create(_T("EP-Anteil 6"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 340), CSize(80, 20)), this, 1001);

	m_comboBox_Anzahl_LVInfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 140), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil1.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 190), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil2.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 220), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil3.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 250), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil4.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 280), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil5.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 310), CSize(120, 20)), this, 1003);
	m_comboBox_EP_Anteil6.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 340), CSize(120, 20)), this, 1003);

	m_button_Gliederung.Create(_T("LV-Gliederung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT |BS_FLAT,
		CRect(CPoint(600, 110), CSize(120, 40)), this, 1003);
	m_button_Gliederung.SetFont(&m_font_button);

	m_groupbox_2 = new CButton();
	m_groupbox_2->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFT | BS_GROUPBOX,
		CRect(CPoint(20, 400), CSize(500, 100)), this, 1003);
	m_groupbox_2->SetFont(&m_font);

	m_staticText_Skontosatz_Anteil.Create(_T("Skontosatz [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 420), CSize(120, 20)), this, 1001);
	m_staticText_Skonto_Tage.Create(_T("Skonto-Tage"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 460), CSize(120, 20)), this, 1001);
	m_staticText_Zeit_Anteil.Create(_T("Zeitanteil"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 420), CSize(80, 20)), this, 1001);
	m_staticText_Ausführungszeit.Create(_T("Ausführungszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 460), CSize(120, 20)), this, 1001);

	m_edit_Skontosatz_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(180, 420), CSize(40, 20)), this, 1002);
	m_edit_Skonto_Tage.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(180, 460), CSize(40, 20)), this, 1002);
	m_comboBox_Zeit_Anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(380, 420), CSize(120, 20)), this, 1003);
	m_edit_Ausführungszeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(380, 460), CSize(120, 20)), this, 1002);


	m_groupbox_3 = new CButton();
	m_groupbox_3->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_LEFT | BS_GROUPBOX,
		CRect(CPoint(20, 520), CSize(500, 60)), this, 1003);
	m_groupbox_3->SetFont(&m_font);

	m_staticText_EP_Nachkomma.Create(_T("EP-Nachkommastellen"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 540), CSize(150, 20)), this, 1001);
	m_staticText_Nachlasswert.Create(_T("Nachlasswert runden"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 540), CSize(150, 20)), this, 1001);

	m_comboBox_EP_Nachkomma.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
		CRect(CPoint(180, 540), CSize(40, 20)), this, 1003);
	m_checkbox_Nachlass.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(CPoint(480,540),CSize(20,20)), this, 1003);

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
	CEdit* editControls[] = {
	&m_edit_LV_Summe_Net,
	&m_edit_Nachlass,
	&m_edit_Pauschal,
	&m_edit_Zwischensumme,
	&m_edit_USt_Anteil,
	&m_edit_Brutto_Summe,
	&m_edit_Skontosatz_Anteil,
	&m_edit_Skonto_Tage,
	&m_edit_Ausführungszeit,
	&m_edit_LV_Name,
	&m_edit_LV_Datum,
	&m_edit_LV_Bezeichnung,
	&m_edit_LV_AnzahlPos,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
	}*/
	CStatic* staticControls[] =
	{
	&m_staticText_Version,
	&m_staticText_Ausgabejahr,
	&m_staticText_Erstellungdatum,
	&m_staticText_Erstellungszeit,
	&m_staticText_Programm,
	&m_staticText_Umsetzprogramm,
	};

	for (CStatic* pStatic : staticControls)
	{
		pStatic->DestroyWindow();
	}

	m_staticText_Title.Create(_T("Informationen zum GAEB Datenaustausch"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_staticText_Title.SetFont(&m_font_bold);

	m_xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");
	m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	m_xmlDoc->parse<0>(m_xmlFile->data());
	rapidxml::xml_node<>* root = m_xmlDoc->first_node();

	m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	m_pProjektInfo = m_pGAEBInfo->next_sibling();
	m_award = m_pProjektInfo->next_sibling();

	for (CStatic* pStatic : staticControls)
	{
		pStatic->DestroyWindow();
	}
	m_staticText_Version.Create(_T("Version:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(120, 20)), this, 1001);
	m_staticText_Ausgabejahr.Create(_T("Ausgabejahr der Regelung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 90), CSize(250, 20)), this, 1001);
	m_staticText_Erstellungdatum.Create(_T("Erstellungsdatum der Datei:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 110), CSize(250, 20)), this, 1001);
	m_staticText_Erstellungszeit.Create(_T("Erstellungszeit der Datei:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 130), CSize(250, 20)), this, 1001);
	m_staticText_Programm.Create(_T("Programmsystem:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 150), CSize(250, 20)), this, 1001);
	m_staticText_Umsetzprogramm.Create(_T("Umsetzprogramm:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 170), CSize(250, 20)), this, 1001);


	int yPos_GaebInfo = 70;  // Starting y position for controls
	//GEAB Info
	xml_node<>* SubChild = m_pGAEBInfo->first_node();
	for (SubChild; SubChild; SubChild = SubChild->next_sibling())
	{
		//CString subChildValue(SubChild->name());		
		CString subChildText(SubChild->value());
		CStatic* pstaticValue = new CStatic();
		pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
			CRect(CPoint(270, yPos_GaebInfo), CSize(clientRect.Width(), 20)), this, 1001);
		yPos_GaebInfo += 20;
		pstaticValue->SetFont(&m_font);
		
		CString cert_text(SubChild->name());
		if (cert_text == "Certific")
		{
			m_staticText_Certificate.Create(_T("Prüfzertifikat:	"), WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, 190), CSize(250, 20)), this, 1001);
			m_staticText_Certificate.SetFont(&m_font);
		}

	}
	for (CStatic* pStatic : staticControls)
	{
		pStatic->SetFont(&m_font);
	}
}


// CKalkulationsInfosView diagnostics

#ifdef _DEBUG
void CLVInfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLVInfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CKalkulationsInfosView message handlers

HBRUSH CLVInfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
