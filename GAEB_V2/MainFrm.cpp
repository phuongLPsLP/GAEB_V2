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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "GAEB_V2.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "GAEB_V2View.h"
#include "CProjektInfosView.h"
#include "CAuftraggeberView.h"
#include "CAuftragnehmerView.h"
#include "CVergabeinfosView.h"
#include "CLVInfosView.h"
#include "CLVView.h"
#include "CVertragView.h"
#include "CLVBereichView.h"
#include "CHinweisText.h"
#include "CPositionView.h"
#include "CLV_MainView.h"
#include "CDocumentClass.h"

#include <memory>

#define IDC_TREE1 1200
#define IDC_BLANKVIEW 1201

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	//ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_BUTTON52, &CMainFrame::OnExit)
	ON_COMMAND(ID_BUTTON52, &CMainFrame::OnExit)
	ON_COMMAND(ID_BUTTON48, &CMainFrame::OnNew)
	ON_COMMAND(ID_BUTTON47, &CMainFrame::OnOpenFile)
	ON_COMMAND(ID_BUTTON5, &CMainFrame::OnExport)

	ON_COMMAND(ID_CHECK3, &CMainFrame::OnDetailsAnsicht)
	ON_UPDATE_COMMAND_UI(ID_CHECK3, &CMainFrame::OnUpdateDetailsAnsicht)
	ON_COMMAND(ID_CHECK4, &CMainFrame::OnTabelleAnsicht)
	ON_UPDATE_COMMAND_UI(ID_CHECK4, &CMainFrame::OnUpdateTabelleAnsicht)
	ON_COMMAND(ID_BUTTON3, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_BUTTON3, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_BUTTON4, &CMainFrame::OnInfo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON4, &CMainFrame::OnUpdateInfo)
	ON_COMMAND(ID_CHECK_STRUKTUR, &CMainFrame::OnStrukturAnsicht)
	ON_UPDATE_COMMAND_UI(ID_CHECK_STRUKTUR, &CMainFrame::OnUpdateStrukturAnsicht)
	ON_COMMAND(ID_CHECK2, &CMainFrame::OnCheck_G90)
	ON_UPDATE_COMMAND_UI(ID_CHECK2, &CMainFrame::OnUpdateCheck_G90)
	ON_COMMAND(ID_CHECK_G2000, &CMainFrame::OnCheck_G2000)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G2000, &CMainFrame::OnUpdateCheck_G2000)
	ON_COMMAND(ID_CHECK_GXML, &CMainFrame::OnCheck_GXML)
	ON_UPDATE_COMMAND_UI(ID_CHECK_GXML, &CMainFrame::OnUpdateCheck_GXML)
	ON_COMMAND(ID_CHECK_G90, &CMainFrame::OnCheck_G90)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G90, &CMainFrame::OnUpdateCheck_G90)
	ON_COMMAND(ID_CHECK_81, &CMainFrame::OnCheck_Phase81)
	ON_UPDATE_COMMAND_UI(ID_CHECK_81, &CMainFrame::OnUpdateCheck_Phase81)
	ON_COMMAND(ID_CHECK_82, &CMainFrame::OnCheck_Phase82)
	ON_UPDATE_COMMAND_UI(ID_CHECK_82, &CMainFrame::OnUpdateCheck_Phase82)
	ON_COMMAND(ID_CHECK_83, &CMainFrame::OnCheck_Phase83)
	ON_UPDATE_COMMAND_UI(ID_CHECK_83, &CMainFrame::OnUpdateCheck_Phase83)
	ON_COMMAND(ID_CHECK_84, &CMainFrame::OnCheck_Phase84)
	ON_UPDATE_COMMAND_UI(ID_CHECK_84, &CMainFrame::OnUpdateCheck_Phase84)
	ON_COMMAND(ID_CHECK_85, &CMainFrame::OnCheck_Phase85)
	ON_UPDATE_COMMAND_UI(ID_CHECK_85, &CMainFrame::OnUpdateCheck_Phase85)
	ON_COMMAND(ID_CHECK_86, &CMainFrame::OnCheck_Phase86)
	ON_UPDATE_COMMAND_UI(ID_CHECK_86, &CMainFrame::OnUpdateCheck_Phase86)
	ON_COMMAND(ID_CHECK_89, &CMainFrame::OnCheck_Phase89)
	ON_UPDATE_COMMAND_UI(ID_CHECK_89, &CMainFrame::OnUpdateCheck_Phase89)
	ON_COMMAND(ID_CHECK_93, &CMainFrame::OnCheck_Phase93)
	ON_UPDATE_COMMAND_UI(ID_CHECK_93, &CMainFrame::OnUpdateCheck_Phase93)
	ON_COMMAND(ID_CHECK_94, &CMainFrame::OnCheck_Phase94)
	ON_UPDATE_COMMAND_UI(ID_CHECK_94, &CMainFrame::OnUpdateCheck_Phase94)
	ON_COMMAND(ID_CHECK_LV_MENGE, &CMainFrame::OnCheck_LVMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_LV_MENGE, &CMainFrame::OnUpdateCheck_LVMenge)
	ON_COMMAND(ID_CHECK_VA_MENGE, &CMainFrame::OnCheck_VAMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_VA_MENGE, &CMainFrame::OnUpdateCheck_VAMenge)
	ON_COMMAND(ID_CHECK_RE_MENGE, &CMainFrame::OnCheck_REMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_RE_MENGE, &CMainFrame::OnUpdateCheck_REMenge)
	ON_COMMAND(ID_CHECK18, &CMainFrame::OnCheck_GAEB_2000)
	ON_UPDATE_COMMAND_UI(ID_CHECK18, &CMainFrame::OnUpdateCheck_GAEB_2000)
	ON_COMMAND(ID_CHECK19, &CMainFrame::OnCheck_GAEB_XML_REB)
	ON_UPDATE_COMMAND_UI(ID_CHECK19, &CMainFrame::OnUpdateCheck_GAEB_XML_REB)
	ON_COMMAND(ID_CHECK20, &CMainFrame::OnCheck_GAEB_VB)
	ON_UPDATE_COMMAND_UI(ID_CHECK20, &CMainFrame::OnUpdateCheck_GAEB_VB)
	ON_COMMAND(ID_CHECK21, &CMainFrame::OnCheck_LV_M_Aufmaﬂ)
	ON_UPDATE_COMMAND_UI(ID_CHECK21, &CMainFrame::OnUpdateCheck_LV_M_Aufmaﬂ)
	ON_COMMAND(ID_CHECK22, &CMainFrame::OnCheck_VA_M_Aufmaﬂ)
	ON_UPDATE_COMMAND_UI(ID_CHECK22, &CMainFrame::OnUpdateCheck_VA_M_Aufmaﬂ)
	ON_COMMAND(ID_CHECK23, &CMainFrame::OnCheck_RE_M_Aufmaﬂ)
	ON_UPDATE_COMMAND_UI(ID_CHECK23, &CMainFrame::OnUpdateCheck_RE_M_Aufmaﬂ)
	ON_COMMAND(ID_BUTTON_Speichern, &CMainFrame::OnButton_Speichern)
	ON_COMMAND(ID_BUTTON_SPEICHERN_UNTER, &CMainFrame::OnButton_SpeichernUnter)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMainFrame::OnTreeSelectedItem)
