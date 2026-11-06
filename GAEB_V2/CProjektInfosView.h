#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CProjektInfosView view

class CProjektInfosView : public CView
{
	DECLARE_DYNCREATE(CProjektInfosView)

public:
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

	CBrush m_brush_edit_bg_color;

	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

	int y_pos_projectinfo;

	CString* m_format;
	CString m_path;
	std::vector<CStatic*> m_dynamicStatics;

	CRect clientRect;
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
	CString Utf8ToCString(const char* utf8Str);

	static bool ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines);
	static bool ReadFileLinesCP850ToCStringW(const CString& filePath, std::vector<CString>& outLines);
	static bool TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue);
	void CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase);
};


