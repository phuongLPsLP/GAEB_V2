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

// GAEB_V2.h : main header file for the GAEB_V2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <afxstr.h>  // For CStringArray
#include <afxtempl.h> // For MFC containers like CArray, CStringArray


// CGAEBV2App:
// See GAEB_V2.cpp for the implementation of this class
//

class CGAEBV2App : public CWinAppEx
{
public:
	CGAEBV2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	CStringArray m_einheitList;
	CStringArray m_PosArtList;
	CStringArray m_PosGruppeList;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void Init_List();
	
	DECLARE_MESSAGE_MAP()
};

extern CGAEBV2App theApp;
