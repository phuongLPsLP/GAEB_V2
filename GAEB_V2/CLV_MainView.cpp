// CLV_MainView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLV_MainView.h"


// CLV_MainView

IMPLEMENT_DYNCREATE(CLV_MainView, CView)

CLV_MainView::CLV_MainView()
{

}

CLV_MainView::~CLV_MainView()
{
}

BEGIN_MESSAGE_MAP(CLV_MainView, CView)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_CONTROL(BN_CLICKED, 1101, &CLV_MainView::OnBnClickedToggleGAEBInfo)
	ON_CONTROL(BN_CLICKED, 1102, &CLV_MainView::OnBnClickedToggleProjektInfo)
	ON_CONTROL(BN_CLICKED, 1103, &CLV_MainView::OnBnClickedToggleVergabenfo)
	ON_CONTROL(BN_CLICKED, 1104, &CLV_MainView::OnBnClickedToggleLVInfo)
	ON_CONTROL(BN_CLICKED, 1105, &CLV_MainView::OnBnClickedToggleRegelungInfo)
	ON_CONTROL(BN_CLICKED, 1106, &CLV_MainView::OnBnClickedToggleLeistungsverzeichnis)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CLV_MainView drawing

void CLV_MainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}
void CLV_MainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CRect clientRect;
	CSize textSize;
	GetClientRect(&clientRect);
	CClientDC dc(this);	

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 18; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_italic;
	::ZeroMemory(&lf_italic, sizeof(LOGFONT));
	lf_italic.lfHeight = 18; // Font height
	lf_italic.lfWeight = FW_NORMAL;
	lf_italic.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_italic.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_italic.CreateFontIndirect(&lf_italic);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18; // Font height
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfUnderline = TRUE; // Italic
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_underline.CreateFontIndirect(&lf_underline);

	LOGFONT lf_button_font;
	::ZeroMemory(&lf_button_font, sizeof(LOGFONT));
	lf_button_font.lfHeight = 20; // Font height
	lf_button_font.lfWeight = FW_BOLD;
	lf_button_font.lfUnderline = TRUE; // Underline
	_tcscpy_s(lf_button_font.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_button.CreateFontIndirect(&lf_button_font);


	m_button_info_gaeb.Create(_T("Informationen zum GAEB Datenaustausch"), WS_CHILD | WS_VISIBLE |  BS_OWNERDRAW | BS_LEFT ,
		CRect(CPoint(20,20), CSize(clientRect.Width(), 50)), this, 1101);
	m_button_info_projekt.Create(_T("Informationen zum Projekt"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT ,
		CRect(CPoint(), CSize()), this, 1102);
	m_button_info_vergabe.Create(_T("Informationen zur Vergabe"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT ,
		CRect(CPoint(), CSize()), this, 1103);
	m_button_info_LV.Create(_T("Informationen zum LV"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT ,
		CRect(CPoint(), CSize()), this, 1104);
	m_button_info_regelung.Create(_T("Informationen zu vertraglichen Regelungen"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(), CSize()), this, 1105);
	m_button_LV.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT, 
		CRect(CPoint(), CSize()), this, 1106);

	rapidxml::file<> xmlFile("07_GAEB.X83");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<>* root = doc.first_node(); // Root = GAEB

	m_staticText_Version.Create(_T("Version:"), WS_CHILD |WS_VISIBLE,
		CRect(CPoint(20, 90), CSize(120, 20)), this, 1001);
	m_staticText_Ausgabejahr.Create(_T("Ausgabejahr der Regelung:"), WS_CHILD |WS_VISIBLE,
		CRect(CPoint(20, 110), CSize(250, 20)), this, 1001);
	m_staticText_Erstellungdatum.Create(_T("Erstellungsdatum der Datei:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 130), CSize(250, 20)), this, 1001);
	m_staticText_Erstellungszeit.Create(_T("Erstellungszeit der Datei:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 150), CSize(250, 20)), this, 1001);
	m_staticText_Programm.Create(_T("Programmsystem:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 170), CSize(250, 20)), this, 1001);
	m_staticText_Umsetzprogramm.Create(_T("Umsetzprogramm:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 190), CSize(250, 20)), this, 1001);

	m_staticText_Name.Create(_T("Name:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 270), CSize(120, 20)), this, 1001);
	m_staticText_Bezeichnung.Create(_T("Bezeichnung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 290), CSize(120, 20)), this, 1001);
	m_staticText_Kurzbeschreibung.Create(_T("Kurzbeschreibung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 310), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung.Create(_T("Währung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 330), CSize(120, 20)), this, 1001);
	m_staticText_WaehrungBez.Create(_T("Bezeichnung der Währung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 350), CSize(250, 20)), this, 1001);


	int yPos_GaebInfo = 90;  // Starting y position for controls
	int yPos_ProjInfo = 270;
	xml_node<>* GAEBInfo = root->first_node();	//firstChild = GAEBInfo, 

	//GEAB Info
	for (xml_node<>* SubChild = GAEBInfo->first_node(); SubChild; SubChild = SubChild->next_sibling())
	{
		//CString subChildValue(SubChild->name());		
		CString subChildText(SubChild->value());
		CStatic* pstaticValue = new CStatic();
		pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE, 
			CRect(CPoint(270, yPos_GaebInfo), CSize(clientRect.Width(), 20)), this, 1001);
		m_vecStatics.push_back(pstaticValue);  // store pointer
		yPos_GaebInfo += 20;
		pstaticValue->SetFont(&m_font);
	}
	xml_node<>* PrjInfo = GAEBInfo->next_sibling();	//nextsiblings = PrjInfo

	for (xml_node<>* SubChild = PrjInfo->first_node(); SubChild; SubChild = SubChild->next_sibling())
	{
		CString subChildText(SubChild->value());
		CStatic* pstaticValue = new CStatic();
		pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE, 
			CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
		//m_vecStatics.push_back(pstaticValue);  // store pointer
		yPos_ProjInfo += 20;
		pstaticValue->SetFont(&m_font);
	}


	CStatic* editControls_static[] = {
	&m_staticText_Version,
	&m_staticText_Ausgabejahr,
	&m_staticText_Erstellungdatum,
	&m_staticText_Erstellungszeit,
	&m_staticText_Programm,
	&m_staticText_Umsetzprogramm,
	&m_staticText_Name,
	&m_staticText_Bezeichnung,
	&m_staticText_Kurzbeschreibung,
	&m_staticText_Waehrung,
	&m_staticText_WaehrungBez,
	};
	for (CStatic* pStatic : editControls_static)
	{
		if (pStatic->GetSafeHwnd())
		{
			pStatic->SetFont(&m_font);

		}
	}

	CButton* editControls[] = {
		&m_button_info_gaeb,
		&m_button_info_projekt,
		&m_button_info_vergabe,
		&m_button_info_regelung,
		&m_button_info_LV,
		&m_button_Inhaltverzeichnis
	};
	for (CButton* pButton : editControls)
	{
		if (pButton->GetSafeHwnd())
		{
			pButton->SetFont(&m_font_button);

		}
	}
}

void CLV_MainView::OnBnClickedToggleGAEBInfo()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
	for (auto pStatic : m_vecStatics)
	{
		pStatic->ShowWindow(state);
	}
	m_staticText_Version.ShowWindow(state);
	m_staticText_Ausgabejahr.ShowWindow(state);
	m_staticText_Erstellungdatum.ShowWindow(state);
	m_staticText_Erstellungszeit.ShowWindow(state);
	m_staticText_Programm.ShowWindow(state);
	m_staticText_Umsetzprogramm.ShowWindow(state);
}

void CLV_MainView::OnBnClickedToggleProjektInfo()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
	 m_staticText_Name.ShowWindow(state);
	 m_staticText_Bezeichnung.ShowWindow(state);
	 m_staticText_Kurzbeschreibung.ShowWindow(state);
	 m_staticText_Waehrung.ShowWindow(state);
	 m_staticText_WaehrungBez.ShowWindow(state);
}

void CLV_MainView::OnBnClickedToggleVergabenfo()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
}

void CLV_MainView::OnBnClickedToggleLVInfo()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
}

void CLV_MainView::OnBnClickedToggleRegelungInfo()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
}

void CLV_MainView::OnBnClickedToggleLeistungsverzeichnis()
{
	m_bInfoVisible = !m_bInfoVisible;
	int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
}

#ifdef _DEBUG
void CLV_MainView::AssertValid() const
{
	CView::AssertValid();
}
#ifndef _WIN32_WCE
void CLV_MainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

HBRUSH CLV_MainView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	if (ctrlID == 1003) {
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	return hbr;
}

void CLV_MainView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	// Draw the button text
	CString text;	
	switch (nIDCtl)
	{
	case 1101:
		m_button_info_gaeb.GetWindowText(text);
		break;
	case 1102:
		m_button_info_projekt.GetWindowText(text);
		break;
	case 1103:
		m_button_info_regelung.GetWindowText(text);
		break;
	case 1104:
		m_button_info_vergabe.GetWindowText(text);
		break;
	case 1105:
		m_button_info_LV.GetWindowText(text);
		break;
		// case 1008:
		//     m_button_Inhaltverzeichnis.GetWindowText(text);
		//     break;
	default:
		CView::OnDrawItem(nIDCtl, lpDrawItemStruct);
		return;
	}	
	pDC->FillSolidRect(&rect, RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->DrawText(text, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}

BOOL CLV_MainView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if (m_button_info_gaeb)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
