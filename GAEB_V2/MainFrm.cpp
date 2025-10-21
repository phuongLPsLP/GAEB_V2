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

#define WM_UPDATE_SCROLLVIEW  (WM_APP + 1)

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
#include "CLangtextView.h"
#include "CProgressDialog.h"

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

	ON_COMMAND(ID_BUTTON3, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_BUTTON3, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_BUTTON4, &CMainFrame::OnInfo)
	ON_UPDATE_COMMAND_UI(ID_BUTTON4, &CMainFrame::OnUpdateInfo)
	ON_COMMAND(ID_CHECK_STRUKTUR, &CMainFrame::OnStrukturAnsicht)
	ON_UPDATE_COMMAND_UI(ID_CHECK_STRUKTUR, &CMainFrame::OnUpdateStrukturAnsicht)
	ON_COMMAND(ID_CHECK_G2000, &CMainFrame::OnCheck_G2000)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G2000, &CMainFrame::OnUpdateCheck_G2000)
	ON_COMMAND(ID_CHECK_GXML, &CMainFrame::OnCheck_GXML)
	ON_UPDATE_COMMAND_UI(ID_CHECK_GXML, &CMainFrame::OnUpdateCheck_GXML)
	ON_COMMAND(ID_CHECK_G90, &CMainFrame::OnCheck_G90)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G90, &CMainFrame::OnUpdateCheck_G90)	
	ON_COMMAND(ID_CHECK_LV_MENGE, &CMainFrame::OnCheck_LVMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_LV_MENGE, &CMainFrame::OnUpdateCheck_LVMenge)
	ON_COMMAND(ID_CHECK_VA_MENGE, &CMainFrame::OnCheck_VAMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_VA_MENGE, &CMainFrame::OnUpdateCheck_VAMenge)
	ON_COMMAND(ID_CHECK_RE_MENGE, &CMainFrame::OnCheck_REMenge)
	ON_UPDATE_COMMAND_UI(ID_CHECK_RE_MENGE, &CMainFrame::OnUpdateCheck_REMenge)
	ON_COMMAND(ID_BUTTON_Speichern, &CMainFrame::OnButton_Speichern)
	ON_COMMAND(ID_BUTTON_SPEICHERN_UNTER, &CMainFrame::OnButton_SpeichernUnter)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMainFrame::OnTreeSelectedItem)

	ON_COMMAND(ID_KURZTEXT, &CMainFrame::OnKurztext)
	ON_UPDATE_COMMAND_UI(ID_KURZTEXT, &CMainFrame::OnUpdateKurztext)
	ON_COMMAND(ID_LANGTEXT, &CMainFrame::OnLangtext)
	ON_UPDATE_COMMAND_UI(ID_LANGTEXT, &CMainFrame::OnUpdateLangtext)
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
rapidxml::xml_document<>* CMainFrame::GetXmlDoc()
{
	return m_xmlDoc.get();  // if you're using unique_ptr
}
rapidxml::xml_node<>* CMainFrame::GetRootNode() {
	return m_root;  // if you're using unique_ptr
}
rapidxml::xml_node<>* CMainFrame::GetGAEBInfoNode() {
	return m_pGAEBInfo;  // if you're using unique_ptr
}
rapidxml::xml_node<>* CMainFrame::GetProjektInfoNode()
{
	return m_pProjektInfo;  // if you're using unique_ptr
}
rapidxml::xml_node<>* CMainFrame::GetAwardNode()
{
	return m_award;  // if you're using unique_ptr
}
void CMainFrame::LoadXMLFile()
{
	CProgressDialog dlg;
	dlg.Create(IDD_PROGRESS, this);
	dlg.ShowWindow(SW_SHOW);

	for (int i = 0; i <= 100; i++)
	{
		CString msg;
		msg.Format(_T("GAEB Daten werden eingelesen [%d%%]"), i);
		dlg.SetMessage(msg);
		
		dlg.SetProgress(i);
		AfxPumpMessage();
		Sleep(20);  

	}
	dlg.DestroyWindow();
}
//void CMainFrame::FillClassView()
void CMainFrame::FillClassView(const CString& filePath)
{
	CT2A asciiPath(filePath);
	m_xmlFile = std::make_unique<rapidxml::file<>>(asciiPath);
	//m_xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");

	m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	m_xmlDoc->parse<0>(m_xmlFile->data());
	m_root = m_xmlDoc->first_node();
	m_root->name("Leistungsverzeichnis");

	m_pGAEBInfo = m_root->first_node("GAEBInfo");
	m_pProjektInfo = m_pGAEBInfo ? m_pGAEBInfo->next_sibling("PrjInfo") : nullptr;
	m_award = m_pProjektInfo ? m_pProjektInfo->next_sibling("Award") : nullptr;
	m_addtext = m_award ? m_award->next_sibling("AddText") : nullptr;

	m_wndClassView.DeleteAllItems();

	HTREEITEM info = m_wndClassView.InsertItem(_T("Informationen"), TVI_ROOT, TVI_LAST);
	HTREEITEM project_info = m_wndClassView.InsertItem(_T("Projekt"), info, TVI_LAST);
	HTREEITEM vergabe_info = m_wndClassView.InsertItem(_T("Vergabe"), info, TVI_LAST);
	HTREEITEM vertrag_info = m_wndClassView.InsertItem(_T("Vertragliche Regelung"), info, TVI_LAST);
	LV_Main = m_wndClassView.InsertItem(_T("Leistungsverzeichnis"), TVI_ROOT, TVI_LAST);

	m_wndClassView.Expand(info, TVE_EXPAND);

	if (!m_root) return;

	if (!m_award) return;

	xml_node<>* boqNode = m_award->first_node("BoQ");
	if (!boqNode) return;

	xml_node<>* boQbodyNode = boqNode->first_node("BoQBody");
	if (!boQbodyNode) return;

	std::vector<int> rootPath;


	for (xml_node<>* child_node = boQbodyNode->first_node(); child_node; child_node = child_node->next_sibling()) {
		Recursive_Node(child_node, rootPath, LV_Main);
	}

	m_wndClassView.Expand(LV_Main, TVE_EXPAND);	
	HTREEITEM hDefault = m_wndClassView.GetChildItem(info);
	if (!hDefault) {
		hDefault = info;
	}
	m_wndClassView.SelectItem(hDefault);
	m_wndClassView.EnsureVisible(hDefault);
	OnTreeSelectedItem(nullptr, nullptr);
}

