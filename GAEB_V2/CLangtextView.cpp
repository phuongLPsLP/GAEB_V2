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

    GetClientRect(&clientRect);
    CClientDC dc(this);
	CSize sizeTotal;
	// TODO: calculate the total size of this view
//	sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);

    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    m_Doc = pMainFrame->GetXmlDoc();
    m_Root = pMainFrame->GetRootNode();
    m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
    m_pProjektInfo = pMainFrame->GetProjektInfoNode();
    m_award = pMainFrame->GetAwardNode();

    m_staticText_Title_LV_Langtext.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE,
        CRect(CPoint(20, 20), CSize(clientRect.Width(), 30)), this, 1001);
	m_staticText_Title_LV_Langtext.SetFont(pMainFrame->GetFontBold());

	int state = SW_SHOW;
	CStatic* staticControls_LV_Langtext[] =
	{
	 &m_staticText_OZ_LT,
	 &m_staticText_Menge_LT,
	 &m_staticText_Einheit_LT,
	 &m_staticText_LeiBe_LT,
	 &m_staticText_Einheitpreis_LT,
	 &m_staticText_Gesamtpreis_LT,
	};

	if (state == SW_SHOW) {
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
						int yPos_LV = 100;
						xml_node<>* bodyNode = BoQChild_node; // should be BoQBody
						if (CString(bodyNode->name()) == "BoQBody")
						{
							std::vector<int> rootPath;
							for (xml_node<>* ctgyNode = bodyNode->first_node("BoQCtgy"); ctgyNode; ctgyNode = ctgyNode->next_sibling("BoQCtgy"))
							{
								//PrintAllIDs(ctgyNode, yPos_LV, rootPath);
								TraverseBoQCtgy_LT(ctgyNode, yPos_LV, rootPath);

							}
						}
					}
				}
			}
		}
	}
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

