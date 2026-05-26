// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "GAEB_V2.h"
#include "MainFrm.h"

#define WM_UPDATE_SCROLLVIEW  (WM_APP + 1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "GAEB_V2View.h"
#include "CProjektInfosView.h"
#include "CVergabeinfosView.h"
#include "CLVInfosView.h"
#include "CVertragView.h"
#include "CPositionView.h"
#include "CLV_MainView.h"
#include "CDocumentClass.h"
#include "CLangtextView.h"
#include "CProgressDialog.h"

#include <memory>
#include <map>

#define IDC_TREE1 1200
#define IDC_BLANKVIEW 1201


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	//ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_SCHLIESSEN, &CMainFrame::OnExit)
	ON_COMMAND(ID_BUTTON48, &CMainFrame::OnNew)
	ON_COMMAND(ID_BUTTON47, &CMainFrame::OnOpenFile)
	ON_COMMAND(ID_BUTTON5, &CMainFrame::OnExport)

	ON_COMMAND(ID_INDEX, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_INDEX, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_INDEX, &CMainFrame::OnIndex)
	ON_UPDATE_COMMAND_UI(ID_INDEX, &CMainFrame::OnUpdateIndex)
	ON_COMMAND(ID_INFO, &CMainFrame::OnInfo)
	ON_UPDATE_COMMAND_UI(ID_INFO, &CMainFrame::OnUpdateInfo)
	ON_COMMAND(ID_CHECK_STRUKTUR, &CMainFrame::OnStrukturAnsicht)
	ON_UPDATE_COMMAND_UI(ID_CHECK_STRUKTUR, &CMainFrame::OnUpdateStrukturAnsicht)
	ON_COMMAND(ID_CHECK_G2000, &CMainFrame::OnCheck_G2000)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G2000, &CMainFrame::OnUpdateCheck_G2000)
	ON_COMMAND(ID_CHECK_GXML, &CMainFrame::OnCheck_GXML)
	ON_UPDATE_COMMAND_UI(ID_CHECK_GXML, &CMainFrame::OnUpdateCheck_GXML)
	ON_COMMAND(ID_CHECK_G90, &CMainFrame::OnCheck_G90)
	ON_UPDATE_COMMAND_UI(ID_CHECK_G90, &CMainFrame::OnUpdateCheck_G90)		
	ON_COMMAND(ID_BUTTON_Speichern, &CMainFrame::OnButton_Speichern)
	ON_COMMAND(ID_BUTTON_SPEICHERN_UNTER, &CMainFrame::OnButton_SpeichernUnter)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMainFrame::OnTreeSelectedItem)

	ON_COMMAND(ID_KURZTEXT, &CMainFrame::OnKurztext)
	ON_UPDATE_COMMAND_UI(ID_KURZTEXT, &CMainFrame::OnUpdateKurztext)
	ON_COMMAND(ID_LANGTEXT, &CMainFrame::OnLangtext)
	ON_UPDATE_COMMAND_UI(ID_LANGTEXT, &CMainFrame::OnUpdateLangtext)
	ON_UPDATE_COMMAND_UI(ID_EXPORT, &CMainFrame::OnUpdateExport)
END_MESSAGE_MAP()


static CString GetField(const CString& line, int start, int len);


// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);	
	m_LVInfosView = nullptr;
	m_PInfoView = nullptr;
	m_VergabeView = nullptr;
	m_PosView = nullptr;
	m_VertragView = nullptr;
	m_MainView = nullptr;
}

CMainFrame::~CMainFrame()
{
}
rapidxml::xml_document<>* CMainFrame::GetXmlDoc()
{
	return m_xmlDoc.get();  
}
rapidxml::xml_node<>* CMainFrame::GetRootNode() {
	return m_root;
}
rapidxml::xml_node<>* CMainFrame::GetGAEBInfoNode() {
	return m_pGAEBInfo;
}
rapidxml::xml_node<>* CMainFrame::GetProjektInfoNode()
{
	return m_pProjektInfo; 
}
rapidxml::xml_node<>* CMainFrame::GetAwardNode()
{
	return m_award;  
}
void CMainFrame::LoadXMLFile()
{
	CProgressDialog dlg;
	dlg.Create(IDD_PROGRESS, this);
	dlg.ShowWindow(SW_SHOW);

	for (int i = 0; i <= 100; i++)
	{
		CString msg;
		msg.Format(_T("GAEB Daten werden eingelesen [%d%%]"), i);
		dlg.SetMessage(msg);
		
		dlg.SetProgress(i);
		AfxPumpMessage();
		Sleep(20);  
	}
	dlg.DestroyWindow();
}

