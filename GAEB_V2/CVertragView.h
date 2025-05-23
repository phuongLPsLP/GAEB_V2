#pragma once


// CVertragView view

class CVertragView : public CView
{
	DECLARE_DYNCREATE(CVertragView)

protected:
	CVertragView();           // protected constructor used by dynamic creation
	virtual ~CVertragView();
	

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
	CStatic m_staticText_Text;
	CEdit m_edit_Text;

	CButton m_button_bold;
	CButton m_button_italic;
	CButton m_button_underline;

	CComboBox m_combobox_textSize;
	CComboBox m_combobox_textFont;

	CFont m_font;
	CFont m_font_italic;
	CFont m_font_underline;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEditBold();
};


