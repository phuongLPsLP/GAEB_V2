// CLV_MainView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLV_MainView.h"


// CLV_MainView

IMPLEMENT_DYNCREATE(CLV_MainView, CScrollView)

CLV_MainView::CLV_MainView()
{

}

CLV_MainView::~CLV_MainView()
{
}

BEGIN_MESSAGE_MAP(CLV_MainView, CScrollView)
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
	CScrollView::OnInitialUpdate();
	m_wndSize.cy = 100000;
	SetScrollSizes(MM_TEXT, m_wndSize);

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
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI"));
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_italic;
	::ZeroMemory(&lf_italic, sizeof(LOGFONT));
	lf_italic.lfHeight = 18; // Font height
	lf_italic.lfWeight = FW_NORMAL;
	lf_italic.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_italic.lfFaceName, _T("Segoe UI"));
	m_font_italic.CreateFontIndirect(&lf_italic);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18; // Font height
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfUnderline = TRUE; // Italic
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI")); 
	m_font_underline.CreateFontIndirect(&lf_underline);

	LOGFONT lf_button_font;
	::ZeroMemory(&lf_button_font, sizeof(LOGFONT));
	lf_button_font.lfHeight = 20; // Font height
	lf_button_font.lfWeight = FW_BOLD;
	lf_button_font.lfUnderline = TRUE; // Underline
	_tcscpy_s(lf_button_font.lfFaceName, _T("Segoe UI")); 
	m_font_button.CreateFontIndirect(&lf_button_font);


	m_button_info_gaeb.Create(_T("Informationen zum GAEB Datenaustausch"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1101);
	m_button_info_projekt.Create(_T("Informationen zum Projekt"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(20, 230), CSize(clientRect.Width(), 50)), this, 1102);
	m_button_info_vergabe.Create(_T("Informationen zur Vergabe"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(), CSize()), this, 1103);
	m_button_info_LV.Create(_T("Informationen zum LV"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(), CSize()), this, 1104);
	m_button_info_regelung.Create(_T("Informationen zu vertraglichen Regelungen"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(20,400), CSize(clientRect.Width(), 50)), this, 1105);
	m_button_LV.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | BS_LEFT,
		CRect(CPoint(20, 450), CSize(clientRect.Width(), 50)), this, 1106);

	m_xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");
	m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	m_xmlDoc->parse<0>(m_xmlFile->data());
	rapidxml::xml_node<>* root = m_xmlDoc->first_node();

	m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	m_pProjektInfo = m_pGAEBInfo->next_sibling();
	m_award = m_pProjektInfo->next_sibling();


	/*
	//rapidxml::file<> xmlFile("07_GAEB.X83");
	//rapidxml::xml_document<> doc;
	//doc.parse<0>(xmlFile.data());
	//rapidxml::xml_node<>* root = doc.first_node(); // Root = GAEB
	//xml_node<>* GAEBInfo = root->first_node();	//firstChild = GAEBInfo,
	//xml_node<>* PrjInfo = GAEBInfo->next_sibling();	//nextsiblings = PrjInfo
	*/

	CButton* editControls[] = {
		&m_button_info_gaeb,
		&m_button_info_projekt,
		&m_button_info_vergabe,
		&m_button_info_regelung,
		&m_button_LV,
		//&m_button_info_LV,
	};
	for (CButton* pButton : editControls)
	{
		if (pButton->GetSafeHwnd())
		{
			pButton->SetFont(&m_font_button);
		}
	}

	 m_bInfoVisible = SW_SHOW;
	 m_bInfoVisible_PrjInfo = SW_SHOW;
	 m_bInfoVisible_VergInfo = SW_SHOW;
	 m_bInfoVisible_LVInfo = SW_SHOW;
	 m_bInfoVisible_RegInfo = SW_SHOW;
	 m_bInfoVisible_LV = SW_SHOW;
}

