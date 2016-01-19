/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_RENDERD3D11PREREQUISITES_H_
#define _HR_RENDERD3D11PREREQUISITES_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include "HrCommon/Include/HrPrerequisites.h"
#include "HrMain/Include/HrLog.h"
#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

typedef ID3D11Device            IHRD3D11Device;
typedef ID3D11DeviceContext     IHRD3D11DeviceContext;
typedef ID3D11RasterizerState   IHRD3D11RasterizerState;
typedef IDXGIFactory1           IHRDXGIFactory;
typedef IDXGIAdapter1           IHRDXGIAdapter;
typedef IDXGIDevice1            IHRDXGIDevice;
typedef IDXGISwapChain          IHRDXGISwapChain;
typedef DXGI_SWAP_CHAIN_DESC    DXGI_HR_SWAP_CHAIN_DESC;


//#define D3D11DEVICE HrD3D11Device::GetInstance()->GetDevice()

#endif


