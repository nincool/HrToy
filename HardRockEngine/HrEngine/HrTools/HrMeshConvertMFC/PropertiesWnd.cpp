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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "HrMeshConvertMFC.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "HrMeshView.h"
#include "HrRenderApp.h"
#include "HrConvertUtil.h"

#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace Hr;

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, CPropertiesWnd::OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPropertiesWnd::SetMainFrame(CMainFrame* pMainFrame)
{
	m_pMainFrame = pMainFrame;
}

void CPropertiesWnd::OnSelectMeshDisplaMaterial(int nMeshIndex, const Hr::HrModelDataInfo::HrMaterialDataInfo& materialInfo)
{
	if (m_strCachedMaterialName == materialInfo.strMaterialName)
	{
		return;
	}
	m_nMeshIndex = nMeshIndex;

	m_pMateiralSetting->SetValue((_variant_t)(Hr::HrStringUtil::Utf8ToWstring(materialInfo.strMaterialName).c_str()));

	m_pMaterialName->SetValue((_variant_t)(Hr::HrStringUtil::Utf8ToWstring(materialInfo.strMaterialName).c_str()));
	COLORREF albedoValue = RGB(materialInfo.v4Albedo[0] * 255, materialInfo.v4Albedo[1] * 255, materialInfo.v4Albedo[2] * 255);
	m_pMaterialAlbedo->SetColor(albedoValue);
	COLORREF emissiveValue = RGB(materialInfo.v4Emissive[0] * 255, materialInfo.v4Emissive[1] * 255, materialInfo.v4Emissive[2] * 255);
	m_pMaterialEmissive->SetColor(emissiveValue);
	auto variantValue = _variant_t(materialInfo.fGlossiness, VT_R8);
	m_pMaterialShininess->SetValue(variantValue);
	auto reflectValue = _variant_t(materialInfo.fReflective, VT_R8);
	m_pMaterialReflective->SetValue(reflectValue);

	for (int i = 0; i < m_arrMaterialTexture.size(); ++i)
	{
		if (!materialInfo.m_arrTexNames[i].empty())
		{
			std::wstring strTextureName = Hr::HrStringUtil::Utf8ToWstring(materialInfo.m_arrTexNames[i]);
			m_arrMaterialTexture[i]->SetValue((_variant_t)strTextureName.c_str());
		}
		else
		{
			m_arrMaterialTexture[i]->SetValue((_variant_t)(_T("")));
		}
	}
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString(_T("Application"));
	m_wndObjectCombo.AddString(_T("Properties Window"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
	std::cout << "OnProperties1" << std::endl;
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: Add your command handler code here
	std::cout << "OnProperties2" << std::endl;
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_pHrSettingGroup = new CMFCPropertyGridProperty(_T("HrSetting"));
	{
		{
			//static const TCHAR szFilter[] = _T("Texture Files(*.png)|*.png|All Files(*.*)|*.*||");
			//m_pHrSettingGroup->AddSubItem(new CMFCPropertyGridFileProperty(_T("Texture"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the texture")));
			auto pUnitScale = new CMFCPropertyGridProperty(_T("UnitScale"), (_variant_t)1.0f, _T("Specifies the window's height"));
			m_pHrSettingGroup->AddSubItem(pUnitScale);
		}
		{
			static const TCHAR szFilter[] = _T("Material Files(*.material)|*.material|All Files(*.*)|*.*||");
			m_pMateiralSetting = new CMFCPropertyGridProperty(_T("Material"), _T("Default"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
			m_pMateiralSetting->AddOption(_T("Default"));
			m_pMateiralSetting->AddOption(_T("Standard"));
			m_pMateiralSetting->AddOption(_T("Thin"));
			m_pMateiralSetting->AddOption(_T("Resizable"));
			m_pMateiralSetting->AddOption(_T("Dialog Frame"));
			m_pMateiralSetting->AllowEdit(FALSE);
			m_pHrSettingGroup->AddSubItem(m_pMateiralSetting);
		}
	}
	m_wndPropList.AddProperty(m_pHrSettingGroup);

	m_pMaterialGroup = new CMFCPropertyGridProperty(_T("Material"));
	{
		m_pMaterialName = new CMFCPropertyGridProperty(_T("Name"), (_variant_t)_T(""), _T("Specifies the text that will be displayed in the window's title bar"));
		m_pMaterialGroup->AddSubItem(m_pMaterialName);
		
		m_pMaterialAlbedo = new CMFCPropertyGridColorProperty(_T("Albedo"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
		m_pMaterialAlbedo->EnableOtherButton(_T("Other..."));
		m_pMaterialAlbedo->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
		m_pMaterialGroup->AddSubItem(m_pMaterialAlbedo);

		m_pMaterialEmissive = new CMFCPropertyGridColorProperty(_T("Emissive"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
		m_pMaterialEmissive->EnableOtherButton(_T("Other..."));
		m_pMaterialEmissive->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
		m_pMaterialGroup->AddSubItem(m_pMaterialEmissive);

		auto variantValue = _variant_t(3.0f, VT_R8);
		m_pMaterialShininess = new CMFCPropertyGridProperty(_T("Glossiness"), variantValue, _T("Specifies the window's width"));
		//m_pMaterialShininess->EnableSpinControl(TRUE, 0, 20);
		m_pMaterialGroup->AddSubItem(m_pMaterialShininess);

		variantValue = _variant_t(1.0f, VT_R8);
		m_pMaterialReflective = new CMFCPropertyGridProperty(_T("Reflective"), variantValue, _T("Specifies the window's width"));
		m_pMaterialGroup->AddSubItem(m_pMaterialReflective);

		std::array<std::wstring, HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS> arrTextureTypeName;
		arrTextureTypeName[0] = _T("TEX_ALBEDO");
		arrTextureTypeName[1] = _T("TEX_METALNESS");
		arrTextureTypeName[2] = _T("TEX_GLOSSINESS");
		arrTextureTypeName[3] = _T("TEX_EMISSIVE");
		arrTextureTypeName[4] = _T("TEX_NORMAL");
		arrTextureTypeName[5] = _T("TEX_HEIGHT");
		arrTextureTypeName[6] = _T("TEX_BUMP");
		for (size_t i = 0; i < arrTextureTypeName.size(); ++i)
		{
			static const TCHAR szFilter[] = _T("png Files(*.png)|*.png|All Files(*.*)|*.*||");
			m_arrMaterialTexture[i] = new CMFCPropertyGridFileProperty(arrTextureTypeName[i].c_str(), TRUE, _T(""), _T("png"), 0, szFilter, _T("Specifies the window icon"));
			//m_pMaterialGroup->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon")));
			m_pMaterialGroup->AddSubItem(m_arrMaterialTexture[i]);
		}
	}
	m_wndPropList.AddProperty(m_pMaterialGroup);

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Appearance"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t) false, _T("Specifies the window's font will be non-bold and controls will have a 3D border")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t) _T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t) 250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Folder"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t) _T("Value 1"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t) _T("Value 2"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t) _T("Value 3"), _T("This is a description")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

LRESULT CPropertiesWnd::OnPropertyChanged(__in WPARAM wParam, __in LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	//is the property ctrl
	if ((long)wParam == 2)
	{

	}

	int pID = pProp->GetData();
	CString str = pProp->GetName();
	if (str == _T("Material"))
	{
		COleVariant var = pProp->GetValue();
		std::wstring strValue = var.bstrVal;
		if (strValue == _T("Standard"))
		{
			std::string strMaterialName = HrStringUtil::WstringToUtf8(var.bstrVal);
			m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->ChangeMaterial(m_nMeshIndex, strMaterialName);
			auto& modelDataInfo = m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->GetModelDataInfo();
			OnSelectMeshDisplaMaterial(m_nMeshIndex, modelDataInfo.vecMaterialDataInfo[m_nMeshIndex]);
		}
	}
	else if (str == _T("Glossiness"))
	{
		COleVariant var = pProp->GetValue();
		float fGlossiness = var.dblVal;
		m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->SetMaterialGlossiness(m_nMeshIndex, fGlossiness);
	}
	else if (str == _T("Reflective"))
	{
		COleVariant var = pProp->GetValue();
		float fReflective = var.dblVal;
		m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->SetMaterialReflective(m_nMeshIndex, fReflective);
	}
	else if (str == _T("TEX_ALBEDO"))
	{
		COleVariant var = pProp->GetValue();
		std::string strTexPath = HrStringUtil::WstringToUtf8(var.bstrVal);
		m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->SetMaterialTexture(m_nMeshIndex, Hr::HrModelDataInfo::HrMaterialDataInfo::TS_ALBEDO, strTexPath);
		auto& modelDataInfo = m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->GetModelDataInfo();
		OnSelectMeshDisplaMaterial(m_nMeshIndex, modelDataInfo.vecMaterialDataInfo[m_nMeshIndex]);
	}
	else if (str == _T("TEX_NORMAL"))
	{
		COleVariant var = pProp->GetValue();
		std::string strTexPath = HrStringUtil::WstringToUtf8(var.bstrVal);
		m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->SetMaterialTexture(m_nMeshIndex, Hr::HrModelDataInfo::HrMaterialDataInfo::TS_NORMAL, strTexPath);
		auto& modelDataInfo = m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->GetModelDataInfo();
		OnSelectMeshDisplaMaterial(m_nMeshIndex, modelDataInfo.vecMaterialDataInfo[m_nMeshIndex]);
	}
	else if (str == _T("UnitScale"))
	{
		COleVariant var = pProp->GetValue();
		float fUnitScale = var.fltVal;
		m_pMainFrame->GetRenderViewDlg()->GetRenderApp()->GetEditorScene()->GetConvertUtil()->SetUnitScale(fUnitScale);
	}

	return 0;
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}
