#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

// CKalkulationsInfosView view

class CLVInfosView : public CView
{
	DECLARE_DYNCREATE(CLVInfosView)

public:
	CLVInfosView();           // protected constructor used by dynamic creation
	virtual ~CLVInfosView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();
	CString GetField(const CString& line, int start, int len);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected: 

	CStatic m_staticText_Title;

	CRect clientRect;

	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

	std::vector<CStatic*> m_dynamicStatics;

	CString* m_format;
	CString m_path;
	CString m_phase;

	CBrush m_brush_edit_bg_color;


	int y_pos_gaebinfo;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString Utf8ToCString(const char* utf8Str);

	static bool ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines);
	static bool TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue);
	void CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase);
	void ClearAllStatics();

};


