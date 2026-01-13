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
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect);
	CClientDC dc(this);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();


	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	m_format = pMainFrame->GetFormat();

	

	m_staticText_Title.Create(_T("Informationen zum GAEB Datenaustausch"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_staticText_Title.SetFont(pMainFrame->GetFontBold());

	//GAEB 2000
	if(*m_format == "2000")
	{
		std::vector<CString> lines;

		CString version, versMon, versJahr, progName, datum, zeichensatz;

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
			else if (key.CompareNoCase(_T("Datum")) == 0) datum = value;
			else if (key.CompareNoCase(_T("Zeichensatz")) == 0) zeichensatz = value;

		}
		CString msg;
		msg.Format(_T("GAEBInfo aus Datei:\r\n")
			_T("Version: %s\r\n")
			_T("VersMon: %s\r\n")
			_T("VersJahr: %s\r\n")
			_T("ProgName: %s\r\n")
			_T("Datum: %s\r\n")
			_T("Zeichensatz: %s"),
			version.GetString(),
			versMon.GetString(),
			versJahr.GetString(),
			progName.GetString(),
			datum.GetString(),
			zeichensatz.GetString());
		AfxMessageBox(msg);
	}
	//GAEB XML
	else
	{
		CString year;
		CString month;
		CString day;
		int yPos_GaebInfo = 70;

		for (xml_node<>* gaebinfo_node = m_pGAEBInfo->first_node(); gaebinfo_node; gaebinfo_node = gaebinfo_node->next_sibling())
		{
			CString subChild_name(gaebinfo_node->name());
			CString name = Utf8ToCString(gaebinfo_node->name());
			CString value = Utf8ToCString(gaebinfo_node->value());

			if (name == "Version") { name = _T("Version:"); }
			else if (name == "VersDate")
			{
				name = _T("Ausgabejahr der Regelung::");
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
	if (ctrlID == 1001)
	{
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

