#pragma once


// CPositionView view

class CPositionView : public CView
{
	DECLARE_DYNCREATE(CPositionView)

protected:
	CPositionView();           // protected constructor used by dynamic creation
	virtual ~CPositionView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate(); // first time after construct

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:

	CStatic m_staticText_Position;
	CStatic m_staticText_Ordnungszahl;
	CStatic m_staticText_Positionsart;
	CStatic m_staticText_Menge;
	CStatic m_staticText_Einheit;
	CStatic m_staticText_Kurztext;
	CStatic m_staticText_Langtext;
	CStatic m_staticText_Einheitpreis;
	CStatic m_staticText_Nachlass;
	CStatic m_staticText_Gesamtpreis;
	CStatic m_staticText_Summe;
	
	CEdit m_edit_OZ;
	CEdit m_edit_Menge;
	CEdit m_edit_Einheit;
	CComboBox m_combobox_PosArt;
	CEdit m_edit_langtext;
	CEdit m_edit_kurztext;
	CEdit m_edit_einheitpreis;
	CEdit m_edit_nachlass;
	CEdit m_edit_gesamt;
	CEdit m_edit_summe;

	CButton m_button_bold_KT;
	CButton m_button_italic_KT;
	CButton m_button_underline_KT;

	CComboBox m_combobox_textSize_KT;
	CComboBox m_combobox_textFont_KT;

	CButton m_button_bold_LT;
	CButton m_button_italic_LT;
	CButton m_button_underline_LT;

	CComboBox m_combobox_textSize_LT;
	CComboBox m_combobox_textFont_LT;

	CComboBox m_combobox_einheit;

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;

	CBrush m_edit_bg_color;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


