#pragma once


#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;
// CVergabeinfosView view

class CVergabeinfosView : public CView
{
	DECLARE_DYNCREATE(CVergabeinfosView)

protected:
	CVergabeinfosView();           // protected constructor used by dynamic creation
	virtual ~CVergabeinfosView();

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

	CRect clientRect_Vergabe;

	CStatic m_staticText_Vergabeinfos;

	CStatic m_staticText_Datenaustauschphase;

	CStatic m_staticText_Vergabe;
	CStatic m_staticText_Vergabeart;
	CStatic m_staticText_Waehrung;
	CStatic m_staticText_Waehrung_Bez;
	CStatic m_staticText_Eröffnungstermins_Datum;
	CStatic m_staticText_Eröffnungstermins_Uhrzeit;
	CStatic m_staticText_Zuschlagsfrist;

	CStatic m_staticText_Auftraggeber;
	CStatic m_staticText_Name;
	CStatic m_staticText_Str_Nr;
	CStatic m_staticText_PLZ;
	CStatic m_staticText_Ort;
	CStatic m_staticText_Tel;
	CStatic m_staticText_Mail;
	CStatic m_staticText_DV;
	CStatic m_staticText_Vergabe_Nr;

	CStatic m_staticText_Auftragnehmer;
	CStatic m_staticText_Adresse_nehmer;
	CStatic m_staticText_Name_nehmer;
	CStatic m_staticText_Str_Nr_nehmer;
	CStatic m_staticText_PLZ_nehmer;
	CStatic m_staticText_Ort_nehmer;


	CFont m_font;
	CFont m_font_bold;
	CFont m_font_underline;
	CBrush m_brush_edit_bg_color;


	std::unique_ptr<rapidxml::file<>> m_xmlFile;
	std::unique_ptr<rapidxml::xml_document<>> m_xmlDoc;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr; //FirstChild = GAEBInfo
	rapidxml::xml_node<>* m_pProjektInfo = nullptr; //nextsibling = PrjInfo
	rapidxml::xml_node<>* m_award = nullptr; //nextsibling = Award

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