void CMainFrame::FillClassView(const CString& filePath)
{
	CT2A asciiPath(filePath);
	m_wndClassView.DeleteAllItems();

	HTREEITEM info = m_wndClassView.InsertItem(TVIF_TEXT | TVIF_IMAGE |TVIF_SELECTEDIMAGE,
		_T("Informationen"),
		0,1,0,0,0,
		TVI_ROOT, TVI_LAST);
	HTREEITEM project_info = m_wndClassView.InsertItem(_T("Projekt"), info, TVI_LAST);
	HTREEITEM vergabe_info = m_wndClassView.InsertItem(_T("Vergabe"), info, TVI_LAST);
	HTREEITEM vertrag_info = m_wndClassView.InsertItem(_T("Vertragliche Regelung"), info, TVI_LAST);
	LV_Main = m_wndClassView.InsertItem(_T("Leistungsverzeichnis"), TVI_ROOT, TVI_LAST);

	if (m_format == "XML") {
		//Parse XML File
		m_xmlFile = std::make_unique<rapidxml::file<>>(asciiPath);
		m_xmlDoc = std::make_unique<rapidxml::xml_document<>>();
		m_xmlDoc->parse<0>(m_xmlFile->data());
		m_root = m_xmlDoc->first_node();
		m_root->name("Leistungsverzeichnis");


		m_pGAEBInfo = m_root->first_node("GAEBInfo");
		m_pProjektInfo = m_pGAEBInfo ? m_pGAEBInfo->next_sibling("PrjInfo") : nullptr;
		m_award = m_pProjektInfo ? m_pProjektInfo->next_sibling("Award") : nullptr;
		m_addtext = m_award ? m_award->next_sibling("AddText") : nullptr;


		if (!m_root) return;

		if (!m_award) return;

		xml_node<>* boqNode = m_award->first_node("BoQ");
		if (!boqNode) return;

		xml_node<>* boQbodyNode = boqNode->first_node("BoQBody");
		if (!boQbodyNode) return;

		std::vector<int> rootPath;

		xml_node<>* remark_node = boQbodyNode->first_node("Remark");

		if (remark_node) {
			Item_data* pData = new Item_data;
			HTREEITEM thisItem = nullptr;
			CString remark_kurztext;
			CString remark_fulltext;
			CString OZ = nullptr;

			xml_node<>* descr_node = remark_node->first_node("Description");

			if (descr_node)
			{
				for (xml_node<>* descr_childNode = descr_node->first_node(); descr_childNode; descr_childNode = descr_childNode->next_sibling()) {
					CString descr_child_name(descr_childNode->name());

					if (descr_child_name == "CompleteText") {
						xml_node<>* outltext_node = descr_childNode->first_node("OutlineText");
						xml_node<>* detailtext_node = descr_childNode->first_node("DetailTxt");
						if (outltext_node) {
							for (outltext_node; outltext_node; outltext_node = outltext_node->next_sibling("OutlineText")) {
								for (xml_node<>* textoutTxt_node = outltext_node->first_node(); textoutTxt_node; textoutTxt_node = textoutTxt_node->next_sibling()) {
									for (xml_node<>* p_node = textoutTxt_node->first_node(); p_node; p_node = p_node->next_sibling()) {
										for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling()) {
											CString spantext = Utf8ToString(span_node->value());
											if (!spantext.IsEmpty()) {
												remark_kurztext += spantext + _T(" ");
											}
										}
									}
								}
							}
							thisItem = m_wndClassView.InsertItem(remark_kurztext, LV_Main);

						}
						else {
							thisItem = m_wndClassView.InsertItem(_T("Hinweis"), LV_Main);
						}

						if (detailtext_node) {
							for (xml_node<>* text_node = detailtext_node->first_node(); text_node; text_node = text_node->next_sibling()) {
								for (xml_node<>* p_node = text_node->first_node(); p_node; p_node = p_node->next_sibling()) {
									for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling()) {
										CString span_name(span_node->name());
										CString span_value = Utf8ToString(span_node->value());
										if (span_name.CompareNoCase(_T("br")) == 0) {
											remark_fulltext += _T("\r\n");
										}
										else if (span_name.CompareNoCase(_T("span")) == 0) {
											remark_fulltext += span_value + _T(" ");
										}
									}
									remark_fulltext += _T("\r\n");
								}
							}
						}
						else {
							remark_fulltext = _T("");
						}
					}
					else if (descr_child_name == "OutlineText") {
						for (xml_node<>* outltext_node = descr_childNode->first_node(); outltext_node; outltext_node = outltext_node->next_sibling()) {
							for (xml_node<>* textoutTxt_node = outltext_node->first_node(); textoutTxt_node; textoutTxt_node = textoutTxt_node->next_sibling()) {
								for (xml_node<>* p_node = textoutTxt_node->first_node(); p_node; p_node = p_node->next_sibling()) {
									for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling()) {
										CString spantext = Utf8ToString(span_node->value());
										if (!spantext.IsEmpty()) {
											remark_kurztext += spantext + _T(" ");
										}
									}
								}
							}
						}
						thisItem = m_wndClassView.InsertItem(remark_kurztext, LV_Main);
					}
				}

			}
			else {
				for (remark_node; remark_node; remark_node = remark_node->next_sibling())
				{
					remark_fulltext = _T(" ");
					remark_kurztext = _T("Hinweis");
					thisItem = m_wndClassView.InsertItem(remark_kurztext, LV_Main);
				}
			}


			pData->Full_Kurztext_data = remark_kurztext;
			pData->Full_Langtext_data = remark_fulltext;

			if (pData != nullptr)
				m_wndClassView.SetItemData(thisItem, reinterpret_cast<DWORD_PTR>(pData));
		}

		for (xml_node<>* child_node = boQbodyNode->first_node(); child_node; child_node = child_node->next_sibling()) {
			Recursive_Node(child_node, rootPath, LV_Main);
		}
	}

	else if (m_format == "2000") {
		CStdioFile file;
		std::vector<CString> lines;

		if (file.Open(filePath, CFile::modeRead | CFile::typeText)) {
			CString line;
			while (file.ReadString(line)) {
				lines.push_back(line);
			}
			file.Close();
		}

		struct NodeCtx
		{
			CString type;
			CString oz;
			CString bez;
			CString kurztext;
			CString langtext;
			CString menge;
			CString me;
			CString ep;
			CString bedarf;
			HTREEITEM item = nullptr;
		};

		bool inBeschreibung = false;
		bool readingKurztext = false;
		bool readingLangtext = false;
		CString textBuffer;

		std::vector<NodeCtx> stack;

		auto GetTagValue = [](CString line, CString tag) -> CString
			{
				line.Trim();

				CString start = _T("[") + tag + _T("]");
				int p1 = line.Find(start);
				if (p1 < 0)
					return _T("");

				p1 += start.GetLength();

				int p2 = line.Find(_T("[end]"), p1);
				if (p2 < 0)
					return _T("");

				CString value = line.Mid(p1, p2 - p1);
				value.Trim();
				return value;
			};

		auto FormatOZ2000 = [](CString oz) -> CString
			{
				oz.Trim();

				if (oz.GetLength() == 3)
					return oz; // 000

				if (oz.GetLength() == 5)
					return oz.Left(3) + _T(".") + oz.Mid(3, 2); // 000.10

				if (oz.GetLength() == 9)
					return oz.Left(3) + _T(".") + oz.Mid(3, 2) + _T(".") + oz.Mid(5, 4); // 000.10.0010

				return oz;
			};

		auto EnsureCurrentItem = [&]()
			{
				if (stack.empty())
					return;

				NodeCtx& cur = stack.back();

				if (cur.item != nullptr)
					return;

				if (cur.oz.IsEmpty())
					return;

				CString display = FormatOZ2000(cur.oz);

				if (!cur.bez.IsEmpty())
					display += _T(" ") + cur.bez;

				HTREEITEM parent = LV_Main;

				if (stack.size() >= 2)
				{
					NodeCtx& parentCtx = stack[stack.size() - 2];
					if (parentCtx.item != nullptr)
						parent = parentCtx.item;
				}

				Item_data* pData = new Item_data;
				pData->Full_Kurztext_data = display;
				pData->Full_Langtext_data = _T("");

				cur.item = m_wndClassView.InsertItem(display, parent);
				m_wndClassView.SetItemData(cur.item, reinterpret_cast<DWORD_PTR>(pData));
			};

		for (const auto& raw : lines)
		{
			if (readingKurztext || readingLangtext)
			{
				if (line.Find(_T("[end]")) >= 0)
				{
					int p = line.Find(_T("[end]"));
					textBuffer += line.Left(p);

					CString text = textBuffer;
					text.Replace(_T("\\line"), _T("\r\n"));
					text.Replace(_T("\\par"), _T("\r\n"));
					text.Trim();

					// Position suchen = oberster Stack-Eintrag mit type Position
					for (int i = (int)stack.size() - 1; i >= 0; --i)
					{
						if (stack[i].type == _T("Position"))
						{
							Item_data* pData = reinterpret_cast<Item_data*>(
								m_wndClassView.GetItemData(stack[i].item)
								);

							if (pData)
							{
								if (readingKurztext)
								{
									stack[i].kurztext = text;

									CString display = FormatOZ2000(stack[i].oz) + _T(" ") + text;
									m_wndClassView.SetItemText(stack[i].item, display);
									pData->Full_Kurztext_data = display;
								}
								else
								{
									stack[i].langtext = text;
									pData->Full_Langtext_data = text;
								}
							}

							break;
						}
					}

					readingKurztext = false;
					readingLangtext = false;
					textBuffer.Empty();
				}
				else
				{
					textBuffer += line + _T("\r\n");
				}

				continue;
			}
			CString line = raw;
			line.Trim();

			if (line.Find(_T("#begin[LVBereich]")) >= 0)
			{
				NodeCtx ctx;
				ctx.type = _T("LVBereich");
				stack.push_back(ctx);
			}
			else if (line.Find(_T("#begin[Position]")) >= 0)
			{
				NodeCtx ctx;
				ctx.type = _T("Position");
				stack.push_back(ctx);			
			}					

			else if (line.Find(_T("#begin[Beschreibung]")) >= 0) {
				inBeschreibung = true;		
			}
			else if (line.Find(_T("#end[Beschreibung]")) >= 0) {
				inBeschreibung = false;
			}

			else if (line.Find(_T("#end[LVBereich]")) >= 0 ||
				line.Find(_T("#end[Position]")) >= 0)
			{
				if (!stack.empty())
					stack.pop_back();
			}
			else if (!stack.empty())
			{
				CString oz = GetTagValue(line, _T("OZ"));
				if (!oz.IsEmpty())
				{
					stack.back().oz = oz;
					EnsureCurrentItem();
				}

				CString bez = GetTagValue(line, _T("Bez"));
				CString beztxt = GetTagValue(line, _T("BezTx"));
				if (!beztxt.IsEmpty()) {
					bez = beztxt;
				}

				if (!bez.IsEmpty())
				{
					stack.back().bez = bez;

					if (stack.back().item != nullptr)
					{
						CString display = FormatOZ2000(stack.back().oz) + _T(" ") + bez;
						m_wndClassView.SetItemText(stack.back().item, display);

						Item_data* pData = reinterpret_cast<Item_data*>(
							m_wndClassView.GetItemData(stack.back().item)
							);

						if (pData)
							pData->Full_Kurztext_data = display;
					}
				}				
			}

			if (line.Find(_T("[Kurztext]")) >= 0)
			{
				readingKurztext = true;
				textBuffer.Empty();
				continue;
			}

			if (line.Find(_T("[Langtext]")) >= 0)
			{
				readingLangtext = true;
				textBuffer.Empty();
				continue;
			}
		}

		m_wndClassView.Expand(LV_Main, TVE_EXPAND);
	}

	else if (m_format == "90")
	{
		CStdioFile file;
		std::vector<CString> lines;

		if (file.Open(filePath, CFile::modeRead | CFile::typeText))
		{
			CString line;
			while (file.ReadString(line))
				lines.push_back(line);

			file.Close();
		}

		std::map<CString, HTREEITEM> itemMap;

		CString currentOZ;
		HTREEITEM currentItem = nullptr;

		auto clean = [](CString  s) -> CString {
			s.Trim();
			return s;
			};

		auto GetParentOZ = [&](const CString& oz) -> CString
			{
				CString s = oz;
				s.Trim();

				if (s.GetLength() == 7 || s.GetLength() == 8)
					return s.Left(4);

				if (s.GetLength() == 4)
					return s.Left(2);

				if (s.GetLength() > 1)
					return s.Left(s.GetLength() - 1);

				return _T("");
			};

		auto ReadOZ11 = [&](const CString& line) -> CString
			{
				CString oz = GetField(line, 2, 9);
				oz.Trim();
				oz.Remove(_T(' '));
				return oz;
			};

		auto ReadOZ21 = [&](const CString& line) -> CString
			{
				CString ozTeil = GetField(line, 2, 4);
				CString posTeil = GetField(line, 6, 3);

				ozTeil.Trim();
				posTeil.Trim();

				CString pos;
				pos.Format(_T("%03d"), _ttoi(posTeil));

				return ozTeil + pos;
			};

		auto ReadOZ23 = [&](const CString& line) -> CString
			{
				CString oz = GetField(line, 2, 8);
				oz.Trim();
				return oz;
			};


		auto InsertOrUpdateItem = [&](const CString& oz, const CString& text)
			{
				CString cleanOZ = oz;
				cleanOZ.Trim();

				if (cleanOZ.IsEmpty())
					return;

				CString displayText = cleanOZ;

				CString cleanText = text;
				cleanText.Trim();

				if (!cleanText.IsEmpty())
					displayText += _T(" ") + cleanText;

				if (itemMap.find(cleanOZ) != itemMap.end())
				{
					m_wndClassView.SetItemText(itemMap[cleanOZ], displayText);
					return;
				}

				CString parentOZ = GetParentOZ(cleanOZ);

				HTREEITEM parent = LV_Main;
				if (!parentOZ.IsEmpty() && itemMap.find(parentOZ) != itemMap.end())
					parent = itemMap[parentOZ];

				Item_data* pData = new Item_data;
				pData->Full_Kurztext_data = displayText;
				pData->Full_Langtext_data = _T("");

				HTREEITEM item = m_wndClassView.InsertItem(displayText, parent);
				m_wndClassView.SetItemData(item, reinterpret_cast<DWORD_PTR>(pData));

				itemMap[cleanOZ] = item;
				currentOZ = cleanOZ;
				currentItem = item;
			};



		for (const auto& raw : lines)
		{
			CString line = raw;
			line.TrimRight(_T("\r\n"));

			if (line.GetLength() < 2)
				continue;

			CString satzart = GetField(line, 0, 2);

			if (satzart == _T("11"))
			{
				CString oz = ReadOZ11(line);
				InsertOrUpdateItem(oz, _T(""));
			}
			else if (satzart == _T("12"))
			{
				CString text = GetField(line, 2, 70);
				if (!currentOZ.IsEmpty())
					InsertOrUpdateItem(currentOZ, text);
			}
			else if (satzart == _T("21"))
			{
				CString oz = ReadOZ21(line);
				InsertOrUpdateItem(oz, _T(""));
			}
			else if (satzart == _T("25"))
			{
				CString text = GetField(line, 2, 70);
				if (!currentOZ.IsEmpty())
					InsertOrUpdateItem(currentOZ, text);
			}
			else if (satzart == _T("26"))
			{
				CString lang = GetField(line, 2, 70);

				if (currentItem != nullptr)
				{
					Item_data* pData = reinterpret_cast<Item_data*>(
						m_wndClassView.GetItemData(currentItem)
						);

					if (pData)
					{
						if (!pData->Full_Langtext_data.IsEmpty())
							pData->Full_Langtext_data += _T("\r\n");

						pData->Full_Langtext_data += lang;
					}
				}
			}
			else if (satzart == _T("23"))
			{
				CString oz = ReadOZ23(line);

				if (!oz.IsEmpty())
				{
					// Parent automatisch erzeugen
					CString bereich = oz.Left(2);
					CString titel = oz.Left(4);

					if (itemMap.find(bereich) == itemMap.end())
						InsertOrUpdateItem(bereich, _T(""));

					if (itemMap.find(titel) == itemMap.end())
						InsertOrUpdateItem(titel, _T(""));

					InsertOrUpdateItem(oz, _T(""));

					currentOZ = oz;
					currentItem = itemMap[oz];

					Item_data* pData =
						reinterpret_cast<Item_data*>(
							m_wndClassView.GetItemData(currentItem));

					if (pData)
					{
						CString ep = GetField(line, 12, 10);
						CString gp = GetField(line, 24, 12);

						pData->UP = ep;
						pData->IT = gp;
					}
				}
			}
		}

		for (auto& pair : itemMap)
		{
			m_wndClassView.Expand(pair.second, TVE_EXPAND);
		}
	}
	

	m_wndClassView.Expand(info, TVE_EXPAND);
	m_wndClassView.Expand(LV_Main, TVE_EXPAND);	

	HTREEITEM hDefault = m_wndClassView.GetChildItem(info);
	if (!hDefault) {
		hDefault = info;
	}
	//OnTreeSelectedItem(nullptr, nullptr);
	m_wndClassView.SelectItem(info);
	m_wndClassView.SetFocus();
}

