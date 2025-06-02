#pragma once


// CHinweisText view

class CHinweisText : public CView
{
	DECLARE_DYNCREATE(CHinweisText)

protected:
	CHinweisText();           // protected constructor used by dynamic creation
	virtual ~CHinweisText();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:

	CStatic m_staticText_Hinweis;
	CStatic m_staticText_Langtext;
	CStatic m_staticText_Kurztext;

	CEdit m_edit_langtext;
	CEdit m_edit_kurztext;

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

	CFont m_font;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;

	CBrush m_edit_bg_color;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


