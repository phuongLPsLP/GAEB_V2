// CVertragView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVertragView.h"


// CVertragView

IMPLEMENT_DYNCREATE(CVertragView, CView)

CVertragView::CVertragView()
{

}

CVertragView::~CVertragView()
{
}

BEGIN_MESSAGE_MAP(CVertragView, CView)
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
}

void CVertragView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(20, 90);

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18; // Font height
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_italic;
	::ZeroMemory(&lf_italic, sizeof(LOGFONT));
	lf_italic.lfHeight = 18; // Font height
	lf_italic.lfWeight = FW_NORMAL;
	lf_italic.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_italic.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_italic.CreateFontIndirect(&lf_italic);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18; // Font height
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_underline.CreateFontIndirect(&lf_underline);

	m_staticText_Text.Create(_T("Vertragliche Regelung"), WS_CHILD| WS_VISIBLE, CRect(CPoint(20,20), CSize(200,30)), this, 1001);
	m_edit_Text.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, rect, this, 1002);

	m_combobox_textFont.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST| CBS_SORT, CRect(CPoint(20, 50), CSize(200, 20)), this, 1003);
	m_combobox_textSize.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, CRect(CPoint(250, 50), CSize(100, 20)), this, 1003);
	m_button_bold.Create(_T("B"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(370, 50), CSize(30, 20)), this, 1003);
	m_button_italic.Create(_T("I"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(410, 50), CSize(30, 20)), this, 1003);
	m_button_underline.Create(_T("U"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(450, 50), CSize(30, 20)), this, 1003);

	m_button_bold.SetFont(&m_font);
	m_button_italic.SetFont(&m_font_italic);
	m_button_underline.SetFont(&m_font_underline);

	m_combobox_textFont.SelectString(-1, _T("Segoe UI"));  // Or any preferred font*/

	LOGFONT lf_textFont = {};
	lf_textFont.lfCharSet = DEFAULT_CHARSET;
	lf_textFont.lfFaceName[0] = '\0';  //

	CClientDC dc(this);  // Get a device context
	EnumFontFamiliesEx(dc.GetSafeHdc(), &lf_textFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&m_combobox_textFont, 0);

	//m_toolbar_Edit.LoadToolBar(IDR_MAINFRAME_256);
	//!m_toolbar_Edit.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)

	CStatic* staticControls[] = {
	&m_staticText_Text,
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}
}

// Static callback function




// CVertragView diagnostics

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
	}
	//Edit box
	if (ctrlID == 1002)
	{
		m_textColor_editbox = RGB(0, 0, 0);
		pDC->SetTextColor(m_textColor_editbox);       // Black text
		pDC->SetBkColor(RGB(255, 255, 180));
		// Return the brush for background color
		return m_brush_editbox;

	}*/

	return hbr;
}
