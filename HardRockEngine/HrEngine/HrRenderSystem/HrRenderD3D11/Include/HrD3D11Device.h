#ifndef _HR_D3D11DEVICE_H_
#define _HR_D3D11DEVICE_H_

#include "HrD3D11RenderPrerequisites.h"

namespace Hr
{
	class HrD3D11EnumOutputInfo
	{
	public:
		HrD3D11EnumOutputInfo()
		{
			m_pOutput = nullptr;
		}

		void Release()
		{
			SAFE_RELEASE(m_pOutput);
		}

		IDXGIOutput* m_pOutput;
		DXGI_OUTPUT_DESC desc;

		std::vector<DXGI_MODE_DESC> m_vecPlayModeList;
	};

	class HrD3D11Adapter
	{
	public:
		HrD3D11Adapter(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter);
		~HrD3D11Adapter();

		HrString GetDriverDescription() const;
		IHRDXGIAdapter* GetDeviceAdapter() const
		{
			return m_pDXGIAdapter;
		}

		void Release();
	public:
		std::vector<HrD3D11EnumOutputInfo*> m_vecEnumOutputInfo;
	private:
		unsigned int m_nApdapterNumber;
		DXGI_ADAPTER_DESC1 m_AdapterIdentifier;

		IHRDXGIAdapter* m_pDXGIAdapter;
	};

	class HrD3D11Device : public RenderSysAllocatedObject
	{
	public:
		HrD3D11Device();
		~HrD3D11Device();
		
		HR_INSTANCE(HrD3D11Device);
	public:
		void SetDevice(IHRD3D11Device* pDevice);
		void Release();

		HrD3D11Adapter* GetCurrentAdapter();
	public:
		// List of valid sampling counts (multisampling)
		std::vector<UINT> m_vecMultiSampleCountList;
		// List of number of quality levels for each multisample count
		std::vector<UINT> m_vecMultiSampleQualityList;

		std::vector<HrD3D11Adapter*> m_vecAdapters;

		DXGI_HR_SWAP_CHAIN_DESC m_swapChainDesc;
	protected:
		HR_SYNTHESIZE(IHRDXGIFactory*, m_pD3D11DXGIFactory, DXGIFactory);
		HrD3D11Adapter* m_pAdapter;

		HR_SYNTHESIZE(DXGI_FORMAT, m_format, Format);
		HR_SYNTHESIZE_READONLY(IHRD3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE_READONLY(IHRD3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);

		HR_SYNTHESIZE(IHRDXGISwapChain*, m_pSwapChain, SwapChain);
		HR_SYNTHESIZE(ID3D11RenderTargetView*, m_pRenderTargetView, RenderTargetView);
		HR_SYNTHESIZE(ID3D11Texture2D*, m_pDepthStencil, DepthStencil);
		HR_SYNTHESIZE(ID3D11DepthStencilView*, m_pDepthStencilView, DepthStencilView);

		HR_SYNTHESIZE(uint32, m_nWidth, Width);
		HR_SYNTHESIZE(uint32, m_nHeight, Height);
	};
}


#endif

