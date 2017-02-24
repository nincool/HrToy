#ifndef _HR_RASTERIZERSTATE_H_
#define _HR_RASTERIZERSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{
	class HR_CORE_API HrRasterizerState
	{
	public:
		struct RasterizerStateDesc
		{
			EnumRasterizerFillModel fillMode;
			EnumRasterizerCullModel cullMode;
			bool bfrontCounterClockWise;
			bool bDepthClipEnable;
		};
	public:
		HrRasterizerState();
		virtual ~HrRasterizerState();

		virtual void Bind(HrRender* pRender) = 0;

		static size_t GetRasterizerStateKey(RasterizerStateDesc& desc);
	};
}

#endif




