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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "CalendarBar.h"
#include "Resource.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <map>

//#include "C:\Users\marku\Downloads\rapidxml-1.13\rapidxml-1.13\rapidxml.hpp"
//#include "C:\Users\marku\Downloads\rapidxml-1.13\rapidxml-1.13\rapidxml_utils.hpp"
//#include "C:\Users\marku\Downloads\rapidxml-1.13\rapidxml-1.13\rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;


class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
};

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:	

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	//int AddXMLToTreeCtrl(HTREEITEM parentItem, xml_node<>* node, int currentDepth, int& maxDepth);
	//int AddXMLToTreeCtrl(HTREEITEM parentItem, CString string,  xml_node<>* node, int currentDepth, int& maxDepth);
	HTREEITEM AddXMLToTreeCtrl(HTREEITEM parentItem, CString string, xml_node<>* node, int currentDepth, int& maxDepth);


protected:  // control bar embedded members

	CFont m_font;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;
	CFont m_font_title;
	CFont m_font_button;

	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutlookBar       m_wndNavigationBar;

	CTreeCtrl m_wndClassView;

	BOOL m_checkbox_Struktur = FALSE;
	BOOL m_checkbox_Tabelle = FALSE;
	BOOL m_checkbox_Details = FALSE;
	
	BOOL m_checkbox_G90 = FALSE;
	BOOL m_checkbox_G2000 = FALSE;
	BOOL m_checkbox_GXML = FALSE;

	BOOL m_checkbox_G81 = FALSE;
	BOOL m_checkbox_G82 = FALSE;
	BOOL m_checkbox_G83 = FALSE;
	BOOL m_checkbox_G84 = FALSE;
	BOOL m_checkbox_G85 = FALSE;
	BOOL m_checkbox_G86 = FALSE;
	BOOL m_checkbox_G89 = FALSE;
	BOOL m_checkbox_G93 = FALSE;
	BOOL m_checkbox_G94 = FALSE;

	BOOL m_checkbox_LVMenge = FALSE;
	BOOL m_checkbox_VAMenge = FALSE;
	BOOL m_checkbox_REMenge = FALSE;

	BOOL m_checkbox_G200_Aufmaﬂ = FALSE;
	BOOL m_checkbox_GXML_Aufmaﬂ = FALSE;
	BOOL m_checkbox_GVB_Aufmaﬂ = FALSE;

	BOOL m_checkbox_LV_M_Aufmaﬂ = FALSE;
	BOOL m_checkbox_VA_M_Aufmaﬂ = FALSE;
	BOOL m_checkbox_RE_M_Aufmaﬂ = FALSE;

	HTREEITEM LV_Main;

	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award

	void FillClassView();
	//CCalendarBar      m_wndCalendar;
	//CMFCCaptionBar    m_wndCaptionBar;

// Generated message map functions

