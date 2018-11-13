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
#include "ViewTree.h"
#include "HrMeshView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
{
	WM_NOTIFY + WM_REFLECT_BASE, (WORD)(int)NM_CLICK, 0, 0, AfxSigNotify_v, \
		(AFX_PMSG) \
		(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(NMHDR*, LRESULT*)> \
		(&CViewTree::OnClkTree))
},
END_MESSAGE_MAP()

CViewTree::CViewTree()
{
	m_pListener = nullptr;
}

CViewTree::~CViewTree()
{
}

void CViewTree::OnClkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint point;
	GetCursorPos(&point);//获得鼠标点击的位置
	ScreenToClient(&point);//转化为客户坐标
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem = HitTest(point, &uFlags);//获得当前点击节点的ITEM

	if (m_pListener)
		m_pListener->OnViewTreeLBtnDown(CurrentItem);
}

void CViewTree::SetListener(HrViewTreeListener* pListener)
{
	m_pListener = pListener;
}

/////////////////////////////////////////////////////////////////////////////
// CViewTree message handlers

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}
