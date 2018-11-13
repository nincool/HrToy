#ifndef _HR_SAMPLERSTATE_H_
#define _HR_SAMPLERSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{

	class HR_CORE_API HrSamplerState
	{
	public:
		struct HrSamplerStateDesc 
		{
			size_t hashName;
			EnumSamplerFilter samplerFilter;
			EnumTextureAddressMode texAddressU;
			EnumTextureAddressMode texAddressV;
			EnumTextureAddressMode texAddressW;
			float fMipLODBias;
			uint32 nMaxAnisotropy;
			EnumComparisonFunc comFunc;
			float borderColorArr[4];
			float fMinLOD;
			float fMaxLOD;

			HrSamplerStateDesc() :samplerFilter(SF_FILTER_MIN_MAG_MIP_LINEAR)
				, texAddressU(TAM_TEXTURE_ADDRESS_WRAP)
				, texAddressV(TAM_TEXTURE_ADDRESS_WRAP)
				, texAddressW(TAM_TEXTURE_ADDRESS_WRAP)
				, fMipLODBias(0.0f)
				, nMaxAnisotropy(1)
				, comFunc(CF_NEVER)
				, fMinLOD(0)
				, fMaxLOD(FLT_MAX)
			{
				hashName = 0;
				memset(borderColorArr, 0, sizeof(borderColorArr));
			};
		};
	public:
		HrSamplerState();
		virtual ~HrSamplerState();

		virtual void Accept(const HrRenderPtr& pRender) = 0;
	protected:

	};
}

#endif



