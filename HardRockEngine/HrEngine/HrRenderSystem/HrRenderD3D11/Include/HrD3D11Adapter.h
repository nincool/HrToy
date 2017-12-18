#ifndef _HR_D3D11ADAPTER_H_
#define _HR_D3D11ADAPTER_H_

#include "HrD3D11RenderPrerequisite.h"

struct IDXGIAdapter1;

namespace Hr
{
	class HrD3D11VideoMode;

	class HrD3D11Adapter
	{
	public:
		HrD3D11Adapter(uint32 nAdapterIndex, IDXGIAdapter1* pAdapter);
		~HrD3D11Adapter();

		void Release();

		void EnumerateModeList();

		uint32 GetAdapterIndex()
		{
			return m_nAdapterIndex;
		}

		IDXGIAdapter1* GetAdapter()
		{
			return m_pAdapter;
		}
	private:
		uint32 m_nAdapterIndex;
		IDXGIAdapter1* m_pAdapter;

		//显示模式列表
		std::vector<HrD3D11VideoMode> m_vecModes;
	};
}

#endif

