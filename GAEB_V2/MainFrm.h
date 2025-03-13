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

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutlookBar       m_wndNavigationBar;
	//CMFCShellTreeCtrl m_wndTree;
	CTreeCtrl m_wndClassView;
	void FillClassView();
	//CCalendarBar      m_wndCalendar;
	//CMFCCaptionBar    m_wndCaptionBar;

// Generated message map functions
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
	afx_msg void OnG90();
	afx_msg void OnUpdateG_90(CCmdUI* pCmdUI);
	afx_msg void OnG_2000();
	afx_msg void OnUpdateG_200(CCmdUI* pCmdUI);
	afx_msg void OnG_XML();
	afx_msg void OnUpdateG_XML(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_81();
	afx_msg void OnCheckbox_81_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_82();
	afx_msg void OnCheckbox_82_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_83();
	afx_msg void OnCheckbox_83_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_84();
	afx_msg void OnCheckbox_84_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_85();
	afx_msg void OnCheckbox_85_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_86();
	afx_msg void OnCheckbox_86_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_89();
	afx_msg void OnCheckbox_89_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_93();
	afx_msg void OnCheckbox_93_Update(CCmdUI* pCmdUI);
	afx_msg void OnCheckbox_94();
	afx_msg void OnCheckbox_94_Update(CCmdUI* pCmdUI);
};


