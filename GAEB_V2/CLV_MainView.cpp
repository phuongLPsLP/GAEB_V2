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

static double ParseGermanDouble(CString s);
static CString GetField(const CString& line, int start, int len);
static double ParseGaebNumber(const CString& text, int decimals);
static CString FormatGaebNumber(double value, int decimals);
static CString NormalizeOZ(CString s);
static CString FormatOZByParent(const CString& parentRawOZ, const CString& parentFormattedOZ, const CString& childRawOZ);


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
	SetScrollSizes(MM_TEXT, m_wndSize);

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
	ClearAllViews();
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


	m_format = pMainFrame->GetFormat();

	if (*m_format == "2000")
	{

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

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		for (const auto& raw : lines)
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
			if (line.CompareNoCase(_T("#end[LVBereich]")) == 0)
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
			if (line.CompareNoCase(_T("#begin[Hinweis]")) == 0)
			{

			}
			if (line.CompareNoCase(_T("#end[Hinweis]")) == 0)
			{

			}

			CString key, value;
			if (!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (inLVBereich && !inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0) {
					value.Trim();
					currentLV.ber_oz = value;

					if (lvStack.empty())
						currentLV.ber_oz_formatted = value;
					else
						currentLV.ber_oz_formatted =
						FormatOZByParent(lvStack.back().ber_oz,
							lvStack.back().ber_oz_formatted,
							value);

					lvStack.push_back(currentLV);
				}
				else if (key.CompareNoCase(_T("BezTx")) == 0) {
					if (!lvStack.empty())
						lvStack.back().ber_kurztext = value;
					else
						currentLV.ber_kurztext = value;
				}

				else if (key.CompareNoCase(_T("Bez")) == 0) {
					if (!lvStack.empty())
						lvStack.back().ber_kurztext = value;
					else
						currentLV.ber_kurztext = value;
				}
				continue;
			}
			if (inPosition) {
				if (key.CompareNoCase(_T("OZ")) == 0)
				{
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
				else if (key.CompareNoCase(_T("BezTx")) == 0) currentPos.pos_kurztext = value;
				else if (key.CompareNoCase(_T("EP")) == 0) currentPos.pos_einheitpreis = value;
				else if (key.CompareNoCase(_T("GP")) == 0) currentPos.pos_gesamtpreis = value;
				else if (key.CompareNoCase(_T("Langtext")) == 0) currentPos.pos_langtext = value;
				continue;
			}
		}

		CFont* pFont = pMainFrame->GetFont();
		int id = 2200;
		for (auto& p : positions) {
			double menge = ParseGermanDouble(p.pos_menge);
			double ep = ParseGermanDouble(p.pos_einheitpreis);
			if (menge > 0 && ep > 0) {
				CString gesamt;
				gesamt.Format(_T("%.2f"), menge * ep);
				p.pos_gesamtpreis = gesamt;
			}
		}
		std::set<CString> printedLv;

		auto AddListRow = [&](const CString& oz, const CString& menge, const CString& me,
			const CString& text, const CString& ep, const CString& gp)
			{
				int i = m_list_LV.InsertItem(m_list_LV.GetItemCount(), oz);
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
				if (printedLv.insert(oz).second)
				{
					AddListRow(oz, _T(""), _T(""), lv.ber_kurztext, _T(""), _T(""));
				}
			}

			AddListRow(pos.pos_oz,
				pos.pos_menge,
				pos.pos_einheit,
				pos.pos_kurztext,
				pos.pos_einheitpreis,
				pos.pos_gesamtpreis);
		}
	}

	else if (*m_format == "90")
	{

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

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		struct LVRow
		{
			CString oz;
			CString menge;
			CString einheit;
			CString kurztext;
			CString einheitpreis;
			CString gesamtpreis;
		};

		std::vector<LVRow> rows;

		bool art21 = false;
		for (const auto& raw : lines) {

			CString line = raw;
			line.TrimRight(_T("\r\n"));
			line.Trim();

			if (line.IsEmpty() || line.GetLength() < 2)
				continue;

			CString satzart = GetField(line, 0, 2);

			if (satzart == _T("21")) {
				art21 = true;
				break;
			}
		}

		if (art21) {
			LVRow currentRow;
			bool hasCurrentRow = false;
			for (const auto& raw : lines)
			{
				CString line = raw;
				line.TrimRight(_T("\r\n"));

				if (line.IsEmpty() || line.GetLength() < 2)
					continue;

				CString satzart = GetField(line, 0, 2);
				if (satzart == _T("21")) {

					if (hasCurrentRow)
						rows.push_back(currentRow);

					currentRow = LVRow{};
					hasCurrentRow = true;

					CString mengeKenz = GetField(line, 12, 3);
					CString mengeRaw = GetField(line, 24, 11);
					CString einheitRaw = GetField(line, 34, 4);

					double menge = ParseGaebNumber(mengeRaw, 3);

					currentRow.menge = FormatGaebNumber(menge, 2);
					currentRow.einheit = einheitRaw;
				}

				else if (satzart == _T("23")) { //preisangabe einer Position			
					if (!hasCurrentRow)
						continue;

					CString ozRaw = GetField(line, 2, 8);
					CString gpRaw = GetField(line, 24, 12);
					CString epRaw = GetField(line, 12, 10);

					if (currentRow.oz.IsEmpty())
						currentRow.oz = ozRaw;

					double gp = ParseGaebNumber(gpRaw, 2);
					double ep = ParseGaebNumber(epRaw, 2);

					currentRow.oz = ozRaw;
					currentRow.einheitpreis = FormatGaebNumber(ep, 2);
					currentRow.gesamtpreis = FormatGaebNumber(gp, 2);
				}

				else if (satzart == _T("25")) {
					if (!hasCurrentRow)
						continue;
					CString kurztextRaw = GetField(line, 2, 70);
					if (currentRow.kurztext.IsEmpty())
						currentRow.kurztext = kurztextRaw;

				}

				else if (satzart == _T("32"))
				{
					if (hasCurrentRow)
					{
						rows.push_back(currentRow);
						currentRow = LVRow{};
						hasCurrentRow = false;
					}

					CString bereich = GetField(line, 2, 4);
					CString summeRaw = GetField(line, 12, 12);

					double summe = ParseGaebNumber(summeRaw, 2);

					LVRow row;
					row.oz = bereich;
					row.menge = _T("");
					row.einheit = _T("");
					row.kurztext = _T("");
					row.einheitpreis = _T("");
					row.gesamtpreis = FormatGaebNumber(summe, 2);
					rows.push_back(row);
				}

				else if (satzart == _T("11")) {
					if (!hasCurrentRow)
						continue;

					CString ozRaw = GetField(line, 2, 9);
					if (currentRow.oz.IsEmpty())
						currentRow.oz = ozRaw;
					currentRow.oz = ozRaw;

				}
			}
			if (hasCurrentRow)
				rows.push_back(currentRow);
		}

		else {
			for (const auto& raw : lines)
			{
				CString line = raw;
				line.TrimRight(_T("\r\n"));

				if (line.IsEmpty() || line.GetLength() < 2)
					continue;

				CString satzart = GetField(line, 0, 2);

				if (satzart == _T("23"))
				{
					LVRow row;

					CString ozRaw = GetField(line, 2, 8);
					CString epRaw = GetField(line, 12, 10);
					CString gpRaw = GetField(line, 24, 12);

					double ep = ParseGaebNumber(epRaw, 2);
					double gp = ParseGaebNumber(gpRaw, 2);

					row.oz = ozRaw;
					row.menge = _T("");
					row.einheit = _T("");
					row.kurztext = _T("");
					row.einheitpreis = FormatGaebNumber(ep, 2);
					row.gesamtpreis = FormatGaebNumber(gp, 2);

					rows.push_back(row);
				}
				else if (satzart == _T("32"))
				{
					LVRow row;

					CString bereich = GetField(line, 2, 4);
					CString summeRaw = GetField(line, 12, 12);

					double summe = ParseGaebNumber(summeRaw, 2);

					//row.oz = _T("Summe ") + bereich;
					row.oz = bereich;
					row.menge = _T("");
					row.einheit = _T("");
					//row.kurztext = _T("Bereichssumme");
					row.einheitpreis = _T("");
					row.gesamtpreis = FormatGaebNumber(summe, 2);

					rows.push_back(row);
				}
				else if (satzart == _T("11")) {
					LVRow row;

					CString ozRaw = GetField(line, 2, 8);
					CString epRaw = GetField(line, 12, 10);
					CString gpRaw = GetField(line, 24, 12);

					double ep = ParseGaebNumber(epRaw, 2);
					double gp = ParseGaebNumber(gpRaw, 2);

					row.oz = ozRaw;
					row.menge = _T("");
					row.einheit = _T("");
					row.kurztext = _T("");
					row.einheitpreis = FormatGaebNumber(ep, 2);
					row.gesamtpreis = FormatGaebNumber(gp, 2);

					rows.push_back(row);
				}
			}
		}



		CFont* pFont = pMainFrame->GetFont();
		CFont* pBold = pMainFrame->GetFontBold();
		int id = 4000;

		for (const auto& row : rows)
		{
			int i = m_list_LV.InsertItem(m_list_LV.GetItemCount(), row.oz);
			m_list_LV.SetItemText(i, 1, row.menge);
			m_list_LV.SetItemText(i, 2, row.einheit);
			m_list_LV.SetItemText(i, 3, row.kurztext);
			m_list_LV.SetItemText(i, 4, row.einheitpreis);
			m_list_LV.SetItemText(i, 5, row.gesamtpreis);
		}
	}

	//GAEB XML

	else
	{
		m_staticText_OZ.Create(_T("Ordnungszahl"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(20, 70), CSize(120, 20)), this, 1001);
		m_staticText_Menge.Create(_T("Menge"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(180, 70), CSize(80, 20)), this, 1002);
		m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(300, 70), CSize(80, 20)), this, 1003);
		m_staticText_LeiBe.Create(_T("Leitungsbeschreibung"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(420, 70), CSize(700, 20)), this, 1004);
		m_staticText_Einheitpreis.Create(_T("Einheitpreis [EUR]"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(1250, 70), CSize(180, 20)), this, 1005);
		m_staticText_Gesamtpreis.Create(_T("Gesamtpreis [EUR]"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(1450, 70), CSize(180, 20)), this, 1006);

		for (CStatic* pStatic_LV : staticControls_LV)
		{
			pStatic_LV->SetFont(pMainFrame->GetFontBold());
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

static CString GetField(const CString& line, int start, int len) {
	if (start >= line.GetLength())
		return _T("");
	int reallen = min(len, line.GetLength() - start);
	CString s = line.Mid(start, reallen);
	s.Trim();
	return s;
}

static double ParseGaebNumber(const CString& text, int decimals) {
	CString s = text;
	s.Trim();
	if (s.IsEmpty())
		return 0.0;

	long long raw = _ttoi64(s);
	double factor = 1.0;

	for (int i = 0; i < decimals; ++i)
		factor *= 10.0;

	return raw / factor;
}

static CString FormatGaebNumber(double value, int decimals)
{
	CString s;
	s.Format(_T("%.*f"), decimals, value);
	s.Replace(_T("."), _T(",")); 
	return s;
}

static double ParseGermanDouble(CString s)
{
	s.Trim();
	s.Replace(_T("."), _T(""));
	s.Replace(_T(","), _T("."));
	return _tstof(s);
}

static CString NormalizeOZ(CString s)
{
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
	for (; i < j; ++i) 
	{
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

	if (p.IsEmpty() || c.IsEmpty()) 
	{
		return c;
	}

	int pref = CommonPrefixLen(p, c);
	if (pref > 0 && pref <= c.GetLength())
	{
		CString suffix = c.Mid(pref);
		suffix.Trim();

		if (suffix.IsEmpty())
			return parentFormattedOZ;

		if (!parentFormattedOZ.IsEmpty())
			return parentFormattedOZ + _T(".") + suffix;

		return c.Left(pref) + _T(".") + suffix;
	}
	return c;
}
void CLV_MainView::ClearAllViews()
{
	// 1) ListCtrl leeren (falls vorhanden)
	if (m_list_LV.GetSafeHwnd())
	{
		m_list_LV.DeleteAllItems();
	}

	// 2) Dynamische Statics löschen
	for (CStatic* p : m_dynamicStatics)
	{
		if (p && ::IsWindow(p->GetSafeHwnd()))
			p->DestroyWindow();
		delete p;
	}
	m_dynamicStatics.clear();

	// 3) Header-Statics sicher entfernen
	CStatic* headers[] =
	{
		&m_staticText_OZ,
		&m_staticText_Menge,
		&m_staticText_Einheit,
		&m_staticText_LeiBe,
		&m_staticText_Einheitpreis,
		&m_staticText_Gesamtpreis
	};

	for (CStatic* p : headers)
	{
		if (p && ::IsWindow(p->GetSafeHwnd()))
			p->DestroyWindow();
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
