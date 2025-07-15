#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;


// CVertragView view

class CVertragView : public CScrollView
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
	CRect clientRect_VR;

	CButton m_button_bold;
	CButton m_button_italic;
	CButton m_button_underline;

	CComboBox m_combobox_textSize;
	CComboBox m_combobox_textFont;

	CFont m_font;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;
	CFont m_font_button;

	CBrush m_edit_bg_color;

	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEditBold();
	CString Utf8ToCString(const char* utf8Str);

};


