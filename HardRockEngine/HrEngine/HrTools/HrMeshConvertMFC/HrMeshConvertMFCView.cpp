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

// HrMeshConvertMFCView.cpp : implementation of the CHrMeshConvertMFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HrMeshConvertMFC.h"
#endif

#include "HrMeshConvertMFCDoc.h"
#include "HrMeshConvertMFCView.h"

#include "HrCore/Include/Kernel/HrDirector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHrMeshConvertMFCView

IMPLEMENT_DYNCREATE(CHrMeshConvertMFCView, CView)

BEGIN_MESSAGE_MAP(CHrMeshConvertMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHrMeshConvertMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHrMeshConvertMFCView construction/destruction

CHrMeshConvertMFCView::CHrMeshConvertMFCView()
{
	// TODO: add construction code here

}

CHrMeshConvertMFCView::~CHrMeshConvertMFCView()
{
}

BOOL CHrMeshConvertMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if (CView::PreCreateWindow(cs))
	{
		//HWND hWnd = GetSafeHwnd();
		//if (!Hr::HrDirector::Instance()->Init(hWnd))
		//{
		//	throw std::runtime_error("error");

		//	return FALSE;
		//}

		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

// CHrMeshConvertMFCView drawing

void CHrMeshConvertMFCView::OnDraw(CDC* /*pDC*/)
{
	CHrMeshConvertMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHrMeshConvertMFCView printing


void CHrMeshConvertMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHrMeshConvertMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHrMeshConvertMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHrMeshConvertMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHrMeshConvertMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHrMeshConvertMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHrMeshConvertMFCView diagnostics

#ifdef _DEBUG
void CHrMeshConvertMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CHrMeshConvertMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHrMeshConvertMFCDoc* CHrMeshConvertMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHrMeshConvertMFCDoc)));
	return (CHrMeshConvertMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CHrMeshConvertMFCView message handlers
