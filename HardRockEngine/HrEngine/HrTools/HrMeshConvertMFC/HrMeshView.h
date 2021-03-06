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

#pragma once

#include "ViewTree.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"

#include <unordered_map>

class CMainFrame;
namespace Hr
{
	class HrManager;
}

class CMeshToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class HrMeshView : public CDockablePane
{
public:
	HrMeshView();
	virtual ~HrMeshView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	void FillClassView(const Hr::HrModelDataInfo& modelInfo);

	void SetManager(Hr::HrManager* pManager);
protected:
	CMeshToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;

	Hr::HrManager* m_pManager;

	std::unordered_map<HTREEITEM, std::string> m_mapItemsInfo;

	// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void OnLBtnDown(HTREEITEM hitItem);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);


	DECLARE_MESSAGE_MAP()

};

