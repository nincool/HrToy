// HrRenderView.cpp : implementation file
//

#include "stdafx.h"
#include "HrStudioMFC.h"
#include "HrRenderView.h"
#include "afxdialogex.h"

#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "HrRenderApp.h"
#include "HrUIDefine.h"

using namespace Hr;

// HrRenderView dialog

IMPLEMENT_DYNAMIC(HrRenderView, CDialogEx)

HrRenderView::HrRenderView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FORMVIEW, pParent)
{
}

HrRenderView::~HrRenderView()
{
}

void HrRenderView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HrRenderView, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// HrRenderView message handlers

int HrRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rvPos(Hr::HrUIDefine::m_s_nRenderFrameLeft
		, Hr::HrUIDefine::m_s_nRenderFrameTop
		, Hr::HrUIDefine::m_s_nRenderFrameWidth + Hr::HrUIDefine::m_s_nRenderFrameLeft
		, Hr::HrUIDefine::m_s_nRenderFrameHeight + Hr::HrUIDefine::m_s_nRenderFrameTop);
	MoveWindow(rvPos);

	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	m_nLeft = rc.left;
	m_nTop = rc.top;
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;

	//HWND hWnd = GetSafeHwnd();
	//m_pRenderApp = std::make_shared<HrRenderApp>(hWnd);
	//m_pRenderApp->Run();

	return TRUE;
}

void HrRenderView::OnPaint()
{
	//m_pRenderApp->RenderOnce();
	UpdateWindow();
}

void HrRenderView::OnMouseMove(UINT nHitTest, CPoint point)
{
	//m_pRenderApp->OnMouseMove(point.x, point.y);
}

void HrRenderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//m_pRenderApp->OnRMouseButtonDown(point.x, point.y);
}

void HrRenderView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//m_pRenderApp->OnRMouseButtonUp(point.x, point.y);
}

BOOL HrRenderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//m_pRenderApp->OnMouseWheel(static_cast<float>(zDelta));

	return true;
}