HTREEITEM CMainFrame::AddXMLToTreeCtrl(HTREEITEM parentItem, CString string, xml_node<>* node, int currentDepth, int& maxDepth)
//int CMainFrame::AddXMLToTreeCtrl(HTREEITEM parentItem, CString string, xml_node<>* node, int currentDepth, int& maxDepth)
{
	if (!node) return parentItem;
	//if (!node) return currentDepth;
	if (currentDepth > maxDepth)
		maxDepth = currentDepth;

	HTREEITEM hItem = m_wndClassView.InsertItem(string, parentItem);

	for (xml_node<>* child = node->first_node(); child; child = child->next_sibling())
	{		
		if (child->type() == rapidxml::node_element && CString(child->name()) != _T("LblTx"))
		{
			CString childText(child->name());

			if(child->value() && strlen(child->value()) > 0)
			{
				childText += _T(": ");
				childText += Utf8ToString(child->value());	
			}
			AddXMLToTreeCtrl(hItem, childText, child, currentDepth + 1, maxDepth);
		}
	}
	return hItem;
}


void CMainFrame::OnTreeSelectedItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	if (!pNMTreeView) return;  // safety check
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (!hItem) return;
	HTREEITEM hSelectedItem = m_wndClassView.GetSelectedItem();
	HTREEITEM hroot = m_wndClassView.GetRootItem();
	CString itemText = m_wndClassView.GetItemText(hSelectedItem);	
	CView* pView = GetActiveView();

	m_wndClassView.SetFocus();

	if (itemText == _T("Informationen")) {
		SwitchView(RUNTIME_CLASS(CLVInfosView));	
	}
	else if (itemText == _T("Projekt")) {
		SwitchView(RUNTIME_CLASS(CProjektInfosView));
	}
	else if (itemText == _T("Vergabe")) {
		SwitchView(RUNTIME_CLASS(CVergabeinfosView));
	}
	else if (itemText == _T("Vertragliche Regelung")) {
		SwitchView(RUNTIME_CLASS(CVertragView));
	}
	else if (itemText == _T("Leistungsverzeichnis")) {
		m_checkbox_KT = TRUE;
		m_checkbox_LT = FALSE;

		SwitchView(RUNTIME_CLASS(CLV_MainView));		
	}
	else {
		/*SwitchView(RUNTIME_CLASS(CLangtextView));
		CLangtextView* plistView = DYNAMIC_DOWNCAST(CLangtextView, pView);
		if (plistView) {
			plistView->SelectItemByText(itemText);
		}*/

		CPositionView* pposView = DYNAMIC_DOWNCAST(CPositionView, GetActiveView());
		if (pposView) 
		{
			pposView->SetTextOZ(itemText);	//Ornungszahl und Bezeichnung setzen
		}
	}
	if (pResult) {
		*pResult = 0;
	}

}

