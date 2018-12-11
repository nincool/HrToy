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
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Scene/HrSceneNode.h"

class CMainFrame;

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

	void SetMainFrame(CMainFrame* pMainFrame);

	//void OnSelectMeshDisplaMaterial(int nMeshIndex, const Hr::HrModelDataInfo::HrMaterialDataInfo& materialInfo);
	void OnSelectModel(const Hr::HrModelDataInfo* pModelDataInfo, Hr::HrSceneNode* pSceneNode);
// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	//int m_nMeshIndex = 0;

	CMFCPropertyGridProperty* m_pHrSettingGroup;
	
	CMFCPropertyGridProperty* m_pPosX;
	CMFCPropertyGridProperty* m_pPosY;
	CMFCPropertyGridProperty* m_pPosZ;

	CMFCPropertyGridProperty* m_pRotateX;
	CMFCPropertyGridProperty* m_pRotateY;
	CMFCPropertyGridProperty* m_pRotateZ;

	CMFCPropertyGridProperty* m_pScaleX;
	CMFCPropertyGridProperty* m_pScaleY;
	CMFCPropertyGridProperty* m_pScaleZ;
	
	std::string m_strCachedMaterialName;
	CMFCPropertyGridProperty* m_pMaterialGroup;
	CMFCPropertyGridProperty* m_pMaterialName;
	CMFCPropertyGridColorProperty* m_pMaterialAlbedo;
	CMFCPropertyGridColorProperty* m_pMaterialEmissive;
	CMFCPropertyGridProperty* m_pMaterialShininess;
	CMFCPropertyGridProperty* m_pMaterialReflective;

	std::array<CMFCPropertyGridProperty*, Hr::HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS> m_arrMaterialTexture;

	CMainFrame* m_pMainFrame;

	const Hr::HrModelDataInfo* m_pModelData;
	Hr::HrSceneNode* m_pSceneNode;
// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;
};

