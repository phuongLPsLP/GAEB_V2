#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CLV_MainView view

class CLV_MainView : public CScrollView
{
	DECLARE_DYNCREATE(CLV_MainView)

protected:
	CLV_MainView();           // protected constructor used by dynamic creation
	virtual ~CLV_MainView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate(); // called first time after construct
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	std::vector<CStatic*> m_vecStatics_GAEBInfo;
	std::vector<CStatic*> m_vecStatics_Prjnfo;
	std::vector<CStatic*> m_vecStatics_VergInfo;
	std::vector<CStatic*> m_vecStatics_LVInfo;
	std::vector<CStatic*> m_vecStatics_RegInfo;
	std::vector<CStatic*> m_vecStatics_LV;

	CRect clientRect;
	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award

	CTreeCtrl m_LV_Angabe_View;

	CStatic m_staticText_Title;
	CButton m_button_info_gaeb;
	CButton m_button_info_projekt;
	CButton m_button_info_vergabe;
	CButton m_button_info_LV;
	CButton m_button_info_regelung;
	CButton m_button_LV;
	CButton m_button_Inhaltverzeichnis;


	BOOL m_bInfoVisible;
	BOOL m_bInfoVisible_PrjInfo;
	BOOL m_bInfoVisible_VergInfo;
	BOOL m_bInfoVisible_LVInfo;
	BOOL m_bInfoVisible_RegInfo;
	BOOL m_bInfoVisible_LV;

	CStatic m_staticText_Version;
	CStatic m_staticText_Ausgabejahr;
	CStatic m_staticText_Erstellungdatum;
	CStatic m_staticText_Erstellungszeit;
	CStatic m_staticText_Programm;
	CStatic m_staticText_Umsetzprogramm;
	CStatic m_staticText_blank;

	CStatic m_staticText_Name;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Kurzbeschreibung;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_WaehrungBez;

	CListCtrl m_listCtrl;
	CHeaderCtrl* pHeader;

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;
	CFont m_font_button;
	CBrush m_brush_edit_bg_color;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedToggleGAEBInfo();
	afx_msg void OnBnClickedToggleProjektInfo();
	afx_msg void OnBnClickedToggleVergabenfo();
	afx_msg void OnBnClickedToggleLVInfo();
	afx_msg void OnBnClickedToggleRegelungInfo();
	afx_msg void OnBnClickedToggleLeistungsverzeichnis();

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	CString Utf8ToCString(const char* utf8Str);

};


