#ifndef _HR_D3D11UTILITY_H_
#define _HR_D3D11UTILITY_H_

#include "HrD3D11RendererPrerequisites.h"

namespace Hr
{
	class HrD3D11Adapter
	{
	public:
		HrD3D11Adapter(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter);
		~HrD3D11Adapter();

		std::string GetDriverDescription() const;
		IHRDXGIAdapter* GetDeviceAdapter() const
		{
			return m_pDXGIAdapter;
		}
	private:
		unsigned int m_nApdapterNumber;
		DXGI_ADAPTER_DESC1 m_AdapterIdentifier;

		IHRDXGIAdapter* m_pDXGIAdapter;
	};

	class HrD3D11Utility
	{
	public:
		HrD3D11Utility();
		~HrD3D11Utility();

	public:
		bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);

		bool CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);
		bool CreateDXGIFactory();
		bool CreateDXDevice(HrD3D11Adapter* pD3DAdapter = nullptr);

		bool EnumerateAdapter();
		//Check Mutisamplelevels
		void BuildMutisampleQualityList();
		HrD3D11Adapter* GetDefaultAdapter();

	protected:
		HR_INSTANCE(HrD3D11Utility);
	protected:
		HR_SYNTHESIZE_READONLY(HWND, m_hWnd, hWnd);
		std::vector<HrD3D11Adapter*> m_vecAdapters;
	};
}

#endif