static CString GetField(const CString& line, int start, int len) {
	if (start >= line.GetLength())
		return _T("");
	int reallen = min(len, line.GetLength() - start);
	CString s = line.Mid(start, reallen);
	s.Trim();
	return s;
}

void CMainFrame::OnTreeSelectedItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	if (!pNMTreeView) return; 
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (!hItem) return;

	HTREEITEM hSelectedItem = m_wndClassView.GetSelectedItem();
	HTREEITEM hroot = m_wndClassView.GetRootItem();
	CString itemText = m_wndClassView.GetItemText(hSelectedItem);	
	CView* pView = GetActiveView();

	m_wndClassView.SetFocus();

	if (itemText == _T("Informationen")) {
		SwitchView(RUNTIME_CLASS(CLVInfosView), m_LVInfosView);
	}
	else if (itemText == _T("Projekt")) {
		SwitchView(RUNTIME_CLASS(CProjektInfosView), m_PInfoView);

	}
	else if (itemText == _T("Vergabe")) {
		SwitchView(RUNTIME_CLASS(CVergabeinfosView), m_VergabeView);
	}
	else if (itemText == _T("Vertragliche Regelung")) {
		//SwitchView(RUNTIME_CLASS(CVertragView), (CView*&)m_VertragView);
	}
	else if (itemText == _T("Leistungsverzeichnis")) {
		m_checkbox_KT = TRUE;
		m_checkbox_LT = FALSE;

		SwitchView(RUNTIME_CLASS(CLV_MainView), (CView*&)m_MainView);

	}
	else {
		SwitchView(RUNTIME_CLASS(CPositionView), m_PosView );
		Item_data* pInfo = (Item_data*)m_wndClassView.GetItemData(hSelectedItem);
		CView* pNewView = GetActiveView();
		CPositionView* plistView = DYNAMIC_DOWNCAST(CPositionView, pNewView);
		if (itemText == "...") {
			itemText = _T(" ");
		}

		if (plistView) {
			plistView->SetTextOZ(itemText);
			plistView->SetLangtext(pInfo->Full_Langtext_data);
			plistView->SetMenge(pInfo->Qty);
			plistView->SetEinheit(pInfo->QU);
			plistView->SetEinheitpreis(pInfo->UP);
			plistView->SetUP1(pInfo->UP1);
			plistView->SetUP2(pInfo->UP2);
			plistView->SetUP3(pInfo->UP3);
			plistView->SetUP4(pInfo->UP4);
			plistView->SetUP5(pInfo->UP5);
			plistView->SetUP6(pInfo->UP6);
			plistView->SetGesamtpreis(pInfo->IT);
			plistView->SetZeit(pInfo->TimeQu);
			plistView->SetSumme(pInfo->Total);
			plistView->SetNachlass(pInfo->DiscountAnteil);
		}

	}
	if (pResult) {
		*pResult = 0;
	}

}

