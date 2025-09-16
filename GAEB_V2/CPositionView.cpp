// CPositionView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CPositionView.h"
#include "MainFrm.h"

// CPositionView

IMPLEMENT_DYNCREATE(CPositionView, CView)

CPositionView::CPositionView()
{

}

CPositionView::~CPositionView()
{
}


BEGIN_MESSAGE_MAP(CPositionView, CView)
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

// CPositionView drawing

void CPositionView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(20, 740);
	pDC->LineTo(240, 740);

	pDC->SelectObject(pOldPen);
}

void CPositionView::OnInitialUpdate()
{
	CGAEBV2App* pApp = (CGAEBV2App*)AfxGetApp();
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(20, 180);
	Invalidate();
	UpdateWindow();
	m_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	CClientDC dc(this);

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 18; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_edit_small;
	::ZeroMemory(&lf_edit_small, sizeof(LOGFONT));
	lf_edit_small.lfHeight = 16;
	lf_edit_small.lfWeight = FW_NORMAL;
	_tcscpy_s(lf_edit_small.lfFaceName, _T("Segoe UI"));
	m_font_edit.CreateFontIndirect(&lf_edit_small);


	m_staticText_Position.Create(_T("Position"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(200, 30)), this, 1001);

	m_staticText_Ordnungszahl.Create(_T("Ordnungszahl (OZ)"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 50), CSize(100, 50)), this, 1001);
	m_staticText_Positionsart.Create(_T("Positionsart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 100), CSize(80, 20)), this, 1001);
	m_staticText_Kurztext.Create(_T("Kurztext"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 140), CSize(80, 20)), this, 1001);
	m_staticText_Langtext.Create(_T("Langtext"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 250), CSize(80, 20)), this, 1001);
	
	m_edit_OZ.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160,50), CSize(120,20)), this, 1002);
	m_edit_OZ.SetWindowTextW(m_text_OZ);

	m_combobox_PosArt.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT |WS_VSCROLL, 
		CRect(CPoint(160, 100), CSize(250, 20)), this, 1003);
	m_combobox_PosArt.SetFont(&m_font);
	
/*	CRect rcButton(160, 140, 280, 70);
	m_combobox_textFont_KT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		rcButton, this, 1003);
	m_combobox_textSize_KT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
		CRect(CPoint(310, 140), CSize(80, 20)), this, 1003);
	m_button_bold_KT.Create(_T("B"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(410, 140), CSize(30, 20)), this, 1003);
	m_button_italic_KT.Create(_T("I"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(450, 140), CSize(30, 20)), this, 1003);
	m_button_underline_KT.Create(_T("U"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(490, 140), CSize(30, 20)), this, 1003);

	m_button_bold_KT.SetFont(&m_font_bold);
	m_button_italic_KT.SetFont(&m_font_italic);
	m_button_underline_KT.SetFont(&m_font_underline);*/

	m_edit_kurztext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(20, 180), CSize(rect.Width(), 50)), this, 1005);
	m_edit_kurztext.SetFont(&m_font);

