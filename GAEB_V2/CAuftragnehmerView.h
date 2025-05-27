#pragma once


// CAuftragnehmerView view

class CAuftragnehmerView : public CView
{
	DECLARE_DYNCREATE(CAuftragnehmerView)

protected:
	CAuftragnehmerView();           // protected constructor used by dynamic creation
	virtual ~CAuftragnehmerView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
	virtual void OnInitialUpdate();
#endif
#endif
protected:
	CButton *m_groupbox_Adressdaten_AN;

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

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CBrush m_brush_edit_bg_color;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


