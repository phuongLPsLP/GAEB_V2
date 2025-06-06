#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CLV_MainView view

class CLV_MainView : public CView
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

	std::vector<CStatic*> m_vecStatics;

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
	CStatic m_staticText_Version;
	CStatic m_staticText_Ausgabejahr;
	CStatic m_staticText_Erstellungdatum;
	CStatic m_staticText_Erstellungszeit;
	CStatic m_staticText_Programm;
	CStatic m_staticText_Umsetzprogramm;

	CStatic m_staticText_Name;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Kurzbeschreibung;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_WaehrungBez;

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
};