public: 	
	rapidxml::xml_document<>* GetXmlDoc();                  // Accessor
	rapidxml::xml_node<>* GetRootNode();
	rapidxml::xml_node<>* GetGAEBInfoNode();
	rapidxml::xml_node<>* GetProjektInfoNode();
	rapidxml::xml_node<>* GetAwardNode();

	CView* m_pCurrentView = nullptr;
	std::map<CRuntimeClass*, CView*> m_viewMap;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	//afx_msg void OnViewCaptionBar();
	//afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnTreeSelectedItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void SwitchView(CRuntimeClass* pNewViewClass);
	afx_msg void Recursive_Node(xml_node<>* ctgyNode, std::vector<int> path);
	afx_msg void Recursive_Item(xml_node<>* itemNode, std::vector<int> path);
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CTreeCtrl& tree, int nInitialWidth);
		//CCalendarBar& calendar, 
	//BOOL CreateCaptionBar();

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
public:
	afx_msg void OnExit();
	afx_msg void OnNew();
	afx_msg void OnOpenFile();
	afx_msg void OnExport();
	afx_msg void OnDetailsAnsicht();
	afx_msg void OnUpdateDetailsAnsicht(CCmdUI* pCmdUI);
	afx_msg void OnTabelleAnsicht();
	afx_msg void OnUpdateTabelleAnsicht(CCmdUI* pCmdUI);
	afx_msg void OnIndex();
	afx_msg void OnUpdateIndex(CCmdUI* pCmdUI);
	afx_msg void OnInfo();
	afx_msg void OnUpdateInfo(CCmdUI* pCmdUI);
	afx_msg void OnStrukturAnsicht();
	afx_msg void OnUpdateStrukturAnsicht(CCmdUI* pCmdUI);
	afx_msg void OnCheck_G2000();
	afx_msg void OnUpdateCheck_G2000(CCmdUI* pCmdUI);
	afx_msg void OnCheck_GXML();
	afx_msg void OnUpdateCheck_GXML(CCmdUI* pCmdUI);
	afx_msg void OnCheck_G90();
	afx_msg void OnUpdateCheck_G90(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase81();
	afx_msg void OnUpdateCheck_Phase81(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase82();
	afx_msg void OnUpdateCheck_Phase82(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase83();
	afx_msg void OnUpdateCheck_Phase83(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase84();
	afx_msg void OnUpdateCheck_Phase84(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase85();
	afx_msg void OnUpdateCheck_Phase85(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase86();
	afx_msg void OnUpdateCheck_Phase86(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase89();
	afx_msg void OnUpdateCheck_Phase89(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase93();
	afx_msg void OnUpdateCheck_Phase93(CCmdUI* pCmdUI);
	afx_msg void OnCheck_Phase94();
	afx_msg void OnUpdateCheck_Phase94(CCmdUI* pCmdUI);
	afx_msg void OnCheck_LVMenge();
	afx_msg void OnUpdateCheck_LVMenge(CCmdUI* pCmdUI);
	afx_msg void OnCheck_VAMenge();
	afx_msg void OnUpdateCheck_VAMenge(CCmdUI* pCmdUI);
	afx_msg void OnCheck_REMenge();
	afx_msg void OnUpdateCheck_REMenge(CCmdUI* pCmdUI);
	afx_msg void OnCheck_GAEB_2000();
	afx_msg void OnUpdateCheck_GAEB_2000(CCmdUI* pCmdUI);
	afx_msg void OnCheck_GAEB_XML_REB();
	afx_msg void OnUpdateCheck_GAEB_XML_REB(CCmdUI* pCmdUI);
	afx_msg void OnCheck_GAEB_VB();
	afx_msg void OnUpdateCheck_GAEB_VB(CCmdUI* pCmdUI);
	afx_msg void OnCheck_LV_M_Aufmaﬂ();
	afx_msg void OnUpdateCheck_LV_M_Aufmaﬂ(CCmdUI* pCmdUI);
	afx_msg void OnCheck_VA_M_Aufmaﬂ();
	afx_msg void OnUpdateCheck_VA_M_Aufmaﬂ(CCmdUI* pCmdUI);
	afx_msg void OnCheck_RE_M_Aufmaﬂ();
	afx_msg void OnUpdateCheck_RE_M_Aufmaﬂ(CCmdUI* pCmdUI);
	afx_msg void OnButton_Speichern();
	afx_msg void OnButton_SpeichernUnter();
	afx_msg void OnLangtext();
	afx_msg void OnUpdateLangtext(CCmdUI* pCmdUI);
	afx_msg void OnKurztext();
	afx_msg void OnUpdateKurztext(CCmdUI* pCmdUI);

	CFont* GetFont() { return &m_font; }
	CFont* GetFontBold() { return &m_font_bold; }
	CFont* GetFontItalic() { return &m_font_italic; }
	CFont* GetFontUnderline() { return &m_font_underline; }
	CFont* GetFontTitle() { return &m_font_title; }

	CString Utf8ToString(const char* utf8Str);

};


