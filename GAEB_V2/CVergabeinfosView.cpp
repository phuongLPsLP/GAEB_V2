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
	m_format = pMainFrame->GetFormat();
	y_pos_vergabeinfo = 70;

	m_staticText_Vergabeinfos.Create(_T("Informationen zur Vergabe"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 20), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Vergabeinfos.SetFont(pMainFrame->GetFontBold());

	if(*m_format == "2000")
	{
		std::vector<CString> lines;
		m_path = pMainFrame->GetPath();

		if (!ReadFileLinesAnsiToCStringW(m_path, lines)) {
			AfxMessageBox(_T("Datei konnte nicht gelesen werden."));
			return;
		}

		CString phase, auftragsgeber, auftragsnehmer, adresse, name1, name2, name3, name4, tel, fon, fax, mail, str, plz, ort, waehrung,
			wae_bez;
		bool inGaebInfo = false;
		for (const auto& raw : lines)
		{
			CString line = raw;
			line.Trim();
			if (line.IsEmpty())
				continue;
			if (line.CompareNoCase(_T("#begin[VergabeInfo]")) == 0) {
				inGaebInfo = true;
				continue;
			}
			if (line.CompareNoCase(_T("#end[VergabeInfo]")) == 0) {
				inGaebInfo = false;
				continue;
			}
			if (!inGaebInfo)
				continue;
			CString key, value;
			if (!TryParseGaebKeyValueLine(line, key, value))
				continue;

			if (key.CompareNoCase(_T("DP")) == 0) phase = value;
			else if (key.CompareNoCase(_T("AG")) == 0) auftragsgeber = value;
			else if (key.CompareNoCase(_T("AN")) == 0) auftragsnehmer = value;
			else if (key.CompareNoCase(_T("Adresse")) == 0) adresse = value;
			else if (key.CompareNoCase(_T("Strasse")) == 0) str = value;
			else if (key.CompareNoCase(_T("PLZ")) == 0) plz = value;
			else if (key.CompareNoCase(_T("Ort")) == 0) ort = value;
			else if (key.CompareNoCase(_T("Telefon")) == 0) tel = value;
			else if (key.CompareNoCase(_T("Fax")) == 0) fax = value;
			else if (key.CompareNoCase(_T("Email")) == 0) mail = value;
			else if (key.CompareNoCase(_T("Name1")) == 0) name1 = value;
			else if (key.CompareNoCase(_T("Name2")) == 0) name2 = value;
			else if (key.CompareNoCase(_T("Name3")) == 0) name3 = value;
			else if (key.CompareNoCase(_T("Name4")) == 0) name4 = value;
			else if (key.CompareNoCase(_T("Wae")) == 0) waehrung = value;
			else if (key.CompareNoCase(_T("WaeBez")) == 0) wae_bez = value;


		}

		CFont* pFont = pMainFrame->GetFont();

		CreateStaticText(this, _T("Datenaustauschphase:"), phase, y_pos_vergabeinfo, pFont, 2000);
		CreateStaticText(this, _T("Auftragsgeber:"), auftragsgeber, y_pos_vergabeinfo, pFont, 2020);
		CreateStaticText(this, _T("Auftragsnehmer:"), auftragsnehmer, y_pos_vergabeinfo, pFont, 2030);
		CreateStaticText(this, _T("Adresse:"), adresse, y_pos_vergabeinfo, pFont, 2040);
		CreateStaticText(this, _T("Strasse:"), str, y_pos_vergabeinfo, pFont, 2050);
		CreateStaticText(this, _T("PLZ:"), plz, y_pos_vergabeinfo, pFont, 2060);
		CreateStaticText(this, _T("Ort:"), ort, y_pos_vergabeinfo, pFont, 2070);
		CreateStaticText(this, _T("Telefon:"), tel, y_pos_vergabeinfo, pFont, 2090);
		CreateStaticText(this, _T("Fax:"), fax, y_pos_vergabeinfo, pFont, 2100);
		CreateStaticText(this, _T("Email:"), name1, y_pos_vergabeinfo, pFont, 2110);
		CreateStaticText(this, _T("Name1:"), name1, y_pos_vergabeinfo, pFont, 2120);
		CreateStaticText(this, _T("Name2:"), name2, y_pos_vergabeinfo, pFont, 2130);
		CreateStaticText(this, _T("Name3:"), name3, y_pos_vergabeinfo, pFont, 2140);
		CreateStaticText(this, _T("Name4:"), name4, y_pos_vergabeinfo, pFont, 2150);
		CreateStaticText(this, _T("Währung:"), waehrung, y_pos_vergabeinfo, pFont, 2160);
		CreateStaticText(this, _T("Bezeichnung der Währung:"), wae_bez, y_pos_vergabeinfo, pFont, 2170);

	}

	//GAEB XML
	else {
		m_Doc = pMainFrame->GetXmlDoc();
		m_Root = pMainFrame->GetRootNode();
		m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
		m_pProjektInfo = pMainFrame->GetProjektInfoNode();
		m_award = pMainFrame->GetAwardNode();


		CString year;
		CString month;
		CString day;
		CSize size = CSize(clientRect_Vergabe.Width(), 20);
		for (award_node = m_award->first_node(); award_node; award_node = award_node->next_sibling())
		{
			CString award_node_text(award_node->name());

			//Vergabeinfo
			if (award_node_text == "AwardInfo") {
				for (xml_node<>* awardinfo_node = award_node->first_node(); awardinfo_node; awardinfo_node = awardinfo_node->next_sibling()) {
					CString value = Utf8ToCString(awardinfo_node->value());
					CString name = Utf8ToCString(awardinfo_node->name());


					if (name == "Cat") {
						name = "Vergabeart:";
						if (value == "OpenProc") {
							value = _T("Offenes Verfahren");
						}
						else if (value == "ClosedProc") {
							value = _T("Nichtoffenes Verfahren");
						}
						else if (value == "NegProc" || value == "NegProcOpen") {
							value = _T("Verhandlungsverfahren");
						}
						else if (value == "OpenCall") {
							value = _T("Öffentliche Ausschreibung");
						}
						else if (value == "SelectCall") {
							value = _T("Beschränkte Ausschreibung ohne öffentlichem Teilnahmewettbewerb");
						}
						else if (value == "SelectCallPostOpen") {
							value = _T("Beschränkte Ausschreibung nach öffentlichem Teilnahmewettbewerb");
						}
						else if (value == "NegCont") {
							value = _T("Freihändige Vergabe");
						}
						else if (value == "IntNATO") {
							value = _T("Internationale NATO-Ausschreibung");
						}
						else if (value == "CompetDialog") {
							value = _T("Wettbewerblicher Dialog");
						}
						else if (value == "InnovationPartnership") {
							value = _T("Innovationspartnerschaft");
						}

					}
					else if (name == "Cur") { name = _T("Währung:"); }
					else if (name == "CurLbl") { name = _T("Bezeichnung der Währung:"); }
					else if (name == "OpenDate")
					{
						name = _T("Datum des Eröffnungstermins:");
						CString rawOpenDate(value);
						year = rawOpenDate.Mid(0, 4);
						month = rawOpenDate.Mid(5, 2);
						day = rawOpenDate.Mid(8, 2);
						if (rawOpenDate.GetLength() >= 10) {
							value.Format(_T("%s.%s.%s"), day, month, year);
						}
						else if (rawOpenDate.GetLength() <= 7) {
							value.Format(_T("%s.%s"), month, year);
						}
					}
					else if (name == "OpenTime") { name = _T("Uhrzeit des Eröffnungstermins:"); }
					else if (name == "EvalEnd")
					{
						name = _T("Ende der Zuschlagsfrist:");
						CString rawEvalDate(value);
						year = rawEvalDate.Mid(0, 4);
						month = rawEvalDate.Mid(5, 2);
						day = rawEvalDate.Mid(8, 2);
						if (rawEvalDate.GetLength() >= 10) {
							value.Format(_T("%s.%s.%s"), day, month, year);
						}
						else if (rawEvalDate.GetLength() <= 7) {
							value.Format(_T("%s.%s"), month, year);
						}
					}
					else if (name == "SubmLoc") { name = _T("Abgabeort:"); }
					else if (name == "CnstStart")
					{
						name = _T("Voraussichtlicher Beginn \nder Ausführungszeit:");
						CString rawBeginnDate(value);
						year = rawBeginnDate.Mid(0, 4);
						month = rawBeginnDate.Mid(5, 2);
						day = rawBeginnDate.Mid(8, 2);
						if (rawBeginnDate.GetLength() >= 10) {
							value.Format(_T("%s.%s.%s"), day, month, year);
						}
						else if (rawBeginnDate.GetLength() <= 7) {
							value.Format(_T("%s.%s"), month, year);
						}
						size = CSize(clientRect_Vergabe.Width(), 50);
					}
					else if (name == "CnstEnd")
					{
						name = _T("Voraussichtlicher Ende \nder Ausführungszeit:");
						CString rawEndDate(value);
						year = rawEndDate.Mid(0, 4);
						month = rawEndDate.Mid(5, 2);
						day = rawEndDate.Mid(8, 2);
						if (rawEndDate.GetLength() >= 10) {
							value.Format(_T("%s.%s.%s"), day, month, year);
						}
						else if (rawEndDate.GetLength() <= 7) {
							value.Format(_T("%s.%s"), month, year);
						}
						size = CSize(clientRect_Vergabe.Width(), 50);
						y_pos_vergabeinfo += 20;
					}

					CStatic* pstaticValue_name = new CStatic();
					CStatic* pstaticValue_value = new CStatic();
					pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE | BS_MULTILINE,
						CRect(CPoint(20, y_pos_vergabeinfo), size), this, 1001);
					pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(270, y_pos_vergabeinfo), size), this, 1001);
					pstaticValue_value->SetFont(pMainFrame->GetFont());
					pstaticValue_name->SetFont(pMainFrame->GetFont());
					y_pos_vergabeinfo += 20;
				}
			}

			//Auftraggerber
			else if (award_node_text == "OWN") {
				Auftraggeber();
			}

			//Auftragnehmer
			else if (award_node_text == "CTR") {
				Auftragnehmer();
			}
		}
	}
}

