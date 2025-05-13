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

// GAEB_V2View.h : interface of the CGAEBV2View class
//

#pragma once
#include "GAEB_V2Doc.h"
#include "vector"

using namespace std;


class CGAEBV2View : public CView
{
protected: // create from serialization only
	CGAEBV2View() noexcept;
	DECLARE_DYNCREATE(CGAEBV2View)
	

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGAEBV2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CGAEBV2Doc* GetDocument() const;

#endif

protected:
	CStatic m_staticText_OZ;
	CStatic m_staticText_PA;
	CStatic m_staticText_KT;
	CStatic m_staticText_LT;
	CStatic m_staticText_M;
	CStatic m_staticText_ET;
	CStatic m_staticText_EP;

	CEdit m_edit_KT;
	CEdit m_edit_LT;
	CEdit m_edit_OZ;
	CEdit m_edit_M;
	CEdit m_edit_EP;
	CEdit m_edit_Hinweis;

	CComboBox m_comboBox_PA;
	CComboBox m_comboBox_ET;

	CBrush m_brush_combobox;
	CBrush m_brush_editbox;
	CBrush m_brush_static;

	COLORREF m_borderColor;
	COLORREF m_textColor_combobox;
	COLORREF m_textColor_editbox;
	COLORREF m_textColor;


/*protected:
	CStatic m_GroupBox_Adresse_Daten_AG;

	CStatic m_staticText_Name1_AG;
	CStatic m_staticText_Strasse_AG;
	CStatic m_staticText_PLZ_AG;
	CStatic m_staticText_Ort_AG;
	CStatic m_staticText_Land_AG;

	CStatic m_staticText_Ansprechpartner_AG;
	CStatic m_staticText_Telefon_AG;
	CStatic m_staticText_Fax_AG;
	CStatic m_staticText_Email_AG;
	CStatic m_staticText_IL_Num_AG;
	CStatic m_staticText_Steuer_AG;

	CEdit m_edit_Name1_AG;
	CEdit m_edit_Name2_AG;
	CEdit m_edit_Name3_AG;
	CEdit m_edit_Srasse_AG;
	CEdit m_edit_PLZ_AG;
	CEdit m_edit_Ort_AG;
	CEdit m_edit_Land_AG;
	CEdit m_edit_Ansprechpartner_AG;
	CEdit m_edit_Tel_AG;
	CEdit m_edit_Fax_AG;
	CEdit m_edit_Email_AG;
	CEdit m_edit_IL_Num_AG;
	CEdit m_edit_Steuer_AG;*/
/*protected:
	CStatic m_GroupBox_Adresse_Daten_AN;

	CStatic m_staticText_Name1_AN;
	CStatic m_staticText_Strasse_AN;
	CStatic m_staticText_PLZ_AN;
	CStatic m_staticText_Ort_AN;
	CStatic m_staticText_Land_AN;

	CStatic m_staticText_Ansprechpartner_AN;
	CStatic m_staticText_Telefon_AN;
	CStatic m_staticText_Fax_AN;
	CStatic m_staticText_Email_AN;
	CStatic m_staticText_IL_Num_AN;
	CStatic m_staticText_Steuer_AN;

	CEdit m_edit_Name1_AN;
	CEdit m_edit_Name2_AN;
	CEdit m_edit_Name3_AN;
	CEdit m_edit_Srasse_AN;
	CEdit m_edit_PLZ_AN;
	CEdit m_edit_Ort_AN;
	CEdit m_edit_Land_AN;
	CEdit m_edit_Ansprechpartner_AN;
	CEdit m_edit_Tel_AN;
	CEdit m_edit_Fax_AN;
	CEdit m_edit_Email_AN;
	CEdit m_edit_IL_Num_AN;
	CEdit m_edit_Steuer_AN;*/

protected:
	CStatic m_staticText_Name;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Beschreibung;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_Leistungsbreich;

	CEdit m_edit_Name;
	CEdit m_edit_Bezeichnung;
	CEdit m_edit_Beschreibung;
	CEdit m_edit_Waehrung;
	CEdit m_edit_Bez;
	CEdit m_edit_Leistungsbreich;

	CButton m_button_Zusatztext;



// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
	afx_msg	int OnCreate_FirstView(LPCREATESTRUCT lpCreateStruct);
	//afx_msg int OnCreate_Auftraggeber_View(LPCREATESTRUCT lpCreateStruct);
	//afx_msg int OnCreate_Auftragnehmer_View(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_Projektinfos_View(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_Vergabeninfos_View(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_Kalkulationsinfos_View(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#ifndef _DEBUG  // debug version in GAEB_V2View.cpp
inline CGAEBV2Doc* CGAEBV2View::GetDocument() const
   { return reinterpret_cast<CGAEBV2Doc*>(m_pDocument); }
#endif

