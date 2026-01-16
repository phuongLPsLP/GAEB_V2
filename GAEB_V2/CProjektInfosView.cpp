// CProjektInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CProjektInfosView.h"
#include "MainFrm.h"


// CProjektInfosView

IMPLEMENT_DYNCREATE(CProjektInfosView, CView)

CProjektInfosView::CProjektInfosView()
{

}

CProjektInfosView::~CProjektInfosView()
{
}

BEGIN_MESSAGE_MAP(CProjektInfosView, CView)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CProjektInfosView drawing

void CProjektInfosView::OnDraw(CDC* pDC)
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

void CProjektInfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect);
	CClientDC dc(this);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_format = pMainFrame->GetFormat();

	y_pos_projectinfo = 70;

	m_static_text_Title_project.Create(_T("Informationen zum Projekt"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_static_text_Title_project.SetFont(pMainFrame->GetFontBold());


	if (*m_format == "2000") {
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		CString name, bezeichnung, waehrung, wae_bez;

		bool inPrjInfo = false;
		for (const auto& raw : lines)
		{
			CString line = raw;
			line.Trim();
			if (line.IsEmpty())
				continue;
			if (line.CompareNoCase(_T("#begin[PrjInfo]")) == 0) {
				inPrjInfo = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[PrjInfo]")) == 0) {
				inPrjInfo = false;
				continue;
			}
			if (!inPrjInfo)
				continue;
			CString key, value;
			if (!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (key.CompareNoCase(_T("Name")) == 0) name = value;
			else if (key.CompareNoCase(_T("Bez")) == 0) bezeichnung = value;
			else if (key.CompareNoCase(_T("Wae")) == 0) waehrung = value;
			else if(key.CompareNoCase(_T("WaeBez")) == 0) wae_bez = value;
		}

		CFont* pFont = pMainFrame->GetFont();

		CreateStaticText(this, _T("Name:"), name, y_pos_projectinfo, pFont, 2000);
		CreateStaticText(this, _T("Bezeichnung:"), bezeichnung, y_pos_projectinfo, pFont, 2020);
		CreateStaticText(this, _T("Währung:"), waehrung, y_pos_projectinfo, pFont, 2030);
		CreateStaticText(this, _T("Währungsbezeichnung:"), wae_bez, y_pos_projectinfo, pFont, 2040);		
	}

	//GAEB XML
	else {
		m_Doc = pMainFrame->GetXmlDoc();
		m_Root = pMainFrame->GetRootNode();
		m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
		m_pProjektInfo = pMainFrame->GetProjektInfoNode();
		m_award = pMainFrame->GetAwardNode();

		for (xml_node<>* prjInfo_node = m_pProjektInfo->first_node(); prjInfo_node; prjInfo_node = prjInfo_node->next_sibling())
		{
			CString value = Utf8ToCString(prjInfo_node->value()); ;
			CString name(Utf8ToCString(prjInfo_node->name()));

			if (name == "NamePrj") { name = _T("Name:"); }
			else if (name == "LblPrj") { name = _T("Bezeichnung:"); }
			else if (name == "Cur") { name = _T("Währung:"); }
			else if (name == "CurLbl") { name = _T("Bezeichnung der Währung:"); }
			else if (name == "BidCommPerm")
			{
				name = _T("Bieter Kommentar zugelassen:");
				if (value == "No") { value = _T("Nein"); }
				else if (value == "Yes") { value = _T("Ja"); }
			}
			else if (name == "Descrip")
			{
				name = _T("Kurzbeschreibung:");
				xml_node<>* des_span = prjInfo_node->first_node("span");
				if (des_span) {
					value = Utf8ToCString(des_span->value());
				}
			}

			CStatic* pstaticValue_name = new CStatic();
			CStatic* pstaticValue_value = new CStatic();
			pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
				CRect(CPoint(20, y_pos_projectinfo), CSize(clientRect.Width(), 20)), this, 1001);
			pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, y_pos_projectinfo), CSize(clientRect.Width(), 20)), this, 1001);
			pstaticValue_value->SetFont(pMainFrame->GetFont());
			pstaticValue_name->SetFont(pMainFrame->GetFont());
			y_pos_projectinfo += 20;
		}
	}
}

bool CProjektInfosView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
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

bool CProjektInfosView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
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

void CProjektInfosView::CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase) 
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

#ifdef _DEBUG
void CProjektInfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjektInfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

HBRUSH CProjektInfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	return hbr;
}


CString CProjektInfosView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;

}