void CLV_MainView::OnBnClickedToggleGAEBInfo()
{
	//int state = m_bInfoVisible ? SW_SHOW : SW_HIDE;
	int state = m_bInfoVisible;
	m_bInfoVisible = !m_bInfoVisible;

	for (auto pStatic : m_vecStatics_GAEBInfo)
	{
		pStatic->ShowWindow(state);
	}
	CStatic* staticControls[] =
	{
	&m_staticText_Version,
	&m_staticText_Ausgabejahr,
	&m_staticText_Erstellungdatum,
	&m_staticText_Erstellungszeit,
	&m_staticText_Programm,
	&m_staticText_Umsetzprogramm,
	&m_staticText_blank,
	};

	if (state == SW_SHOW) {
		for (CStatic* pStatic : staticControls)
		{
			pStatic->DestroyWindow();
		}
		m_staticText_Version.Create(_T("Version:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 90), CSize(120, 20)), this, 1001);
		m_staticText_Ausgabejahr.Create(_T("Ausgabejahr der Regelung:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 110), CSize(250, 20)), this, 1001);
		m_staticText_Erstellungdatum.Create(_T("Erstellungsdatum der Datei:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 130), CSize(250, 20)), this, 1001);
		m_staticText_Erstellungszeit.Create(_T("Erstellungszeit der Datei:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 150), CSize(250, 20)), this, 1001);
		m_staticText_Programm.Create(_T("Programmsystem:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 170), CSize(250, 20)), this, 1001);
		m_staticText_Umsetzprogramm.Create(_T("Umsetzprogramm:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 190), CSize(250, 20)), this, 1001);
		m_staticText_blank.Create(_T(" "), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 210), CSize(250, 20)), this, 1001);

		int yPos_GaebInfo = 90;  // Starting y position for controls
		//GEAB Info
		xml_node<>* SubChild = m_pGAEBInfo->first_node();
		for (SubChild; SubChild; SubChild = SubChild->next_sibling())
		{
			//CString subChildValue(SubChild->name());		
			CString subChildText(SubChild->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_GaebInfo), CSize(clientRect.Width(), 20)), this, 1001);
			m_vecStatics_GAEBInfo.push_back(pstaticValue);  // store pointer
			yPos_GaebInfo += 20;
			pstaticValue->SetFont(&m_font);
		}		
		for (CStatic* pStatic : staticControls)
		{
			pStatic->SetFont(&m_font);
			pStatic->ShowWindow(state);
		}
	}
	else {
		for (CStatic* pStatic : staticControls)
		{
			pStatic->ShowWindow(state);
		}
	}
}

void CLV_MainView::OnBnClickedToggleProjektInfo()
{
	int state = m_bInfoVisible_PrjInfo;
	m_bInfoVisible_PrjInfo = !m_bInfoVisible_PrjInfo;

	for (auto pStatic_PrjInfo : m_vecStatics_Prjnfo)
	{
		pStatic_PrjInfo->ShowWindow(state);
	}

	CStatic* staticControls_PrjInfo[] =
	{
	 &m_staticText_Name,
	 &m_staticText_Bezeichnung,
	 &m_staticText_Kurzbeschreibung,
	 &m_staticText_Waehrung,
	 &m_staticText_WaehrungBez,
	};

	if (state == SW_SHOW) {
		for (CStatic* pStatic_PrjInfo : staticControls_PrjInfo)
		{
			pStatic_PrjInfo->DestroyWindow();
		}
		m_staticText_Name.Create(_T("Name:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 300), CSize(120, 20)), this, 1001);
		m_staticText_Bezeichnung.Create(_T("Bezeichnung:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 320), CSize(120, 20)), this, 1001);
		m_staticText_Kurzbeschreibung.Create(_T("Kurzbeschreibung:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 340), CSize(120, 20)), this, 1001);
		m_staticText_Waehrung.Create(_T("Währung:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 360), CSize(120, 20)), this, 1001);
		m_staticText_WaehrungBez.Create(_T("Bezeichnung der Währung:"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 380), CSize(250, 20)), this, 1001);

		int yPos_ProjInfo = 300;
		for (xml_node<>* SubChild = m_pProjektInfo->first_node(); SubChild; SubChild = SubChild->next_sibling())
		{
			CString subChildText(SubChild->value());
			if (subChildText == "") {
				subChildText = SubChild->first_node()->value();
				CStatic* pstaticValue = new CStatic();
				pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
				m_vecStatics_Prjnfo.push_back(pstaticValue);  // store pointer
				yPos_ProjInfo += 20;
				pstaticValue->SetFont(&m_font);
			}
			else {
				CStatic* pstaticValue = new CStatic();
				pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
				m_vecStatics_Prjnfo.push_back(pstaticValue);  // store pointer
				yPos_ProjInfo += 20;
				pstaticValue->SetFont(&m_font);
			}
		}
		for (CStatic* pStatic : staticControls_PrjInfo)
		{
			pStatic->SetFont(&m_font);
			pStatic->ShowWindow(state);
		}
	}	
	
	else {
		for (CStatic* pStatic_PrjInfo : staticControls_PrjInfo)
		{
			pStatic_PrjInfo->ShowWindow(state);
		}
	}


}

void CLV_MainView::OnBnClickedToggleVergabenfo()
{
	int state = m_bInfoVisible_VergInfo;
	m_bInfoVisible_VergInfo = !m_bInfoVisible_VergInfo;

}

void CLV_MainView::OnBnClickedToggleLVInfo()
{
	int state = m_bInfoVisible_LVInfo;
	m_bInfoVisible_LVInfo = !m_bInfoVisible_LVInfo;

}

void CLV_MainView::OnBnClickedToggleRegelungInfo()
{
	//Add text = Vertragliche regelung
	int state = m_bInfoVisible_RegInfo;
	m_bInfoVisible_RegInfo = !m_bInfoVisible_RegInfo;
	for (auto pStatic_RegInfo : m_vecStatics_RegInfo)
	{
		pStatic_RegInfo->ShowWindow(state);
	}
	if (state == SW_SHOW) {

		int yPos_LV = 480;
		for (xml_node<>* award = m_award->first_node(); award; award = award->next_sibling())
		{
			CString award_text(award->name());
			//awardtext = DP / OWN / AddText
			if (award_text == "AddText")
			{
				for (xml_node<>* addtext_node = award->first_node(); addtext_node; addtext_node = addtext_node->next_sibling())
				{
					//CString addtext_text(addtext_node->name());
					//OutlineAddText / DetailAddText

					for (xml_node<>* p_node = addtext_node->first_node(); p_node; p_node = p_node->next_sibling())
					{
						//CString p_node_text(p_node->name());
						//<p>		
						CStatic* pstaticValue = new CStatic();
						CString Fulltext;
						for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
						{
							CString span_node_text = Utf8ToCString(span_node->value());
							if (!span_node_text.IsEmpty()) {
								Fulltext += span_node_text;
							}
						}
						pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE,
							CRect(CPoint(20, yPos_LV), CSize(clientRect.Width(), 20)), this, 1001);
						m_vecStatics_RegInfo.push_back(pstaticValue);  // store pointer
						yPos_LV += 20;
						pstaticValue->SetFont(&m_font);
					}
				}
			}
		}
		int finalY = yPos_LV;
		SetScrollSizes(MM_TEXT, CSize(1000, finalY + 20));
	}

	else {
	}
}

void CLV_MainView::OnBnClickedToggleLeistungsverzeichnis()
{
	int state = m_bInfoVisible_LV;
	m_bInfoVisible_LV = !m_bInfoVisible_LV;

	for (auto pStatic_LV : m_vecStatics_LV)
	{
		pStatic_LV->ShowWindow(state);
	}
	CStatic* staticControls_LV[] =
	{
	 &m_staticText_OZ,
	 &m_staticText_Menge,
	 &m_staticText_Einheit,
	 &m_staticText_LeiBe,
	 &m_staticText_Einheitpreis,
	 &m_staticText_Gesamtpreis,
	};


	if (state == SW_SHOW) {
		for (CStatic* pStatic_LV : staticControls_LV)
		{
			pStatic_LV->DestroyWindow();
		}
		m_staticText_OZ.Create(_T("Ordnungszahl"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 520), CSize(120, 20)), this, 1001);
		m_staticText_Menge.Create(_T("Menge"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(180, 520), CSize(80, 20)), this, 1001);
		m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(300, 520), CSize(80, 20)), this, 1001);
		m_staticText_LeiBe.Create(_T("Leitungsbeschreibung"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(420, 520), CSize(500, 20)), this, 1001);
		m_staticText_Einheitpreis.Create(_T("Einheitpreis [EUR]"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(960, 520), CSize(120, 20)), this, 1001);
		m_staticText_Gesamtpreis.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(1120, 520), CSize(180, 20)), this, 1001);
			//CRect(420, 520, 50, 10), this, 1002);

		//m_listCtrl.DestroyWindow(); // Destroy the old control
		//m_listCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS,
			//CRect(CPoint(20, 500), CSize(clientRect.Width() - 20, clientRect.Height())), this, 1001);
		 //Enable full row select and grid lines
		/*m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

		m_listCtrl.InsertColumn(1, _T("Ordnungszahl"), LVCFMT_LEFT, 100);
		m_listCtrl.InsertColumn(2, _T("Menge"), LVCFMT_RIGHT, 100);
		m_listCtrl.InsertColumn(3, _T("Einheit"), LVCFMT_RIGHT, 100);
		m_listCtrl.InsertColumn(4, _T("Leistungsbeschreibung"), LVCFMT_LEFT, 1000);
		m_listCtrl.InsertColumn(5, _T("Einheitpreis [EUR]"), LVCFMT_RIGHT, 150);
		m_listCtrl.InsertColumn(6, _T("Gesamtpreis [EUR]"), LVCFMT_RIGHT, 150);
		m_listCtrl.ShowWindow(SW_SHOW); */
		for (CStatic* pStatic_LV : staticControls_LV)
		{
			pStatic_LV->SetFont(&m_font_bold);
			pStatic_LV->ShowWindow(state);
		}

		for (xml_node<>* BoQ_node = m_award->first_node(); BoQ_node; BoQ_node = BoQ_node->next_sibling())
		{
			CString BoQ_node_text(BoQ_node->name());
			//BoQ_node_text = DP / OWN / AddText / BoQ
			if (BoQ_node_text == "BoQ")
			{
				for (xml_node<>* BoQChild_node = BoQ_node->first_node(); BoQChild_node; BoQChild_node = BoQChild_node->next_sibling())
				{// BoQInfo / BoQBody
					CString BoQChild_node_text(BoQChild_node->name());
					if (BoQChild_node_text == "BoQInfo")
					{
						continue;
					}
					else {
						int yPos_LV = 560;					
						xml_node<>* BoQCtgy_node = BoQChild_node->first_node();
						CStatic* pstaticValue = new CStatic();
						int nItem;
						PrintAllIDs(BoQCtgy_node, pstaticValue, yPos_LV);
						//for (BoQCtgy_node; BoQCtgy_node; BoQCtgy_node = BoQCtgy_node->next_sibling())
						//{
							/*	if (Item_node) {								//Itemlist

									xml_node<>* itemlist_parent = Item_node->parent()->parent();
									CString itemlist_parent_attr(itemlist_parent->first_attribute()->value());
									nItem = m_listCtrl.InsertItem(nindex, itemlist_parent_attr);
									CString Item_node_text(Item_node->name());

									//if (Item_node_text == "Itemlist") {
										for (xml_node<>* item_node = Item_node->first_node(); item_node; item_node = item_node->next_sibling())
										{
											nindex++;
											CString item_node_attr_text(item_node->first_attribute()->value());
											 nItem = m_listCtrl.InsertItem(nindex, item_node_attr_text);

											for (xml_node<>* item_child_node = item_node->first_node(); item_child_node; item_child_node = item_child_node->next_sibling()) {
												CString item_child_node_text(item_child_node->name());
												CString item_child_node_value(item_child_node->value());

												if (item_child_node_text == "Qty") {
													m_listCtrl.SetItemText(nItem, 1, item_child_node_value);
												}
												else if (item_child_node_text == "QU") {
													m_listCtrl.SetItemText(nItem, 2, item_child_node_value);
												}
												else if (item_child_node_text == "UP") {
													m_listCtrl.SetItemText(nItem, 4, item_child_node_value);
												}
												else if (item_child_node_text == "IT") {
													m_listCtrl.SetItemText(nItem, 5, item_child_node_value);
												}
												else if (item_child_node_text = "TimeQu") {

												}
												else if (item_child_node_text == "Description") {
													for (xml_node<>* text_node = item_child_node->first_node(); text_node; text_node = text_node->next_sibling()) {
														CString text_node_text(text_node->name());
														if (text_node_text == "DetailTxt") {}
														else if (text_node_text == "OutlineText") {}
													}
												}
											}
										}
									//}
								}
								else {

									AfxMessageBox(_T("not found"));
								}

								//}
					}
				}

			}

			else
			{
				//m_listCtrl.ShowWindow(SW_HIDE);
				m_bInfoVisible_LV = SW_SHOW;
			}*/
					}
				}
			}
		}


	}
	else {
		for (CStatic* pStatic_LV : staticControls_LV)
		{
			pStatic_LV->ShowWindow(state);
		}
	}

}

#ifdef _DEBUG
void CLV_MainView::AssertValid() const
{
	CScrollView::AssertValid();
}
#ifndef _WIN32_WCE
void CLV_MainView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

HBRUSH CLV_MainView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CScrollView::OnCtlColor(pDC, pWnd, nCtlColor);
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
		m_button_info_vergabe.GetWindowText(text);
		break;
	case 1104:
		m_button_info_LV.GetWindowText(text);
		break;
	case 1105:
		m_button_info_regelung.GetWindowText(text);
		break;
	case 1106:
		m_button_LV.GetWindowText(text);
		break;
		// case 1008:
		//     m_button_Inhaltverzeichnis.GetWindowText(text);
		//     break;
	default:
		CScrollView::OnDrawItem(nIDCtl, lpDrawItemStruct);
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
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

CString CLV_MainView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}

bool CLV_MainView::GetDeepestChild(xml_node<>* node, xml_node<>*& last)
{
	if (!node) return false;

	CString nodeName(node->name());
	 if (nodeName == "Itemlist") {
		last = node;
		return true;
	}

	for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
	{
		if (GetDeepestChild(child, last))
			return true;
	}
	return false;
}

//void CLV_MainView::PrintAllIDs(xml_node<>* node, CListCtrl* pList, int& index)
void CLV_MainView::PrintAllIDs(xml_node<>* node, CStatic* cStatic, int& index)
{
	int index_menge;
	for (xml_node<>* ctgyNode = node; ctgyNode; ctgyNode = ctgyNode->next_sibling())
	{
		xml_attribute<>* ID_Attr = ctgyNode->first_attribute("ID");
		//xml_attribute<>* NoPart_Attr = ctgyNode->first_attribute("RNoPart");

		CString id = ID_Attr ? CString(ID_Attr->value()) : _T("");
		//CString rNo = NoPart_Attr ? CString(NoPart_Attr->value()) : _T("");
		//int itemIndex = pList->InsertItem(index++, rNo + _T("."));
		//int nItem = pList->InsertItem(index++, id);
		CStatic* cStatic = new CStatic();

		cStatic->Create(id, WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, index), CSize(120, 20)), this, 1001);
		m_vecStatics_GAEBInfo.push_back(cStatic);
		index += 20;
		cStatic->SetFont(&m_font);

		xml_node<>* bodyNode = ctgyNode->first_node("BoQBody");
		if (bodyNode)
		{
			xml_node<>* itemListNode = bodyNode->first_node("Itemlist");
			if (itemListNode)
			{
				for (xml_node<>* itemNode = itemListNode->first_node("Item"); itemNode; itemNode = itemNode->next_sibling("Item"))
				{
					CString itemId = CString(itemNode->first_attribute("ID")->value());
					CStatic* cStatic = new CStatic();
					cStatic->Create(itemId, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(20, index), CSize(120, 20)), this, 1001);
					m_vecStatics_GAEBInfo.push_back(cStatic);
									
					cStatic->SetFont(&m_font);
					//int row = pList->InsertItem(index++, itemId); 
					for (xml_node<>* child = itemNode->first_node(); child; child = child->next_sibling())
					{
						CString tag(child->name());
						CString val(child->value());
						
						if (tag == "Qty") {
							//pList->SetItemText(row, 1, val); // Menge
							CStatic* cStatic_Qty = new CStatic();
							cStatic_Qty->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
							cStatic_Qty->SetFont(&m_font);
							m_vecStatics_GAEBInfo.push_back(cStatic_Qty);
							//index_menge += 20;
						}
						//	cStatic->SetFont(&m_font);
						else if (tag == "QU") {
							//pList->SetItemText(row, 2, val); // Einheit
							CStatic* cStatic_QU = new CStatic();
							cStatic_QU->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(300, index), CSize(120, 20)), this, 1001);
							cStatic_QU->SetFont(&m_font);
							m_vecStatics_GAEBInfo.push_back(cStatic_QU);
							//index += 20;
						}
						else if (tag == "UP") {
							//pList->SetItemText(row, 4, val); // Einheitpreis
							CStatic* cStatic_UP = new CStatic();
							cStatic_UP->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(960, index), CSize(120, 20)), this, 1001);
							cStatic_UP->SetFont(&m_font);
							m_vecStatics_GAEBInfo.push_back(cStatic_UP);
							//index += 20;
						}
						else if (tag == "IT") {
							//pList->SetItemText(row, 5, val); // Gesamtpreis
							CStatic* cStatic_IT = new CStatic();
							cStatic_IT->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(1120, index), CSize(120, 20)), this, 1001);
							cStatic_IT->SetFont(&m_font);
							m_vecStatics_GAEBInfo.push_back(cStatic_IT);
							//index += 20;
						}
						else if (tag == "Description")
						{
							xml_node<>* complete_txt_node = child->first_node();	//CompleteText
							xml_node<>* detail_txt_node = complete_txt_node->first_node();	//DetailTxt
							xml_node<>* outline_txt_node = complete_txt_node->first_node()->next_sibling();	//OutlineText
							CString Fulltext;

							for (xml_node<>* p_node = detail_txt_node->first_node()->first_node(); p_node; p_node = p_node->next_sibling()) {


								for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
								{
									CString span_node_text = Utf8ToCString(span_node->value());
									//span_node_text.Replace(_T("<br/>"), _T("\r\n"));
									//span_node_text.Replace(_T("<br>"), _T("\r\n"));
									if (!span_node_text.IsEmpty()) {
										Fulltext += span_node_text;
									}
									CStatic* cStatic_text = new CStatic();
									
									CDC* pdc = GetDC();
									CFont* pOldFont = pdc->SelectObject(&m_font);
									CRect textRect(CPoint(420, index), CSize(500,0));
									pdc->DrawText(Fulltext, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);

									pdc->SelectObject(pOldFont);
									ReleaseDC(pdc);

									cStatic_text->Create(Fulltext, WS_CHILD | WS_VISIBLE,
										CRect(420, index, 0, 10), this, 1001);
									m_vecStatics_GAEBInfo.push_back(cStatic_text);
									cStatic_text->SetFont(&m_font);

									//index += 20;
								}
							}
						}
					}
					index += 20;

				}
			}
			else
			{
				// Recurse into nested BoQCtgy (child categories)
				xml_node<>* childCtgy = bodyNode->first_node("BoQCtgy");
				if (childCtgy)
					PrintAllIDs(childCtgy, cStatic, index);
			}
		}
	}
}


void CLV_MainView::GetDeviceScrollSize(int& nMapMode, SIZE & sizeTotal, SIZE & sizePage, SIZE & sizeLine)
		const
{
	
}