void CMainFrame::SwitchView(CRuntimeClass* pNewViewClass, CView*& pViewPtr)
{
	CView* pOldView = GetActiveView();
	if (pOldView == nullptr || pOldView->IsKindOf(pNewViewClass)) {
		return; // Already the correct view or invalid
	}
	CDocument* pDoc = pOldView->GetDocument();
	CCreateContext context;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = pNewViewClass;
	// Create new view
	CView* pNewView = (CView*)pNewViewClass->CreateObject();
	ASSERT(pNewView->IsKindOf(RUNTIME_CLASS(CView)));

	CRect rect;
	pOldView->GetWindowRect(&rect);
	ScreenToClient(&rect);

	pNewView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect, this, AFX_IDW_PANE_FIRST, &context);
	pNewView->OnInitialUpdate();
	SetActiveView(pNewView);
	pNewView->ShowWindow(SW_SHOW);

	pOldView->ShowWindow(SW_HIDE);
	pOldView->DestroyWindow();
}


void CMainFrame::Recursive_Item(xml_node<>* itemNode, std::vector<int> path, HTREEITEM parentItem)
{
	int itemCount = 0;

	for (xml_node<>* item = itemNode->first_node(); item; item = item->next_sibling()) {
		CString item_name(item->name());

		Item_data* pData = new Item_data;
		HTREEITEM item_added = nullptr;

		if (item_name == "Item")
		{

 			itemCount++;
			std::vector<int> currentPath_item = path;
			currentPath_item.push_back(itemCount);

			// Format like "1.2.3"
			CString formattedPath_item;
			for (size_t i = 0; i < currentPath_item.size(); ++i)
			{
				formattedPath_item.AppendFormat(_T("%d"), currentPath_item[i]);
				//if (i < currentPath_item.size() - 1)
				formattedPath_item.Append(_T(". "));
			}

			CString Fulltext, Full_Langtext, menge, einheit, einheitpreis, gesamtpreis, 
				zeitansatz, comp1, comp2, comp3, comp4, comp5, comp6, nachlass_anteil, nachlass_pauschal;
			xml_node<>* descr_node = item->first_node("Description");
			if (descr_node) {
				for (xml_node<>* item_child = item->first_node(); item_child; item_child = item_child->next_sibling())
				{
					CString tag(item_child->name());
					CString val(Utf8ToString(item_child->value()));

					if (//descr_node)
						tag == "Description")
					{
						xml_node<>* complete_txt_node = item_child->first_node("CompleteText");

						for (xml_node<>* compl_text = complete_txt_node->first_node(); compl_text; compl_text = compl_text->next_sibling())
						{
							CString compl_text_name(compl_text->name());


							//Langtext
							if (compl_text_name == "DetailTxt") {
								for (xml_node<>* detail_text = compl_text->first_node(); detail_text; detail_text = detail_text->next_sibling()) {
									CString detail_text_name(detail_text->name());
									if (detail_text_name == "Text") {
										for (xml_node<>* p_node = detail_text->first_node(); p_node; p_node = p_node->next_sibling())
										{
											for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())	//span
											{
												CString span_node_text = Utf8ToString(span_node->value());
												CString nodeName(span_node->name());

												//if (!span_node_text.IsEmpty()) {
													//Full_Langtext += span_node_text;
												//}

												if (nodeName.CompareNoCase(_T("br")) == 0)
												{
													Full_Langtext += _T("\r\n");
												}
												else if (nodeName.CompareNoCase(_T("span")) == 0)
												{
													CString spanText = Utf8ToString(span_node->value());
													Full_Langtext += spanText + _T(" ");
												}
											}
											Full_Langtext += _T("\r\n");
										}

									}
								}
							}							

							//Kurztext
							if (compl_text_name == "OutlineText") {
								for (xml_node<>* OutlTxt = compl_text->first_node(); OutlTxt; OutlTxt = OutlTxt->next_sibling()) //Text
								{
									for (xml_node<>* TextOutlTxt = OutlTxt->first_node(); TextOutlTxt; TextOutlTxt = TextOutlTxt->next_sibling()) //p
									{
										for (xml_node<>* p_node_kurztext = TextOutlTxt->first_node(); p_node_kurztext; p_node_kurztext = p_node_kurztext->next_sibling())	//span
										{
											for (xml_node<>* span_node_kurztext = p_node_kurztext->first_node(); span_node_kurztext; span_node_kurztext = span_node_kurztext->next_sibling())	//span
											{
												CString span_node_kurztext_text = Utf8ToString(span_node_kurztext->value());
												if (!span_node_kurztext_text.IsEmpty()) {
													Fulltext += span_node_kurztext_text;
													Fulltext = formattedPath_item + Fulltext;
													int maxDepth_item = 0;
												}
											}
										}
									}
								}
								item_added = m_wndClassView.InsertItem(Fulltext, parentItem);
							}
						}
					}

					else if (tag == "Qty") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						menge = val;

					}
					else if (tag == "UP")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						einheitpreis = val;
					}
					else if (tag == "IT")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						gesamtpreis = val;
					}
					else if (tag == "TimeQu") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						zeitansatz = val;
					}
					else if (tag == "QU") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						einheit = val;
					}
					else if (tag == "UPComp1")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp1 = val;
					}
					else if (tag == "UPComp2")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp2 = val;
					}
					else if (tag == "UPComp3")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp3 = val;
					}
					else if (tag == "UPComp4")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp4 = val;
					}
					else if (tag == "UPComp5")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp5 = val;
					}
					else if (tag == "UPComp6")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp6 = val;
					}
					else if (tag == "DiscountPcnt") {
						if (val.Find('.') != -1) {
							val.Replace(_T("."), _T(","));
						}
						nachlass_anteil = val;
					}
				}
			}
			else {
				for (xml_node<>* item_child = item->first_node(); item_child; item_child = item_child->next_sibling())
				{
					Fulltext = formattedPath_item;
					Full_Langtext = _T("");
					CString tag(item_child->name());
					CString val(Utf8ToString(item_child->value()));
					if (tag == "Qty") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						menge = val;

					}
					else if (tag == "UP")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						einheitpreis = val;
					}
					else if (tag == "IT")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						gesamtpreis = val;
					}
					else if (tag == "TimeQu") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						zeitansatz = val;
					}
					else if (tag == "QU") {
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						einheit = val;
					}
					else if (tag == "UPComp1")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp1 = val;
					}
					else if (tag == "UPComp2")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp2 = val;
					}
					else if (tag == "UPComp3")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp3 = val;
					}
					else if (tag == "UPComp4")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp4 = val;
					}
					else if (tag == "UPComp5")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp5 = val;
					}
					else if (tag == "UPComp6")
					{
						if (val.Find('.') != -1)
						{
							val.Replace(_T("."), _T(","));
						}
						comp6 = val;
					}
					else if (tag == "DiscountPcnt") {
						if (val.Find('.') != -1) {
							val.Replace(_T("."), _T(","));
						}
						nachlass_anteil = val;
					}

				}
				item_added = m_wndClassView.InsertItem(Fulltext, parentItem);

			}

			pData->Full_Kurztext_data = Fulltext;
			pData->Full_Langtext_data = Full_Langtext;
			pData->Qty = menge;
			pData->QU = einheit;
			pData->UP = einheitpreis;
			pData->IT = gesamtpreis;
			pData->TimeQu = zeitansatz;
			pData->UP1 = comp1;
			pData->UP2 = comp2;
			pData->UP3 = comp3;
			pData->UP4 = comp4;
			pData->UP5 = comp5;
			pData->UP6 = comp6;
			pData->DiscountAnteil = nachlass_anteil;


			if (item_added != nullptr)
				m_wndClassView.SetItemData(item_added, reinterpret_cast<DWORD_PTR>(pData));
		}

		else if (item_name == "Remark") {
			xml_node<>* descr_node = item->first_node();
			CString Remark_Kurztext, Remark_Langtext;
			
			if (!descr_node) 
			{  
				item_added = m_wndClassView.InsertItem(_T("..."), parentItem);
			}
			else if (descr_node) {
				for (xml_node<>* descr_childNode = descr_node->first_node(); descr_childNode; descr_childNode = descr_childNode->next_sibling())
				{
					CString desct_childNode_name(descr_childNode->name());
					if (desct_childNode_name == "CompleteText") {
						xml_node<>* detailtext_node = descr_childNode->first_node("DetailTxt");
						xml_node<>* outlinetext_node = descr_childNode->first_node("OutlineText");

						for (detailtext_node; detailtext_node; detailtext_node = detailtext_node->next_sibling("DetailTxt")) {
							for (xml_node<>* text_node = detailtext_node->first_node("Text"); text_node; text_node = text_node->next_sibling("Text")) {
								for (xml_node<>* p_node = text_node->first_node(); p_node; p_node = p_node->next_sibling())
								{
									for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
									{
										CString span_node_text = Utf8ToString(span_node->value());
										CString nodeName(span_node->name());
										if (nodeName.CompareNoCase(_T("br")) == 0)
										{
											Remark_Langtext += _T("\r\n");
										}
										else if (nodeName.CompareNoCase(_T("span")) == 0)
										{
											CString spanText = Utf8ToString(span_node->value());
											Remark_Langtext += spanText + _T(" ");
										}

										Remark_Langtext += _T("\r\n");
									}
								}
							}
						}
						for (outlinetext_node; outlinetext_node; outlinetext_node = outlinetext_node->next_sibling()) {
							for (xml_node<>* OutlTxt_node = outlinetext_node->first_node("OutlTxt"); OutlTxt_node; OutlTxt_node = OutlTxt_node->next_sibling()) {
								for (xml_node<>* TextOutlTxt_node = OutlTxt_node->first_node("TextOutlTxt"); TextOutlTxt_node; TextOutlTxt_node = TextOutlTxt_node->next_sibling()) {
									for (xml_node<>* p_node = TextOutlTxt_node->first_node(); p_node; p_node = p_node->next_sibling()) {
										for (xml_node<>* span_node = p_node->first_node(); span_node; span_node = span_node->next_sibling())
										{
											CString span_node_kurztext = Utf8ToString(span_node->value());
											if (!span_node_kurztext.IsEmpty()) {
												Remark_Kurztext += span_node_kurztext;
											}
										}
										item_added = m_wndClassView.InsertItem(Remark_Kurztext, parentItem);
										//item_added.

									}
								}
							}
						}
					}
					pData->Full_Kurztext_data = Remark_Kurztext;
					pData->Full_Langtext_data = Remark_Langtext;
					if (item_added != nullptr)
						m_wndClassView.SetItemData(item_added, reinterpret_cast<DWORD_PTR>(pData));
				}
			}
		}
	}
}
void CMainFrame::Recursive_Node(xml_node<>* ctgyNode, std::vector<int> path, HTREEITEM parentItem)
{
	int ctgyCount = 0;
	std::vector<int> currentPath = path;
	if (auto* attr = ctgyNode->first_attribute("RNoPart"))
		ctgyCount = atoi(attr->value());
	currentPath.push_back(ctgyCount);

	CString formattedPath;
	for (size_t i = 0; i < currentPath.size(); ++i)
	{
		formattedPath.AppendFormat(_T("%d"), currentPath[i]);
		//if (i < currentPath.size() - 1)
		formattedPath.Append(_T(". "));
	}
	m_path = formattedPath;


	for (xml_node<>* ctgy_childNode = ctgyNode->first_node(); ctgy_childNode; ctgy_childNode = ctgy_childNode->next_sibling())
	{
		CString ctgy_child_name(ctgy_childNode->name());


		if (ctgy_child_name == "BoQBody")
		{
			xml_node<>* lblTx = ctgyNode->first_node("LblTx");
			xml_node<>* itemList = ctgy_childNode->first_node("Itemlist");
			xml_node<>* totals = ctgyNode->first_node("Totals");
			CString Full_lbltx;
			CString Total_Preis = nullptr;
			HTREEITEM thisItem;

			// LblTx 
			if (lblTx) {
				CString lblText;
				for (xml_node<>* span = lblTx->first_node(); span; span = span->next_sibling()) {
					CString node_name(span->name());
					if (node_name == "p") {
						for (xml_node<>* p_node = span->first_node(); p_node; p_node = p_node->next_sibling()) {
							CString span_text = Utf8ToString(p_node->value());
							if (!span_text.IsEmpty()) {
								lblText += span_text;
							}
						}
					}
					else if (node_name == "span") {
						lblText += Utf8ToString(span->value());
					}
				}
				Full_lbltx = formattedPath + lblText;
			}

			if (totals) {
				for (xml_node<>* total_node = totals->first_node("Total"); total_node; total_node = total_node->next_sibling()) {
					CString total_value = Utf8ToString(total_node->value());
					if (total_value.Find('.') != -1)
					{
						total_value.Replace(_T("."), _T(","));
					}
					Total_Preis = total_value;
				}
			}

			if (Full_lbltx.IsEmpty()) {
				thisItem = m_wndClassView.InsertItem(m_path, parentItem);
				Item_data* pnewData = new Item_data;
				pnewData->Total = Total_Preis;
				m_wndClassView.SetItemData(thisItem, (DWORD_PTR)pnewData);
			}
			else
			{
				thisItem = m_wndClassView.InsertItem(Full_lbltx, parentItem);
				Item_data* pnewData = new Item_data;
				pnewData->Total = Total_Preis;
				m_wndClassView.SetItemData(thisItem, (DWORD_PTR)pnewData);
			}



			if (itemList) {
				Recursive_Item(itemList, currentPath, thisItem);
			}

			for (xml_node<>* ctgy_child_node = ctgy_childNode->first_node("BoQCtgy"); ctgy_child_node;
				ctgy_child_node = ctgy_child_node->next_sibling("BoQCtgy")) {
				Recursive_Node(ctgy_child_node, currentPath, thisItem);
			}
		}
		else if (ctgy_child_name == "Totals") {
			continue;

		}
	}
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	//Create font
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 18;
	lf.lfWeight = FW_NORMAL;
	_tcscpy_s(lf.lfFaceName, _T("Segoe UI"));
	m_font.CreateFontIndirect(&lf);

	LOGFONT lf_bold;
	::ZeroMemory(&lf_bold, sizeof(LOGFONT));
	lf_bold.lfHeight = 20; // Font height
	lf_bold.lfWeight = FW_BOLD;
	_tcscpy_s(lf_bold.lfFaceName, _T("Segoe UI"));
	m_font_bold.CreateFontIndirect(&lf_bold);

	LOGFONT lf_italic;
	::ZeroMemory(&lf_italic, sizeof(LOGFONT));
	lf_italic.lfHeight = 18; // Font height
	lf_italic.lfWeight = FW_NORMAL;
	lf_italic.lfItalic = TRUE; // Italic
	_tcscpy_s(lf_italic.lfFaceName, _T("Segoe UI"));
	m_font_italic.CreateFontIndirect(&lf_italic);

	LOGFONT lf_underline;
	::ZeroMemory(&lf_underline, sizeof(LOGFONT));
	lf_underline.lfHeight = 18; // Font height
	lf_underline.lfWeight = FW_NORMAL;
	lf_underline.lfUnderline = TRUE; // Italic
	_tcscpy_s(lf_underline.lfFaceName, _T("Segoe UI"));
	m_font_underline.CreateFontIndirect(&lf_underline);

	LOGFONT lf_font_title;
	::ZeroMemory(&lf_font_title, sizeof(LOGFONT));
	lf_font_title.lfHeight = 18; // Font height
	lf_font_title.lfWeight = FW_BOLD;
	lf_font_title.lfItalic = TRUE; // Underline
	_tcscpy_s(lf_font_title.lfFaceName, _T("Segoe UI"));
	m_font_title.CreateFontIndirect(&lf_font_title);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);


	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Create and setup "Outlook" navigation bar:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndClassView, 250))
		//m_wndCalendar, 
	{
		TRACE0("Failed to create navigation pane\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CTreeCtrl& tree,  int nInitialWidth)
	//CCalendarBar& calendar
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // fail to create
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == nullptr)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	//calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	//pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != nullptr);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}



void CMainFrame::DoDataExchange(CDataExchange* pDX)
{
	CMainFrame::DoDataExchange(pDX); // Call base class method
	DDX_Control(pDX, IDC_TREE1, m_wndClassView);
}



void CMainFrame::OnExit()
{
	// TODO: Add your command handler code here
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


void CMainFrame::OnNew()
{
	// TODO: Add your command handler code here
	ASSERT(AfxGetMainWnd() != NULL);
	AfxGetMainWnd()->SendMessage(STD_FILENEW);
}


void CMainFrame::OnOpenFile()
{
	CFileDialog fileDlg(TRUE, _T("txt"), nullptr, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("alle Formate (*.*) | *.*||"), this);
	if (fileDlg.DoModal() == IDOK) {
		filePath = fileDlg.GetPathName();
		fileName = fileDlg.GetFileName();

		CString ext = PathFindExtension(filePath);
		if (ext.CompareNoCase(_T(".X80")) == 0 || ext.CompareNoCase(_T(".x80")) == 0) {
			m_string_phase = _T("X80 Universelle LV-Daten");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X81")) == 0 || ext.CompareNoCase(_T(".x81")) == 0) {
			m_string_phase = _T("X81 Leistungsbeschreibung");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X82")) == 0 || ext.CompareNoCase(_T(".x82")) == 0) {
			m_string_phase = _T("X82 Kostenanschlag");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X83")) == 0 || ext.CompareNoCase(_T(".x83")) == 0) {
			m_string_phase = _T("X83 Angebotsaufforderung");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X84")) == 0 || ext.CompareNoCase(_T(".x84")) == 0) {
			AfxMessageBox(_T("Hinweis beim Laden von .X84 Datei: \r\n Sie laden eine Angebotsabgabedatei(D84) ohne vorher ein LV geladen zu haben(D81, D82, D83, D86)! \r\n Eine reine Angebotsabgabe enthält nur die Ordnungsnummern und die Preise. \r\n Durch die fehlenden Mengenangaben wird die Darstellung der Daten nicht korrekt sein."));

			m_string_phase = _T("X84 Angebotsabgabe");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X85")) == 0 || ext.CompareNoCase(_T(".x85")) == 0) {
			m_string_phase = _T("X85 Nebenangebot");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X86")) == 0 || ext.CompareNoCase(_T(".x86")) == 0) {
			m_string_phase = _T("X86 Auftragserteilung");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".X94")) == 0 || ext.CompareNoCase(_T(".x94")) == 0) {
			m_string_phase = _T("X94 Handel - Preisangebot");
			m_checkbox_GXML = TRUE;
			m_checkbox_G90 = FALSE;
			m_checkbox_G2000 = FALSE;
		}

//GAEB 2000
		else if (ext.CompareNoCase(_T(".P81")) == 0 || ext.CompareNoCase(_T(".p81")) == 0) {
			m_string_phase = _T("P81 Leistungsbeschreibung");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P82")) == 0 || ext.CompareNoCase(_T(".p82")) == 0) {
			m_string_phase = _T("P82 Kostenanschlag");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P83")) == 0 || ext.CompareNoCase(_T(".p83")) == 0) {
			m_string_phase = _T("P83 Angebotsaufforderung");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P84")) == 0 || ext.CompareNoCase(_T(".p84")) == 0) {
			m_string_phase = _T("P84 Angebotsabgabe");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P85")) == 0 || ext.CompareNoCase(_T(".p85")) == 0) {
			m_string_phase = _T("P85 Nebenangebot");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P86")) == 0 || ext.CompareNoCase(_T(".p86")) == 0) {
			m_string_phase = _T("P86 Auftragserteilung");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".P94")) == 0 || ext.CompareNoCase(_T(".p94")) == 0) {
			m_string_phase = _T("P94 Handel - Preisangebot");
			m_checkbox_G2000 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G90 = FALSE;
		}
