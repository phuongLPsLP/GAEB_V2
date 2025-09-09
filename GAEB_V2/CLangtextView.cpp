// CLangtextView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLangtextView.h"
#include "MainFrm.h"


// CLangtextView

IMPLEMENT_DYNCREATE(CLangtextView, CScrollView)

CLangtextView::CLangtextView()
{

}

CLangtextView::~CLangtextView()
{
}


BEGIN_MESSAGE_MAP(CLangtextView, CScrollView)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLangtextView drawing


void CLangtextView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	int maxBottom = 0;

	GetClientRect(&clientRect);
	CClientDC dc(this);

	CSize sizeTotal;
	sizeTotal.cx = 2000;     
	sizeTotal.cy = 50000;   
	SetScrollSizes(MM_TEXT, sizeTotal);

	int yPos_LV = 100;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	m_staticText_Title_LV_Langtext.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 30)), this, 1001);
	m_staticText_Title_LV_Langtext.SetFont(pMainFrame->GetFontBold());

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();


	CStatic* staticControls_LV_Langtext[] =
	{
	 &m_staticText_OZ_LT,
	 &m_staticText_Menge_LT,
	 &m_staticText_Einheit_LT,
	 &m_staticText_LeiBe_LT,
	 &m_staticText_Einheitpreis_LT,
	 &m_staticText_Gesamtpreis_LT,
	};

	for (CStatic* pStatic_LV_LT : staticControls_LV_Langtext)
	{
		pStatic_LV_LT->DestroyWindow();
	}
	m_staticText_OZ_LT.Create(_T("Ordnungszahl"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(120, 20)), this, 1001);
	m_staticText_Menge_LT.Create(_T("Menge"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(180, 70), CSize(80, 20)), this, 1001);
	m_staticText_Einheit_LT.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(300, 70), CSize(80, 20)), this, 1001);
	m_staticText_LeiBe_LT.Create(_T("Leitungsbeschreibung"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(420, 70), CSize(700, 20)), this, 1001);
	m_staticText_Einheitpreis_LT.Create(_T("Einheitpreis [EUR]"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(1160, 70), CSize(120, 20)), this, 1001);
	m_staticText_Gesamtpreis_LT.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(1320, 70), CSize(180, 20)), this, 1001);

	for (CStatic* pStatic_LV : staticControls_LV_Langtext)
	{
		pStatic_LV->SetFont(pMainFrame->GetFontBold());
		//pStatic_LV->ShowWindow(state);
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
					xml_node<>* bodyNode = BoQChild_node; // should be BoQBody
					if (CString(bodyNode->name()) == "BoQBody")
					{
						std::vector<int> rootPath;
						for (xml_node<>* ctgyNode = bodyNode->first_node("BoQCtgy"); ctgyNode; ctgyNode = ctgyNode->next_sibling("BoQCtgy")) {
							TraverseBoQCtgy_LT(ctgyNode, yPos_LV,rootPath);
						}			
					}
				}
			}
		}
	}
	CRect clientRect;
	GetClientRect(&clientRect);
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect.Width(), yPos_LV));

}

void CLangtextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
    CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    if (!pFrame) return;

    // Use title font
    CFont* pTitleFont = pFrame->GetFontTitle();
    CFont* pOldFont = pDC->SelectObject(pTitleFont);
    pDC->SelectObject(pOldFont);

    CFont* pFont = pFrame->GetFont();
    pOldFont = pDC->SelectObject(pFont);
    pDC->SelectObject(pOldFont);

    CFont* pBold = pFrame->GetFontBold();
    pOldFont = pDC->SelectObject(pBold);
    pDC->SelectObject(pOldFont);

    CFont* pItalic = pFrame->GetFontItalic();
    pOldFont = pDC->SelectObject(pItalic);
    pDC->SelectObject(pOldFont);

    CFont* pUnderline = pFrame->GetFontUnderline();
    pOldFont = pDC->SelectObject(pUnderline);
    pDC->SelectObject(pOldFont);
}


// CLangtextView diagnostics

#ifdef _DEBUG
void CLangtextView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CLangtextView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLangtextView message handlers

HBRUSH CLangtextView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CScrollView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	return hbr;
}

CString CLangtextView::Utf8ToCString(const char* utf8Str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
    CString result;
    MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
    result.ReleaseBuffer();
    return result;
}

void CLangtextView::TraverseBoQCtgy_LT(xml_node<>* ctgyNode, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int ctgyCount = 0;
	if (auto* attr = ctgyNode->first_attribute("RNoPart"))
		ctgyCount = atoi(attr->value());
	std::vector<int> currentPath = levelPath;
	currentPath.push_back(ctgyCount);

	// Format like "1.2.3"
	CString formattedPath;
	for (size_t i = 0; i < currentPath.size(); ++i)
	{
		formattedPath.AppendFormat(_T("%d"), currentPath[i]);
		if (i < currentPath.size() - 1)
			formattedPath.Append(_T("."));
	}

	CStatic* staticCtrl = new CStatic();
	staticCtrl->Create(formattedPath, WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, index), CSize(120, 20)), this, 1001);
	staticCtrl->SetFont(pMainFrame->GetFont());
	m_vecStatics_GAEBInfo.push_back(staticCtrl);

	xml_node<>* bodyNode = ctgyNode->first_node("BoQBody");
	if (bodyNode)
	{

		// LblTx (optional)
		xml_node<>* lblTx = ctgyNode->first_node("LblTx");
		if (lblTx) {
			CString lblText;
			for (xml_node<>* span = lblTx->first_node(); span; span = span->next_sibling()) {
				lblText += Utf8ToCString(span->value());
			}
			CStatic* static_lbl = new CStatic();
			static_lbl->Create(lblText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(180, index), CSize(500, 20)), this, 1001);
			static_lbl->SetFont(pMainFrame->GetFontTitle());
			m_vecStatics_GAEBInfo.push_back(static_lbl);

			index += 20;
		}

		// Traverse items if any
		xml_node<>* itemList = bodyNode->first_node("Itemlist");
		if (itemList)
		{
			TraverseItemlist_LT(itemList, index, currentPath);
		}
		// Recurse into nested categories
		for (xml_node<>* subCtgy = bodyNode->first_node("BoQCtgy"); subCtgy; subCtgy = subCtgy->next_sibling("BoQCtgy"))
		{
			TraverseBoQCtgy_LT(subCtgy, index, currentPath);
		}
	}
}

