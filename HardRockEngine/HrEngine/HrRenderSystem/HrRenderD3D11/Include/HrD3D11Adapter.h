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
	private:
		HR_SYNTHESIZE_READONLY(uint32, m_nAdapterIndex, AdapterIndex);
		HR_SYNTHESIZE_READONLY(IDXGIAdapter1*, m_pAdapter, Adapter);

		//��ʾģʽ�б�
		std::vector<HrD3D11VideoMode> m_vecModes;
	};
}

#endif