//GAEB 90
		else if (ext.CompareNoCase(_T(".D81")) == 0 || ext.CompareNoCase(_T(".d81")) == 0) {
			m_string_phase = _T("D81 Leistungsbeschreibung");
			m_checkbox_G90 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".D82")) == 0 || ext.CompareNoCase(_T(".d82")) == 0) {
			m_string_phase = _T("D82 Kostenanschlag");
			m_checkbox_G90 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".D83")) == 0 || ext.CompareNoCase(_T(".d83")) == 0) {
			m_string_phase = _T("D83 Angebotsaufforderung");
			m_checkbox_G90 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".D84")) == 0 || ext.CompareNoCase(_T(".d84")) == 0) {
			m_string_phase = _T("D84 Angebotsabgabe");
			m_checkbox_G90 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G2000 = FALSE;
		}
		else if (ext.CompareNoCase(_T(".D85")) == 0 || ext.CompareNoCase(_T(".d85")) == 0) {
			m_string_phase = _T("D85 Nebenangebot");
			m_checkbox_G90 = TRUE;
		}
		else if (ext.CompareNoCase(_T(".D86")) == 0 || ext.CompareNoCase(_T(".d86")) == 0) {
			m_string_phase = _T("D86 Auftragserteilung");
			m_checkbox_G90 = TRUE;
			m_checkbox_GXML = FALSE;
			m_checkbox_G2000 = FALSE;
		}

		if (m_checkbox_G90 == TRUE) {
			m_format = _T("90");
		}
		else if (m_checkbox_G2000 == TRUE) {
			m_format = _T("2000");
		}
		else {
			m_format = _T("XML");
		}

		FillClassView(filePath);

		SwitchView(RUNTIME_CLASS(CLVInfosView), m_LVInfosView);
		m_wndClassView.SelectItem(m_wndClassView.GetRootItem());
		m_wndClassView.SetFocus();

		CDocument* pDoc = GetActiveDocument();
		if (pDoc) {
			pDoc->SetTitle(fileName);
		}
	}
}


