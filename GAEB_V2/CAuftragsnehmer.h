#pragma once
#include <afxwin.h>
#include "GAEB_V2Doc.h"
class CAuftragsnehmer :    public CView
{
protected: // create from serialization only
	CAuftragsnehmer() noexcept;
	DECLARE_DYNCREATE(CAuftragsnehmer)


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
	virtual ~CAuftragsnehmer();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CGAEBV2Doc* GetDocument() const;

#endif
protected:
	//CStatic m_GroupBox_Adresse_Daten_AN;

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
	CEdit m_edit_Steuer_AN;

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_Auftragsnehmer_View(LPCREATESTRUCT lpCreateStruct);


};

