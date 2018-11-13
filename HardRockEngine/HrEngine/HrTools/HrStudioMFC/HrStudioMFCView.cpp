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

// HrStudioMFCView.cpp : implementation of the CHrStudioMFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HrStudioMFC.h"
#endif

#include "HrStudioMFCDoc.h"
#include "HrStudioMFCView.h"

#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrUIDefine.h"

#include "HrRenderView.h"
#include "HrRenderApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHrStudioMFCView

IMPLEMENT_DYNCREATE(CHrStudioMFCView, CView)

BEGIN_MESSAGE_MAP(CHrStudioMFCView, CView)
	// Standard printing commands
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHrStudioMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHrStudioMFCView construction/destruction

CHrStudioMFCView::CHrStudioMFCView()
{
	// TODO: add construction code here

}

CHrStudioMFCView::~CHrStudioMFCView()
{
}

BOOL CHrStudioMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if (CView::PreCreateWindow(cs))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

// CHrStudioMFCView drawing

void CHrStudioMFCView::OnDraw(CDC* /*pDC*/)
{
	CHrStudioMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


int CHrStudioMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CView::OnCreate(lpCreateStruct);

	return 0;
}

// CHrStudioMFCView printing


void CHrStudioMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHrStudioMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHrStudioMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHrStudioMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHrStudioMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHrStudioMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHrStudioMFCView diagnostics

#ifdef _DEBUG
void CHrStudioMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CHrStudioMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHrStudioMFCDoc* CHrStudioMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHrStudioMFCDoc)));
	return (CHrStudioMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CHrStudioMFCView message handlers