void CMainFrame::OnExport()
{
	// TODO: Add your command handler code here

	CDialog dlg(IDD_DIALOG_EXPORT, this);
	dlg.DoModal();
}



void CMainFrame::OnUpdateExport(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnDetailsAnsicht()
{
	// TODO: Add your command handler code here
	m_checkbox_Details = !m_checkbox_Details;
	m_checkbox_Tabelle = FALSE;
	
}


void CMainFrame::OnUpdateDetailsAnsicht(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_checkbox_Details ? 1 : 0); 
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnTabelleAnsicht()
{
	// TODO: Add your command handler code here	
	m_checkbox_Tabelle = !m_checkbox_Tabelle;
	m_checkbox_Details = FALSE;
}


void CMainFrame::OnUpdateTabelleAnsicht(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_Tabelle ? 1 : 0);
	pCmdUI->Enable(TRUE);
}



void CMainFrame::OnIndex()
{
	CDialog dlg(IDD_DIALOG_INDEX, this);
	dlg.DoModal();
}

void CMainFrame::OnUpdateIndex(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnInfo()
{
	// TODO: Add your command handler code here
	CDialog dlg(IDD_DIALOG_INFO, this);
	dlg.DoModal();
}

void CMainFrame::OnUpdateInfo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnStrukturAnsicht()
{
	// TODO: Add your command handler code here
	m_checkbox_Struktur = !m_checkbox_Struktur;
}

void CMainFrame::OnUpdateStrukturAnsicht(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here	
	pCmdUI->SetCheck(m_checkbox_Struktur ? 1 : 0); 
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_G2000()
{
	// TODO: Add your command handler code here
	m_checkbox_G2000 = !m_checkbox_G2000;
	m_checkbox_G90 = FALSE;
	m_checkbox_GXML = FALSE;
}

void CMainFrame::OnUpdateCheck_G2000(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G2000 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_GXML()
{
	// TODO: Add your command handler code here
	m_checkbox_GXML = !m_checkbox_GXML;
	m_checkbox_G2000 = FALSE;
	m_checkbox_G90 = FALSE;
}

void CMainFrame::OnUpdateCheck_GXML(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_GXML ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnCheck_G90()
{
	// TODO: Add your command handler code here
	m_checkbox_G90 = !m_checkbox_G90;
	m_checkbox_G2000 = FALSE;
	m_checkbox_GXML  = FALSE;
}

void CMainFrame::OnUpdateCheck_G90(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_G90 ? 1 : 0);
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButton_Speichern()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnButton_SpeichernUnter()
{
	// TODO: Add your command handler code here
}

/*void CMainFrame::Load_GAEB_2000(const CString& filePath)
{
	std::vector<CString> lines;
	if (!ReadFileLinesAnsiToCStringW(filePath, lines))
	{
		AfxMessageBox(_T("Konnte Datei nicht lesen."));
		return;
	}

}*/

CString CMainFrame::Utf8ToString(const char* utf8Str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
	CString result;
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, result.GetBuffer(len), len);
	result.ReleaseBuffer();
	return result;	
	//return CString();
}



void CMainFrame::OnKurztext()
{
	// TODO: Add your command handler code here
	m_checkbox_KT = !m_checkbox_KT;
	m_checkbox_LT = FALSE;
	SwitchView(RUNTIME_CLASS(CLV_MainView), (CView*&)m_MainView);
}

void CMainFrame::OnUpdateKurztext(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_KT ? 1 : 0);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnLangtext()
{
	// TODO: Add your command handler code here
	m_checkbox_LT = !m_checkbox_LT;
	m_checkbox_KT = FALSE;
	SwitchView(RUNTIME_CLASS(CLangtextView), (CView*&)m_LangtextView);
}

void CMainFrame::OnUpdateLangtext(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_checkbox_LT ? 1 : 0);
	pCmdUI->Enable(TRUE);
}


