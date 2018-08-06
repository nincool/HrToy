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
