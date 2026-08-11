// CPositionView.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "CPositionView.h"
#include "MainFrm.h"

// CPositionView

IMPLEMENT_DYNCREATE(CPositionView, CView)

CPositionView::CPositionView()
{

}

CPositionView::~CPositionView()
{
}

BEGIN_MESSAGE_MAP(CPositionView, CView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


static int CALLBACK EnumFontFamExProc(const LOGFONT* lpelfe, const TEXTMETRIC* lpntme, DWORD FontType, LPARAM lParam)
{
	CComboBox* pCombo = reinterpret_cast<CComboBox*>(lParam);
	if (pCombo)
	{
		CString fontName = lpelfe->lfFaceName;
		if (fontName.GetLength() > 0 && fontName[0] != '@')  
		{
			// Avoid duplicates
			if (pCombo->FindStringExact(-1, fontName) == CB_ERR)
				pCombo->AddString(fontName);
		}
	}
	return 1;  
}

// CPositionView drawing

void CPositionView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

void CPositionView::OnInitialUpdate()
{
	CGAEBV2App* pApp = (CGAEBV2App*)AfxGetApp();
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(20, 180);
	Invalidate();
	UpdateWindow();
	m_edit_bg_color.CreateSolidBrush(RGB(255, 255, 200));

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	m_Doc = pMainFrame->GetXmlDoc();
	m_Root = pMainFrame->GetRootNode();
	m_pGAEBInfo = pMainFrame->GetGAEBInfoNode();
	m_pProjektInfo = pMainFrame->GetProjektInfoNode();
	m_award = pMainFrame->GetAwardNode();

	CClientDC dc(this);

	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 18; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI")); // Or "Arial", etc.
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_edit_small;
	::ZeroMemory(&lf_edit_small, sizeof(LOGFONT));
	lf_edit_small.lfHeight = 16;
	lf_edit_small.lfWeight = FW_NORMAL;
	_tcscpy_s(lf_edit_small.lfFaceName, _T("Segoe UI"));
	m_font_edit.CreateFontIndirect(&lf_edit_small);

	m_format = *pMainFrame->GetFormat();
	//m_format = pMainFrame->GetFormat();

	//GAEB XML
	if (m_format == "XML") {
		xml_node<>* boqNode = m_award->first_node("BoQ");
		xml_node<>* boqInfoNode = boqNode->first_node("BoQInfo");

		//Einheitpreis Anteile
		for (xml_node<>* lblupcomp_node = boqInfoNode->first_node(); lblupcomp_node; lblupcomp_node = lblupcomp_node->next_sibling()) {
			CString lblupcomp_node_name(lblupcomp_node->name());
			if (lblupcomp_node_name == "LblUPComp1") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 750), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
			else if (lblupcomp_node_name == "LblUPComp2") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 790), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
			else if (lblupcomp_node_name == "LblUPComp3") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 830), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
			else if (lblupcomp_node_name == "LblUPComp4") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 870), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
			else if (lblupcomp_node_name == "LblUPComp5") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 910), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
			else if (lblupcomp_node_name == "LblUPComp6") {
				CString value = Utf8ToString(lblupcomp_node->value());
				CStatic* pstaticValue_value = new CStatic();
				pstaticValue_value->Create(value, WS_CHILD | WS_VISIBLE,
					CRect(CPoint(860, 950), CSize(120, 20)), this, 1001);
				pstaticValue_value->SetFont(pMainFrame->GetFont());
			}
		}
	}


	//GAEB 2000
	else if (m_format == "2000") {	

	
	}

	//GAEB 90
	else if (m_format == "90") {
	}

	m_staticText_Position.Create(_T("Position"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 20), CSize(200, 30)), this, 1001);

	m_staticText_Ordnungszahl.Create(_T("Ordnungszahl (OZ)"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 50), CSize(100, 50)), this, 1001);
	m_staticText_Kurztext.Create(_T("Kurztext"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 140), CSize(80, 20)), this, 1001);
	m_staticText_Langtext.Create(_T("Langtext"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 250), CSize(80, 20)), this, 1001);
	
	m_edit_OZ.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160,50), CSize(120,20)), this, 1002);
	m_edit_OZ.SetWindowTextW(m_text_OZ);

	m_edit_kurztext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(20, 180), CSize(rect.Width(), 50)), this, 1005);
	m_edit_kurztext.SetFont(&m_font);


	m_edit_langtext.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT
		| ES_AUTOVSCROLL | ES_AUTOHSCROLL |	WS_VSCROLL | WS_HSCROLL, 
		CRect(CPoint(20, 290), CSize(rect.Width(), 400)), this, 1005);
	m_edit_langtext.SetFont(&m_font);

	m_staticText_Menge.Create(_T("Menge"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 710), CSize(80, 20)), this, 1001);
	m_staticText_Einheit.Create(_T("Einheit"), WS_CHILD | WS_VISIBLE, CRect(CPoint(360, 710), CSize(80, 20)), this, 1001);
	m_staticText_Einheitpreis.Create(_T("Einheitpreis [Euro]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 750), CSize(120, 20)), this, 1001);
	m_staticText_Nachlass.Create(_T("Nachlass [%]"), WS_CHILD | WS_VISIBLE, CRect(CPoint(20, 790), CSize(120, 20)), this, 1001);
	m_staticText_Gesamtpreis.Create(_T("Gesamtbetrag [Euro]"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 830), CSize(150, 20)), this, 1001);
	m_staticText_Summe.Create(_T("Summe Pos. [Euro]"), WS_CHILD | WS_VISIBLE |BS_MULTILINE, CRect(CPoint(20, 870), CSize(150, 20)), this, 1001);
	m_staticText_Anteilpreis.Create(_T("Einheitpreis-Anteile"), WS_CHILD | WS_VISIBLE, CRect(CPoint(600,750), CSize(120, 20)), this, 1001);


	m_staticText_Zeitansatz.Create(_T("Zeitansatz"), WS_CHILD | WS_VISIBLE, CRect(CPoint(600,710), CSize(80,20)), this, 1001);
	m_staticText_Stunden.Create(_T("Stunden"), WS_CHILD | WS_VISIBLE, CRect(CPoint(860, 710), CSize(80, 20)), this, 1001);
	m_edit_zeit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT,
		CRect(CPoint(740,710), CSize(80,20)), this, 1002);	


	m_edit_Menge.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 710), CSize(80, 20)), this, 1002);
	m_combobox_einheit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL,
		CRect(CPoint(260, 710), CSize(80, 20)), this, 1003);
	m_edit_einheitpreis.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 750), CSize(80, 20)), this, 1002);
	m_edit_nachlass.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 790), CSize(80, 20)), this, 1002);
	m_edit_gesamt.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 830), CSize(80, 20)), this, 1002);
	m_edit_summe.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(160, 870), CSize(80, 20)), this, 1002);

	m_edit_UP1.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 750), CSize(80, 20)), this, 1002);
	m_edit_UP2.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 790), CSize(80, 20)), this, 1002);
	m_edit_UP3.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 830), CSize(80, 20)), this, 1002);
	m_edit_UP4.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 870), CSize(80, 20)), this, 1002);
	m_edit_UP5.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 910), CSize(80, 20)), this, 1002);
	m_edit_UP6.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(740, 950), CSize(80, 20)), this, 1002);


	if (pApp && pApp->m_einheitList.GetSize() > 0)
	{
		for (int i = 0; i < pApp->m_einheitList.GetSize(); ++i)
		{
			m_combobox_einheit.AddString(pApp->m_einheitList[i]);
		}
	}
	m_combobox_einheit.SetFont(&m_font);



	CStatic* staticControls_bold[] = {
	&m_staticText_Position,
	};

	for (CStatic* pStatic : staticControls_bold)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font_bold);
	}
	CStatic* staticControls_normal[] = {
	&m_staticText_Ordnungszahl,
	&m_staticText_Menge,
	&m_staticText_Einheit,
	&m_staticText_Kurztext,
	&m_staticText_Langtext,
	&m_staticText_Einheit,
	&m_staticText_Einheitpreis,
	&m_staticText_Nachlass,
	&m_staticText_Gesamtpreis,
	&m_staticText_Zeitansatz,
	&m_staticText_Stunden,
	&m_staticText_Anteilpreis,
	};

	for (CStatic* pStatic : staticControls_normal)
	{
		if (pStatic->GetSafeHwnd())
			pStatic->SetFont(&m_font);
	}


	CEdit* editControls[] = {
		&m_edit_einheitpreis,
		&m_edit_gesamt,
		&m_edit_Menge,
		&m_edit_nachlass,
		&m_edit_summe,
		&m_edit_OZ,
		&m_edit_zeit,
		&m_edit_kurztext,
		&m_edit_langtext,
		&m_edit_UP1,
		& m_edit_UP2,
		& m_edit_UP3,
		& m_edit_UP4,
		& m_edit_UP5,
		& m_edit_UP6,

	};
	for (CEdit* pEdit : editControls)
	{
		if (pEdit->GetSafeHwnd())
		{
			pEdit->SetFont(&m_font_edit);
			pEdit->SetReadOnly(FALSE);
		}

		
	}
}

