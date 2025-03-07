// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// GAEB_V2View.cpp : implementation of the CGAEBV2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GAEB_V2.h"
#endif



#include "GAEB_V2Doc.h"
#include "GAEB_V2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


#define IDC_STATICTEXT_OZ 1001


// CGAEBV2View

IMPLEMENT_DYNCREATE(CGAEBV2View, CView)

BEGIN_MESSAGE_MAP(CGAEBV2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGAEBV2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CGAEBV2View construction/destruction

CGAEBV2View::CGAEBV2View() noexcept
{
	// TODO: add construction code here

}

CGAEBV2View::~CGAEBV2View()
{
}

BOOL CGAEBV2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

// CGAEBV2View drawing

void CGAEBV2View::OnDraw(CDC* pDC)
{
	CGAEBV2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
}



// CGAEBV2View printing


void CGAEBV2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGAEBV2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGAEBV2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGAEBV2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGAEBV2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGAEBV2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGAEBV2View diagnostics

#ifdef _DEBUG
void CGAEBV2View::AssertValid() const
{
	CView::AssertValid();
}

void CGAEBV2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGAEBV2Doc* CGAEBV2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGAEBV2Doc)));
	return (CGAEBV2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGAEBV2View message handlers


int CGAEBV2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CPoint pt(400, 430);
	CSize sz(70, 30);
	

	// TODO:  Add your specialized creation code here
	m_staticText_OZ.Create(_T("Ordnungszahl"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint(50, 40), CSize(100,20)),this, 1001);
	m_staticText_PA.Create(_T("Positionsart"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint(50, 80), CSize( 100, 20)),this, 1001);
	m_staticText_KT.Create(_T("Kurztext"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint(50, 120),CSize(100, 20)),this, 1001);
	m_staticText_LT.Create(_T("Langtext"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint( 50, 200), CSize( 100, 20)), this, 1001);
	m_staticText_M.Create(_T("Menge"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint( 50, 430), CSize( 100, 20)),this,  1001);
	m_staticText_ET.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE | SS_LEFT,CRect(pt,sz), this, 1001);
	m_staticText_EP.Create(_T("Einheitpreis"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(CPoint(50, 490), CSize(100, 20)), this, 1001);




	//Edit Box
	/*m_edit_KT.SetWindowText(_T("Hello, MFC!")); // Set text
	CString str_kurztext;
	m_edit_KT.GetWindowText(str_kurztext); // Get text*/

	m_edit_OZ.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |SS_LEFT, CRect(CPoint(200, 40), CSize(80, 20)), this, 1002);
	m_edit_M.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE   | SS_RIGHT, CRect(CPoint(200,430), CSize(100, 20)), this, 1002);
	m_edit_KT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, CRect(CPoint(200, 120), CSize (700, 50)), this, 1002);
	m_edit_LT.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, CRect(CPoint(200, 200), CSize(700, 200)), this, 1002);
	m_edit_EP.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, CRect(CPoint(200, 490), CSize(100, 20)), this, 1002);
	
	//Hinweistext --> nur Kurztext_editbox und Hinweistext_editbox
	
	m_edit_Hinweis.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, CRect(), this, 1002);
	//Combox box 

	//PosArt
	m_comboBox_PA.Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | CBS_DROPDOWNLIST, CRect(CPoint(200,80), CSize(300,20)), this, 1003);
	m_comboBox_PA.AddString(_T("A - Alternativposition"));
	m_comboBox_PA.AddString(_T("B - Bedarfposition mit Grundpreis"));
	m_comboBox_PA.AddString(_T("E - Bedarfposition ohne Grundpreis"));
	m_comboBox_PA.AddString(_T("G - Grundposition"));
	m_comboBox_PA.AddString(_T("H - Hinweistext"));
	m_comboBox_PA.AddString(_T("N - Normalposistion"));
	m_comboBox_PA.AddString(_T("W - Wahlposition"));
	m_comboBox_PA.AddString(_T("Z - Zuschlagposition"));



	//Einheit
	m_comboBox_ET.Create(WS_CHILD | WS_VISIBLE |ES_MULTILINE| CBS_DROPDOWNLIST, CRect(CPoint(550, 430), CSize(100, 30)), this, 1003);
	m_comboBox_ET.AddString(_T("Stk"));
	m_comboBox_ET.AddString(_T("m"));
	m_comboBox_ET.AddString(_T("m2"));
	m_comboBox_ET.AddString(_T("m3"));
	m_comboBox_ET.AddString(_T("psch"));
	m_comboBox_ET.AddString(_T("pkg"));
	m_comboBox_ET.AddString(_T("kg"));
	m_comboBox_ET.AddString(_T("t"));
	m_comboBox_ET.AddString(_T("Std"));
	m_comboBox_ET.AddString(_T("Min"));
	
	//Set custom colors
	m_brush_combobox.CreateSolidBrush(RGB(200, 220, 255));
	m_brush_editbox.CreateSolidBrush(RGB(255, 255, 180));
	m_brush_static.CreateSolidBrush(RGB(200, 220, 255));

	//Set text colors
	m_textColor = RGB(0, 0, 0);
	m_textColor_combobox = RGB(0, 0, 0);
	m_textColor_editbox = RGB(0, 0, 0);

	return 0;
}




HBRUSH CGAEBV2View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	int ctrlID = pWnd->GetDlgCtrlID();

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}

	//Combobox
	if (ctrlID == 1003)
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
	}
	return hbr;
}
