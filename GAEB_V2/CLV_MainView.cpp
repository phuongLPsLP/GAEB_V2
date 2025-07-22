// CLV_MainView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLV_MainView.h"
#include "MainFrm.h"


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
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CLV_MainView drawing

void CLV_MainView::OnDraw(CDC* pDC)
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
void CLV_MainView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	//m_wndSize.cy = 100000;
//	SetScrollSizes(MM_TEXT, m_wndSize);

	CSize textSize;
	GetClientRect(&clientRect);
	CClientDC dc(this);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	m_staticText_Title.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_staticText_Title.SetFont(pMainFrame->GetFontBold());


	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	OnBnClickedToggleLeistungsverzeichnis();
}

void CLV_MainView::OnBnClickedToggleLeistungsverzeichnis()
{
	int state = SW_SHOW;
	CStatic* staticControls_LV[] =
	{
	 &m_staticText_OZ,
	 &m_staticText_Menge,
	 &m_staticText_Einheit,
	 &m_staticText_LeiBe,
	 &m_staticText_Einheitpreis,
	 &m_staticText_Gesamtpreis,
	};

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	for (CStatic* pStatic_LV : staticControls_LV)
	{
		pStatic_LV->DestroyWindow();
	}
	m_staticText_OZ.Create(_T("Ordnungszahl"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(120, 20)), this, 1001);
	m_staticText_Menge.Create(_T("Menge"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(180, 70), CSize(80, 20)), this, 1001);
	m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(300, 70), CSize(80, 20)), this, 1001);
	m_staticText_LeiBe.Create(_T("Leitungsbeschreibung"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(420, 70), CSize(700, 20)), this, 1001);
	m_staticText_Einheitpreis.Create(_T("Einheitpreis [EUR]"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(1160, 70), CSize(120, 20)), this, 1001);
	m_staticText_Gesamtpreis.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(1320, 70), CSize(180, 20)), this, 1001);

	for (CStatic* pStatic_LV : staticControls_LV)
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
							PrintAllIDsRecursive(ctgyNode, yPos_LV, rootPath);
						}
					}
				}
			}
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


CString CLV_MainView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}


void CLV_MainView::PrintAllIDsRecursive(xml_node<>* node, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	int count = 0;
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

		if (lbltx) {
			for (xml_node<>* span_node_lbltx = lbltx->first_node(); span_node_lbltx; span_node_lbltx = span_node_lbltx->next_sibling()) {
				CString LblTx_value = Utf8ToCString(span_node_lbltx->value());
				CStatic* static_lbltx = new CStatic();
				static_lbltx->Create(LblTx_value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(180, index), CSize(clientRect.Width(), 20)), this, 1001);
				static_lbltx->SetFont(pMainFrame->GetFontTitle());
				m_vecStatics_GAEBInfo.push_back(static_lbltx);
			}
		}
		index += 20;
		if (body)
		{
			xml_node<>* itemListNode = body->first_node("Itemlist");
			xml_node<>* child = body->first_node("BoQCtgy");

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
						else if (tag == "TimeQu"){}
						else if (tag == "Description")
						{
							xml_node<>* complete_txt_node = child->first_node();	//CompleteText
							CString Fulltext_lang;
							CString Fulltext_kurz;

							for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
							{
								CString compl_text_name(compl_text->name());

								//Langtext
								if (compl_text_name == "DetailTxt") {
									
								}
								//Kurztext
								else if (compl_text_name == "OutlineText") {
									for (xml_node<>* OutlTxt = compl_text->first_node(); OutlTxt; OutlTxt = OutlTxt->next_sibling()) //Text
									{
										for (xml_node<>* TextOutlTxt = OutlTxt->first_node(); TextOutlTxt; TextOutlTxt = TextOutlTxt->next_sibling()) //p
										{
											for (xml_node<>* p_node_kurztext = TextOutlTxt->first_node(); p_node_kurztext; p_node_kurztext = p_node_kurztext->next_sibling())	//span
											{
												for (xml_node<>* span_node_kurztext = p_node_kurztext->first_node(); span_node_kurztext; span_node_kurztext = span_node_kurztext->next_sibling())	//span
												{
													CString span_node_kurztext_text = Utf8ToCString(span_node_kurztext->value());
													//span_node_text.Replace(_T("<br/>"), _T("\r\n"));
													//span_node_text.Replace(_T("<br>"), _T("\r\n"));
													if (!span_node_kurztext_text.IsEmpty()) {
														Fulltext_kurz += span_node_kurztext_text;
													}
													CStatic* cStatic_kurztext = new CStatic();
													cStatic_kurztext->Create(Fulltext_kurz, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
														CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
													cStatic_kurztext->SetFont(pMainFrame->GetFont());
													m_vecStatics_GAEBInfo.push_back(cStatic_kurztext);
													//index += 20;
												}
											}
										}
									}
								}
								else if (compl_text_name == "ComplTSA") { continue; }
								else if (compl_text_name == "ComplTSB") { continue; }
							}
						}
					}
					index += 20; // Increment index for next item
				}
			}		
			if (child)
				PrintAllIDsRecursive(child, index, currentPath);
		}

	}

	int finalY = index;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect.Width(), finalY + 20));
}

void CLV_MainView::GetDeviceScrollSize(int& nMapMode, SIZE & sizeTotal, SIZE & sizePage, SIZE & sizeLine)
		const
{	
}
