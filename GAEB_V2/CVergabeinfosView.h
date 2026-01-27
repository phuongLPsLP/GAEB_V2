#pragma once


#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;
// CVergabeinfosView view

class CVergabeinfosView : public CView
{
	DECLARE_DYNCREATE(CVergabeinfosView)

public:
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

	CStatic m_staticText_Auftraggeber;

	CStatic m_staticText_Auftragnehmer;

	CBrush m_brush_edit_bg_color;

	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

	rapidxml::xml_node<>* award_node = nullptr;

	int y_pos_auftraggeber;
	int y_pos_auftragnehmer;
	int y_pos_vergabeinfo;

	std::vector<CStatic*> m_dynamicStatics;

	CString* m_format;
	CString m_path;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void CVergabeinfosView::Auftraggeber();
	void CVergabeinfosView::Auftragnehmer();	
	CString Utf8ToCString(const char* utf8Str);

	static bool ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines);
	static bool TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue);
	void CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase);
	void ClearAllStatics();
};


