// HrRenderViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HrMeshConvertMFC.h"
#include "HrRenderViewDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "HrUIDefine.h"
#include "HrRenderApp.h"
#include "HrMeshView.h"
// HrRenderViewDlg dialog

IMPLEMENT_DYNAMIC(HrRenderViewDlg, CDialogEx)

BEGIN_MESSAGE_MAP(HrRenderViewDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

HrRenderViewDlg::HrRenderViewDlg(HrMeshView* pMeshView, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENDERVIEW_DLG, pParent)
{
	m_pMeshView = pMeshView;
}

HrRenderViewDlg::~HrRenderViewDlg()
{
}

BOOL HrRenderViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rtPos(Hr::HrUIDefine::m_s_nRenderFrameLeft
		, Hr::HrUIDefine::m_s_nRenderFrameTop
		, Hr::HrUIDefine::m_s_nRenderFrameWidth + Hr::HrUIDefine::m_s_nRenderFrameLeft
		, Hr::HrUIDefine::m_s_nRenderFrameHeight + Hr::HrUIDefine::m_s_nRenderFrameTop);

	MoveWindow(rtPos);

	HWND hWnd = GetSafeHwnd();
	m_pRenderApp = std::make_shared<Hr::HrRenderApp>(hWnd);
	m_pRenderApp->Run();

	return true;
}

BOOL HrRenderViewDlg::PreTranslateMessage(MSG* pMsg)
{
	bool rt = CDialogEx::PreTranslateMessage(pMsg);

	m_pRenderApp->RenderOnce();

	return rt;
}

void HrRenderViewDlg::OnOpenFile(const std::string& strFile)
{
	auto& modelDataInfo = m_pRenderApp->LoadOriginalMeshData(strFile);
	m_pMeshView->FillClassView(modelDataInfo);
	//todo
	auto pConvertUtil = m_pRenderApp->GetEditorScene()->GetConvertUtil();
}

void HrRenderViewDlg::OnSaveFile(const std::string& strFile)
{
	m_pRenderApp->SaveConvertMeshData(strFile);
}

void HrRenderViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void HrRenderViewDlg::OnPaint()
{
	CDialogEx::OnPaint();
}

void HrRenderViewDlg::OnMouseMove(UINT nHitTest, CPoint point)
{
	m_pRenderApp->OnMouseMove(point.x, point.y);
}

void HrRenderViewDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_pRenderApp->OnRMouseButtonDown(point.x, point.y);
}

void HrRenderViewDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_pRenderApp->OnRMouseButtonUp(point.x, point.y);
}

BOOL HrRenderViewDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_pRenderApp->OnMouseWheel(static_cast<float>(zDelta));

	return true;
}




// HrRenderViewDlg message handlers
