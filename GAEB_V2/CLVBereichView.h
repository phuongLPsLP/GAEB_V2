#pragma once


// CLVBereichView view

class CLVBereichView : public CView
{
	DECLARE_DYNCREATE(CLVBereichView)

protected:
	CLVBereichView();           // protected constructor used by dynamic creation
	virtual ~CLVBereichView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected: 
	CStatic m_staticText_LV_Bereich;
	CStatic m_staticText_OZ;
	CStatic m_staticText_PosArt;
	CStatic m_statticText_Bezeichnung;

	CButton *m_groupbox_Summe;

	CStatic m_staticText_Summe;
	CStatic m_staticText_Nachlass_Anteil;
	CStatic m_staticText_Nachlass;
	CStatic m_staticText_Summe_nach_Nachlass;
	CStatic m_staticText_Pauschalsumme;
	CStatic m_StaticText_Ust;
	CStatic m_staticText_Summe_LV_Bereich;

	CEdit m_edit_oz;
	CComboBox m_combobox_posArt;
	CEdit m_edit_bezeichnung;

	CEdit m_edit_summe;
	CEdit m_edit_nachlass_anteil;
	CEdit m_edit_nachlass;
	CEdit m_edit_summe_nach_nachlass;
	CEdit m_edit_pauschal;
	CEdit m_edit_ust;
	CEdit m_edit_summe_bereich;

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CFont m_font_button;
	CBrush m_brush_edit_bg_color;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


