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

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	m_static_text_Title_project.Create(_T("Informationen zum Projekt"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect.Width(), 50)), this, 1001);
	m_static_text_Title_project.SetFont(pMainFrame->GetFontBold());

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
		//CString subChildText(SubChild->value());
		if (subChildText == "") {
			subChildText = SubChild->first_node()->value();
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
			yPos_ProjInfo += 20;
			pstaticValue->SetFont(pMainFrame->GetFont());
		}
		else {
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(subChildText, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_ProjInfo), CSize(clientRect.Width(), 20)), this, 1001);
			yPos_ProjInfo += 20;
			pstaticValue->SetFont(pMainFrame->GetFont());
		}
	}
	for (CStatic* pStatic : staticControls_PrjInfo)
	{
		pStatic->SetFont(pMainFrame->GetFont());
	}	
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
	if (ctrlID == 1001)
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