/*	m_combobox_textFont_LT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		CRect(CPoint(160, 250), CSize(120, 20)), this, 1003);
	m_combobox_textSize_LT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
		CRect(CPoint(310, 250), CSize(80, 20)), this, 1003);
	m_button_bold_LT.Create(_T("B"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(410, 250), CSize(30, 20)), this, 1003);
	m_button_italic_LT.Create(_T("I"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(450, 250), CSize(30, 20)), this, 1003);
	m_button_underline_LT.Create(_T("U"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(490, 250), CSize(30, 20)), this, 1003);

	m_button_bold_LT.SetFont(&m_font_bold);
	m_button_italic_LT.SetFont(&m_font_italic);
	m_button_underline_LT.SetFont(&m_font_underline);*/

	m_edit_langtext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(20, 290), CSize(rect.Width(), 270)), this, 1005);
	m_edit_langtext.SetFont(&m_font);

	m_staticText_Menge.Create(_T("Menge"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 580), CSize(80, 20)), this, 1001);
	m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(360, 580), CSize(80, 20)), this, 1001);
	m_staticText_Einheitpreis.Create(_T("Einheitpreis [Euro]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 620), CSize(120, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 660), CSize(120, 20)), this, 1001);
	m_staticText_Gesamtpreis.Create(_T("Gesamtbetrag [Euro]"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 700), CSize(150, 20)), this, 1001);
	m_staticText_Summe.Create(_T("Summe Pos. [Euro]"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 760), CSize(150, 20)), this, 1001);

	m_edit_Menge.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 580), CSize(80, 20)), this, 1002);
	m_combobox_einheit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		CRect(CPoint(260, 580), CSize(80, 20)), this, 1003);
	m_edit_einheitpreis.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 620), CSize(80, 20)), this, 1002);
	m_edit_nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 660), CSize(80, 20)), this, 1002);
	m_edit_gesamt.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 700), CSize(80, 20)), this, 1002);
	m_edit_summe.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 760), CSize(80, 20)), this, 1002);

	/*LOGFONT lf_textFont = {};
	lf_textFont.lfCharSet = DEFAULT_CHARSET;
	lf_textFont.lfFaceName[0] = '\0';

	EnumFontFamiliesEx(dc.GetSafeHdc(), &lf_textFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&m_combobox_textFont_KT, 0);
	m_combobox_textFont_KT.SelectString(-1, _T("Segoe UI"));  

	EnumFontFamiliesEx(dc.GetSafeHdc(), &lf_textFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&m_combobox_textFont_LT, 0);
	m_combobox_textFont_LT.SelectString(-1, _T("Segoe UI")); 


	int standardFontSizes[] = {
	8, 9, 10, 11, 12, 14, 16, 18,
	20, 22, 24, 26, 28, 36, 48, 72
	};

	for (int i = 0; i < _countof(standardFontSizes); ++i)
	{
		CString str;
		str.Format(_T("%d"), standardFontSizes[i]);
		m_combobox_textSize_KT.AddString(str);
		m_combobox_textSize_LT.AddString(str);
	}
	m_combobox_textSize_KT.SelectString(-1, _T("11"));
	m_combobox_textSize_LT.SelectString(-1, _T("11"));*/


	if (pApp && pApp->m_einheitList.GetSize() > 0)
	{
		for (int i = 0; i < pApp->m_einheitList.GetSize(); ++i)
		{
			m_combobox_einheit.AddString(pApp->m_einheitList[i]);
		}
	}

	if (pApp && pApp->m_PosArtList.GetSize() > 0) 
	{
		for (int i = 0; i < pApp->m_PosArtList.GetSize(); ++i) 
		{
			m_combobox_PosArt.AddString(pApp->m_PosArtList[i]);
		}
	}
	m_combobox_einheit.SetFont(&m_font);


	CStatic* staticControls_bold[] = {
	&m_staticText_Position,
	};

	for (CStatic* pStatic : staticControls_bold)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font_bold);
	}
	CStatic* staticControls_normal[] = {
	&m_staticText_Ordnungszahl,
	&m_staticText_Positionsart,
	&m_staticText_Menge,
	&m_staticText_Einheit,
	&m_staticText_Kurztext,
	&m_staticText_Langtext,
	&m_staticText_Einheit,
	&m_staticText_Einheitpreis,
	&m_staticText_Nachlass,
	&m_staticText_Gesamtpreis
	};

	for (CStatic* pStatic : staticControls_normal)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}


	CEdit* editControls[] = {
		&m_edit_Einheit,
		&m_edit_einheitpreis,
		&m_edit_gesamt,
		&m_edit_Menge,
		&m_edit_nachlass,
		&m_edit_summe,
		&m_edit_OZ,
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
		}
	}
}


// CPositionView diagnostics

#ifdef _DEBUG
void CPositionView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPositionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPositionView message handlers


HBRUSH CPositionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	//Combobox

	/*if (ctrlID == 1003)
	{
		if (nCtlColor == CTLCOLOR_LISTBOX) // ListBox (Dropdown area)
		{
			pDC->SetBkColor(RGB(200, 220, 255)); // Light Blue Background
			pDC->SetTextColor(RGB(255, 0, 0));     // Black Text
			return m_brush_combobox;
		}

		else if (nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_STATIC) // ComboBox text area
		{
			pDC->SetBkColor(RGB(255, 255, 180)); // Light Yellow
			pDC->SetTextColor(RGB(0, 0, 0));   // Black text
			return m_brush_combobox;
		}
		return CView::OnCtlColor(pDC, pWnd, nCtlColor);
	}*/
	//Edit box
	if (ctrlID == 1005)
	{
		pDC->SetBkColor(RGB(255, 255, 200));
		// Return the brush for background color
		return m_edit_bg_color;
	}
	return hbr;
}

void CPositionView::SetText(LPCTSTR lpszText)
{
	if (m_edit_OZ.GetSafeHwnd() != NULL && ::IsWindow(m_edit_OZ.m_hWnd))
	{
		m_edit_OZ.SetWindowText(lpszText);
	}
	else
	{
		m_text_OZ = lpszText;
	}

}
