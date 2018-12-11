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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "HrRenderViewDlg.h"
#include "HrMeshView.h"
#include "HrPrefabModelView.h"

#include <memory>
namespace Hr
{
	class HrRenderApp;
}


class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CPropertiesWnd& GetPropertiesWnd()
	{
		return m_wndProperties;
	}

	std::shared_ptr<HrRenderViewDlg> GetRenderViewDlg()
	{
		return m_pRenderViewDlg;
	}
protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
	HrMeshView        m_wndMeshView;
	HrPrefabModelView m_wndPrefabModelView;
	
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	//afx_msg void OnFilePrintPreview();
	//afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	int m_nLeft;
	int m_nTop;

	int m_nWidth;
	int m_nHeight;

	std::string m_strCurrentOpenFile;

	std::shared_ptr<HrRenderViewDlg> m_pRenderViewDlg;
public:
	afx_msg void OnViewStatusBar();
	afx_msg void OnButtonSavePrefabText();
	afx_msg void OnButtonOpenMesh();
	afx_msg void OnBtnHrSavePrefabBinary();
	afx_msg void OnBtnHrOpenPrefab();
};