END_MESSAGE_MAP()


// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

//CTreeCtrl
void CMainFrame::FillClassView()
{

	//rapidxml::file<> xmlFile("../../Test.xml");
	//rapidxml::file<> xmlFile("C:/Users/phuon/source/repos/GAEB_V2/GAEB_V2/Test.xml");
	//rapidxml::file<> xmlFile("Test.xml");
	//rapidxml::file<> xmlFile("C:/Users/marku/Downloads/07_GAEB.X83");


	/*	
	CDocumentClass* pDoc = dynamic_cast<CDocumentClass*>(GetActiveDocument());
	if (!pDoc) return;
	auto xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");
	auto xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	xmlDoc->parse<0>(xmlFile->data());
	rapidxml::xml_node<>* root = xmlDoc->first_node();	
	rapidxml::xml_node<>*  m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	rapidxml::xml_node<>* pProjektInfo = m_pGAEBInfo ? m_pGAEBInfo->next_sibling() : nullptr;
	rapidxml::xml_node<>* pAward = pProjektInfo ? pProjektInfo->next_sibling() : nullptr;
		
	pDoc->m_xmlFile = std::move(xmlFile);
	pDoc->m_xmlDoc = std::move(xmlDoc);
	pDoc->m_pGAEBInfo = m_pGAEBInfo;
	pDoc->m_pProjektInfo = pProjektInfo;
	pDoc->m_award = pAward;*/

	rapidxml::file<> xmlFile("07_GAEB.X83");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<>* root = doc.first_node();
	root->name("Leistungsverzeichnis");

	m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	m_pProjektInfo = m_pGAEBInfo->next_sibling();
	m_award = m_pProjektInfo->next_sibling();

	m_wndClassView.DeleteAllItems();

	HTREEITEM info = m_wndClassView.InsertItem(_T("Informationen"), TVI_ROOT, TVI_LAST);
	HTREEITEM gabe_info = m_wndClassView.InsertItem(_T("GAEB-Datenaustausch"), info, TVI_LAST);
	HTREEITEM project_info = m_wndClassView.InsertItem(_T("Projekt"), info, TVI_LAST);
	HTREEITEM vergabe_info = m_wndClassView.InsertItem(_T("Vergabe"), info, TVI_LAST);
//	HTREEITEM auftraggeber = m_wndClassView.InsertItem(_T("Auftraggeber"), info, TVI_LAST);
//	HTREEITEM auftragnehmer = m_wndClassView.InsertItem(_T("Auftragnehmer"), info, TVI_LAST);
	HTREEITEM vertrag_info = m_wndClassView.InsertItem(_T("Vertragliche Regelung"), info, TVI_LAST);


	m_wndClassView.Expand(info, TVE_EXPAND);


	if (!root) return;

	int maxDepth = 0;
	AddXMLToTreeCtrl(TVI_ROOT, root, 1, maxDepth);
}


int CMainFrame::AddXMLToTreeCtrl(HTREEITEM parentItem, xml_node<>* node, int currentDepth, int& maxDepth)
{
	if (!node) return currentDepth;
	if (currentDepth > maxDepth)
		maxDepth = currentDepth;
	CString nodeLabel(node->name());

	for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		CString attrName(attr->name());

		//Check if root contains any context 
		if (attrName.IsEmpty() == FALSE) 
		{
			attrName = "";	//set attribute to empty string if it is not empty
		}
		else {
			CString attrStr;
			attrStr.Format(_T(" [%S=\"%S\"]"), attr->name(), attr->value());
			nodeLabel += attrStr;
		}

	}
	HTREEITEM hItem = m_wndClassView.InsertItem(nodeLabel, parentItem);
	const char* nodeValue = node->value();
	if (nodeValue && strlen(nodeValue) > 0 && CString(nodeValue).Trim().GetLength() > 0)
	{
		//CString valueText;
		//valueText.Format(CString(nodeValue));
		CString valueText(nodeValue); 
		m_wndClassView.InsertItem(valueText, hItem);
	}
	
	for (xml_node<>* child = node->first_node(); child; child = child->next_sibling()) 
	{
		if (child->type() == rapidxml::node_element)
		{
			AddXMLToTreeCtrl(hItem, child, currentDepth + 1, maxDepth);
		}
	}

	return maxDepth;
}