void CMainFrame::SwitchView(CRuntimeClass* pNewViewClass)
{
	/*if (m_pCurrentView && m_pCurrentView->IsKindOf(pNewViewClass)) {
		return;
	}

	CView* pnewView = nullptr;
	CView* pOldView;
	if (!m_viewCache.Lookup(pNewViewClass, (void*&)pnewView)) {
		pOldView = GetActiveView();
		CDocument* pDoc = pOldView ? pOldView->GetDocument() : nullptr;
		CCreateContext context;
		context.m_pCurrentDoc = pDoc;
		context.m_pNewViewClass = pNewViewClass;

		pnewView = (CView*)pNewViewClass->CreateObject();
		ASSERT(pnewView->IsKindOf(RUNTIME_CLASS(CView)));

		CRect rect;
		if (pOldView) {
			pOldView->GetWindowRect(&rect);
			ScreenToClient(&rect);
		}
		else {
			GetClientRect(&rect);
		}
		pnewView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect, this, AFX_IDW_PANE_FIRST, &context);
		pnewView->OnInitialUpdate();

		m_viewCache.SetAt(pNewViewClass, pnewView);
	}

	if (m_pCurrentView) 
	{
		m_pCurrentView->ShowWindow(SW_HIDE);

	}

	pnewView->ShowWindow(SW_SHOW);
	SetActiveView(pnewView);
	m_pCurrentView = pnewView;*/

	
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

void CMainFrame::Recursive_Node(xml_node<>* ctgyNode, std::vector<int> path, HTREEITEM parentItem)
{
	int ctgyCount = 0;
	std::vector<int> currentPath = path;
	if (auto* attr = ctgyNode->first_attribute("RNoPart"))
		ctgyCount = atoi(attr->value());
	currentPath.push_back(ctgyCount);

	CString formattedPath;
	for (size_t i = 0; i < currentPath.size(); ++i)
	{
		formattedPath.AppendFormat(_T("%d"), currentPath[i]);
		//if (i < currentPath.size() - 1)
		formattedPath.Append(_T(". "));
	}
	m_path = formattedPath;

	xml_node<>* bodyNode = ctgyNode->first_node("BoQBody");
	xml_node<>* ctgyNode_child = ctgyNode->first_node("BoQCtgy");

	if (bodyNode) 
	{
		xml_node<>* lblTx = ctgyNode->first_node("LblTx");
		xml_node<>* itemList = bodyNode->first_node("Itemlist");
		CString Full_lbltx;
		// LblTx 
		if (lblTx) {
			CString lblText;
			for (xml_node<>* span = lblTx->first_node(); span; span = span->next_sibling()) {
				CString node_name(span->name());
				if (node_name == "p") {
					for (xml_node<>* p_node = span->first_node(); p_node; p_node = p_node->next_sibling()){
						CString span_text = Utf8ToString(p_node->value());
						if (!span_text.IsEmpty()) {
							lblText += span_text;
						}
					}
				}
				else if (node_name == "span") {
					lblText += Utf8ToString(span->value());
					//Kurz_text = lblText;
					//m_path = formattedPath;
				}
			}
			Full_lbltx = formattedPath + lblText;
		}
		HTREEITEM thisItem = m_wndClassView.InsertItem(Full_lbltx, parentItem);

		if (itemList) {
			Recursive_Item(itemList, currentPath, thisItem);
		}

		for (xml_node<>* ctgy_child_node = bodyNode->first_node("BoQCtgy"); ctgy_child_node;
			ctgy_child_node = ctgy_child_node->next_sibling("BoQCtgy")) {
			Recursive_Node(ctgy_child_node, currentPath, thisItem);
		}
	}


}

void CMainFrame::Recursive_Item(xml_node<>* itemNode, std::vector<int> path, HTREEITEM parentItem)
{
	int itemCount = 0;

	for (xml_node<>* item = itemNode->first_node("Item"); item; item = item->next_sibling("Item"))
	{
		itemCount++;
		std::vector<int> currentPath_item = path;
		currentPath_item.push_back(itemCount);

		// Format like "1.2.3"
		CString formattedPath_item;
		for (size_t i = 0; i < currentPath_item.size(); ++i)
		{
			formattedPath_item.AppendFormat(_T("%d"), currentPath_item[i]);
			//if (i < currentPath_item.size() - 1)
			formattedPath_item.Append(_T(". "));
		}	

		for(xml_node<>* item_child = item->first_node(); item_child; item_child = item_child->next_sibling())
		{
			CString tag(item_child->name());
			CString Fulltext;

			if(tag == "Description")
			{
				xml_node<>* complete_txt_node = item_child->first_node();	

				for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
				{
					CString compl_text_name(compl_text->name());
					//Kurztext
					if (compl_text_name == "OutlineText") {
						for (xml_node<>* OutlTxt = compl_text->first_node(); OutlTxt; OutlTxt = OutlTxt->next_sibling()) //Text
						{
							for (xml_node<>* TextOutlTxt = OutlTxt->first_node(); TextOutlTxt; TextOutlTxt = TextOutlTxt->next_sibling()) //p
							{
								for (xml_node<>* p_node_kurztext = TextOutlTxt->first_node(); p_node_kurztext; p_node_kurztext = p_node_kurztext->next_sibling())	//span
								{
									for (xml_node<>* span_node_kurztext = p_node_kurztext->first_node(); span_node_kurztext; span_node_kurztext = span_node_kurztext->next_sibling())	//span
									{
										CString span_node_kurztext_text = Utf8ToString(span_node_kurztext->value());
										if (!span_node_kurztext_text.IsEmpty()) {
											Fulltext += span_node_kurztext_text;
											Fulltext = formattedPath_item + Fulltext;			

											int maxDepth_item = 0;
											m_wndClassView.InsertItem(Fulltext, parentItem);
											//AddXMLToTreeCtrl(parentItem, Fulltext, item, 1, maxDepth_item);
										}
									}
								}
							}
						}
					}
				}			
			}
		}
	}
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	//Create font
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 20; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI"));
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_italic;
	::ZeroMemory(&lf_italic, sizeof(LOGFONT));
	lf_italic.lfHeight = 18; // Font height
	lf_italic.lfWeight = FW_NORMAL;
	lf_italic.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_italic.lfFaceName, _T("Segoe UI"));
	m_font_italic.CreateFontIndirect(&lf_italic);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18; // Font height
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfUnderline = TRUE; // Italic
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI"));
	m_font_underline.CreateFontIndirect(&lf_underline);

	LOGFONT lf_font_title;
	::ZeroMemory(&lf_font_title, sizeof(LOGFONT));
	lf_font_title.lfHeight = 18; // Font height
	lf_font_title.lfWeight = FW_BOLD;
	lf_font_title.lfItalic = TRUE; // Underline
	_tcscpy_s(lf_font_title.lfFaceName, _T("Segoe UI"));
	m_font_title.CreateFontIndirect(&lf_font_title);

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

	//FillClassView();

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
	CFileDialog fileDlg(TRUE, _T("txt"), nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("alle Formate (*.*) | *.*||"), this);
	if (fileDlg.DoModal() == IDOK) {
		CString filePath = fileDlg.GetPathName();
		CString fileName = fileDlg.GetFileName();

		CString ext = PathFindExtension(filePath);
		if (ext.CompareNoCase(_T(".X80")) == 0) {
			m_string_phase = _T("X80 Universelle LV-Daten");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X81")) == 0) {
			m_string_phase = _T("X81 Leistungsbeschreibung");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X82")) == 0) {
			m_string_phase = _T("X82 Kostenanschlag");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X83")) == 0) {
			m_string_phase = _T("X83 Angebotsaufforderung");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X84")) == 0) {
			m_string_phase = _T("X84 Angebotsabgabe");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X85")) == 0) {
			m_string_phase = _T("X85 Nebenangebot");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X86")) == 0) {
			m_string_phase = _T("X86 Auftragserteilung");
			m_checkbox_GXML = TRUE;
		}
		else if (ext.CompareNoCase(_T(".X94")) == 0) {
			m_string_phase = _T("X94 Handel - Preisangebot");
			m_checkbox_GXML = TRUE;
		}

//GAEB 2000
		else if (ext.CompareNoCase(_T(".P81")) == 0) {
			m_string_phase = _T("P81 Leistungsbeschreibung");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P82")) == 0) {
			m_string_phase = _T("P82 Kostenanschlag");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P83")) == 0) {
			m_string_phase = _T("P83 Angebotsaufforderung");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P84")) == 0) {
			m_string_phase = _T("P84 Angebotsabgabe");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P85")) == 0) {
			m_string_phase = _T("P85 Nebenangebot");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P86")) == 0) {
			m_string_phase = _T("P86 Auftragserteilung");
			m_checkbox_G2000 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".P94")) == 0) {
			m_string_phase = _T("P94 Handel - Preisangebot");
			m_checkbox_G2000 = TRUE;
		}
