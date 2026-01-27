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
		CRect(CPoint(1250, 70), CSize(180, 20)), this, 1001);
	m_staticText_Gesamtpreis.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(1450, 70), CSize(180, 20)), this, 1001);

	for (CStatic* pStatic_LV : staticControls_LV)
	{
		pStatic_LV->SetFont(pMainFrame->GetFontBold());
	}

	m_format = pMainFrame->GetFormat();

	if (*m_format == "2000") 
	{
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();
		bool inLVBereich = false;   
		bool inPosition = false;


		struct LVBereich {
			CString ber_oz;
			CString ber_kurztext;
		};

		struct LVPosition {
			CString pos_oz;
			CString pos_menge;
			CString pos_einheit;
			CString pos_kurztext;
			CString pos_einheitpreis;
			CString pos_gesamtpreis;
			std::vector<LVBereich> path;
		};

		std::vector<LVBereich> lvStack;
		std::vector<LVPosition> positions;

		LVBereich currentLV{};
		LVPosition currentPos{};

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		for(const auto& raw : lines)
		{
			CString line = raw;
			line.Trim();
			if (line.IsEmpty())
				continue;

			if (line.CompareNoCase(_T("#begin[LVBereich]")) == 0)
			{
				// neuer Bereich beginnt: wir sammeln OZ/BezTx und pushen beim #end oder sobald wir OZ haben?
				// robust: wir merken einen "currentLv", pushen erst, wenn wir OZ oder BezTx gesehen haben.
				currentLV = LVBereich{};
				inLVBereich = true;
				continue;
			}
			if(line.CompareNoCase(_T("#end[LVBereich]")) == 0)
			{
				// Wenn currentLv noch nicht gepusht wurde (weil OZ/BezTx erst gelesen wurde),
				// dann wurde er schon in lvStack gepusht? -> siehe unten: wir pushen sofort, sobald OZ kommt.
				// Hier müssen wir einfach poppen, wenn Stack nicht leer.
				if (!lvStack.empty())
					lvStack.pop_back();

				inLVBereich = false;
				continue;
			}

			if (line.CompareNoCase(_T("#begin[Position]")) == 0)
			{
				currentPos = LVPosition{};
				currentPos.path = lvStack;  // aktueller Bereichspfad
				inPosition = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[Position]")) == 0)
			{
				positions.push_back(currentPos);
				inPosition = false;
				continue;
			}

			CString key, value;
			if(!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (inLVBereich && !inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0) {
					currentLV.ber_oz = value;
					lvStack.push_back(currentLV);
				}
				else if (key.CompareNoCase(_T("BezTx")) == 0) {
					if (!lvStack.empty())
						lvStack.back().ber_kurztext = value;
					else
						currentLV.ber_kurztext = value; 
				}
				continue;
			}
			if (inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0) currentPos.pos_oz = value;
				else if(key.CompareNoCase(_T("Menge")) == 0) currentPos.pos_menge = value;
				else if (key.CompareNoCase(_T("Einheit")) == 0) currentPos.pos_einheit = value;
				else if (key.CompareNoCase(_T("Kurztext")) == 0) currentPos.pos_kurztext = value;
				else if (key.CompareNoCase(_T("Einheitpreis")) == 0) currentPos.pos_einheitpreis = value;
				else if (key.CompareNoCase(_T("Gesamtpreis")) == 0) currentPos.pos_gesamtpreis = value;
				continue;
			}
		}
	}

	else {
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
								TraverseBoQCtgy(ctgyNode, yPos_LV, rootPath);
							}
						}
					}
				}
			}
		}
	}
}

bool CLV_MainView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
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
	if (len64 > 200ULL * 1024ULL * 1024ULL) // simple safety limit 200MB
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

	// Lines splitten (\r\n oder \n)
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

		// CRLF oder einzelnes CR / LF überspringen
		if (content[end] == _T('\r') && end + 1 < n && content[end + 1] == _T('\n'))
			start = end + 2;
		else
			start = end + 1;
	}

	return true;
}

bool CLV_MainView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
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

void CLV_MainView::CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase)
{

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	const int labelX = 20;
	const int valueX = 270;
	const int height = 20;
	const int labelWidth = 240;
	const int valueWidth = 400;

	CStatic* pLabel = new CStatic();

	pLabel->Create(label,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
		CRect(labelX, yPos, labelX + labelWidth, yPos + height),
		this, idBase);

	CStatic* pValue = new CStatic();
	pValue->Create(value,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
		CRect(valueX, yPos, valueX + valueWidth, yPos + height),
		this, idBase);
	pLabel->SetFont(pMainFrame->GetFont());
	pValue->SetFont(pMainFrame->GetFont());

	m_dynamicStatics.push_back(pLabel);
	m_dynamicStatics.push_back(pValue);

	yPos += height;
}