void CMainFrame::OnTreeSelectedItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hSelectedItem = m_wndClassView.GetSelectedItem();
	HTREEITEM hroot = m_wndClassView.GetRootItem();
	CString itemText = m_wndClassView.GetItemText(hSelectedItem);	
	CView* pView = GetActiveView();

	if (itemText == _T("Auftraggeber")) {
		SwitchView(RUNTIME_CLASS(CAuftraggeberView));
	}
	else if (itemText == _T("Auftragnehmer")) {
		SwitchView(RUNTIME_CLASS(CAuftragnehmerView));
	}
	else if (itemText == _T("Projekt")) {
		SwitchView(RUNTIME_CLASS(CProjektInfosView));
	}
	else if (itemText == _T("Vergabe")) {
		SwitchView(RUNTIME_CLASS(CVergabeinfosView));
	}
	else if (itemText == _T("GAEB-Datenaustausch")) {
		SwitchView(RUNTIME_CLASS(CLVInfosView));
	}
	else if (itemText == _T("Vertragliche Regelung")) {
		SwitchView(RUNTIME_CLASS(CVertragView));
	}
	else if (itemText == _T("Leistungsverzeichnis")) {
		SwitchView(RUNTIME_CLASS(CLV_MainView));		
	}
	HTREEITEM parent = m_wndClassView.GetParentItem(hSelectedItem);
	CString parent_itemText = m_wndClassView.GetItemText(parent);
	if (parent_itemText == _T("Leistungsverzeichnis")) {
		if (hSelectedItem == m_wndClassView.GetChildItem(parent))
		{
			SwitchView(RUNTIME_CLASS(CHinweisText));
		}
		else {
			SwitchView(RUNTIME_CLASS(CPositionView));
		}
	}
	
	
	*pResult = 0;
}

void CMainFrame::SwitchView(CRuntimeClass* pNewViewClass)
{
	CView* pOldView = GetActiveView();
	if (pOldView == nullptr || pOldView->IsKindOf(pNewViewClass)) {
		return; // Already the correct view or invalid
	}
	CDocument* pDoc = pOldView->GetDocument();
	CCreateContext context;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = pNewViewClass;
	// Create new view
	CView* pNewView = (CView*)pNewViewClass->CreateObject();
	ASSERT(pNewView->IsKindOf(RUNTIME_CLASS(CView)));

	CRect rect;
	pOldView->GetWindowRect(&rect);
	ScreenToClient(&rect);

	pNewView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect, this, AFX_IDW_PANE_FIRST, &context);
	pNewView->OnInitialUpdate();
	SetActiveView(pNewView);
	pNewView->ShowWindow(SW_SHOW);

	pOldView->ShowWindow(SW_HIDE);
	pOldView->DestroyWindow();
	//RecalcLayout();
}

//CTreeCtrl

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);


	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Create and setup "Outlook" navigation bar:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndClassView, 250))
		//m_wndCalendar, 
	{
		TRACE0("Failed to create navigation pane\n");
		return -1;      // fail to create
	}
	
	// Create a caption bar:
	/*if (!CreateCaptionBar())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}*/

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);
	FillClassView();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CTreeCtrl& tree,  int nInitialWidth)
	//CCalendarBar& calendar
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // fail to create
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == nullptr)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	//calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	//pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

/*BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}*/

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}




#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

/*void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}
*/
void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != nullptr);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}



void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CMainFrame::DoDataExchange(pDX); // Call base class method
	DDX_Control(pDX, IDC_TREE1, m_wndClassView);
}