void CLangtextView::TraverseItemlist_LT(xml_node<>* itemList, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int itemCount = 0;
	for (xml_node<>* item = itemList->first_node("Item"); item; item = item->next_sibling("Item"))
	{
		itemCount++;
		std::vector<int> currentPath_item = levelPath;
		currentPath_item.push_back(itemCount);

		// Format like "1.2.3"
		CString formattedPath_item;
		for (size_t i = 0; i < currentPath_item.size(); ++i)
		{
			formattedPath_item.AppendFormat(_T("%d"), currentPath_item[i]);
			if (i < currentPath_item.size() - 1)
				formattedPath_item.Append(_T("."));
		}

		CStatic* staticCtrl_item = new CStatic();
		staticCtrl_item->Create(formattedPath_item, WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, index), CSize(120, 20)), this, 1001);
		staticCtrl_item->SetFont(pMainFrame->GetFont());
		m_vecStatics_GAEBInfo.push_back(staticCtrl_item);
		
		// Iterate over item's children
		for (xml_node<>* child = item->first_node(); child; child = child->next_sibling())
		{
			xml_node<>* complete_txt_node = child->first_node();
			CString Fulltext;

			CString tag(child->name());
			CString val(Utf8ToCString(child->value()));

			CString idValue;
			if (auto* idAttr = item->first_attribute("ID"))
			{
				idValue = Utf8ToCString(idAttr->value());
			}			

			if (tag == "Qty") {
				CStatic* cStatic_Qty = new CStatic();
				cStatic_Qty->Create(val, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
				cStatic_Qty->SetFont(pMainFrame->GetFont());
				m_vecStatics_GAEBInfo.push_back(cStatic_Qty);
			}
			else if (tag == "QU") {
				CStatic* cStatic_QU = new CStatic();
				cStatic_QU->Create(val, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(300, index), CSize(120, 20)), this, 1001);
				cStatic_QU->SetFont(pMainFrame->GetFont());
				m_vecStatics_GAEBInfo.push_back(cStatic_QU);
			}
			else if (tag == "UP") {
				CStatic* cStatic_UP = new CStatic();
				cStatic_UP->Create(val, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(960, index), CSize(120, 20)), this, 1001);
				cStatic_UP->SetFont(pMainFrame->GetFont());
				m_vecStatics_GAEBInfo.push_back(cStatic_UP);
			}
			else if (tag == "IT") {
				CStatic* cStatic_IT = new CStatic();
				cStatic_IT->Create(val, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(1120, index), CSize(120, 20)), this, 1001);
				cStatic_IT->SetFont(pMainFrame->GetFont());
				m_vecStatics_GAEBInfo.push_back(cStatic_IT);
			}
			else if (tag == "Description")
			{
				
				for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
				{
					CString compl_text_name(compl_text->name());
					//Langtext
					if (compl_text_name == "DetailTxt") {
						for (xml_node<>* DetailTxt_Text = compl_text->first_node(); DetailTxt_Text; DetailTxt_Text = DetailTxt_Text->next_sibling()) //Text
						{
							CString DetailTxt_Text_name(DetailTxt_Text->name());
							if (DetailTxt_Text_name == "Text") {
								for (xml_node<>* p_node = DetailTxt_Text->first_node(); p_node; p_node = p_node->next_sibling())
								{
									for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
									{
										CString nodeName(span_node->name());

										if (nodeName.CompareNoCase(_T("br")) == 0)
										{
											Fulltext += _T("\r\n");
										}
										else if (nodeName.CompareNoCase(_T("span")) == 0)
										{
											CString spanText = Utf8ToCString(span_node->value());
											Fulltext += spanText;
										}
									}

								}
							}
						}
					}
				}
				CRect client_Rect;
				GetClientRect(&client_Rect);
				CRect textRect(420, index, client_Rect.Width() - 50, index);

				CClientDC dc(this);
				CFont* pOldFont = dc.SelectObject(pMainFrame->GetFont());
				dc.DrawText(Fulltext, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);

				CStatic* pstaticValue = new CStatic();
				pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_EDITCONTROL,
					textRect, this, 1001);

				TRACE(_T("Description-Block: index=%d -> id=%s  height=%d \n"),
					index, idValue, textRect.Height());

				pstaticValue->SetFont(pMainFrame->GetFont());
				m_vecStatics_GAEBInfo.push_back(pstaticValue);
				//index = static_cast<int>(textRect.bottom) + 10;
				index = index + textRect.Height() + 10;
				dc.SelectObject(pOldFont);
			}		

		}
	}
	
	CStatic* cStatic_test = new CStatic();
	cStatic_test->Create(_T("test"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(420, 42000), CSize(120, 20)), this, 1001);
	cStatic_test->SetFont(pMainFrame->GetFont());
}