void CLV_MainView::ClearAllStatics()
{
	for (CStatic* p : m_dynamicStatics)
	{
		if (p && ::IsWindow(p->GetSafeHwnd()))
			p->DestroyWindow();
		delete p;
	}
	m_dynamicStatics.clear();
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
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);  
		return (HBRUSH)GetStockObject(NULL_BRUSH);
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


void CLV_MainView::TraverseBoQCtgy(xml_node<>* ctgyNode, int& index, std::vector<int> path)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int ctgyCount = 0;
	if (auto* attr = ctgyNode->first_attribute("RNoPart"))
		ctgyCount = atoi(attr->value());
	std::vector<int> currentPath = path;
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

	for (xml_node<>* ctgy_childNode = ctgyNode->first_node(); ctgy_childNode; ctgy_childNode = ctgy_childNode->next_sibling()) {
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
				CStatic* static_lbl = new CStatic();
				static_lbl->Create(lblText, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(180, index), CSize(500, 20)), this, 1001);
				static_lbl->SetFont(pMainFrame->GetFontTitle());
				m_vecStatics_GAEBInfo.push_back(static_lbl);

				index += 20;
			}

			//Remark
			xml_node<>* remark = ctgy_childNode->first_node("Remark");
			if (remark) {
				TraverseRemark(remark, index);
			}

			// Traverse items if any
			xml_node<>* itemList = ctgy_childNode->first_node("Itemlist");
			if (itemList) {
				index += 20;
				TraverseItemlist(itemList, index, currentPath);
			}
			// Recurse into nested categories
			for (xml_node<>* subCtgy = ctgy_childNode->first_node("BoQCtgy"); subCtgy; subCtgy = subCtgy->next_sibling("BoQCtgy"))
			{
				index += 20;
				TraverseBoQCtgy(subCtgy, index, currentPath);
			}

		}
		else if (ctgy_child_name == "Totals") {
			if (ctgy_childNode->first_node() != nullptr) 
			{
				for (xml_node<>* totals_node = ctgy_childNode->first_node(); totals_node; totals_node = totals_node->next_sibling())
				{
					CString totals_name(totals_node->name());
					if(totals_name == "Total")
					{
						CString val_total = Utf8ToCString(totals_node->value());
					}
					else if (totals_name == "DiscountPcnt")
					{
						CString val_discnt = Utf8ToCString(totals_node->value());

					}
					else if (totals_name == "TotAfterDisc")
					{
						CString val_total_aft_discnt = Utf8ToCString(totals_node->value());
					}

				}
			}
		
		}
	}

	int finalY = index;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect.Width(), finalY + 20));
}

