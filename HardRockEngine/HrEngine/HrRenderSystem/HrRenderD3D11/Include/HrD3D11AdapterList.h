#ifndef _HR_D3D11ADAPTERLIST_H_
#define _HR_D3D11ADAPTERLIST_H_

#include "HrD3D11RenderPrerequisite.h"

namespace Hr
{
	class HrD3D11Adapter;

	class HrD3D11AdapterList
	{
	public:
		HrD3D11AdapterList();
		~HrD3D11AdapterList();

		void Release();

		void AddOneAdapter(HrD3D11Adapter* pAdapter);
		
	public:
		std::vector<HrD3D11Adapter*> m_vecAdapters;
	};
}



#endif