#ifdef _DEBUG
void CPositionView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPositionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


HBRUSH CPositionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);
	int ctrlID = pWnd->GetDlgCtrlID();

	if (ctrlID == 1001)
	{
		pDC->SetBkMode(TRANSPARENT);  // Set transparent background
		return (HBRUSH)GetStockObject(NULL_BRUSH); // No background fill
	}
	//Edit box
	if (ctrlID == 1005)
	{
		pDC->SetBkColor(RGB(255, 255, 200));
		// Return the brush for background color
		return m_edit_bg_color;
	}
	return hbr;
}

void CPositionView::SetTextOZ(CString text)
{
	CString oz_part;
	CString text_part;
	int i = 0;
	int len = text.GetLength();
	bool letter = false;
	for (int i = 0; i < text.GetLength(); i++)
	{
		if (_istalpha(text[i]))
		{
			letter = true;
		}
	}

	if (letter == true) {

		while (i < len && (_istdigit(text[i]) || text[i] == '.')) {
			oz_part += text[i];
			i++;
		}
		while (i < len && _istspace(text[i])) {
			i++;
		}
		text_part = text.Mid(i);

	}

	else {
		while (i < len) {
			oz_part += text[i];
			i++;
		}
	}



	if (m_edit_OZ.GetSafeHwnd() != NULL && ::IsWindow(m_edit_OZ.m_hWnd))
	{
		m_edit_OZ.SetWindowText(oz_part);
	}

	else {
		m_text_OZ = oz_part;
	}

	if (m_edit_bez.GetSafeHwnd() != NULL && ::IsWindow(m_edit_bez.m_hWnd)) {
		m_edit_bez.SetWindowText(text_part);
	}
	else {
		m_text_bez = text_part;
	}

	if (m_edit_kurztext.GetSafeHwnd() != NULL && ::IsWindow(m_edit_kurztext.m_hWnd)) {
		m_edit_kurztext.SetWindowText(text_part);
	}
	else {
		m_text_bez = text_part;
	}
}

