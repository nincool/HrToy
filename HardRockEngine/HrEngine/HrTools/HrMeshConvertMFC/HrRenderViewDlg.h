#pragma once


// HrRenderViewDlg dialog
#include <memory>
#include <string>

namespace Hr
{
	class HrRenderApp;
}
class HrMeshView;

class HrRenderViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HrRenderViewDlg)

public:
	HrRenderViewDlg(HrMeshView* pMeshView = nullptr, CWnd* pParent = NULL);   // standard constructor
	virtual ~HrRenderViewDlg();

	std::shared_ptr<Hr::HrRenderApp> GetRenderApp()
	{
		return m_pRenderApp;
	}
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_RENDERVIEW_DLG
};
#endif
	virtual BOOL OnInitDialog() override;
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;

	void OnOpenFile(const std::string& strFile);
	void OnSaveFile(const std::string& strFile);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	std::shared_ptr<Hr::HrRenderApp> m_pRenderApp;

	HrMeshView* m_pMeshView;
};
