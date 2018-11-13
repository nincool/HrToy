#ifndef _HR_DEPTHSTENCILSTATE_H_
#define _HR_DEPTHSTENCILSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HR_CORE_API HrDepthStencilState
	{
	public:
		struct HrDepthStencilStateDesc
		{
			size_t hashName;
			bool bDepthEnable;
			EnumDepthWriteMask depthWriteMask;
			EnumComparisonFunc depthCompareFunc;
			bool bStencilEnable;
			uint8 stencilReadMask;
			uint8 stencilWriteMask;
			EnumComparisonFunc frontFaceCompareFunc;
			EnumStencilOperation frontFaceStencilFailOp;
			EnumStencilOperation frontFaceStencilDepthFailOp;
			EnumStencilOperation frontFaceStencilPassOp;
			EnumComparisonFunc backFaceCompareFunc;
			EnumStencilOperation backFaceStencilFailOp;
			EnumStencilOperation backFaceStencilDepthFailOp;
			EnumStencilOperation backFaceStencilPassOp;
			uint32 nStencilRef;
			HrDepthStencilStateDesc():
				bDepthEnable(true),
				depthWriteMask(DWM_ALL),
				depthCompareFunc(CF_ALWAYS),
				bStencilEnable(false),
				stencilReadMask(0xFF),
				stencilWriteMask(0xFF),
				frontFaceCompareFunc(CF_ALWAYS),
				frontFaceStencilFailOp(SO_KEEP),
				frontFaceStencilDepthFailOp(SO_KEEP),
				frontFaceStencilPassOp(SO_KEEP),
				backFaceCompareFunc(CF_ALWAYS),
				backFaceStencilFailOp(SO_KEEP),
				backFaceStencilDepthFailOp(SO_KEEP),
				backFaceStencilPassOp(SO_KEEP),
				nStencilRef(0xffffffff)
			
			{}
		};
	public:
		HrDepthStencilState();
		virtual ~HrDepthStencilState();

		virtual void Accept(const HrRenderPtr& pRender) = 0;

	protected:
	};
}


#endif




