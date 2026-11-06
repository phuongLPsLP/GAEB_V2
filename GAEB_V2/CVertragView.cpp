// CVertragView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVertragView.h"
#include "CDocumentClass.h"
#include "MainFrm.h"



// CVertragView

IMPLEMENT_DYNCREATE(CVertragView, CScrollView)

CVertragView::CVertragView()
{

}

CVertragView::~CVertragView()
{
}

BEGIN_MESSAGE_MAP(CVertragView, CScrollView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


static int CALLBACK EnumFontFamExProc(const LOGFONT* lpelfe, const TEXTMETRIC* lpntme, DWORD FontType, LPARAM lParam)
{
	CComboBox* pCombo = reinterpret_cast<CComboBox*>(lParam);
	if (pCombo)
	{
		//pCombo->AddString(lpelfe->lfFaceName);  // Add font name
		CString fontName = lpelfe->lfFaceName;
		
		if (fontName.GetLength() > 0 && fontName[0] != '@')  // 🔹 Skip vertical fonts
		{
			// Avoid duplicates
			if (pCombo->FindStringExact(-1, fontName) == CB_ERR)
				pCombo->AddString(fontName);
		}
	}
	return 1;  // Continue enumeration
}

// CVertragView drawing

void CVertragView::OnDraw(CDC* pDC)
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

void CVertragView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect_VR);
	CClientDC dc(this);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	SetScrollSizes(MM_TEXT, CSize(clientRect_VR.Width(), 3000));

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	CStatic* staticControls_Vertrag_Info[] =
	{
		&m_staticText_Text,
	};

	for (CStatic* pStatic_Vertrag_Info : staticControls_Vertrag_Info)
	{
		pStatic_Vertrag_Info->DestroyWindow();
	}

	m_staticText_Text.Create(_T("Informationen zu vertraglichen Regelungen"), WS_CHILD | WS_VISIBLE ,
		CRect(CPoint(20, 20), CSize(clientRect_VR.Width(), 30)), this, 1001);
	for (CStatic* pStatic : staticControls_Vertrag_Info)
	{
		pStatic->SetFont(pMainFrame->GetFontBold());
	}
	y_pos_vertrag = 70;
	m_format = pMainFrame->GetFormat();

	//GAEB 2000 
	if (*m_format == "2000")
	{
		struct LVZusText
		{
			CString titel;     // [Text]
			CString inhalt;    // [TextRTF]
		};

		LVZusText currentZusText;
		std::vector<LVZusText> zusTexte;

		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}
		bool inZusText = false;
		bool readingTextRTF = false;
		CString textBuffer;

		for (const auto& raw : lines)
		{
			CString line = raw;
			line.Trim();
			if (line.CompareNoCase(_T("#begin[ZusText]")) == 0)
			{
				currentZusText = LVZusText{};
				inZusText = true;
				continue;
			}

			if (line.CompareNoCase(_T("#end[ZusText]")) == 0) {
				zusTexte.push_back(currentZusText);
				inZusText = false;
				continue;
			}

			if (!inZusText)
				continue;

			if (line.Find(_T("[TextRTF]")) >= 0)
			{
				readingTextRTF = true;

				int p = line.Find(_T("[TextRTF]")) + 9;

				textBuffer = line.Mid(p);

				continue;
			}
			if (readingTextRTF)
			{
				if (line.Find(_T("[end]")) >= 0)
				{
					int p = line.Find(_T("[end]"));
					textBuffer += _T("\r\n") + line.Left(p);

					currentZusText.inhalt = textBuffer;

					readingTextRTF = false;
					textBuffer.Empty();
				}
				else
				{
					textBuffer += _T("\r\n") + line;
				}

				continue;
			}
		}

		CFont* pFont = pMainFrame->GetFont();
		int id = 3000;
		for (const auto& zt : zusTexte) {
			if (zt.inhalt.IsEmpty())
				continue;

			CString text = zt.inhalt;
			text.Replace(_T("\r\n\r\n\r\n"), _T("\r\n\r\n"));
			CDC* pDC = GetDC();
			CFont* pOldFont = pDC->SelectObject(pMainFrame->GetFont());

			CRect textRect(20, y_pos_vertrag, clientRect_VR.Width() - 40, 0);
			pDC->DrawText(text, &textRect, DT_WORDBREAK | DT_CALCRECT);

			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);

			int height = textRect.Height() + 20;

			CStatic* pstaticValue = new CStatic();
			//CRect textRect(0, 0, clientRect_VR.Width() - 40, 0);
			pstaticValue->Create(text, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
				CRect(CPoint(20, y_pos_vertrag), CSize(clientRect_VR.Width() - 40, y_pos_vertrag + height)), 
				this, id++);
			//y_pos_vertrag += textRect.Height() + 20;
			y_pos_vertrag += height + 20;
			pstaticValue->SetFont(pMainFrame->GetFont());
		}
		int finalY = y_pos_vertrag;
		CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect_VR.Width(), finalY + 20));

	}
	else if (*m_format == "90")
	{
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();
		if (!ReadFileLinesCP850ToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		int id = 5000;
		CSize size = CSize(clientRect_VR.Width(), 20);

		for (const auto& raw : lines) {
			CString line = raw;
			line.TrimRight(_T("\r\n"));
			line.Trim();

			if (line.IsEmpty() || line.GetLength() < 2)
				continue;

			CString satzart = line.Left(2);
			CString value = line.Mid(2);
			value = value.Left(value.GetLength() - 6);

			std::string(CT2CA(value)).c_str();

			CStatic* vertrag_regelung_text = new CStatic();
			vertrag_regelung_text->Create(value, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
				CRect(CPoint(20, y_pos_vertrag), size), this, 5000);
			vertrag_regelung_text->SetFont(pMainFrame->GetFont());
			y_pos_vertrag += 20;
		}
	}
	else {
		int id = 3000;

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
						CStatic* pstaticValue = new CStatic();
						CString Fulltext;
						for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
						{
							CString span_node_text = Utf8ToCString(span_node->value());
							if (!span_node_text.IsEmpty()) {
								Fulltext += span_node_text;
							}
						}

						CRect textRect(0, 0, clientRect_VR.Width() - 40, 0); // start with 0 height

						CClientDC dc(this);
						CFont* pOldFont = dc.SelectObject(pMainFrame->GetFont());
						dc.DrawText(Fulltext, &textRect, DT_LEFT | DT_WORDBREAK | DT_CALCRECT);
						dc.SelectObject(pOldFont);

						textRect.OffsetRect(20, y_pos_vertrag); // apply margins


						pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX, textRect,
							this, id ++);
						y_pos_vertrag += textRect.Height() + 20;
						pstaticValue->SetFont(pMainFrame->GetFont());
					}
				}
			}
		}

		for (xml_node<>* addtext_node = m_Root->first_node("AddText"); addtext_node; addtext_node = addtext_node->next_sibling("AddText")) {
			for (xml_node<>* detailtext_node = addtext_node->first_node(); detailtext_node; detailtext_node = detailtext_node->next_sibling())
			{
				for (xml_node<>* p_node = detailtext_node->first_node(); p_node; p_node = p_node->next_sibling())
				{
					CStatic* pstaticValue = new CStatic();
					CString Fulltext;
					for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
					{
						CString span_node_text = Utf8ToCString(span_node->value());
						if (!span_node_text.IsEmpty()) {
							Fulltext += span_node_text;
						}
					}
					CRect textRect(0, 0, clientRect_VR.Width() - 40, 0);
					pstaticValue->Create(Fulltext, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
						CRect(CPoint(20, y_pos_vertrag), CSize(clientRect_VR.Width(), 30)), this, id++);
					y_pos_vertrag += textRect.Height() + 20;
					pstaticValue->SetFont(pMainFrame->GetFont());
				}
			}
		}
		int finalY = y_pos_vertrag;
		CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect_VR.Width(), finalY + 20));
	}
}

#ifdef _DEBUG
void CVertragView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVertragView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVertragView message handlers

HBRUSH CVertragView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	if (ctrlID == 1002)
	{
		pDC->SetBkColor(RGB(255, 255, 200));
		// Return the brush for background color
		return m_edit_bg_color;
	}
	return hbr;
}

CString CVertragView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}

void CVertragView::CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& ypos, CFont* pFont, int idBase) {
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();


}

bool CVertragView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
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


bool CVertragView::ReadFileLinesCP850ToCStringW(const CString& filePath, std::vector<CString>& outLines){
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

	// CP850 -> UTF-18

	int wlen = MultiByteToWideChar(850, 0, buf.data(), len, nullptr, 0);

	if (wlen <= 0)
		return false;

	std::vector<wchar_t> wbuf((size_t)wlen + 1, 0);

	MultiByteToWideChar(850, 0, buf.data(), len, wbuf.data(), wlen);

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