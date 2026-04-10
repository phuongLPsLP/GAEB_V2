  // CKalkulationsInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLVInfosView.h"
#include "MainFrm.h"


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

void CLVInfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	Invalidate();
	UpdateWindow();
	ClearAllStatics();
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect);
	CClientDC dc(this);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_format = pMainFrame->GetFormat();	

	m_staticText_Title.Create(_T("Informationen zum GAEB Datenaustausch"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_staticText_Title.SetFont(pMainFrame->GetFontBold());

	int yPos_GaebInfo = 70;

	//GAEB 2000
	if(*m_format == "2000")
	{
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}
		CString version, versMon, versJahr, progName, datum, zeichensatz, zeit, progsystem;

		bool inGaebInfo = false;
		for (const auto& raw : lines)
		{
			CString line = raw;
			line.Trim();
			if (line.IsEmpty())
				continue;
			if (line.CompareNoCase(_T("#begin[GAEBInfo]")) == 0) {
				inGaebInfo = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[GAEBInfo]")) == 0) {
				inGaebInfo = false;
				continue;
			}
			if (!inGaebInfo)
				continue;
			CString key, value;
			if (!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (key.CompareNoCase(_T("Version")) == 0) version = value;
			else if (key.CompareNoCase(_T("VersMon")) == 0) versMon = value;
			else if (key.CompareNoCase(_T("VersJahr")) == 0) versJahr = value;
			else if (key.CompareNoCase(_T("ProgName")) == 0) progName = value;
			else if (key.CompareNoCase(_T("ProgSystem")) == 0) progsystem = value;
			else if (key.CompareNoCase(_T("Uhrzeit")) == 0) zeit = value;
			else if (key.CompareNoCase(_T("Datum")) == 0) datum = value;
			else if (key.CompareNoCase(_T("Zeichensatz")) == 0) zeichensatz = value;

		}

		CFont* pFont = pMainFrame->GetFont();
		CString date = versMon + _T(".") + versJahr;
		int id = 2000;

		auto AddIfNotEmpty = [&](LPCTSTR label, const CString& value, CFont* font)
			{
				if (!value.IsEmpty())
				{
					CreateStaticText(this, label, value, yPos_GaebInfo, font, id);
					id += 2;
				}
			};
		AddIfNotEmpty( _T("Version:"), version,  pFont);
		AddIfNotEmpty( _T("Ausgabejahr der Regelung:"), date,  pFont);
		AddIfNotEmpty( _T("Erstellungsdatum der Datei:"), datum,  pFont);
		AddIfNotEmpty( _T("Erstellungsszeit der Datei:"), zeit,  pFont);
		AddIfNotEmpty( _T("Programmsystem:"), progName,  pFont);
		AddIfNotEmpty( _T("Umsetzprogramm:"), progsystem,  pFont);
		AddIfNotEmpty( _T("Zeichensatz:"), zeichensatz,  pFont);

	}

	else if (*m_format == "90")
	{
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();

		CString allText;
		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		CString phase, datum, bez, waehrung, auftraggeber;

		bool inGaebInfo = false;
		for (const auto& raw : lines) {

			CString line = raw;
			line.TrimRight(_T("\r\n"));
			if (line.IsEmpty())
				continue;
			if (line.GetLength() < 2)
				continue;
			CString satzart = line.Left(2);
			if (satzart == _T("00") || satzart == _T("01") || satzart == _T("02") || satzart == _T("03") || satzart == _T("08"))
			{
				CString value = line.Mid(2);
				value.Trim();
				 
				CString outline;
				outline.Format(_T("Satzart"), satzart);

				allText += outline;
			}	
		}

		auto AddIfNotEmpty = [&](LPCTSTR label, const CString& value, CFont* font)
			{
				int id = 2000;
				if (!value.IsEmpty())
				{
					CreateStaticText(this, label, value, yPos_GaebInfo, font, id);
					id += 2;
				}
			};

		AddIfNotEmpty(_T("Version:"), version, pFont);
		AddIfNotEmpty(_T("Ausgabejahr der Regelung:"), date, pFont);
		AddIfNotEmpty(_T("Erstellungsdatum der Datei:"), datum, pFont);
		AddIfNotEmpty(_T("Erstellungsszeit der Datei:"), zeit, pFont);
		AddIfNotEmpty(_T("Programmsystem:"), progName, pFont);
		AddIfNotEmpty(_T("Umsetzprogramm:"), progsystem, pFont);
		AddIfNotEmpty(_T("Zeichensatz:"), zeichensatz, pFont);

	}
	//GAEB XML
	else
	{
		
		m_Doc = pMainFrame->GetXmlDoc();
		m_Root = pMainFrame->GetRootNode();
		m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
		m_pProjektInfo = pMainFrame->GetProjektInfoNode();
		m_award = pMainFrame->GetAwardNode();

		CString year;
		CString month;
		CString day;

		for (xml_node<>* gaebinfo_node = m_pGAEBInfo->first_node(); gaebinfo_node; gaebinfo_node = gaebinfo_node->next_sibling())
		{
			CString subChild_name(gaebinfo_node->name());
			CString name = Utf8ToCString(gaebinfo_node->name());
			CString value = Utf8ToCString(gaebinfo_node->value());

			if (name == "Version") { name = _T("Version:"); }
			else if (name == "VersDate")
			{
				name = _T("Ausgabejahr der Regelung:");
				CString rawAusgabe(value);
				year = rawAusgabe.Mid(0, 4);
				month = rawAusgabe.Mid(5, 2);
				day = rawAusgabe.Mid(8, 2);
				if (rawAusgabe.GetLength() >= 10) {
					value.Format(_T("%s.%s.%s"), day, month, year);
				}
				else if (rawAusgabe.GetLength() <= 7) {
					value.Format(_T("%s.%s"), month, year);
				}
			}
			else if (name == "Date")
			{
				name = _T("Erstellungsdatum der Datei:");
				CString rawErstellung(value);
				year = rawErstellung.Mid(0, 4);
				month = rawErstellung.Mid(5, 2);
				day = rawErstellung.Mid(8, 2);
				if (rawErstellung.GetLength() >= 10) {
					value.Format(_T("%s.%s.%s"), day, month, year);
				}
				else if (rawErstellung.GetLength() <= 7) {
					value.Format(_T("%s.%s"), month, year);
				}
			}
			else if (name == "Time") { name = _T("Erstellungszeit der Datei:"); }
			else if (name == "ProgSystem") { name = _T("Programmsystem:"); }
			else if (name == "ProgName") { name = _T("Umsetzprogramm:"); }
			else if (name == "Certific")
			{
				name = _T("Prüfzertifikat:");
				if (value == "Available") value = _T("Ja");
				else value = _T("Nein");
			}

			CStatic* pstaticValue_name = new CStatic();
			CStatic* pstaticValue_value = new CStatic();
			pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
				CRect(CPoint(20, yPos_GaebInfo), CSize(clientRect.Width(), 20)), this, 1001);
			pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_GaebInfo), CSize(clientRect.Width(), 20)), this, 1001);
			pstaticValue_value->SetFont(pMainFrame->GetFont());
			pstaticValue_name->SetFont(pMainFrame->GetFont());
			yPos_GaebInfo += 20;
		}
	}
}

CString CLVInfosView::GetField(const CString& line, int start, int len)
{
	if (start < 0 || len <= 0 || start >= line.GetLength())
		return _T("");

	int maxLen = min(len, line.GetLength() - start);
	CString value = line.Mid(start, maxLen);
	value.Trim();
	return value;
}

void CLVInfosView::ParseGaeb90Position(const CString& line)
{
	/*CString posNr = GetField(line, 2, 10);
	CString kurzTxt = GetField(line, 12, 40);
	CString menge = GetField(line, 52, 11);
	CString einheit = GetField(line, 63, 4);
	CString ep = GetField(line, 67, 12);*/
}


bool CLVInfosView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
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

bool CLVInfosView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
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

void CLVInfosView::CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase)
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

void CLVInfosView::ClearAllStatics()
{
	for (CStatic* p : m_dynamicStatics)
	{
		if (p && ::IsWindow(p->GetSafeHwnd()))
			p->DestroyWindow();
		delete p;
	}
	m_dynamicStatics.clear();
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
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}

	return hbr;
}


CString CLVInfosView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}

