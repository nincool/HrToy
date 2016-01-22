#ifndef _HR_D3D11UTILITY_H_
#define _HR_D3D11UTILITY_H_

#include "HrD3D11RenderPrerequisite.h"

namespace Hr
{
	class HrD3D11Adapter;

	class HrD3D11Utility : public RenderSysAllocatedObject
	{
	public:
		HrD3D11Utility();
		~HrD3D11Utility();

	public:
		bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);

		bool CreateD3DRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);
		bool CreateD3DDXGIFactory();
		bool CreateD3DDXDevice(HrD3D11Adapter* pD3DAdapter = nullptr);

		bool D3DEnumerate();
		bool D3D3EnumerateAdapter();
		void D3DEnumerateModeList();
		//Check Mutisamplelevels
		void BuildMutisampleQualityList();

		bool CreateD3DSwapChain();
		bool CreateD3DViews();
	protected:
		HR_INSTANCE(HrD3D11Utility);
	protected:
		HR_SYNTHESIZE_READONLY(HWND, m_hWnd, hWnd);

	};
}

#endif