void CPositionView::SetLangtext(CString text)
{
	if(m_edit_langtext.GetSafeHwnd() != NULL && ::IsWindow(m_edit_langtext.m_hWnd))
	{
		m_edit_langtext.SetWindowText(text);
	}
	else {
		m_text_FullLangtext = text;
	}
}

void CPositionView::SetMenge(CString text)
{
	if (m_edit_Menge.GetSafeHwnd() != NULL && ::IsWindow(m_edit_Menge.m_hWnd))
	{
		m_edit_Menge.SetWindowText(text);
	}
	else {
		m_text_Menge = text;
	}

}

void CPositionView::SetEinheitpreis(CString text)
{
	if (m_edit_einheitpreis.GetSafeHwnd() != NULL && ::IsWindow(m_edit_einheitpreis.m_hWnd))
	{
		m_edit_einheitpreis.SetWindowText(text);
	}
	else {
		m_text_Einheitpreis = text;
	}

}

void CPositionView::SetEinheit(CString text)
{
	if (text == "St") {
		text = _T("Stk");
	}

	
	if (m_combobox_einheit.GetSafeHwnd() != NULL && ::IsWindow(m_combobox_einheit.m_hWnd))
	{
		// Try to select the matching item
		int index = m_combobox_einheit.FindStringExact(-1, text);
		if (index != CB_ERR)
		{
			m_combobox_einheit.SetCurSel(index);
		}
		else
		{
			// Optional: add the text if it doesn't exist
			index = m_combobox_einheit.AddString(text);
			m_combobox_einheit.SetCurSel(index);
		}
	}
	else
	{
		// Combo box not ready yet — store value for later
		m_text_Einheit = text;
	}
}

