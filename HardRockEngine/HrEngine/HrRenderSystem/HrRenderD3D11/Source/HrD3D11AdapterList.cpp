#include "HrD3D11AdapterList.h"
#include "HrD3D11Adapter.h"

using namespace Hr;

HrD3D11AdapterList::HrD3D11AdapterList()
{
}


HrD3D11AdapterList::~HrD3D11AdapterList()
{
	Release();
}

void HrD3D11AdapterList::AddOneAdapter(HrD3D11Adapter* pAdapter)
{
	m_vecAdapters.push_back(pAdapter);
}

void HrD3D11AdapterList::Release()
{
	for (size_t i = 0; i < m_vecAdapters.size(); ++i)
	{
		m_vecAdapters[i]->Release();
		SAFE_DELETE(m_vecAdapters[i]);
	}
	m_vecAdapters.clear();
}
