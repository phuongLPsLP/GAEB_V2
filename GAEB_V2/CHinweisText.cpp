// CHinweisText.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CHinweisText.h"


// CHinweisText

IMPLEMENT_DYNCREATE(CHinweisText, CView)

CHinweisText::CHinweisText()
{

}

CHinweisText::~CHinweisText()
{
}

BEGIN_MESSAGE_MAP(CHinweisText, CView)
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
// CHinweisText drawing

void CHinweisText::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CHinweisText::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(20, 270);
	m_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

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
	
	m_staticText_Hinweis.Create(_T("Hinweis Text"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(200, 30)), this, 1001);

	m_staticText_Kurztext.Create(_T("Kurztext"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(80, 20)), this, 1001);

	CRect rcButton(140, 70, 300, 70);
	m_combobox_textFont_KT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		rcButton, this, 1003);
	m_combobox_textSize_KT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
		CRect(CPoint(330, 70), CSize(80, 20)), this, 1003);
	m_button_bold_KT.Create(_T("B"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(430, 70), CSize(30, 20)), this, 1003);
	m_button_italic_KT.Create(_T("I"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(470, 70), CSize(30, 20)), this, 1003);
	m_button_underline_KT.Create(_T("U"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(510, 70), CSize(30, 20)), this, 1003);

	m_button_bold_KT.SetFont(&m_font_bold);
	m_button_italic_KT.SetFont(&m_font_italic);
	m_button_underline_KT.SetFont(&m_font_underline);

	m_edit_kurztext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, 
		CRect(CPoint(20,110),CSize(rect.Width(), 100)), this, 1002);

	//Langtext
	m_staticText_Langtext.Create(_T("Langtext"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 230), CSize(80, 20)), this, 1001);

	CRect rcButton_LT(140, 230, 300, 70);
	m_combobox_textFont_LT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		CRect(CPoint(140, 230), CSize(160, 20)), this, 1003);
	m_combobox_textSize_LT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
		CRect(CPoint(330, 230), CSize(80, 20)), this, 1003);
	m_button_bold_LT.Create(_T("B"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(430, 230), CSize(30, 20)), this, 1003);
	m_button_italic_LT.Create(_T("I"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(470, 230), CSize(30, 20)), this, 1003);
	m_button_underline_LT.Create(_T("U"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(510, 230), CSize(30, 20)), this, 1003);

	m_button_bold_LT.SetFont(&m_font_bold);
	m_button_italic_LT.SetFont(&m_font_italic);
	m_button_underline_LT.SetFont(&m_font_underline);

	m_edit_langtext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		rect, this, 1002);

	LOGFONT lf_textFont = {};
	lf_textFont.lfCharSet = DEFAULT_CHARSET;
	lf_textFont.lfFaceName[0] = '\0';

	EnumFontFamiliesEx(dc.GetSafeHdc(), &lf_textFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&m_combobox_textFont_KT, 0);
	m_combobox_textFont_KT.SelectString(-1, _T("Segoe UI"));  // Or any preferred font*/

	EnumFontFamiliesEx(dc.GetSafeHdc(), &lf_textFont, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&m_combobox_textFont_LT, 0);
	m_combobox_textFont_LT.SelectString(-1, _T("Segoe UI"));  // Or any preferred font*/


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
	m_combobox_textSize_KT.SelectString(-1, _T("11"));


	CStatic* staticControls[] = {
	&m_staticText_Hinweis,
	&m_staticText_Kurztext,
	&m_staticText_Langtext
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font_bold);
	}


	CEdit* editControls[] = {
		&m_edit_kurztext,
		&m_edit_langtext
	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font);
		}
	}
}

// CHinweisText diagnostics

#ifdef _DEBUG
void CHinweisText::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHinweisText::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHinweisText message handlers

HBRUSH CHinweisText::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	if (ctrlID == 1002)
	{
		pDC->SetBkColor(RGB(255, 255, 200));
		// Return the brush for background color
		return m_edit_bg_color;
	}
	return hbr;
}