void CPositionView::SetGesamtpreis(CString text)
{
	if (m_edit_gesamt.GetSafeHwnd() != NULL && ::IsWindow(m_edit_gesamt.m_hWnd))
	{
		m_edit_gesamt.SetWindowText(text);
	}
	else {
		m_text_Gesamtpreis = text;
	}
}

void CPositionView::SetNachlass(CString text)
{
	if (m_edit_nachlass.GetSafeHwnd() != NULL && ::IsWindow(m_edit_nachlass.m_hWnd)) 
	{
		m_edit_nachlass.SetWindowText(text);
	}
	else {
		m_text_Nachlass = text;
	}
}

void CPositionView::SetZeit(CString text)
{
	if (m_edit_zeit.GetSafeHwnd() != NULL && ::IsWindow(m_edit_zeit.m_hWnd))
	{
		m_edit_zeit.SetWindowText(text);
	}
	else {
		m_text_Zeitansatz = text;
	}
}

void CPositionView::SetUP1(CString text)
{
	if (m_edit_UP1.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP1.m_hWnd))
	{
		m_edit_UP1.SetWindowText(text);
	}
	else {
		m_text_UP1 = text;
	}
	
}

void CPositionView::SetUP2(CString text)
{
	if (m_edit_UP2.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP2.m_hWnd))
	{
		m_edit_UP2.SetWindowText(text);
	}
	else {
		m_text_UP2 = text;
	}
}

void CPositionView::SetUP3(CString text)
{
	if (m_edit_UP3.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP3.m_hWnd))
	{
		m_edit_UP3.SetWindowText(text);
	}
	else {
		m_text_UP3 = text;
	}
}

void CPositionView::SetUP4(CString text)
{
	if (m_edit_UP4.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP4.m_hWnd))
	{
		m_edit_UP4.SetWindowText(text);
	}
	else {
		m_text_UP4 = text;
	}
}

void CPositionView::SetUP5(CString text)
{
	if (m_edit_UP5.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP5.m_hWnd))
	{
		m_edit_UP5.SetWindowText(text);
	}
	else {
		m_text_UP5 = text;
	}
}

void CPositionView::SetUP6(CString text)
{
	if (m_edit_UP6.GetSafeHwnd() != NULL && ::IsWindow(m_edit_UP6.m_hWnd))
	{
		m_edit_UP6.SetWindowText(text);
	}
	else {
		m_text_UP6 = text;
	}
}

void CPositionView::SetSumme(CString text)
{
	if (m_edit_summe.GetSafeHwnd() != NULL && ::IsWindow(m_edit_summe.m_hWnd))
	{
		m_edit_summe.SetWindowText(text);
	}
	else {
		m_text_Summe = text;
	}
}

void CPositionView::SetCurrentItemData(Item_data* itemData)
{
	m_currentItemData = itemData;

	if (itemData == nullptr)
		return;
	SetTextOZ(m_currentItemData->OZ);
	SetMenge(m_currentItemData->Qty);
	SetEinheit(m_currentItemData->QU);
	SetEinheitpreis(m_currentItemData->UP);
	SetGesamtpreis(m_currentItemData->IT);
	SetNachlass(m_currentItemData->DiscountAnteil);
	SetZeit(m_currentItemData->TimeQu);
}

CString CPositionView::Utf8ToString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;
	//return CString();
}

bool CPositionView::ReadFileLinesAnsiToCStringW(const CString& filePath, std::vector<CString>& outLines)
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
	if (len64 > 200ULL * 1024ULL * 1024ULL)
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

		if (content[end] == _T('\r') && end + 1 < n && content[end + 1] == _T('\n'))
			start = end + 2;
		else
			start = end + 1;
	}

	return true;
}

bool CPositionView::TryParseGaebKeyValueLine(const CString& line, CString& outKey, CString& outValue)
{
	//#begin[GAEBInfo]
	//#end[GAEBInfo]
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
