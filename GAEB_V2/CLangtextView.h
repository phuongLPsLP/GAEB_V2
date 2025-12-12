#pragma once


#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CLangtextView view

class CLangtextView : public CScrollView
{
	DECLARE_DYNCREATE(CLangtextView)

public:
	CLangtextView();           // protected constructor used by dynamic creation
	virtual ~CLangtextView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CRect clientRect;

	CStatic m_staticText_Title_LV_Langtext;
	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

	CStatic m_staticText_OZ_LT;
	CStatic m_staticText_Menge_LT;
	CStatic m_staticText_Einheit_LT;
	CStatic m_staticText_LeiBe_LT;
	CStatic m_staticText_Einheitpreis_LT;
	CStatic m_staticText_Gesamtpreis_LT;

	int index_item;
	int x_pos_leitung;

	CSize m_wndSize;

	CBrush m_brush_edit_bg_color;
	std::vector<CStatic*> m_vecStatics_GAEBInfo;

public:
	virtual void OnDraw(CDC* pDC);      
	virtual void OnInitialUpdate();     
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString Utf8ToCString(const char* utf8Str);
	void TraverseBoQCtgy_LT(xml_node<>* ctgyNode, int& index, std::vector<int> levelPath);
	void TraverseItemlist_LT(xml_node<>* itemList, int& index, std::vector<int> levelPath);
	void TraverseRemark_LT(xml_node<>* descNode, int& index);

};


