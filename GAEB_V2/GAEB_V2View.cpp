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
#include <vector>

using namespace std;

std::vector<CStatic*> m_control_view;

#define IDC_STATICTEXT_OZ 1001


// CGAEBV2View

IMPLEMENT_DYNCREATE(CGAEBV2View, CView)

BEGIN_MESSAGE_MAP(CGAEBV2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGAEBV2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
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
	//OnCreate_FirstView(lpCreateStruct); // Create the first view
}


void CGAEBV2View::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	//CView::OnSysCommand(nID, lParam);
	if ((nID & 0xFFF0) == SC_MINIMIZE)
	{
		// Ignore minimize command
		return;

		//CFrameWnd::OnSysCommand(nID, lParam);
	}
}