void CVergabeinfosView::Auftraggeber() {

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	y_pos_auftraggeber = 300;

	m_staticText_Auftraggeber.Create(_T("Auftraggeber"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 250), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Auftraggeber.SetFont(pMainFrame->GetFontBold());

	for (xml_node<>* own_node = award_node->first_node(); own_node; own_node = own_node->next_sibling()) {
		CString own_node_name(own_node->name());
		CString value = Utf8ToCString(own_node->value());
		CString name = Utf8ToCString(own_node->name());

		if (own_node_name == "Address") {

			for (xml_node<>* address_node = own_node->first_node(); address_node; address_node = address_node->next_sibling()) {

				CString address_value = Utf8ToCString(address_node->value());
				CString address_name = Utf8ToCString(address_node->name());

				if (address_name == "Street") {
					address_name = "Straße und Hausnummer:";
				}
				else if (address_name == "PCode") {
					address_name = "Postleitzahl:";
				}
				else if (address_name == "City") {
					address_name = "Ort:";
				}
				else if (address_name == "Phone") {
					address_name = "Telefon:";
				}
				else if (address_name == "Fax") {
					address_name = "Fax:";
				}
				else if (address_name == "Email") {
					address_name = "E-Mail:";
				}
				else if (address_name == "Name1") {
					address_name = "Name:";
				}
				else if (address_name == "Name2") {
					address_name = "";
				}
				else if (address_name == "Name3") {
					address_name = "";
				}
				else if (address_name == "Name4") {
					address_name = "";
				}
				CStatic* pstaticValue_name = new CStatic();
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_name->Create(address_name, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(20, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_value->Create(address_value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(270, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
				pstaticValue_name->SetFont(pMainFrame->GetFont());
				y_pos_auftraggeber += 20;
			}
		}

		else if (own_node_name == "DPNo") {
			CStatic* pstaticValue_name = new CStatic();
			CStatic* pstaticValue_value = new CStatic();	
			name = _T("DV-Nummer:");
			pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->SetFont(pMainFrame->GetFont());
			pstaticValue_name->SetFont(pMainFrame->GetFont());
			y_pos_auftraggeber += 20;

		}

		else if (own_node_name == "AwardNo") {
			CStatic* pstaticValue_name = new CStatic();
			CStatic* pstaticValue_value = new CStatic();	
			name = _T("Vergabenummer:");
			pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->SetFont(pMainFrame->GetFont());
			pstaticValue_name->SetFont(pMainFrame->GetFont());
			y_pos_auftraggeber += 20;

		}
		else if (own_node_name == "AcctRecNo") {
			CStatic* pstaticValue_name = new CStatic();
			CStatic* pstaticValue_value = new CStatic();
			name = _T("Debitoren-Nummer:");
			pstaticValue_name->Create(name, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(20, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
				CRect(CPoint(270, y_pos_auftraggeber), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
			pstaticValue_value->SetFont(pMainFrame->GetFont());
			pstaticValue_name->SetFont(pMainFrame->GetFont());
			y_pos_auftraggeber += 20;
		}
	}
}

void CVergabeinfosView::Auftragnehmer() {

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	y_pos_auftragnehmer = 520;

	m_staticText_Auftragnehmer.Create(_T("Auftragnehmer"), WS_CHILD | WS_VISIBLE,
		CRect(CPoint(20, 470), CSize(clientRect_Vergabe.Width(), 30)), this, 1001);
	m_staticText_Auftragnehmer.SetFont(pMainFrame->GetFontBold());

	for (xml_node<>* ctr_node = award_node->first_node(); ctr_node; ctr_node = ctr_node->next_sibling() )
	{
		CString ctr_node_text(ctr_node->name());
		if (ctr_node_text == "Address") {
			for (xml_node<>* adresse_node_ctr = ctr_node->first_node(); adresse_node_ctr; adresse_node_ctr = adresse_node_ctr->next_sibling()) {
				CString ctr_node_value = Utf8ToCString(adresse_node_ctr->value());
				CString ctr_node_name = Utf8ToCString(adresse_node_ctr->name());
				if (ctr_node_name == "Street") {
					ctr_node_name = "Straße und Hausnummer:";
				}
				else if (ctr_node_name == "PCode") {
					ctr_node_name = "Postleitzahl:";
				}
				else if (ctr_node_name == "City") {
					ctr_node_name = "Ort:";
				}
				else if (ctr_node_name == "Name1") {
					ctr_node_name = "Name:";
				}
				else if (ctr_node_name == "Name2") {
					ctr_node_name = "";
				}
				else if (ctr_node_name == "Name3") {
					ctr_node_name = "";
				}
				else if (ctr_node_name == "Name4") {
					ctr_node_name = "";
				}
				if (ctr_node_value.IsEmpty()) { continue; }

				else {
					CStatic* pstaticValue_name = new CStatic();
					CStatic* pstaticValue_value = new CStatic();
					pstaticValue_name->Create(ctr_node_name, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(20, y_pos_auftragnehmer), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
					pstaticValue_value->Create(ctr_node_value, WS_CHILD | WS_VISIBLE,
						CRect(CPoint(270, y_pos_auftragnehmer), CSize(clientRect_Vergabe.Width(), 20)), this, 1001);
					pstaticValue_value->SetFont(pMainFrame->GetFont());
					pstaticValue_name->SetFont(pMainFrame->GetFont());
					y_pos_auftragnehmer += 20;
				}
			}
		}
	}

}

bool CVergabeinfosView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
{
	outLines.clear();
	CFile file;

	if (!file.Open(filePath, CFile::modeRead | CFile::shareDenyNone))
		return false;

	ULONGLONG len64 = file.GetLength();
	if (len64 == 0)
	{
		file.Close();
		return true;
	}
	if (len64 > 200ULL * 1024ULL * 1024ULL) // simple safety limit 200MB
	{
		file.Close();
		return false;
	}
	const int len = (int)len64;

	std::vector<char> buf((size_t)len + 1, 0);
	const UINT readBytes = file.Read(buf.data(), (UINT)len);
	file.Close();

	if ((int)readBytes != len)
		return false;

	// ANSI -> UTF-16
	int wlen = MultiByteToWideChar(CP_ACP, 0, buf.data(), len, nullptr, 0);
	if (wlen <= 0)
		return false;

	std::vector<wchar_t> wbuf((size_t)wlen + 1, 0);
	MultiByteToWideChar(CP_ACP, 0, buf.data(), len, wbuf.data(), wlen);
	wbuf[(size_t)wlen] = L'\0';

	CString content(wbuf.data());

	// Lines splitten (\r\n oder \n)
	int start = 0;
	const int n = content.GetLength();
	while (start < n)
	{
		int posCR = content.Find(_T('\r'), start);
		int posLF = content.Find(_T('\n'), start);

		int end;
		if (posCR == -1) end = posLF;
		else if (posLF == -1) end = posCR;
		else end = min(posCR, posLF);

		if (end == -1)
		{
			CString line = content.Mid(start);
			line.TrimRight(_T("\r\n"));
			outLines.push_back(line);
			break;
		}

		CString line = content.Mid(start, end - start);
		line.TrimRight(_T("\r\n"));
		outLines.push_back(line);

		// CRLF oder einzelnes CR / LF überspringen
		if (content[end] == _T('\r') && end + 1 < n && content[end + 1] == _T('\n'))
			start = end + 2;
		else
			start = end + 1;
	}

	return true;
}

bool CVergabeinfosView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
{
	int k1 = line.Find(_T('['));
	if (k1 != 0)
		return false;
	int k2 = line.Find(_T(']'), k1 + 1);
	if (k2 <= 1)
		return false;
	CString s = line;
	s.Trim();

	int endTag = s.ReverseFind(_T('['));
	if (endTag < 0)
		return false;
	CString tail = s.Mid(endTag);
	if (tail.CompareNoCase(_T("[end]")) != 0) return false;

	outKey = s.Mid(1, k2 - 1);
	outKey.Trim();

	outValue = s.Mid(k2 + 1, endTag - (k2 + 1));
	outValue.Trim();
	return !outKey.IsEmpty();
}

void CVergabeinfosView::CreateStaticText(CWnd* parent, const CString& label, const CString& value, int& yPos, CFont* pFont, int idBase)
{

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	const int labelX = 20;
	const int valueX = 270;
	const int height = 20;
	const int labelWidth = 240;
	const int valueWidth = 400;

	CStatic* pLabel = new CStatic();

	pLabel->Create(label,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
		CRect(labelX, yPos, labelX + labelWidth, yPos + height),
		this, idBase);

	CStatic* pValue = new CStatic();
	pValue->Create(value,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOPREFIX,
		CRect(valueX, yPos, valueX + valueWidth, yPos + height),
		this, idBase);
	pLabel->SetFont(pMainFrame->GetFont());
	pValue->SetFont(pMainFrame->GetFont());

	m_dynamicStatics.push_back(pLabel);
	m_dynamicStatics.push_back(pValue);

	yPos += height;
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
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
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