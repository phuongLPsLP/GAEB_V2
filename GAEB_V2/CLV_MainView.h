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
	rapidxml::xml_document<>* m_Doc = nullptr;
	rapidxml::xml_node<>* m_Root = nullptr;
	rapidxml::xml_node<>* m_pGAEBInfo = nullptr;
	rapidxml::xml_node<>* m_pProjektInfo = nullptr;
	rapidxml::xml_node<>* m_award = nullptr;

	CTreeCtrl m_LV_Angabe_View;

	CStatic m_staticText_Title;
	BOOL m_bInfoVisible_LV;

	CStatic m_staticText_OZ;
	CStatic m_staticText_Menge;
	CStatic m_staticText_Einheit;
	CStatic m_staticText_LeiBe;
	CStatic m_staticText_Einheitpreis;
	CStatic m_staticText_Gesamtpreis;

	CBrush m_brush_edit_bg_color;
	CSize m_wndSize;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void OnBnClickedToggleLeistungsverzeichnis();

	CString Utf8ToCString(const char* utf8Str);
	//void PrintAllIDsRecursive(xml_node<>* node, int& index, std::vector<int> levelPath);
	void TraverseBoQCtgy(xml_node<>* ctgyNode, int& index, std::vector<int> levelPath);
	void TraverseItemlist(xml_node<>* itemList, int& index, std::vector<int> levelPath);
	CString FormatPath(const std::vector<int>& path);
private:
	void GetDeviceScrollSize(int& nMapMode,
		SIZE& sizeTotal,
		SIZE& sizePage,
		SIZE& sizeLine) const;

};


