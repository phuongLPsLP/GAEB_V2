// CVergabeinfosView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CVergabeinfosView.h"
#include "MainFrm.h"


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
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (!pFrame) return;

	// Use title font
	CFont* pTitleFont = pFrame->GetFontTitle();
	CFont* pOldFont = pDC->SelectObject(pTitleFont);
	pDC->SelectObject(pOldFont);

	CFont* pFont = pFrame->GetFont();
	pOldFont = pDC->SelectObject(pFont);
	pDC->SelectObject(pOldFont);

	CFont* pBold = pFrame->GetFontBold();
	pOldFont = pDC->SelectObject(pBold);
	pDC->SelectObject(pOldFont);

	CFont* pItalic = pFrame->GetFontItalic();
	pOldFont = pDC->SelectObject(pItalic);
	pDC->SelectObject(pOldFont);

	CFont* pUnderline = pFrame->GetFontUnderline();
	pOldFont = pDC->SelectObject(pUnderline);
	pDC->SelectObject(pOldFont);
}

void CVergabeinfosView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_brush_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	GetClientRect(&clientRect_Vergabe);
	CClientDC dc(this);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();
	
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
	m_staticText_Vergabeinfos.SetFont(pMainFrame->GetFontBold());

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
		pStatic_vergabe->SetFont(pMainFrame->GetFont());
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
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}

			else if (DP == 81) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Leistungsbeschreibung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}
			else if (DP == 82) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Kostenanschlag"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}
			else if (DP == 84) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Angebotsabgabe"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}
			else if (DP == 85) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Nebenangebot"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}
			else if (DP == 86) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Auftragserteilung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
			}
			else if (DP == 89) {
				CStatic* pstaticValue_Vergabe = new CStatic();
				pstaticValue_Vergabe->Create(_T("Rechnung"), WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, 70), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_Vergabe->SetFont(pMainFrame->GetFont());
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
				pstaticValue_info->SetFont(pMainFrame->GetFont());
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

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();


	m_staticText_Auftraggeber.Create(_T("Auftraggeber"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 250), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Auftraggeber.SetFont(pMainFrame->GetFontBold());

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
						m_staticText_Fax.SetFont(pMainFrame->GetFont());
					}
					CStatic* pstaticValue = new CStatic();
					pstaticValue->Create(adresse_node_value, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(270, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
					yPos_Proj_Geber += 20;
					pstaticValue->SetFont(pMainFrame->GetFont());
				}
			}
		}
		else if (own_node_text == "DPNo") {
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(pMainFrame->GetFont());
		}
		else if (own_node_text == "AwardNo") {
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber+20), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(pMainFrame->GetFont());
		}
		else if (own_node_text == "AcctRecNo") {
			m_staticText_Deb_Nr.Create(_T("Debitoren-Nummer:"), WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, yPos_Proj_Geber+40), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
			m_staticText_Deb_Nr.SetFont(pMainFrame->GetFont());
			CString value(own_node->value());
			CStatic* pstaticValue = new CStatic();
			pstaticValue->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, yPos_Proj_Geber+40), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue->SetFont(pMainFrame->GetFont());
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
		pStatic_geber->SetFont(pMainFrame->GetFont());
	}
}

void CVergabeinfosView::Auftragnehmer() {

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

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
	m_staticText_Auftragnehmer.SetFont(pMainFrame->GetFontBold());

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
				pstaticValue->SetFont(pMainFrame->GetFont());
			}
		}
	}

	for (CStatic* pStatic_nehmer : staticControls_nehmer)
	{
		pStatic_nehmer->SetFont(pMainFrame->GetFont());
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