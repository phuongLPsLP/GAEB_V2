// CVergabeinfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVergabeinfosView.h"


// CVergabeinfosView

IMPLEMENT_DYNCREATE(CVergabeinfosView, CView)

CVergabeinfosView::CVergabeinfosView()
{

}

CVergabeinfosView::~CVergabeinfosView()
{
}

BEGIN_MESSAGE_MAP(CVergabeinfosView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CVergabeinfosView drawing

void CVergabeinfosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CVergabeinfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect_Vergabe);
	CClientDC dc(this);

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18;
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfItalic = TRUE;
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI"));
	m_font_underline.CreateFontIndirect(&lf_underline);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 20; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

	m_xmlFile = std::make_unique<rapidxml::file<>>("07_GAEB.X83");
	//m_xmlFile = std::make_unique<rapidxml::file<>>("Hof Berufschule Dachdeckerarbeiten 05.X81");
	m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
	m_xmlDoc->parse<0>(m_xmlFile->data());
	rapidxml::xml_node<>* root = m_xmlDoc->first_node();

	m_pGAEBInfo = root->first_node(); // Get GAEBInfo node
	m_pProjektInfo = m_pGAEBInfo->next_sibling();
	m_award = m_pProjektInfo->next_sibling();
	/*	m_groupbox_Ausf¸hrung = new CButton();
		m_groupbox_Gew‰hrleistung = new CButton();
		m_groupbox_Burgschaften = new CButton();
		m_groupbox_Ausf¸hrung->Create(_T("Voraussichtliche Ausf¸hrung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
			CRect(CPoint(20,260), CSize(900,80)), this, 1006);
		m_groupbox_Ausf¸hrung->SetFont(&m_font);
		m_groupbox_Gew‰hrleistung->Create(_T("Gew‰hrleistung"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
			CRect(CPoint(20, 360), CSize(900, 80)), this, 1006);
		m_groupbox_Gew‰hrleistung->SetFont(&m_font);
		m_groupbox_Burgschaften->Create(_T("B¸rgschaften"), WS_CHILD | WS_VISIBLE | BS_LEFTTEXT | BS_GROUPBOX,
			CRect(CPoint(20, 460), CSize(900, 80)), this, 1006);
		m_groupbox_Burgschaften->SetFont(&m_font);

		m_staticText_Vergabeart.Create(_T("Vergabeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(120, 20)), this, 1001);
		m_staticText_Waehrung_vergabeinfos.Create(_T("W‰hrung / Bez."), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 60), CSize(120, 20)), this, 1001);
		m_staticText_Angebotsdatum.Create(_T("Angebotsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 100), CSize(120, 20)), this, 1001);
		m_staticText_Abnahmedatum.Create(_T("Abnahmedatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 140), CSize(120, 20)), this, 1001);
		m_staticText_Auftragsdatum.Create(_T("Auftragsdatum"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 180), CSize(120, 20)), this, 1001);

		m_staticText_Sonderart.Create(_T("Sonderart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 20), CSize(120, 20)), this, 1001);
		m_staticText_Abgabeort.Create(_T("Abgabeort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 60), CSize(120, 20)), this, 1001);
		m_staticText_Angebotszeit.Create(_T("Angebotszeit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 100), CSize(120, 20)), this,1001);
		m_staticText_Zuschlagsfrist.Create(_T("Zuschlagsfrist"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 140), CSize(120, 20)), this,1001);
		m_staticText_Abnahmeart.Create(_T("Abnahmeart"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 180), CSize(120, 20)), this,1001);
		m_staticText_Auftragsnummer.Create(_T("Auftragsnummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 220), CSize(120, 20)), this,1001);


		m_combobox_Vergabeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER| ES_MULTILINE | CBS_DROPDOWNLIST,
			CRect(CPoint(180, 20), CSize(250, 20)), this, 1007);
		m_edit_Waehrung_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(180, 60), CSize(50, 20)), this, 1002);
		m_edit_Bez_vergabeinfos.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(250, 60), CSize(180, 20)), this, 1002);
		m_edit_Angebotsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(180, 100), CSize(120, 20)), this, 1002);
		m_edit_Abnahmedatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(180, 140), CSize(250, 20)), this, 1002);
		m_edit_Auftragsdatum.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(180, 180), CSize(250, 20)), this, 1002);

		m_combobox_Sonderart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | CBS_DROPDOWNLIST,
			CRect(CPoint(670, 20), CSize(250, 20)), this, 1007);
		m_edit_Abgabeort.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(670, 60), CSize(250, 20)), this, 1002);
		m_edit_Angebotszeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(670, 100), CSize(250, 20)), this, 1002);
		m_edit_Zuschlagsfrist.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(670, 140), CSize(250, 20)), this, 1002);
		m_edit_Abnahmeart.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(670, 180), CSize(250, 20)), this, 1002);
		m_edit_Auftragsnummer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
			CRect(CPoint(670, 220), CSize(250, 20)), this, 1002);

		m_staticText_Beginn.Create(_T("Beginn"), WS_CHILD | WS_VISIBLE , CRect(CPoint(30, 300), CSize(120, 20)), this, 1001);
		m_staticText_End_Ausf¸hrung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 300), CSize(120, 20)), this, 1001);

		m_staticText_Dauer.Create(_T("Dauer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 400), CSize(120, 20)), this, 1001);
		m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(270, 400), CSize(80, 20)), this, 1001);
		m_staticText_End_Gew‰hrleistung.Create(_T("Ende"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 400), CSize(120, 20)), this, 1001);

		m_staticText_Ausf¸hrung_Anteil.Create(_T("Ausf¸hrung [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(30, 500), CSize(120, 20)), this, 1001);
		m_staticText_Gew‰hrleist.Create(_T("Gew‰hrleist. [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(510, 500), CSize(120, 20)), this, 1001);

		m_edit_beginn.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 300), CSize(250, 20)), this, 1002);
		m_edit_end_ausf¸hrung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 300), CSize(250, 20)), this, 1002);

		m_edit_dauer.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 400), CSize(50, 20)), this, 1002);
		m_edit_einheit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(350, 400), CSize(80, 20)), this, 1002);
		m_edit_ende_gew‰hrleistung.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 400), CSize(250, 20)), this, 1002);

		m_edit_ausf¸hrung_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(180, 500), CSize(250, 20)), this, 1002);
		m_edit_gew‰hrleist_anteil.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(670, 500), CSize(250, 20)), this, 1002);

		m_button_heute.Create( _T("heute"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(350,100), CSize(80,20)), this, 1004);
		m_button_Zusatztext.Create(_T("Zusatztext"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(CPoint(20, 570), CSize(120, 20)), this, 1004);

		m_button_heute.SetFont(&m_font_button);
		m_button_Zusatztext.SetFont(&m_font_button);

		CStatic* staticControls[] = {
		&m_staticText_Vergabeart,
		&m_staticText_Waehrung_vergabeinfos,
		&m_staticText_Angebotsdatum,
		&m_staticText_Abnahmedatum,
		&m_staticText_Auftragsdatum,
		&m_staticText_Sonderart,
		&m_staticText_Abgabeort,
		&m_staticText_Angebotszeit,
		&m_staticText_Zuschlagsfrist,
		&m_staticText_Abnahmeart,
		&m_staticText_Auftragsnummer,
		&m_staticText_Beginn,
		&m_staticText_End_Ausf¸hrung,
		&m_staticText_Dauer,
		&m_staticText_Einheit,
		&m_staticText_End_Gew‰hrleistung,
		&m_staticText_Ausf¸hrung_Anteil,
		&m_staticText_Gew‰hrleist,
		};

		for (CStatic* pStatic : staticControls)
		{
			if (pStatic->GetSafeHwnd())
				pStatic->SetFont(&m_font);
		}

		CEdit* editControls[] = {
		&m_edit_Waehrung_vergabeinfos,
		&m_edit_Bez_vergabeinfos,
		&m_edit_Angebotsdatum,
		&m_edit_Abnahmedatum,
		&m_edit_Auftragsdatum,
		&m_edit_Abgabeort,
		&m_edit_Angebotszeit,
		&m_edit_Zuschlagsfrist,
		&m_edit_Abnahmeart,
		&m_edit_Auftragsnummer,
		&m_edit_beginn,
		&m_edit_end_ausf¸hrung,
		&m_edit_dauer,
		&m_edit_einheit,
		&m_edit_ende_gew‰hrleistung,
		&m_edit_ausf¸hrung_anteil,
		&m_edit_gew‰hrleist_anteil,
		};
		for (CEdit* pEdit : editControls)
		{
			if (pEdit->GetSafeHwnd())
			{
				pEdit->SetFont(&m_font_edit);
			}
		}*/
	CStatic* staticControls_Vergabe[] =
	{
	&m_staticText_Datenaustauschphase,
	&m_staticText_Vergabeart,
	&m_staticText_Waehrung,
	&m_staticText_Waehrung_Bez,
	&m_staticText_Erˆffnungstermins_Datum,
	&m_staticText_Erˆffnungstermins_Uhrzeit,
	&m_staticText_Zuschlagsfrist,
	};

	m_staticText_Vergabeinfos.Create(_T("Informationen zur Vergabe"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Vergabeinfos.SetFont(&m_font_bold);

	m_staticText_Datenaustauschphase.Create(_T("Datenaustauschphase:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 70), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);

	m_staticText_Vergabeart.Create(_T("Vergabeart:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 100), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Waehrung.Create(_T("W‰hrung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 120), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Waehrung_Bez.Create(_T("Bezeichnung der W‰hrung:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 140), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Erˆffnungstermins_Datum.Create(_T("Datum des Erˆffnungstermins:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 160), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Erˆffnungstermins_Uhrzeit.Create(_T("Uhrzeit des Erˆffnungstermins:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 180), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Zuschlagsfrist.Create(_T("Ende der Zuschlagsfrist:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 200), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);	

	for (CStatic* pStatic_vergabe : staticControls_Vergabe)
	{
		pStatic_vergabe->SetFont(&m_font);
	}

	int yPos_Vergabe = 100;

	for (award_node = m_award->first_node(); award_node; award_node = award_node->next_sibling())
	{
		CString award_node_text(award_node->name());

		//Datenaustauschphase
		if (award_node_text == "DP") {
			int DP = atoi(award_node->value());

			if (DP == 83) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Leistungsbeschreibung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}

			else if (DP == 81) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Leistungsbeschreibung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 82) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Kostenanschlag"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 83) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Angebotsaufforderung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 84) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Angebotsabgabe"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 85) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Nebenangebot"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 86) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Auftragserteilung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}
			else if (DP == 89) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Rechnung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(&m_font);
			}

		}	

		//Vergabeinfo
		else if (award_node_text == "AwardInfo") {
			for (xml_node<>* award_info = award_node->first_node(); award_info; award_info = award_info->next_sibling())
			{
				CString subChildText(award_info->value());
				CStatic* pstaticValue_info = new CStatic();
				pstaticValue_info->Create(subChildText, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, yPos_Vergabe), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				yPos_Vergabe += 20;
				pstaticValue_info->SetFont(&m_font);
			}
		}
		else if (award_node_text == "OWN") {	//Auftraggerber
			Auftraggeber();
		}

		else if (award_node_text == "CTR") {	//Auftragnehmer
			Auftragnehmer();
		}
	}
}

void CVergabeinfosView::Auftraggeber() {

	m_staticText_Auftraggeber.Create(_T("Auftraggeber"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 250), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Auftraggeber.SetFont(&m_font_bold);

	m_staticText_Name.Create(_T("Name:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 280), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Str_Nr.Create(_T("Straﬂe und Hausnummer:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 300), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_PLZ.Create(_T("Postleitzahl:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 320), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Ort.Create(_T("Ort:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 340), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Tel.Create(_T("Telefon:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 360), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);



	int yPos_Proj_Geber = 280;

	for (xml_node<>* own_node = award_node->first_node(); own_node; own_node = own_node->next_sibling()) {
		CString own_node_text(own_node->name());
		if (own_node_text == "Address") {
			for(xml_node<>* adresse_node= own_node->first_node(); adresse_node; adresse_node = adresse_node->next_sibling()) {
				CString adresse_node_value = Utf8ToCString(adresse_node->value());
				CString adresse_node_text(adresse_node->name());				
				if (adresse_node_value.IsEmpty()) { continue; }
				else {
					if (adresse_node_text == "Fax") {
						m_staticText_Fax.Create(_T("Fax:"), WS_CHILD | WS_VISIBLE,
							CRect(CPoint(20, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
						m_staticText_Fax.SetFont(&m_font);
					}
					CStatic* pstaticValue = new CStatic();
					pstaticValue->Create(adresse_node_value, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(270, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
					yPos_Proj_Geber += 20;
					pstaticValue->SetFont(&m_font);
				}
			}
		}
		else if (own_node_text == "DPNo") {
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(&m_font);
		}
		else if (own_node_text == "AwardNo") {
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber+20), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(&m_font);
		}
		else if (own_node_text == "AcctRecNo") {
			m_staticText_Deb_Nr.Create(_T("Debitoren-Nummer:"), WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, yPos_Proj_Geber+40), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
			m_staticText_Deb_Nr.SetFont(&m_font);
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber+40), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(&m_font);
		}
	}
	m_staticText_Mail.Create(_T("E-mail:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, yPos_Proj_Geber-20), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_DV.Create(_T("DV-Nummer:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Vergabe_Nr.Create(_T("Vergabenummer:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, yPos_Proj_Geber+20), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);


	CStatic* staticControls_Geber[] =
	{
	&m_staticText_Name,
	&m_staticText_Str_Nr,
	&m_staticText_PLZ,
	&m_staticText_Ort,
	&m_staticText_Tel,
	&m_staticText_Mail,
	&m_staticText_DV,
	&m_staticText_Vergabe_Nr,
	};

	for (CStatic* pStatic_geber : staticControls_Geber)
	{
		pStatic_geber->SetFont(&m_font);
	}
}

void CVergabeinfosView::Auftragnehmer() {
	CStatic* staticControls_nehmer[] =
	{
	&m_staticText_Name_nehmer,
	&m_staticText_Str_Nr_nehmer,
	&m_staticText_PLZ_nehmer,
	&m_staticText_Ort_nehmer,
	};
	int yPos_Proj_Nehmer = 500;

	m_staticText_Auftragnehmer.Create(_T("Auftragnehmer"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 470), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Auftragnehmer.SetFont(&m_font_bold);

	m_staticText_Name_nehmer.Create(_T("Name:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 500), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Str_Nr_nehmer.Create(_T("Straﬂe und Hausnummer:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 520), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_PLZ_nehmer.Create(_T("Postleitzahl:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 540), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Ort_nehmer.Create(_T("Ort:"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 560), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);

	for (xml_node<>* ctr_node = award_node->first_node(); ctr_node; ctr_node = ctr_node->next_sibling() )
	{
		CString ctr_node_text(ctr_node->name());
		if (ctr_node_text == "Address") {

			for (xml_node<>* adresse_node_ctr = ctr_node->first_node(); adresse_node_ctr; adresse_node_ctr = adresse_node_ctr->next_sibling()) {

				CString ctr_node_value = Utf8ToCString(adresse_node_ctr->value());
				CStatic* pstaticValue = new CStatic();
				pstaticValue->Create(ctr_node_value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, yPos_Proj_Nehmer), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				yPos_Proj_Nehmer += 20;
				pstaticValue->SetFont(&m_font);
			}
		}

	}

	for (CStatic* pStatic_nehmer : staticControls_nehmer)
	{
		pStatic_nehmer->SetFont(&m_font);
	}

}


// CVergabeinfosView diagnostics

#ifdef _DEBUG
void CVergabeinfosView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CVergabeinfosView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVergabeinfosView message handlers

HBRUSH CVergabeinfosView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();
	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	//Combobox

	/*if (ctrlID == 1003)
	{
		if (nCtlColor == CTLCOLOR_LISTBOX) // ListBox (Dropdown area)
		{
			pDC->SetBkColor(RGB(200, 220, 255)); // Light Blue Background
			pDC->SetTextColor(RGB(255, 0, 0));     // Black Text
			return m_brush_combobox;
		}

		else if (nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_STATIC) // ComboBox text area
		{
			pDC->SetBkColor(RGB(255, 255, 180)); // Light Yellow
			pDC->SetTextColor(RGB(0, 0, 0));   // Black text
			return m_brush_combobox;
		}
		return CView::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	//Edit box
	if (ctrlID == 1002)
	{
		m_textColor_editbox = RGB(0, 0, 0);
		pDC->SetTextColor(m_textColor_editbox);       // Black text
		pDC->SetBkColor(RGB(255, 255, 180));
		// Return the brush for background color
		return m_brush_editbox;

	}*/

	return hbr;
}

CString CVergabeinfosView::Utf8ToCString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
}