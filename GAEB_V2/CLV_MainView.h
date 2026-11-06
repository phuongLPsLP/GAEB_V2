#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <set>

using namespace rapidxml;

// CLV_MainView view

class CLV_MainView : public CScrollView
{
	DECLARE_DYNCREATE(CLV_MainView);

public:
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
	CListCtrl m_list_LV;
	bool m_listCreated = false;

	CFont m_headerFontBold;

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
	CString m_path;

	CString* m_format;
	std::vector<CStatic*> m_dynamicStatics;
	int yPos_LV = 100;

	struct LVBereich {
		CString ber_oz;
		CString ber_oz_formatted;
		CString ber_kurztext;
	};

	const int xOZ = 20;
	const int xM = 180;
	const int xME = 300;
	const int xTxt = 420;
	const int xEP = 1250;
	const int xGP = 1450;

	const int hRow = 20;

	struct LVPosition {
		CString pos_oz;
		CString pos_menge;
		CString pos_einheit;
		CString pos_kurztext;
		CString pos_langtext;
		CString pos_einheitpreis;
		CString pos_gesamtpreis;
		std::vector<LVBereich> path;
	};

	struct  LVBeschreibung
	{
		CString beschr_langtext;
		CString beschr_kurztext;
	};
	enum class rowKind{Section, Position};
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
	void TraverseRemark(xml_node<>* remark, int& index);
	CString FormatPath(const std::vector<int>& path);

	static bool ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines);
	static bool ReadFileLinesCP850ToCStringW(const CString& filePath, std::vector<CString>& outLines);

	static bool TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue);
	void CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase);
	void ClearAllStatics();
	//void CLV_MainView::CreateCell(int x, int y, int w, int h, const CString& text, CFont* font, int id);
	//void CLV_MainView::RenderRow(int y,		const CString& oz, const CString& menge, const CString& me,		const CString& text, const CString& ep, const CString& gp,		CFont* font, int& id);
	void CLV_MainView::ClearAllViews();

private:
	void GetDeviceScrollSize(int& nMapMode,
		SIZE& sizeTotal,
		SIZE& sizePage,
		SIZE& sizeLine) const;

};


