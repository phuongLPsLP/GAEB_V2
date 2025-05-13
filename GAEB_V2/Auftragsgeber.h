#pragma once
#include <afxwin.h>
#include "GAEB_V2Doc.h"

class Auftragsgeber :   public CView
{
protected: // create from serialization only
	Auftragsgeber() noexcept;
	DECLARE_DYNCREATE(Auftragsgeber)
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	virtual ~Auftragsgeber();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CGAEBV2Doc* GetDocument() const;
#endif
protected:
	//CStatic m_GroupBox_Adresse_Daten_AG;

	CStatic m_staticText_Name1_AG;
	CStatic m_staticText_Strasse_AG;
	CStatic m_staticText_PLZ_AG;
	CStatic m_staticText_Ort_AG;
	CStatic m_staticText_Land_AG;
	CStatic m_staticText_Ansprechpartner_AG;
	CStatic m_staticText_Telefon_AG;
	CStatic m_staticText_FAX_AG;
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
	CEdit m_edit_Steuer_AG;


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_AuftragsgeberView(LPCREATESTRUCT lpCreateStruct);

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

};