void CMainFrame::OnExit()
{
	// TODO: Add your command handler code here
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


void CMainFrame::OnNew()
{
	// TODO: Add your command handler code here
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(STD_FILENEW);
}


void CMainFrame::OnOpenFile()
{
	// TODO: Add your command handler code here
	/*ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(STD_FILEOPEN);*/
	CFileDialog fileDlg(TRUE, _T("txt"), nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("alle Formate (*.*) | *.*||"), this);
	if (fileDlg.DoModal() == IDOK) {
		CString filePath = fileDlg.GetPathName();
		AfxMessageBox(_T("Selected file: ") + filePath);
		//CDocument* pdoc = GetDocument();
		//OpenFileInExplorer(filePath);

	}
}


void CMainFrame::OnExport()
{
	// TODO: Add your command handler code here
}


void CMainFrame::OnDetailsAnsicht()
{
	// TODO: Add your command handler code here
	m_checkbox_Details = !m_checkbox_Details;
	m_checkbox_Tabelle = FALSE;
	
}


void CMainFrame::OnUpdateDetailsAnsicht(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_checkbox_Details ? 1 : 0); 
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnTabelleAnsicht()
{
	// TODO: Add your command handler code here	
	m_checkbox_Tabelle = !m_checkbox_Tabelle;
	m_checkbox_Details = FALSE;
}


void CMainFrame::OnUpdateTabelleAnsicht(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_Tabelle ? 1 : 0);
	pCmdUI->Enable(TRUE);
}



void CMainFrame::OnIndex()
{
	// TODO: Add your command handler code here
	CDialog dlg(IDD_DIALOG_INDEX, this);

	// Display the dialog modally
	dlg.DoModal();
}

