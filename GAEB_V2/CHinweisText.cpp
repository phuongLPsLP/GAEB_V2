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



	CStatic* staticControls[] = {
	&m_staticText_Hinweis
	};

	for (CStatic* pStatic : staticControls)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font_bold);
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
	if (ctrlID == 1005)
	{
		pDC->SetBkColor(RGB(255, 255, 200));
		// Return the brush for background color
		return m_edit_bg_color;
	}
	return hbr;
}
