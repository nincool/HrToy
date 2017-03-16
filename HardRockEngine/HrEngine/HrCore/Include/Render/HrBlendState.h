#ifndef _HR_BLENDSTATE_H_
#define _HR_BLENDSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{
	class HR_CORE_API HrBlendState
	{
	public:
		struct HrBlendStateDesc
		{
			size_t hashName;
			bool bBlendEnable;
			EnumBlendOperation blendOperation;
			EnumAlphaBlendFactor srcBlend;
			EnumAlphaBlendFactor dstBlend;
			EnumBlendOperation blendOperationAlpha;
			EnumAlphaBlendFactor srcBlendAlpha;
			EnumAlphaBlendFactor dstBlendAlpha;
		};
	public:
		HrBlendState();
		virtual ~HrBlendState();

		virtual void Bind(HrRender* pRender) = 0;
	};
}

#endif
