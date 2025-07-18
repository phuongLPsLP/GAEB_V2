// CProjektInfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CProjektInfosView.h"


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
}

void CProjektInfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//m_font.CreatePointFont(110, _T("Segoe UI")); // 9pt font
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect);
	CClientDC dc(this);

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_edit_small;
	::ZeroMemory(&lf_edit_small, sizeof(LOGFONT));
	lf_edit_small.lfHeight = 16;
	lf_edit_small.lfWeight = FW_NORMAL;
	_tcscpy_s(lf_edit_small.lfFaceName, _T("Segoe UI"));
	m_font_edit.CreateFontIndirect(&lf_edit_small);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 20; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);


	m_xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");
	//m_xmlFile = std::make_unique<rapidxml::file<>>("Hagmans_01761.X86");
	m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	m_xmlDoc->parse<0>(m_xmlFile->data());
	rapidxml::xml_node<>* root = m_xmlDoc->first_node();

	m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	m_pProjektInfo = m_pGAEBInfo->next_sibling();
	m_award = m_pProjektInfo->next_sibling();

	m_static_text_Title_project.Create(_T("Informationen zum Projekt"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_static_text_Title_project.SetFont(&m_font_bold);

	CStatic* staticControls_PrjInfo[] =
	{
	 &m_staticText_Name,
	 &m_staticText_Bezeichnung,
	 &m_staticText_Kurzbeschreibung,
	 &m_staticText_Waehrung,
	 &m_staticText_WaehrungBez,
	};

	for (CStatic* pStatic_PrjInfo : staticControls_PrjInfo)
	{
		pStatic_PrjInfo->DestroyWindow();
	}
	m_staticText_Name.Create(_T("Name:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(120, 20)), this, 1001);
	m_staticText_Bezeichnung.Create(_T("Bezeichnung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 90), CSize(120, 20)), this, 1001);
	m_staticText_Kurzbeschreibung.Create(_T("Kurzbeschreibung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 110), CSize(120, 20)), this, 1001);
	m_staticText_Waehrung.Create(_T("Währung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 130), CSize(120, 20)), this, 1001);
	m_staticText_WaehrungBez.Create(_T("Bezeichnung der Währung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 150), CSize(250, 20)), this, 1001);

	int yPos_ProjInfo = 70;
	for (xml_node<>* SubChild = m_pProjektInfo->first_node(); SubChild; SubChild = SubChild->next_sibling())
	{
		CString subChildText = Utf8ToCString(SubChild->value());
		if (subChildText == "") {
			subChildText = SubChild->first_node()->value();
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
			yPos_ProjInfo += 20;
			pstaticValue->SetFont(&m_font);
		}
		else {
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
			yPos_ProjInfo += 20;
			pstaticValue->SetFont(&m_font);
		}
	}
	for (CStatic* pStatic : staticControls_PrjInfo)
	{
		pStatic->SetFont(&m_font);
	}


	/*	m_staticText_Name.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(80, 20)), this, 1001);
		m_staticText_Bezeichnung.Create(_T("Bezeichnung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 60), CSize(120, 20)), this, 1001);
		m_staticText_Beschreibung.Create(_T("Beschreibung"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 160), CSize(120, 20)), this, 1001);
		m_staticText_Waehrung.Create(_T("Währung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 330), CSize(120, 20)), this, 1001);
		m_staticText_Leistungsbreich.Create(_T("Leistungsbereich"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 370), CSize(120, 20)), this, 1001);

		m_edit_Name.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 20), CSize(120, 20)), this, 1002);
		m_edit_Bezeichnung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 60), CSize(250, 80)), this, 1002);
		m_edit_Beschreibung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 160), CSize(250, 150)), this, 1002);
		m_edit_Bez.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 330), CSize(50, 20)), this, 1002);
		m_edit_Waehrung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(270,330), CSize(160, 20)), this, 1002);
		m_edit_Leistungsbreich.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 370), CSize(80, 20)), this, 1002);

		m_button_Zusatztext.Create(_T("Zusatztext"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(330, 370), CSize(100, 20)), this, 1003);

		CStatic* staticControls[] =
		{
			&m_staticText_Name,
			&m_staticText_Bezeichnung,
			&m_staticText_Beschreibung,
			&m_staticText_Waehrung,
			&m_staticText_Leistungsbreich,
		};

		for (CStatic* pStatic : staticControls)
		{
			if (pStatic->GetSafeHwnd())
				pStatic->SetFont(&m_font);
		}
		CEdit* editControls[] = {
		&m_edit_Name,
		&m_edit_Bezeichnung,
		&m_edit_Beschreibung,
		&m_edit_Waehrung,
		&m_edit_Bez,
		&m_edit_Leistungsbreich,
		};
		for (CEdit* pEdit : editControls)
		{
			if (pEdit->GetSafeHwnd())
			{
				pEdit->SetFont(&m_font_edit);
			}
		}*/
}


// CProjektInfosView diagnostics

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


// CProjektInfosView message handlers

HBRUSH CProjektInfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


CString CProjektInfosView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}