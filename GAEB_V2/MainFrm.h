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

	CString m_string_phase;

	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutlookBar       m_wndNavigationBar;

	CTreeCtrl m_wndClassView;
	CImageList m_ImageList;

	BOOL m_checkbox_Struktur = FALSE;
	BOOL m_checkbox_Tabelle = FALSE;
	BOOL m_checkbox_Details = FALSE;
	
	BOOL m_checkbox_G90 = FALSE;
	BOOL m_checkbox_G2000 = FALSE;
	BOOL m_checkbox_GXML = FALSE;

	BOOL m_checkbox_LT = FALSE;
	BOOL m_checkbox_KT = FALSE;

	BOOL SetItemImage(HTREEITEM hItem, int nImage, int nSelectedImage);


	CString m_path;
	CString Kurz_text;	 
	CString m_format;

	struct Item_data
	{
		CString Full_Langtext_data;
		CString Full_Kurztext_data;
		CString Qty;
		CString QU;
		CString UP;
		CString UP1;
		CString UP2;
		CString UP3;
		CString UP4;
		CString UP5;
		CString UP6;
		CString IT;
		CString TimeQu;
		CString Total;
		CString DiscountAnteil;
		CString DiscountPauschal;
	};

	HTREEITEM LV_Main;

	CStatic m_static_Titel;
	CStatic m_static_austauschphase;
	CStatic m_static_version;

	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award
	rapidxml::xml_node<>* m_addtext = nullptr;

	void LoadXMLFile();

	void FillClassView(const CString& filePath);
	//void FillClassView();


// Generated message map functions

public: 	
	rapidxml::xml_document<>* GetXmlDoc();                  // Accessor
	rapidxml::xml_node<>* GetRootNode();
	rapidxml::xml_node<>* GetGAEBInfoNode();
	rapidxml::xml_node<>* GetProjektInfoNode();
	rapidxml::xml_node<>* GetAwardNode();



	CView* m_pCurrentView = nullptr;
	CMapPtrToPtr m_viewCache;
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
	afx_msg void SwitchView(CRuntimeClass* pNewViewClass, CView*& pViewPtr);
	afx_msg void Recursive_Node(xml_node<>* ctgyNode, std::vector<int> path, HTREEITEM parentItem);
	afx_msg void Recursive_Item(xml_node<>* itemNode, std::vector<int> path, HTREEITEM parentItem);
	
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
	afx_msg void OnUpdateExport(CCmdUI* pCmdUI);
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
	afx_msg void OnButton_Speichern();
	afx_msg void OnButton_SpeichernUnter();


	CFont* GetFont() { return &m_font; }
	CFont* GetFontBold() { return &m_font_bold; }
	CFont* GetFontItalic() { return &m_font_italic; }
	CFont* GetFontUnderline() { return &m_font_underline; }
	CFont* GetFontTitle() { return &m_font_title; }

	CString* GetFormat() { return &m_format; }
	CString& GetPath() { return filePath; }

	CString Utf8ToString(const char* utf8Str);

	afx_msg void OnKurztext();
	afx_msg void OnUpdateKurztext(CCmdUI* pCmdUI);
	afx_msg void OnLangtext();
	afx_msg void OnUpdateLangtext(CCmdUI* pCmdUI);

	CView* m_LVInfosView ;
	CView* m_PInfoView;
	CView* m_VergabeView ;
	CScrollView* m_VertragView ;
	CScrollView* m_MainView ;
	CView* m_PosView;
	CScrollView* m_LangtextView;


	int m_count_infoView = 0;
	int m_count_pView = 0;
	int m_count_vergabeView = 0;
	int m_count_vertragView = 0;
	int m_count_mainView = 0;
	int m_count_posView = 0;
	int m_count_langView = 0;

	CString fileName;
	CString filePath;

};


