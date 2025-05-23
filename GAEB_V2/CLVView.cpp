// CLVView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CLVView.h"


// CLVView

IMPLEMENT_DYNCREATE(CLVView, CScrollView)

CLVView::CLVView()
{

}

CLVView::~CLVView()
{
}


BEGIN_MESSAGE_MAP(CLVView, CScrollView)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CLVView drawing

void CLVView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);
    //CRect rect(0, 0, 800, 600); // Initial size, will adjust later
    m_listCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
        CRect(CPoint(0,0), CSize( sizeTotal)), this, 1001);

    // Enable full row select and grid lines
    m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // Add columns
    m_listCtrl.InsertColumn(1, _T("GAEB-OZ"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(2, _T("Positionsart"), LVCFMT_CENTER, 200);
    m_listCtrl.InsertColumn(3, _T("LV-Menge"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(4, _T("Einheit"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(5, _T("Kurztext"), LVCFMT_CENTER, 300);
    m_listCtrl.InsertColumn(6, _T("Einheitpreis"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(7, _T("Gesamtbetrag"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(8, _T("Zwischensumme"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(9, _T("Bedarf"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(10, _T("Grund-Nr."), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(11, _T("Alternativ-Nr."), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(12, _T("Zuschlagsart"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(13, _T("Bezeichnung"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(14, _T("Position entfällt"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(15, _T("Zeitansatz"), LVCFMT_CENTER, 100);
    m_listCtrl.InsertColumn(16, _T("Bruttosumme"), LVCFMT_CENTER, 100);

    CHeaderCtrl* pHeader = m_listCtrl.GetHeaderCtrl();
    LOGFONT lf;
    ::ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfHeight = 18; // Font height
    lf.lfWeight = FW_BOLD;
    _tcscpy_s(lf.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.

    m_font_header.CreateFontIndirect(&lf);

    pHeader = m_listCtrl.GetHeaderCtrl();
    if (pHeader && ::IsWindow(pHeader->GetSafeHwnd()))
    {
        pHeader->SetFont(&m_font_header);
    }
    rapidxml::file<> xmlFile("Test.xml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<>* root = doc.first_node();
    root->name("Leistungsverzeichnis");

    if (!root) return;

    int maxDepth = 0;
  //  AddXMLToTreeCtrl(TVI_ROOT, root, 1, maxDepth);


    // Add sample rows
    m_listCtrl.InsertItem(0, _T(""));
    m_listCtrl.SetItemText(0, 1, _T("Vertragliche Regelung"));

    m_listCtrl.InsertItem(1, _T("Bob"));
    m_listCtrl.SetItemText(1, 1, _T("25"));
    m_listCtrl.SetItemText(1, 2, _T("Designer"));

}

void CLVView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CLVView diagnostics

#ifdef _DEBUG
void CLVView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CLVView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLVView message handlers

void CLVView::OnSize(UINT nType, int cx, int cy)
{
    CScrollView::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (m_listCtrl.GetSafeHwnd())
    {
        m_listCtrl.MoveWindow(0, 0, cx, cy);  // Stretch with window
    }
}
