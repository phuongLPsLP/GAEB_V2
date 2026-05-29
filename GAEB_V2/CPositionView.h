#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <afxwin.h>
#include <afxext.h>

// CPositionView view

class CPositionView : public CView
{
	DECLARE_DYNCREATE(CPositionView)

public:
	CPositionView();           // protected constructor used by dynamic creation
	virtual ~CPositionView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate(); // first time after construct

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CString m_text_OZ;
	CString m_text_KT;
	CString m_text_bez;
	CString m_text_FullLangtext;	
	CString m_text_Menge;
	CString m_text_Einheit;
	CString m_text_Einheitpreis;
	CString m_text_Gesamtpreis;
	CString m_text_Nachlass;
	CString m_text_Zeitansatz;
	CString m_text_UP1;
	CString m_text_UP2;
	CString m_text_UP3;
	CString m_text_UP4;
	CString m_text_UP5;
	CString m_text_UP6;
	CString m_text_Summe;

protected:

	CStatic m_staticText_Position;
	CStatic m_staticText_Ordnungszahl;
	CStatic m_staticText_Bezeichnung;
	CStatic m_staticText_Positionsart;
	CStatic m_staticText_Menge;
	CStatic m_staticText_Einheit;
	CStatic m_staticText_Kurztext;
	CStatic m_staticText_Langtext;
	CStatic m_staticText_Einheitpreis;
	CStatic m_staticText_Nachlass;
	CStatic m_staticText_Gesamtpreis;
	CStatic m_staticText_Summe;
	CStatic m_staticText_Zeitansatz;
	CStatic m_staticText_Stunden;
	CStatic m_staticText_Anteilpreis;
	
	CEdit m_edit_OZ;
	CEdit m_edit_bez;

	CEdit m_edit_Menge;
	CEdit m_edit_Einheit;
	CComboBox m_combobox_PosArt;
	CEdit m_edit_langtext;
	CEdit m_edit_kurztext;

	CEdit m_edit_einheitpreis;
	CEdit m_edit_nachlass;
	CEdit m_edit_gesamt;
	CEdit m_edit_summe;
	CEdit m_edit_zeit;

	CEdit m_edit_UP1;
	CEdit m_edit_UP2;
	CEdit m_edit_UP3;
	CEdit m_edit_UP4;
	CEdit m_edit_UP5;
	CEdit m_edit_UP6;

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

	CComboBox m_combobox_einheit;

	CFont m_font;
	CFont m_font_edit;
	CFont m_font_bold;
	CFont m_font_italic;
	CFont m_font_underline;

	CBrush m_edit_bg_color;

	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

protected:
	DECLARE_MESSAGE_MAP()
public:
	CString Utf8ToString(const char* utf8Str);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void SetTextOZ(CString text);
	void SetLangtext(CString text);
	void SetMenge(CString text);
	void SetEinheitpreis(CString text);
	void SetEinheit(CString text);
	void SetGesamtpreis(CString text);
	void SetNachlass(CString text);
	void SetZeit(CString text);
	void SetUP1(CString text);
	void SetUP2(CString text);
	void SetUP3(CString text);
	void SetUP4(CString text);
	void SetUP5(CString text);
	void SetUP6(CString text);
	void SetSumme(CString text);
	

	CString m_format;

	CFont* GetFont() { return &m_font; }
	CFont* GetFontBold() { return &m_font_bold; }
	CFont* GetFontEdit() { return &m_font_edit; }
};