void CLV_MainView::TraverseItemlist(xml_node<>* itemList, int& index, std::vector<int> levelPath)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int itemCount = 0;


	for (xml_node<>* item = itemList->first_node(); item; item = item->next_sibling())
	{
		CString item_name(item->name());
		if (item_name == "Item")
		{
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
					CString tag(child->name());
					CString val(Utf8ToCString(child->value()));

					if (tag == "Qty") {	//Menge
						CStatic* cStatic_Qty = new CStatic();
						cStatic_Qty->Create(val, WS_CHILD | WS_VISIBLE,
							CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
						cStatic_Qty->SetFont(pMainFrame->GetFont());
						m_vecStatics_GAEBInfo.push_back(cStatic_Qty);
					}
					else if (tag == "QU") {	//Einheit
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
						xml_node<>* complete_txt_node = child->first_node();	//CompleteText
						CString Fulltext_kurz;


						for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
						{
							CString compl_text_name(compl_text->name());
							//Kurztext
							if (compl_text_name == "OutlineText") {
								for (xml_node<>* OutlTxt = compl_text->first_node(); OutlTxt; OutlTxt = OutlTxt->next_sibling()) //Text
								{
									for (xml_node<>* TextOutlTxt = OutlTxt->first_node(); TextOutlTxt; TextOutlTxt = TextOutlTxt->next_sibling()) //p
									{
										for (xml_node<>* p_node_kurztext = TextOutlTxt->first_node(); p_node_kurztext; p_node_kurztext = p_node_kurztext->next_sibling())	//span
										{
											for (xml_node<>* span_node_kurztext = p_node_kurztext->first_node(); span_node_kurztext; span_node_kurztext = span_node_kurztext->next_sibling())	//span
											{
												CString span_node_kurztext_text = Utf8ToCString(span_node_kurztext->value());
												if (!span_node_kurztext_text.IsEmpty()) {
													Fulltext_kurz += span_node_kurztext_text + _T(" ");
												}
												CStatic* cStatic_kurztext = new CStatic();
												cStatic_kurztext->Create(Fulltext_kurz, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
													CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
												cStatic_kurztext->SetFont(pMainFrame->GetFont());
												m_vecStatics_GAEBInfo.push_back(cStatic_kurztext);
											}
										}
									}
								}
							}
						}
					}
				}
				index += 20;
			}
			else {

				// Iterate over item's children
				for (xml_node<>* child = item->first_node(); child; child = child->next_sibling())
				{
					CString tag(child->name());
					CString val(Utf8ToCString(child->value()));

					if (tag == "Qty") {	//Menge
						CStatic* cStatic_Qty = new CStatic();
						cStatic_Qty->Create(val, WS_CHILD | WS_VISIBLE,
							CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
						cStatic_Qty->SetFont(pMainFrame->GetFont());
						m_vecStatics_GAEBInfo.push_back(cStatic_Qty);
					}
					else if (tag == "QU") {	//Einheit
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
					CStatic* cStatic_kurztext = new CStatic();
					cStatic_kurztext->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
						CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
					cStatic_kurztext->SetFont(pMainFrame->GetFont());

					m_vecStatics_GAEBInfo.push_back(cStatic_kurztext);
				}
				index += 20;
			}
		}
		else if (item_name == "Remark") {
			TraverseRemark(item, index);
		}
	}
}

void CLV_MainView::TraverseRemark(xml_node<>* remark, int& index)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CString remark_Fulltext;
	xml_node<>* descr_node = remark->first_node("Description");


	CStatic* cstatic_hinweis = new CStatic();
	cstatic_hinweis->Create(_T("Hinweistext"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(180, index), CSize(120, 20)), this, 1001);
	cstatic_hinweis->SetFont(pMainFrame->GetFontItalic());
	m_vecStatics_GAEBInfo.push_back(cstatic_hinweis);

	if(descr_node == nullptr) {
		index += 20;
		return;
	}
	else {

		for (xml_node<>* descr_childNode = descr_node->first_node(); descr_childNode; descr_childNode = descr_childNode->next_sibling()) {
			CString descr_childNode_name(descr_childNode->name());

			if (descr_childNode_name == "OutlineText") {
				for (xml_node<>* outltext_node = descr_childNode->first_node(); outltext_node; outltext_node = outltext_node->next_sibling()) {
					for (xml_node<>* textoutTxt_node = outltext_node->first_node(); textoutTxt_node; textoutTxt_node = textoutTxt_node->next_sibling()) {
						for (xml_node<>* p_node = textoutTxt_node->first_node(); p_node; p_node = p_node->next_sibling()) {
							for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling()) {
								CString spantext = Utf8ToCString(span_node->value());
								if (!spantext.IsEmpty()) {
									remark_Fulltext += spantext + _T(" ");
								}
							}
						}
					}
				}
				CStatic* static_remark = new CStatic();
				static_remark->Create(remark_Fulltext, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
					CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
				static_remark->SetFont(pMainFrame->GetFontItalic());
				m_vecStatics_GAEBInfo.push_back(static_remark);
				index += 20;
			}
			else if (descr_childNode_name == "CompleteText") {
				xml_node<>* outltext_node = descr_childNode->first_node("OutlineText");
				if (outltext_node) {
					for (outltext_node; outltext_node; outltext_node = outltext_node->next_sibling("OutlineText")) {
						for (xml_node<>* textoutTxt_node = outltext_node->first_node(); textoutTxt_node; textoutTxt_node = textoutTxt_node->next_sibling()) {
							for (xml_node<>* p_node = textoutTxt_node->first_node(); p_node; p_node = p_node->next_sibling()) {
								for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling()) {
									CString spantext = Utf8ToCString(span_node->value());
									if (!spantext.IsEmpty()) {
										remark_Fulltext += spantext + _T(" ");
									}
								}
							}
						}
					}

					CStatic* static_remark = new CStatic();
					static_remark->Create(remark_Fulltext, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
						CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
					static_remark->SetFont(pMainFrame->GetFontItalic());
					m_vecStatics_GAEBInfo.push_back(static_remark);
					index += 20;
				}

				else {
					CStatic* static_remark = new CStatic();
					static_remark->Create(_T("Hinweistext"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
						CRect(CPoint(420, index), CSize(1000, 20)), this, 1001);
					static_remark->SetFont(pMainFrame->GetFontItalic());
					m_vecStatics_GAEBInfo.push_back(static_remark);
					index += 20;
				}


			}

			
		}
	}
}

CString CLV_MainView::FormatPath(const std::vector<int>& path)
{
	CString result;
	for (size_t i = 0; i < path.size(); ++i)
	{
		result.AppendFormat(_T("%d"), path[i]);
		if (i < path.size() - 1)
			result.Append(_T("."));
	}
	return result;
}

void CLV_MainView::GetDeviceScrollSize(int& nMapMode, SIZE & sizeTotal, SIZE & sizePage, SIZE & sizeLine)
		const
{	
}
