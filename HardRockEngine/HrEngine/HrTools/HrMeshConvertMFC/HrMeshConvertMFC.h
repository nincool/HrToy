// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// HrMeshConvertMFC.h : main header file for the HrMeshConvertMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHrMeshConvertMFCApp:
// See HrMeshConvertMFC.cpp for the implementation of this class
//

class CHrMeshConvertMFCApp : public CWinAppEx
{
public:
	CHrMeshConvertMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void InitConsoleWindow();

	virtual BOOL OnIdle(LONG lCount) override;
// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHrMeshConvertMFCApp theApp;
