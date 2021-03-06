#ifndef _HR_RASTERIZERSTATE_H_
#define _HR_RASTERIZERSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{


	class HR_CORE_API HrRasterizerState
	{
	public:
		//https://docs.microsoft.com/zh-cn/windows/desktop/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
		struct HrRasterizerStateDesc
		{
			size_t hashName;
			EnumRasterizerFillModel fillMode;
			EnumRasterizerCullModel cullMode;
			bool bfrontCounterClockWise;
			int nDepthBias;
			float fDepthBiasClamp;
			float fSlopScaleDepthBias;
			bool bDepthClipEnable;
			//D3D11_RECT rects = { 100, 100, 400, 400 };
			//md3dImmediateContext->RSSetScissorRects(1, &rects);
			//The previous call only sets the scissor rectangles, but it does not enable the scissor test.The scissor test is enabled / disabled via the
			//	D3D11_RASTERIZER_DESC::ScissorEnable.
			bool bScissorEnable;
			bool bMultisampleEnalbe;
			bool bAntialiaseLineEnable;

			HrRasterizerStateDesc():
				hashName(0),
				fillMode(RFM_SOLD),
				cullMode(RCM_CULL_BACK),
				bfrontCounterClockWise(false),
				nDepthBias(0),
				fDepthBiasClamp(0),
				fSlopScaleDepthBias(0),
				bDepthClipEnable(true),
				bScissorEnable(false),
				bMultisampleEnalbe(false),
				bAntialiaseLineEnable(false)
			{}
		};
	public:
		HrRasterizerState();
		virtual ~HrRasterizerState();

		virtual void Accept(const HrRenderPtr& pRender) = 0;
	};
}

#endif


