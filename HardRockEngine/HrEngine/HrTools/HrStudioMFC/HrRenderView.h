#pragma once


// HrRenderView dialog
#include <memory>
namespace Hr
{
	class HrRenderApp;
}

class HrRenderView : public CDialogEx
{
	DECLARE_DYNAMIC(HrRenderView)

public:
	HrRenderView(CWnd* pParent = NULL);   // standard constructor
	virtual ~HrRenderView();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDERVIEW };
#endif

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int m_nLeft;
	int m_nTop;

	int m_nWidth;
	int m_nHeight;

	std::shared_ptr<Hr::HrRenderApp> m_pRenderApp;
};

//class CHrStudioMFCView : public CView
//{
//protected: // create from serialization only
//	CHrStudioMFCView();
//	DECLARE_DYNCREATE(CHrStudioMFCView)
//
//	// Attributes
//public:
//	CHrStudioMFCDoc* GetDocument() const;
//
//	// Operations
//public:
//
//	// Overrides
//public:
//	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//protected:
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
//
//	// Implementation
//public:
//	virtual ~CHrStudioMFCView();
//#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//
//	HrRenderView* m_pRenderViewDlg;
//
//protected:
//
//	// Generated message map functions
//protected:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
//	DECLARE_MESSAGE_MAP()
//};
//
//#ifndef _DEBUG  // debug version in HrStudioMFCView.cpp
//inline CHrStudioMFCDoc* CHrStudioMFCView::GetDocument() const
//{
//	return reinterpret_cast<CHrStudioMFCDoc*>(m_pDocument);
//}
//#endif

