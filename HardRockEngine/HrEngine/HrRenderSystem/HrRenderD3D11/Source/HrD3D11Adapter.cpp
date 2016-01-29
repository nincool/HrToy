#include "HrD3D11Adapter.h"
#include "HrD3D11Device.h"
#include <algorithm>
#include "HrD3D11VideoMode.h"


using namespace Hr;

HrD3D11Adapter::HrD3D11Adapter(uint32 nAdapterIndex, IDXGIAdapter1* pAdapter)
{
	m_nAdapterIndex = nAdapterIndex;
	m_pAdapter = pAdapter;
}


HrD3D11Adapter::~HrD3D11Adapter()
{
}

void HrD3D11Adapter::EnumerateModeList()
{
	std::vector<DXGI_FORMAT> formats;
	formats.push_back(DXGI_FORMAT_R8G8B8A8_UNORM);
	formats.push_back(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);
	formats.push_back(DXGI_FORMAT_B8G8R8A8_UNORM);
	formats.push_back(DXGI_FORMAT_B8G8R8A8_UNORM_SRGB);
	formats.push_back(DXGI_FORMAT_R10G10B10A2_UNORM);

	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (m_pAdapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		if (output != nullptr)
		{
			for (auto const & format : formats)
			{
				UINT num = 0;
				output->GetDisplayModeList(format, DXGI_ENUM_MODES_SCALING, &num, 0);
				if (num > 0)
				{
					std::vector<DXGI_MODE_DESC> mode_descs(num);
					output->GetDisplayModeList(format, DXGI_ENUM_MODES_SCALING, &num, &mode_descs[0]);

					for (auto const & mode_desc : mode_descs)
					{
						HrD3D11VideoMode const video_mode(mode_desc.Width, mode_desc.Height,
							mode_desc.Format);

						// 如果找到一个新模式, 加入模式列表
						if (std::find(m_vecModes.begin(), m_vecModes.end(), video_mode) == m_vecModes.end())
						{
							m_vecModes.push_back(video_mode);
						}
					}
				}
			}

			output->Release();
			output = nullptr;
		}

		++i;
	}

	std::sort(m_vecModes.begin(), m_vecModes.end());
}

void HrD3D11Adapter::Release()
{
	if (m_pAdapter)
	{
		m_pAdapter->Release();
	}
}