void CLangtextView::PrintAllIDs(xml_node<>* node, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	int count = 0;
	//int yPos_LV = 70;

	for (xml_node<>* ctgyNode = node; ctgyNode; ctgyNode = ctgyNode->next_sibling("BoQCtgy"))
	{
		++count;

		std::vector<int> currentPath = levelPath;
		currentPath.push_back(count);

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


		// Recurse if there are child <BoQCtgy> nodes
		xml_node<>* body = ctgyNode->first_node("BoQBody");
		xml_node<>* total = ctgyNode->first_node("Totals");
		xml_node<>* lbltx = ctgyNode->first_node("LblTx");

		int itemcount = 0;

	/*	if (lbltx) {
			for (xml_node<>* span_node_lbltx = lbltx->first_node(); span_node_lbltx; span_node_lbltx = span_node_lbltx->next_sibling()) {
				CString LblTx_value = Utf8ToCString(span_node_lbltx->value());
				CStatic* static_lbltx = new CStatic();
				static_lbltx->Create(LblTx_value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(180, index), CSize(clientRect.Width(), 20)), this, 1001);
				static_lbltx->SetFont(pMainFrame->GetFontTitle());
				m_vecStatics_GAEBInfo.push_back(static_lbltx);
			}
		}*/
		if (body)
		{
			xml_node<>* itemListNode = body->first_node("Itemlist");
			xml_node<>* child = body->first_node("BoQCtgy");

			index += 20;
			if (itemListNode)
			{
				for (xml_node<>* itemNode = itemListNode->first_node("Item"); itemNode; itemNode = itemNode->next_sibling("Item"))
				{
					++itemcount;
					
					std::vector<int> itemPath = currentPath;
					itemPath.push_back(itemcount);
					CString fullItemPath;
					for (size_t m = 0; m < itemPath.size(); ++m) {
						fullItemPath.AppendFormat(_T("%d"), itemPath[m]);
						if (m < itemPath.size() - 1)
							fullItemPath.Append(_T("."));
					}

					CStatic* static_item = new CStatic();
					static_item->Create(fullItemPath, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(20, index), CSize(120, 20)), this, 1001);
					static_item->SetFont(pMainFrame->GetFont());
					m_vecStatics_GAEBInfo.push_back(static_item);

					for (xml_node<>* child = itemNode->first_node(); child; child = child->next_sibling())
					{
						CString tag(child->name());
						CString val(child->value());

						/*if (tag == "Qty") {
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
						else if (tag == "UP") {	//Einheitpreis
							CStatic* cStatic_UP = new CStatic();
							cStatic_UP->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(960, index), CSize(120, 20)), this, 1001);
							cStatic_UP->SetFont(pMainFrame->GetFont());
							m_vecStatics_GAEBInfo.push_back(cStatic_UP);
						}
						else if (tag == "IT") {	//Gesamtpreis
							CStatic* cStatic_IT = new CStatic();
							cStatic_IT->Create(val, WS_CHILD | WS_VISIBLE,
								CRect(CPoint(1120, index), CSize(120, 20)), this, 1001);
							cStatic_IT->SetFont(pMainFrame->GetFont());
							m_vecStatics_GAEBInfo.push_back(cStatic_IT);
						}
						else if (tag == "TimeQu") {}*/
						if (tag == "Description")
						{
							xml_node<>* complete_txt_node = child->first_node();	//CompleteText
							CString Fulltext_lang;

							for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
							{
								CString compl_text_name(compl_text->name());
								//Langtext
								if (compl_text_name == "DetailTxt") {
									for (xml_node<>* DetailTxt_Text = compl_text->first_node(); DetailTxt_Text; DetailTxt_Text = DetailTxt_Text->next_sibling()) //Text
									{
										CString DetailTxt_Text_name(DetailTxt_Text->name());
										if( DetailTxt_Text_name == "Text") {
											for (xml_node<>* p_node = DetailTxt_Text->first_node(); p_node; p_node = p_node->next_sibling())
											{
												//CString p_node_text(p_node->name());
												//<p>		
												CStatic* pstaticValue = new CStatic();
												CString Fulltext;
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
													/*CString span_node_text = Utf8ToCString(span_node->value());
													if (!span_node_text.IsEmpty()) {
														Fulltext += span_node_text;
													}*/
												}

												CRect textRect(420, 90, clientRect.Width() - 40, 0); // start with 0 height

												CClientDC dc(this);
												CFont* pOldFont = dc.SelectObject(pMainFrame->GetFont());
												dc.DrawText(Fulltext, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);
												dc.SelectObject(pOldFont);

												textRect.OffsetRect(20, yPos_LV); // apply margins

												pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX, textRect,
													this,
													1001);
												//CRect(CPoint(20, yPos_LV), CSize(clientRect_VR.Width(), yPos_LV+100)), this, 1001);
											//m_vecStatics_RegInfo.push_back(pstaticValue);  // store pointer
												yPos_LV += textRect.Height() + 20;
												index = yPos_LV;
												pstaticValue->SetFont(pMainFrame->GetFont());
											}
										}
									}
								}
							}
						}
					}
					//index += 20; // Increment index for next item
				}
			}
			if (child)
				PrintAllIDs(child, index, currentPath);
		}

	}

	int finalY = yPos_LV;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect.Width(), finalY + 20));
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

	xml_node<>* bodyNode = ctgyNode->first_node("BoQBody");

	for (xml_node<>* bodyNode = ctgyNode->first_node("BoQBody"); bodyNode; bodyNode = bodyNode->next_sibling("BoQBody")) {
		ctgyCount++;
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
				TraverseItemlist_LT(itemList, index, currentPath);
			// Recurse into nested categories
			for (xml_node<>* subCtgy = bodyNode->first_node("BoQCtgy"); subCtgy; subCtgy = subCtgy->next_sibling("BoQCtgy"))
			{
				TraverseBoQCtgy_LT(subCtgy, index, currentPath);
			}
		}
	}

	int finalY = index;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect.Width(), finalY + 20));
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

			CString tag(child->name());
			CString val(Utf8ToCString(child->value()));

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
				xml_node<>* complete_txt_node = child->first_node();	//CompleteText
				CString Fulltext_lang;

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
									//CString p_node_text(p_node->name());
									//<p>		
									CStatic* pstaticValue = new CStatic();
									CString Fulltext;
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
										/*CString span_node_text = Utf8ToCString(span_node->value());
										if (!span_node_text.IsEmpty()) {
											Fulltext += span_node_text;
										}*/
									}

									CRect textRect(420, 90, clientRect.Width() - 40, 0); // start with 0 height

									CClientDC dc(this);
									CFont* pOldFont = dc.SelectObject(pMainFrame->GetFont());
									dc.DrawText(Fulltext, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);
									dc.SelectObject(pOldFont);

									textRect.OffsetRect(20, yPos_LV); // apply margins

									pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX, textRect,
										this,
										1001);
									//CRect(CPoint(20, yPos_LV), CSize(clientRect_VR.Width(), yPos_LV+100)), this, 1001);
								//m_vecStatics_RegInfo.push_back(pstaticValue);  // store pointer
									yPos_LV += textRect.Height() + 20;
									index = yPos_LV;
									pstaticValue->SetFont(pMainFrame->GetFont());
									index_item = index;
								}
							}
						}
					}
				}
			}
		}

		index += 100;
	}
}
