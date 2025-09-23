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
						this, 1001);
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
					CRect(CPoint(20, y_pos_vertrag), CSize(clientRect_VR.Width(), 30)), this, 1001);
				y_pos_vertrag += textRect.Height() + 20;
				pstaticValue->SetFont(pMainFrame->GetFont());
			}
		}
	}
	int finalY = y_pos_vertrag;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(clientRect_VR.Width(), finalY + 20));
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
