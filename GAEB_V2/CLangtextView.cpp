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

static double ParseGermanDouble(CString s);
static CString GetField(const CString& line, int start, int len);
static CString FormatGaebNumber(double value, int decimals);
static CString NormalizeOZ(CString s);
static CString FormatOZByParent(const CString& parentRawOZ, const CString& parentFormattedOZ, const CString& childRawOZ);
static CString WrapText(CDC* pdc, CString text, int maxWidth);


void CLangtextView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	int maxBottom = 0;	

	/*CSize sizeTotal;
	sizeTotal.cx = 2000;
	sizeTotal.cy = 50000;*/

	SetScrollSizes(MM_TEXT, m_wndSize);
	CSize textSize;
	GetClientRect(&clientRect);
	CClientDC dc(this);

	int yPos_LV = 100;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_format = pMainFrame->GetFormat();

	m_staticText_Title_LV_Langtext.Create(_T("Leistungsverzeichnis"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 30)), this, 1001);
	m_staticText_Title_LV_Langtext.SetFont(pMainFrame->GetFontBold());

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	x_pos_leitung = 20;

	if (*m_format == "90"){}
	else if (*m_format == "2000") {
		if (!m_listCreated)
		{
			CRect rc; GetClientRect(&rc);

			// unterhalb deiner Überschrift starten (z.B. ab y=70)
			CRect rcList(20, 70, rc.right - 20, rc.bottom - 20);
			m_list_LV.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
				rcList, this, 9001);

			m_list_LV.SetExtendedStyle(LVS_EX_FULLROWSELECT);

			m_list_LV.InsertColumn(0, _T("Ordnungszahl"), LVCFMT_LEFT, 120);
			m_list_LV.InsertColumn(1, _T("Menge"), LVCFMT_RIGHT, 80);
			m_list_LV.InsertColumn(2, _T("Einheit"), LVCFMT_LEFT, 80);
			m_list_LV.InsertColumn(3, _T("Leistungsbeschreibung"), LVCFMT_LEFT, 700);
			m_list_LV.InsertColumn(4, _T("Einheitpreis [EUR]"), LVCFMT_RIGHT, 180);
			m_list_LV.InsertColumn(5, _T("Gesamtpreis [EUR]"), LVCFMT_RIGHT, 180);

			m_list_LV.SetFont(pMainFrame->GetFont());
			CHeaderCtrl* pHeader = m_list_LV.GetHeaderCtrl();
			pHeader->SetFont(pMainFrame->GetFontBold());

			m_listCreated = true;
		}
		else
		{
			m_list_LV.DeleteAllItems();
		}

		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();
		bool inLVBereich = false;
		bool inPosition = false;

		std::vector<LVBereich> lvStack;
		std::vector<LVPosition> positions;
		std::vector<LVBeschreibung> beschreibung;

		LVBereich currentLV{};
		LVPosition currentPos{};
		LVBeschreibung currentBesch{};

		bool readingLangtext = false;
		CString textBuffer;

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		auto StartTextBlock = [&](const CString& line, const CString& tag, bool& readingFlag)
			{
				readingFlag = true;
				textBuffer.Empty();
				CString startTag = _T("[") + tag + _T("]");
				int p1 = line.Find(startTag);
				if (p1 < 0) 
					return;
				p1 += startTag.GetLength();
				int p2 = line.Find(_T("end]"), p1);

				if (p2 >= 0) {
					textBuffer = line.Mid(p1, p2 - p1);
					readingFlag = false;
					CString text = textBuffer;
					text.Trim();
				}
				else {
					CString rest = line.Mid(p1);
					rest.Trim();
					if (!rest.IsEmpty())
						textBuffer += rest + _T("\r\n");
				}
				
			};

		for (const auto& raw : lines) 
		{
			CString line = raw;
			line.Trim();			

			if (readingLangtext) {
				if (line.Find(_T("[end]")) >= 0) {
					int p = line.Find(_T("[end]"));
					textBuffer += line.Left(p);

					CString text = textBuffer;
					text.Replace(_T("\\par"), _T(""));
					text.Replace(_T("\\line"), _T("\r\n"));
					text.Replace(_T("{"), _T(""));
					text.Replace(_T("}"), _T(""));
					text.Trim();

					int plain = text.Find(_T("\\plain"));
					if (plain >= 0) {
						text = text.Mid(plain + 6);
						text.Trim();
					}

					currentPos.pos_langtext = text;
					readingLangtext = false;
					textBuffer.Empty();
				}
				else {
					textBuffer += line + _T("\r\n");
				}
				continue;
			}

			if (line.IsEmpty()) {
				continue;
			}
			if (line.CompareNoCase(_T("#begin[LVBereich]")) == 0)
			{
				currentLV = LVBereich{};
				inLVBereich = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[LVBereich]")) == 0)
			{
				if (!lvStack.empty())
					lvStack.pop_back();

				inLVBereich = false;
				continue;
			}
			if (line.CompareNoCase(_T("#begin[Position]")) == 0)
			{
				currentPos = LVPosition{};
				currentPos.path = lvStack;
				inPosition = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[Position]")) == 0)
			{
				positions.push_back(currentPos);
				inPosition = false;
				continue;
			}
			if (line.CompareNoCase(_T("#begin[Hinweis]")) == 0)
			{

			}
			if (line.CompareNoCase(_T("#end[Hinweis]")) == 0)
			{
			}

			if(line.Find(_T("[Langtext]")) >= 0)
			{
				int p1 = line.Find(_T("[Langtext]")) + CString(_T("[Langtext]")).GetLength();
				int p2 = line.Find(_T("[end]"), p1);

				if (p2 >= 0) {
					CString text = line.Mid(p1, p2 - p1);
					text.Trim();
					currentPos.pos_langtext = text;
				}
				else {
					readingLangtext = true;
					textBuffer.Empty();
					CString rest = line.Mid(p1);
					rest.Trim();
					if(!rest.IsEmpty())
						textBuffer += rest + _T("\r\n");
				}
				continue;
			}	
			CString key, value;
			if (!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (inLVBereich && !inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0) 
				{
					value.Trim();
					currentLV.ber_oz = value;

					if(lvStack.empty())
						currentLV.ber_oz_formatted = value;
					else
						currentLV.ber_oz_formatted = FormatOZByParent(lvStack.back().ber_oz, 
							lvStack.back().ber_oz_formatted, value);
					lvStack.push_back(currentLV);
				}
				else if (key.CompareNoCase(_T("BezTx")) == 0) 
				{
					if(!lvStack.empty())
						lvStack.back().ber_langtext = value;
					else 
						currentLV.ber_langtext = value;
				}

				else if (key.CompareNoCase(_T("Bez")) == 0) 
				{
					if(!lvStack.empty())
						lvStack.back().ber_langtext = value;
					else
						currentLV.ber_langtext = value;
				}
				continue;
			}
			if (inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0) {
					value.Trim();
					currentPos.pos_oz = value;
					if (!lvStack.empty())
					{
						currentPos.pos_oz = FormatOZByParent(
							lvStack.back().ber_oz,
							lvStack.back().ber_oz_formatted,
							value
						);
					}
				}
				else if (key.CompareNoCase(_T("Menge")) == 0) currentPos.pos_menge = value;
				else if (key.CompareNoCase(_T("ME")) == 0) currentPos.pos_einheit = value;
				else if (key.CompareNoCase(_T("EP")) == 0) currentPos.pos_einheitpreis = value;
				else if (key.CompareNoCase(_T("GP")) == 0) currentPos.pos_gesamtpreis = value;
				else if (key.CompareNoCase(_T("Langtext")) == 0) currentPos.pos_langtext = value;
				else if (key.CompareNoCase(_T("BezTx")) == 0) currentPos.pos_kurztext = value;
				continue;
			}
		}

		CFont* pFont = pMainFrame->GetFont();
		int id = 3000;
		for (auto& p : positions) 
		{
			double menge = ParseGermanDouble(p.pos_menge);
			double ep = ParseGermanDouble(p.pos_einheitpreis);
			if(menge >0 && ep > 0) {
				CString gesamt;
				gesamt.Format(_T("%.2f"), menge * ep);
				p.pos_gesamtpreis = gesamt;
			}
		}

		std::set<CString> printedLv;
		auto AddListRow = [&](const CString& oz, const CString& menge, const CString& me, const CString& text,
			const CString& ep, const CString& gp) 
			{
				int i = m_list_LV.InsertItem(m_list_LV.GetItemCount(), oz );
				m_list_LV.SetItemText(i, 1, menge);
				m_list_LV.SetItemText(i, 2, me);
				m_list_LV.SetItemText(i, 3, text);
				m_list_LV.SetItemText(i, 4, ep);
				m_list_LV.SetItemText(i, 5, gp);
			};

		for (const auto& pos : positions) 
		{
			for (const auto& lv : pos.path)
			{
				CString oz = lv.ber_oz_formatted;
				if (printedLv.insert(oz).second) {
					AddListRow(oz, _T(""), _T(""), lv.ber_langtext, _T(""), _T(""));
				}
			}

			AddListRow(pos.pos_oz,
				pos.pos_menge,
				pos.pos_einheit,
				pos.pos_langtext,
				pos.pos_einheitpreis,
				pos.pos_gesamtpreis);
		}		
	}
	else if (*m_format == "XML") {
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
			CRect(CPoint(1250, 70), CSize(180, 20)), this, 1001);
		m_staticText_Gesamtpreis_LT.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(1450, 70), CSize(180, 20)), this, 1001);

		for (CStatic* pStatic_LV : staticControls_LV_Langtext)
		{
			pStatic_LV->SetFont(pMainFrame->GetFontBold());
			//pStatic_LV->ShowWindow(state);
		}

		for (xml_node<>* BoQ_node = m_award->first_node(); BoQ_node; BoQ_node = BoQ_node->next_sibling())
		{
			CString BoQ_node_text(BoQ_node->name());
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
						xml_node<>* bodyNode = BoQChild_node;
						if (CString(bodyNode->name()) == "BoQBody")
						{
							xml_node<>* remark_node = bodyNode->first_node("Remark");
							CString Fulltext_remark;
							if (remark_node)
							{
								for (xml_node<>* desc_node = remark_node->first_node("Description"); desc_node; desc_node = desc_node->next_sibling("Description"))
								{
									for (xml_node<>* compl_node = desc_node->first_node("CompleteText"); compl_node; compl_node = compl_node->next_sibling("CompleteText"))
									{
										for (xml_node<>* detailtext_node = compl_node->first_node("DetailTxt"); detailtext_node; detailtext_node = detailtext_node->next_sibling("DetailTxt"))
										{
											for (xml_node<>* text_node = detailtext_node->first_node("Text"); text_node; text_node = text_node->next_sibling("Text"))
											{
												for (xml_node<>* p_node = text_node->first_node(); p_node; p_node = p_node->next_sibling())
												{
													for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
													{
														CString nodeValue = Utf8ToCString(span_node->value());
														CString nodeName(span_node->name());
														if (nodeName.CompareNoCase(_T("br")) == 0) {
															Fulltext_remark += _T("\r\n");
														}
														else if (nodeName.CompareNoCase(_T("span")) == 0) {
															Fulltext_remark += nodeValue + _T(" ");
														}

													}
													Fulltext_remark += _T("\r\n");

												}
											}
										}
									}
								}

							}
							std::vector<int> rootPath;
							for (xml_node<>* ctgyNode = bodyNode->first_node("BoQCtgy"); ctgyNode; ctgyNode = ctgyNode->next_sibling("BoQCtgy")) {
								TraverseBoQCtgy_LT(ctgyNode, yPos_LV, rootPath);
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

	for (xml_node<>* ctgy_childNode = ctgyNode->first_node(); ctgy_childNode; ctgy_childNode = ctgy_childNode->next_sibling())
	{
		CString ctgy_child_name(ctgy_childNode->name());

		if (ctgy_child_name == "BoQBody")
		{

			//LblTx
			xml_node<>* lblTx = ctgyNode->first_node("LblTx");
			if (lblTx) {
				CString lblText;
				for (xml_node<>* span = lblTx->first_node(); span; span = span->next_sibling()) {
					CString node_name(span->name());
					if (node_name == "p") {
						for (xml_node<>* p_node = span->first_node(); p_node; p_node = p_node->next_sibling()) {
							CString spantext = Utf8ToCString(p_node->value());
							lblText += spantext;
						}
					}
					else if (node_name == "span") {
						lblText += Utf8ToCString(span->value());
					}
				}
				CRect lbltx_clienrect;
				GetClientRect(&lbltx_clienrect);
				CRect lbltx_textrect(180, index, lbltx_clienrect.Width() - 200, index);

				CClientDC dc_lbltx(this);
				dc_lbltx.DrawText(lblText, &lbltx_textrect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);

				CStatic* static_lbl = new CStatic();
				static_lbl->Create(lblText, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_EDITCONTROL,
					CRect(CPoint(180, index), CSize(500, 20)), this, 1001);
				static_lbl->SetFont(pMainFrame->GetFontTitle());
				m_vecStatics_GAEBInfo.push_back(static_lbl);
				index += 20;
			}

			//Remark
			xml_node<>* remark = ctgy_childNode->first_node("Remark");
			if (remark) {
				TraverseRemark_LT(remark, index);
			}


			// Traverse items if any
			xml_node<>* itemList = ctgy_childNode->first_node("Itemlist");
			if (itemList)
			{
				index += 20;
				TraverseItemlist_LT(itemList, index, currentPath);
			}

			// Recurse into nested categories
			for (xml_node<>* subCtgy = ctgy_childNode->first_node("BoQCtgy"); subCtgy; subCtgy = subCtgy->next_sibling("BoQCtgy"))
			{
				index += 20;
				TraverseBoQCtgy_LT(subCtgy, index, currentPath);
			}
		}
		else if (ctgy_child_name == "Totals")
		{
			if (ctgy_childNode->first_node() != nullptr) {
				for (xml_node<>* totals_node = ctgy_childNode->first_node(); totals_node; totals_node = totals_node->next_sibling())
				{
					CString totals_name(totals_node->name());
					if (totals_name == "Total") {
						CString val_total = Utf8ToCString(totals_node->value());
					}
					else if (totals_name == "DiscountPcnt") {
						CString val_discont = Utf8ToCString(totals_node->value());
					}
					else if(totals_name == "TotAfterDisc") {
						CString val_total_aft_discnt = Utf8ToCString(totals_node->value());
					}
				}
			}
		}
	}
}

void CLangtextView::TraverseItemlist_LT(xml_node<>* itemList, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int itemCount = 0;
	for (xml_node<>* item = itemList->first_node(); item; item = item->next_sibling())
	{
		CString item_name(item->name());
		if (item_name == "Item") {
			itemCount++;

			CString formattedPath_item;
			xml_attribute<>* rnopart_attr = item->first_attribute("RNoPart");
			CString rnopart_value(rnopart_attr->value());

			std::vector<int> currentPath_item = levelPath;
			currentPath_item.push_back(_ttoi(rnopart_value));

			// Format like "1.2.3"
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

			xml_node<>* descr_node = item->first_node("Description");
			if (descr_node) {
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
							CRect(CPoint(1250, index), CSize(120, 20)), this, 1001);
						cStatic_UP->SetFont(pMainFrame->GetFont());
						m_vecStatics_GAEBInfo.push_back(cStatic_UP);
					}
					else if (tag == "IT") {
						CStatic* cStatic_IT = new CStatic();
						cStatic_IT->Create(val, WS_CHILD | WS_VISIBLE,
							CRect(CPoint(1450, index), CSize(120, 20)), this, 1001);
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
													Fulltext += spanText + _T(" ");
												}
											}

										}
									}
								}
							}
						}
						CRect client_Rect;
						GetClientRect(&client_Rect);
						CRect textRect(420, index, client_Rect.Width() - 500, index);

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
				index += 20;
			}
			else {
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
							CRect(CPoint(1250, index), CSize(120, 20)), this, 1001);
						cStatic_UP->SetFont(pMainFrame->GetFont());
						m_vecStatics_GAEBInfo.push_back(cStatic_UP);
					}
					else if (tag == "IT") {
						CStatic* cStatic_IT = new CStatic();
						cStatic_IT->Create(val, WS_CHILD | WS_VISIBLE,
							CRect(CPoint(1450, index), CSize(120, 20)), this, 1001);
						cStatic_IT->SetFont(pMainFrame->GetFont());
						m_vecStatics_GAEBInfo.push_back(cStatic_IT);
					}
					index += 20;
				}
			}
		}
		else if (item_name == "Remark")
		{
			TraverseRemark_LT(item, index);
		}
	}
}

