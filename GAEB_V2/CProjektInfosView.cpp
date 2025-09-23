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


	y_pos_projectinfo = 70;

	for (xml_node<>* prjInfo_node = m_pProjektInfo->first_node(); prjInfo_node; prjInfo_node = prjInfo_node->next_sibling())
	{
		CString value = Utf8ToCString(prjInfo_node->value()); ;
		CString name(Utf8ToCString(prjInfo_node->name()));

		if (name == "NamePrj"){ name = _T("Name:"); }
		else if( name == "LblPrj"){ name = _T("Bezeichnung:");}
		else if (name == "Cur"){ name = _T("Währung:"); }
		else if (name == "CurLbl"){ name = _T("Bezeichnung der Währung:"); }
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