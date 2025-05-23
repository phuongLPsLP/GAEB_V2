#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

// CLVView view
class CLVView : public CScrollView
{
	DECLARE_DYNCREATE(CLVView)

protected:
	CLVView();           // protected constructor used by dynamic creation
	virtual ~CLVView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:	
	CListCtrl m_listCtrl;
	CHeaderCtrl* pHeader;
	CFont m_font_header;

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


