#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;


// CVertragView view

class CVertragView : public CScrollView
{
	DECLARE_DYNCREATE(CVertragView)

public:
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

	CComboBox m_combobox_textSize;
	CComboBox m_combobox_textFont;

	CBrush m_edit_bg_color;

	int y_pos_vertrag;

	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString Utf8ToCString(const char* utf8Str);

};