//GAEB 90
		else if (ext.CompareNoCase(_T(".D81")) == 0) {
			m_string_phase = _T("D81 Leistungsbeschreibung");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D82")) == 0) {
			m_string_phase = _T("D82 Kostenanschlag");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D83")) == 0) {
			m_string_phase = _T("D83 Angebotsaufforderung");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D84")) == 0) {
			m_string_phase = _T("D84 Angebotsabgabe");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D85")) == 0) {
			m_string_phase = _T("D85 Nebenangebot");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D86")) == 0) {
			m_string_phase = _T("D86 Auftragserteilung");
			m_checkbox_G90 = TRUE;
		}

		FillClassView(filePath);

		CDocument* pDoc = GetActiveDocument();
		if (pDoc) {
			pDoc->SetTitle(fileName);
		}
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
	m_checkbox_G200_Aufmaß = !m_checkbox_G200_Aufmaß;
	m_checkbox_GVB_Aufmaß = FALSE;
	m_checkbox_GXML_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_2000(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G200_Aufmaß ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GAEB_XML_REB()
{
	// TODO: Add your command handler code here
	m_checkbox_GXML_Aufmaß = !m_checkbox_GXML_Aufmaß;
	m_checkbox_G200_Aufmaß = FALSE;
	m_checkbox_GVB_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_XML_REB(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GXML_Aufmaß ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GAEB_VB()
{
	// TODO: Add your command handler code here
	m_checkbox_GVB_Aufmaß = !m_checkbox_GVB_Aufmaß;
	m_checkbox_G200_Aufmaß = FALSE;
	m_checkbox_GXML_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_GAEB_VB(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GVB_Aufmaß ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_LV_M_Aufmaß()
{
	// TODO: Add your command handler code here
	m_checkbox_LV_M_Aufmaß = !m_checkbox_LV_M_Aufmaß;
	m_checkbox_RE_M_Aufmaß = FALSE;
	m_checkbox_VA_M_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_LV_M_Aufmaß(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_LV_M_Aufmaß ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_VA_M_Aufmaß()
{
	// TODO: Add your command handler code here
	m_checkbox_VA_M_Aufmaß = !m_checkbox_VA_M_Aufmaß;
	m_checkbox_LV_M_Aufmaß = FALSE;
	m_checkbox_RE_M_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_VA_M_Aufmaß(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_VA_M_Aufmaß ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_RE_M_Aufmaß()
{
	// TODO: Add your command handler code here
	m_checkbox_RE_M_Aufmaß = !m_checkbox_RE_M_Aufmaß;
	m_checkbox_VA_M_Aufmaß = FALSE;
	m_checkbox_LV_M_Aufmaß = FALSE;
}

void CMainFrame::OnUpdateCheck_RE_M_Aufmaß(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_RE_M_Aufmaß ? 1 : 0);
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

CString CMainFrame::Utf8ToString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;	
	//return CString();
}



void CMainFrame::OnKurztext()
{
	// TODO: Add your command handler code here
	m_checkbox_KT = !m_checkbox_KT;
	m_checkbox_LT = FALSE;
	SwitchView(RUNTIME_CLASS(CLV_MainView));
}

void CMainFrame::OnUpdateKurztext(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_KT ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnLangtext()
{
	// TODO: Add your command handler code here
	m_checkbox_LT = !m_checkbox_LT;
	m_checkbox_KT = FALSE;
	SwitchView(RUNTIME_CLASS(CLangtextView));
}

void CMainFrame::OnUpdateLangtext(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_LT ? 1 : 0);
	pCmdUI->Enable(TRUE);
}