void CLangtextView::TraverseRemark_LT(xml_node<>* remarknode, int& index)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString remark_Fulltext_LT;
	xml_node<>* descr_node_LT = remarknode->first_node();

	CStatic* cstatic_hinweis_LT = new CStatic();
	cstatic_hinweis_LT->Create(_T("Hinweis"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
	cstatic_hinweis_LT->SetFont(pMainFrame->GetFontItalic());
	m_vecStatics_GAEBInfo.push_back(cstatic_hinweis_LT);

	xml_node<>* descr_node = remarknode->first_node();
	if (descr_node == nullptr) {
		index += 20;
		return;
	}
	else {
		for (xml_node<>* descr_childNode = descr_node_LT->first_node(); descr_childNode; descr_childNode = descr_childNode->next_sibling())
		{
			CString desct_childNode_name(descr_childNode->name());

			if (desct_childNode_name == "CompleteText") {
				for (xml_node<>* detailtext_node = descr_childNode->first_node("DetailTxt"); detailtext_node; detailtext_node = detailtext_node->next_sibling("DetailTxt")) {
					for (xml_node<>* text_node = detailtext_node->first_node("Text"); text_node; text_node = text_node->next_sibling("Text")) {
						for (xml_node<>* p_node = text_node->first_node(); p_node; p_node = p_node->next_sibling())
						{
							for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
							{
								CString span_text = Utf8ToCString(span_node->value());
								if (!span_text.IsEmpty())
								{
									remark_Fulltext_LT += span_text + _T(" ");

								}
								remark_Fulltext_LT += _T("\r\n");
							}
						}
					}
				}

			}
		}
	}

	CRect client_Rect;
	GetClientRect(&client_Rect);
	CRect textRect(420, index, client_Rect.Width() - 500, index);

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(pMainFrame->GetFont());
	dc.DrawText(remark_Fulltext_LT, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);

	CStatic* pstaticValue = new CStatic();
	pstaticValue->Create(remark_Fulltext_LT, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_EDITCONTROL,
		textRect, this, 1001);

	TRACE(_T("Description-Block: index=%d -> id=%s  height=%d \n"),
		index, remark_Fulltext_LT, textRect.Height());

	pstaticValue->SetFont(pMainFrame->GetFont());
	m_vecStatics_GAEBInfo.push_back(pstaticValue);
	//index = static_cast<int>(textRect.bottom) + 10;
	index = index + textRect.Height() + 10;
	dc.SelectObject(pOldFont);

	/*CRect remark_itemlist_clienrect;
	GetClientRect(&remark_itemlist_clienrect);
	const int leftmargin_itemlist = 420;
	const int rightmargin_itemlist = remark_itemlist_clienrect.Width() * 0.3;
	const int topposition_itemlist = index;
	const int maxWidth_itemlist = remark_itemlist_clienrect.Width() - leftmargin_itemlist - rightmargin_itemlist;

	CRect remark_itemlist_textrect(leftmargin_itemlist, topposition_itemlist, leftmargin_itemlist + maxWidth_itemlist, topposition_itemlist);
	CClientDC dc_remark_itemlist(this);
	dc_remark_itemlist.DrawText(remark_Fulltext_LT, &remark_itemlist_textrect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);

	CStatic* remark_itemlist_value = new CStatic();
	remark_itemlist_value->Create(remark_Fulltext_LT, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX | SS_EDITCONTROL,
		remark_itemlist_textrect, this, 1001);
	remark_itemlist_value->SetFont(pMainFrame->GetFont());
	m_vecStatics_GAEBInfo.push_back(remark_itemlist_value);
	index = remark_itemlist_textrect.bottom + 20;*/
}

bool CLangtextView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
{
	outLines.clear();
	CFile file;

	if (!file.Open(filePath, CFile::modeRead | CFile::shareDenyNone))
		return false;

	ULONGLONG len64 = file.GetLength();
	if (len64 == 0)
	{
		file.Close();
		return true;
	}
	if (len64 > 200ULL * 1024ULL * 1024ULL)
	{
		file.Close();
		return false;
	}
	const int len = (int)len64;

	std::vector<char> buf((size_t)len + 1, 0);
	const UINT readBytes = file.Read(buf.data(), (UINT)len);
	file.Close();

	if ((int)readBytes != len)
		return false;

	// ANSI -> UTF-16
	int wlen = MultiByteToWideChar(CP_ACP, 0, buf.data(), len, nullptr, 0);
	if (wlen <= 0)
		return false;

	std::vector<wchar_t> wbuf((size_t)wlen + 1, 0);
	MultiByteToWideChar(CP_ACP, 0, buf.data(), len, wbuf.data(), wlen);
	wbuf[(size_t)wlen] = L'\0';

	CString content(wbuf.data());
	int start = 0;
	const int n = content.GetLength();
	while (start < n)
	{
		int posCR = content.Find(_T('\r'), start);
		int posLF = content.Find(_T('\n'), start);

		int end;
		if (posCR == -1) end = posLF;
		else if (posLF == -1) end = posCR;
		else end = min(posCR, posLF);

		if (end == -1)
		{
			CString line = content.Mid(start);
			line.TrimRight(_T("\r\n"));
			outLines.push_back(line);
			break;
		}

		CString line = content.Mid(start, end - start);
		line.TrimRight(_T("\r\n"));
		outLines.push_back(line);

		if (content[end] == _T('\r') && end + 1 < n && content[end + 1] == _T('\n'))
			start = end + 2;
		else
			start = end + 1;
	}

	return true;
}

bool CLangtextView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
{
	//#begin[GAEBInfo]
	//#end[GAEBInfo]
	int k1 = line.Find(_T('['));
	if (k1 != 0)
		return false;
	int k2 = line.Find(_T(']'), k1 + 1);
	if (k2 <= 1)
		return false;
	CString s = line;
	s.Trim();

	int endTag = s.ReverseFind(_T('['));
	if (endTag < 0)
		return false;
	CString tail = s.Mid(endTag);
	if (tail.CompareNoCase(_T("[end]")) != 0) return false;

	outKey = s.Mid(1, k2 - 1);
	outKey.Trim();

	outValue = s.Mid(k2 + 1, endTag - (k2 + 1));
	outValue.Trim();
	return !outKey.IsEmpty();
}



static double ParseGermanDouble(CString s)
{
	s.Trim();
	s.Replace(_T("."), _T(""));
	s.Replace(_T(","), _T("."));
	return _tstof(s);
}

static CString NormalizeOZ(CString s) {
	s.Trim();
	for (int i = 0; i < 64; ++i)
	{
		CString before = s;
		s.Replace(_T("  "), _T(" "));
		if (s == before) break;
	}
	return s;
}

static int CommonPrefixLen(const CString& m, const CString& n)
{
	int i = 0;
	int j = min(m.GetLength(), n.GetLength());
	for (; i < j; ++i) {
		if (m[i] != n[i])
			break;
	}
	return i;
}

static CString FormatOZByParent(const CString& parentRawOZ, const CString& parentFormattedOZ, const CString& childRawOZ)
{
	CString p = parentRawOZ;
	p.Trim();
	CString c = childRawOZ;
	c.Trim();

	if(p.IsEmpty() || c.IsEmpty())
		return c;
	int pref = CommonPrefixLen(p, c);
	if (pref > 0 && pref <= c.GetLength()) {
		CString suffix = c.Mid(pref);
		suffix.Trim();
		if(suffix.IsEmpty())
			return parentFormattedOZ;
		else
			return parentFormattedOZ + _T(".") + suffix;
		return c.Left(pref) + _T(".") + suffix;
	}
	return c;
}

/*static CString WrapText(CDC* pdc, CString text, int maxWidth) {
	CString result, line, word;
	int pos = 0;
	while(AfxExtractSubString(word, text, pos, _T(''))) {
		CString testLine = line.IsEmpty() ? word : line + _T("") + word;
		CSize size = pdc->GetTextExtent(testLine);
		if (size.cx > maxWidth && !line.IsEmpty()) {
			result += line + _T("\r\n");
			line = word;
		}
		else {
			line = testLine;
		}
		pos++;

	}
	if(!line.IsEmpty()) {
		result += line;
	}
	return result;
}*/
