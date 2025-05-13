#pragma once


// CVergabeinfosView view

class CVergabeinfosView : public CView
{
	DECLARE_DYNCREATE(CVergabeinfosView)

protected:
	CVergabeinfosView();           // protected constructor used by dynamic creation
	virtual ~CVergabeinfosView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	CStatic m_staticText_Vergabeart;
	CStatic m_staticText_Waehrung_vergabeinfos;
	CStatic m_staticText_Angebotsdatum;
	CStatic m_staticText_Abnahmedatum;
	CStatic m_staticText_Auftragsdatum;
	CStatic m_staticText_Sonderart;
	CStatic m_staticText_Abgabeort;
	CStatic m_staticText_Angebotszeit;
	CStatic m_staticText_Zuschlagsfrist;
	CStatic m_staticText_Abnahmeart;
	CStatic m_staticText_Auftragsnummer;

	CButton m_groupbox_Ausführung;
	CButton m_groupbox_Gewährleistung;
	CButton m_groupbox_Burgschaften;

	CComboBox m_combobox_Vergabeart;
	CEdit m_edit_Waehrung_vergabeinfos;
	CEdit m_edit_Bez_vergabeinfos;
	CEdit m_edit_Angebotsdatum;
	CEdit m_edit_Abnahmedatum;
	CEdit m_edit_Auftragsdatum;
	CComboBox m_combobox_Sonderart;
	CEdit m_edit_Abgabeort;
	CEdit m_edit_Angebotszeit;
	CEdit m_edit_Zuschlagsfrist;
	CEdit m_edit_Abnahmeart;
	CEdit m_edit_Auftragsnummer;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate_Vergabeninfos_View(LPCREATESTRUCT lpCreateStruct);

};


