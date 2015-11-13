#ifndef _HR_D3DDRIVERLIST_H_
#define _HR_D3DDRIVERLIST_H_

#include "HrD3D11RendererPrerequisites.h"
#include <vector>

namespace Hr
{
	class HrD3D11Driver;


	class HrD3D11DriverList
	{
	public:
		HrD3D11DriverList(IHRDXGIFactory* pDXGIFactory);
		~HrD3D11DriverList();


		HrD3D11Driver* GetDefaultDriver();
	private:
		bool Enumerate(IHRDXGIFactory* pDXGIFactory);

	private:
		std::vector<HrD3D11Driver*> m_vecDrivers;


	};



}


#endif