void CMainFrame::OnUpdateIndex(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnInfo()
{
	// TODO: Add your command handler code here
	CDialog dlg(IDD_DIALOG_INFO, this);
	dlg.DoModal();
}

void CMainFrame::OnUpdateInfo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnStrukturAnsicht()
{
	// TODO: Add your command handler code here
	m_checkbox_Struktur = !m_checkbox_Struktur;
}

void CMainFrame::OnUpdateStrukturAnsicht(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here	
	pCmdUI->SetCheck(m_checkbox_Struktur ? 1 : 0); 
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_G2000()
{
	// TODO: Add your command handler code here
	m_checkbox_G2000 = !m_checkbox_G2000;
	m_checkbox_G90 = FALSE;
	m_checkbox_GXML = FALSE;
}

void CMainFrame::OnUpdateCheck_G2000(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G2000 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GXML()
{
	// TODO: Add your command handler code here
	m_checkbox_GXML = !m_checkbox_GXML;
	m_checkbox_G2000 = FALSE;
	m_checkbox_G90 = FALSE;
}

void CMainFrame::OnUpdateCheck_GXML(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GXML ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_G90()
{
	// TODO: Add your command handler code here
	m_checkbox_G90 = !m_checkbox_G90;
	m_checkbox_G2000 = FALSE;
	m_checkbox_GXML  = FALSE;
}

void CMainFrame::OnUpdateCheck_G90(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G90 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase81()
{
	// TODO: Add your command handler code here
	m_checkbox_G81 = !m_checkbox_G81;
	m_checkbox_G82 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase81(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G81 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase82()
{
	// TODO: Add your command handler code here
	m_checkbox_G82 = !m_checkbox_G82;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase82(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G82 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase83()
{
	// TODO: Add your command handler code here
	m_checkbox_G83 = !m_checkbox_G83;
	m_checkbox_G81 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;

}

void CMainFrame::OnUpdateCheck_Phase83(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G83 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase84()
{
	// TODO: Add your command handler code here
	m_checkbox_G84 = !m_checkbox_G84;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase84(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G84 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase85()
{
	// TODO: Add your command handler code here
	m_checkbox_G85 = !m_checkbox_G85;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase85(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G85 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase86()
{
	// TODO: Add your command handler code here
	m_checkbox_G86 = !m_checkbox_G86;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase86(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G86 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase89()
{
	// TODO: Add your command handler code here
	m_checkbox_G89 = !m_checkbox_G89;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase89(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G89 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase93()
{
	// TODO: Add your command handler code here
	m_checkbox_G93 = !m_checkbox_G93;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G82 = FALSE;
	m_checkbox_G94 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase93(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G93 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_Phase94()
{
	// TODO: Add your command handler code here
	m_checkbox_G94 = !m_checkbox_G94;
	m_checkbox_G81 = FALSE;
	m_checkbox_G83 = FALSE;
	m_checkbox_G84 = FALSE;
	m_checkbox_G85 = FALSE;
	m_checkbox_G86 = FALSE;
	m_checkbox_G89 = FALSE;
	m_checkbox_G93 = FALSE;
	m_checkbox_G82 = FALSE;
}

void CMainFrame::OnUpdateCheck_Phase94(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G94 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_LVMenge()
{
	// TODO: Add your command handler code here
	 m_checkbox_LVMenge = !m_checkbox_LVMenge;
	 m_checkbox_VAMenge = FALSE;
	 m_checkbox_REMenge = FALSE;
}

void CMainFrame::OnUpdateCheck_LVMenge(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_LVMenge ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_VAMenge()
{
	// TODO: Add your command handler code here
	m_checkbox_VAMenge = !m_checkbox_VAMenge;
	m_checkbox_LVMenge = FALSE;
	m_checkbox_REMenge = FALSE;
}

void CMainFrame::OnUpdateCheck_VAMenge(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_VAMenge ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_REMenge()
{
	// TODO: Add your command handler code here
	m_checkbox_REMenge = !m_checkbox_REMenge;
	m_checkbox_VAMenge = FALSE;
	m_checkbox_LVMenge = FALSE;
}

void CMainFrame::OnUpdateCheck_REMenge(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_REMenge ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GAEB_2000()
{
	// TODO: Add your command handler code here
	m_checkbox_G200_Aufmaﬂ = !m_checkbox_G200_Aufmaﬂ;
	m_checkbox_GVB_Aufmaﬂ = FALSE;
	m_checkbox_GXML_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_2000(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G200_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GAEB_XML_REB()
{
	// TODO: Add your command handler code here
	m_checkbox_GXML_Aufmaﬂ = !m_checkbox_GXML_Aufmaﬂ;
	m_checkbox_G200_Aufmaﬂ = FALSE;
	m_checkbox_GVB_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_XML_REB(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GXML_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GAEB_VB()
{
	// TODO: Add your command handler code here
	m_checkbox_GVB_Aufmaﬂ = !m_checkbox_GVB_Aufmaﬂ;
	m_checkbox_G200_Aufmaﬂ = FALSE;
	m_checkbox_GXML_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_VB(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GVB_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_LV_M_Aufmaﬂ()
{
	// TODO: Add your command handler code here
	m_checkbox_LV_M_Aufmaﬂ = !m_checkbox_LV_M_Aufmaﬂ;
	m_checkbox_RE_M_Aufmaﬂ = FALSE;
	m_checkbox_VA_M_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_LV_M_Aufmaﬂ(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_LV_M_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_VA_M_Aufmaﬂ()
{
	// TODO: Add your command handler code here
	m_checkbox_VA_M_Aufmaﬂ = !m_checkbox_VA_M_Aufmaﬂ;
	m_checkbox_LV_M_Aufmaﬂ = FALSE;
	m_checkbox_RE_M_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_VA_M_Aufmaﬂ(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_VA_M_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_RE_M_Aufmaﬂ()
{
	// TODO: Add your command handler code here
	m_checkbox_RE_M_Aufmaﬂ = !m_checkbox_RE_M_Aufmaﬂ;
	m_checkbox_VA_M_Aufmaﬂ = FALSE;
	m_checkbox_LV_M_Aufmaﬂ = FALSE;
}

void CMainFrame::OnUpdateCheck_RE_M_Aufmaﬂ(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_RE_M_Aufmaﬂ ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnButton_Speichern()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnButton_SpeichernUnter()
{
	// TODO: Add your command handler code here
}
