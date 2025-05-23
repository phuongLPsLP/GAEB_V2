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
	virtual void OnInitialUpdate();
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

	CButton	*m_groupbox_Adressdaten;
	CButton	*m_groupbox_Ausführung;
	CButton	*m_groupbox_Gewährleistung;
	CButton	*m_groupbox_Burgschaften;

	CEdit m_edit_Waehrung_vergabeinfos;
	CEdit m_edit_Bez_vergabeinfos;
	CEdit m_edit_Angebotsdatum;
	CEdit m_edit_Abnahmedatum;
	CEdit m_edit_Auftragsdatum;
	CEdit m_edit_Abgabeort;
	CEdit m_edit_Angebotszeit;
	CEdit m_edit_Zuschlagsfrist;
	CEdit m_edit_Abnahmeart;
	CEdit m_edit_Auftragsnummer;	

	CStatic m_staticText_Beginn;
	CStatic m_staticText_End_Ausführung;
	CStatic m_staticText_Dauer;
	CStatic m_staticText_Einheit;
	CStatic m_staticText_End_Gewährleistung;
	CStatic m_staticText_Ausführung_Anteil;
	CStatic m_staticText_Gewährleist;

	CEdit m_edit_beginn;
	CEdit m_edit_end_ausführung;
	CEdit m_edit_dauer;
	CEdit m_edit_einheit;
	CEdit m_edit_ende_gewährleistung;
	CEdit m_edit_ausführung_anteil;
	CEdit m_edit_gewährleist_anteil;

	CComboBox m_combobox_Vergabeart;
	CComboBox m_combobox_Sonderart;

	CButton m_button_Zusatztext;
	CButton m_button_heute;

	CFont m_font;
	CBrush m_brush_statictext_background;
	CFont m_font_button;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


