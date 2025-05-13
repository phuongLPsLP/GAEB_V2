#pragma once


// CProjektInfosView view

class CProjektInfosView : public CView
{
	DECLARE_DYNCREATE(CProjektInfosView)

protected:
	CProjektInfosView();           // protected constructor used by dynamic creation
	virtual ~CProjektInfosView();

protected:
	CStatic m_staticText_Name;
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

	CButton m_button_Zusatztext;


public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_ProjecktInfos_View(LPCREATESTRUCT lpCreateStruct);

};


