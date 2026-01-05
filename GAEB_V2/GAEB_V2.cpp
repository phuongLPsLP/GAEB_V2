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

// GAEB_V2.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GAEB_V2.h"
#include "MainFrm.h"

#include "GAEB_V2Doc.h"
#include "GAEB_V2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGAEBV2App

BEGIN_MESSAGE_MAP(CGAEBV2App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGAEBV2App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGAEBV2App construction

CGAEBV2App::CGAEBV2App() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif


	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GAEBV2.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

// The one and only CGAEBV2App object

CGAEBV2App theApp;


// CGAEBV2App initialization

BOOL CGAEBV2App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	Init_List();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	SetThreadUILanguage(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN));
	SetThreadLocale(MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT));

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	theApp.CleanState();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGAEBV2Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGAEBV2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGAEBV2App::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CGAEBV2App message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CGAEBV2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CGAEBV2App::Init_List()
{
	//List Einheit
	m_einheitList.Add(_T("m")); // Meter
	m_einheitList.Add(_T("Stk")); // Stück
	m_einheitList.Add(_T("m²")); // Quadratmeter
	m_einheitList.Add(_T("m³")); // Kubikmeter
	m_einheitList.Add(_T("psch")); // Pauschal
	m_einheitList.Add(_T("pack")); // Packung
	m_einheitList.Add(_T("kg")); // Kilogramm
	m_einheitList.Add(_T("t")); // Tonne
	m_einheitList.Add(_T("Std")); // Stunde
	m_einheitList.Add(_T("Min")); // Minute
	m_einheitList.Add(_T("lfm")); // Laufmeter

	//List Positionart
	m_PosArtList.Add(_T("H - Hinweistext"));
	m_PosArtList.Add(_T("A - Abschnitt"));
	m_PosArtList.Add(_T("B - Bezugsposition"));
	m_PosArtList.Add(_T("N - Normalposition"));
	m_PosArtList.Add(_T("E - Bedarfsposition ohne GP"));
	m_PosArtList.Add(_T("M - Bedarsfposition mit GP"));
	m_PosArtList.Add(_T("G - Grundposition"));
	m_PosArtList.Add(_T("W - Wahlposition"));
	m_PosArtList.Add(_T("P - Pauschalposition"));
	m_PosArtList.Add(_T("G - Grundposition"));
	m_PosArtList.Add(_T("S - Stundenlohnarbeiten"));
	m_PosArtList.Add(_T("K - Kombiposition"));
	m_PosArtList.Add(_T("Z - Zuschlagsposition"));
	m_PosArtList.Add(_T("AL - Alternativposition"));
	m_PosArtList.Add(_T("L - Leitbeschreibung"));
	m_PosArtList.Add(_T("AB - Ausführungsbeschreibung"));


	//List Position Gruppe
	m_PosGruppeList.Add(_T("NG - Normalgruppe"));
	m_PosGruppeList.Add(_T("LO - Los"));
	m_PosGruppeList.Add(_T("GG - Grundgruppe"));
	m_PosGruppeList.Add(_T("AG - Alternativgruppe"));

}



// CGAEBV2App customization load/save methods

void CGAEBV2App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGAEBV2App::LoadCustomState()
{
}

void CGAEBV2App::SaveCustomState()
{
}

// CGAEBV2App message handlers




