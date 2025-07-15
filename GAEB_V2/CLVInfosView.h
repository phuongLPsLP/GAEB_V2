#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CKalkulationsInfosView view

class CLVInfosView : public CView
{
	DECLARE_DYNCREATE(CLVInfosView)

protected:
	CLVInfosView();           // protected constructor used by dynamic creation
	virtual ~CLVInfosView();

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

	CButton *m_groupbox_LV_Summe;
	CButton *m_groupbox_Bez_EP_Anteil;
	CButton *m_groupbox_2;
	CButton *m_groupbox_3;

	CButton m_button_Gliederung;
	CButton m_button_heute_LVInfos;

	CButton m_checkbox_Nachlass;

	CStatic m_staticText_LV_Name;
	CStatic m_staticText_LV_Datum;
	CStatic m_staticText_LV_Bezeichnung;
	CStatic m_staticText_LV_AnzahlPos;
	CStatic m_staticText_Anzahl_LVInfos;
	CStatic m_staticText_LV_Summe_Net;
	CStatic m_staticText_Nachlass;
	CStatic m_staticText_Pauschal;
	CStatic m_staticText_Zwischensumme;
	CStatic m_staticText_USt_Anteil;
	CStatic m_staticText_Brutto_Summe;
	CStatic m_staticText_EP_Anteil_1;
	CStatic m_staticText_EP_Anteil_2;
	CStatic m_staticText_EP_Anteil_3;
	CStatic m_staticText_EP_Anteil_4;
	CStatic m_staticText_EP_Anteil_5;
	CStatic m_staticText_EP_Anteil_6;

	CStatic m_staticText_Skontosatz_Anteil;
	CStatic m_staticText_Skonto_Tage;
	CStatic m_staticText_Zeit_Anteil;
	CStatic m_staticText_Ausführungszeit;

	CStatic m_staticText_EP_Nachkomma;
	CStatic m_staticText_Nachlasswert;

	CEdit m_edit_LV_Summe_Net;
	CEdit m_edit_Nachlass;
	CEdit m_edit_Pauschal;
	CEdit m_edit_Zwischensumme;
	CEdit m_edit_USt_Anteil;
	CEdit m_edit_Brutto_Summe;
	CEdit m_edit_Skontosatz_Anteil;
	CEdit m_edit_Skonto_Tage;
	CEdit m_edit_Ausführungszeit;
	CEdit m_edit_LV_Name;
	CEdit m_edit_LV_Datum;
	CEdit m_edit_LV_Bezeichnung;
	CEdit m_edit_LV_AnzahlPos;

	CComboBox m_comboBox_Anzahl_LVInfos;
	CComboBox m_comboBox_EP_Anteil1;
	CComboBox m_comboBox_EP_Anteil2;
	CComboBox m_comboBox_EP_Anteil3;
	CComboBox m_comboBox_EP_Anteil4;
	CComboBox m_comboBox_EP_Anteil5;
	CComboBox m_comboBox_EP_Anteil6;
	CComboBox m_comboBox_Zeit_Anteil;
	CComboBox m_comboBox_EP_Nachkomma;

	CStatic m_staticText_Title;
	CStatic m_staticText_Version;
	CStatic m_staticText_Ausgabejahr;
	CStatic m_staticText_Erstellungdatum;
	CStatic m_staticText_Erstellungszeit;
	CStatic m_staticText_Programm;
	CStatic m_staticText_Umsetzprogramm;
	CStatic m_staticText_blank;

	CRect clientRect;
	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award


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


