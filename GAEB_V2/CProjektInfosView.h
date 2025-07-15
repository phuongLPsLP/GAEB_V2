#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CProjektInfosView view

class CProjektInfosView : public CView
{
	DECLARE_DYNCREATE(CProjektInfosView)

protected:
	CProjektInfosView();           // protected constructor used by dynamic creation
	virtual ~CProjektInfosView();

protected:
	/*CStatic m_staticText_Name;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Beschreibung;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_Leistungsbreich;

	CEdit m_edit_Name;
	CEdit m_edit_Bezeichnung;
	CEdit m_edit_Beschreibung;
	CEdit m_edit_Waehrung;
	CEdit m_edit_Bez;
	CEdit m_edit_Leistungsbreich;

	CButton m_button_Zusatztext;*/
	CStatic m_static_text_Title_project;

	CStatic m_staticText_Name;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Kurzbeschreibung;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_WaehrungBez;

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CBrush m_brush_edit_bg_color;

	CRect clientRect;
	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


