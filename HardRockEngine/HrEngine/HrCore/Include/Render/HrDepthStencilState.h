#ifndef _HR_DEPTHSTENCILSTATE_H_
#define _HR_DEPTHSTENCILSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{


	enum EnumDepthWriteMask
	{
		DWM_ZERO,
		DWM_ALL,
	};

	inline EnumDepthWriteMask DepthWriteMash(const std::string& strDepthWriteMask)
	{
		if ("zero" == strDepthWriteMask) return DWM_ZERO;
		if ("all" == strDepthWriteMask) return DWM_ALL;
		return DWM_ALL;
	}

	enum EnumComparisonFunc
	{
		CF_NEVER,
		CF_LESS,
		CF_EQUAL,
		CF_LESS_EQUAL,
		CF_GREATER,
		CF_NOT_EQUAL,
		CF_GREATER_EQUAL,
		CF_ALWAYS,
	};

	inline EnumComparisonFunc ComparisonFunc(const std::string& strComparisonFunc)
	{
		if ("never" == strComparisonFunc) return CF_NEVER;
		if ("less" == strComparisonFunc) return CF_LESS;
		if ("equal" == strComparisonFunc) return CF_EQUAL;
		if ("less_equal" == strComparisonFunc) return CF_LESS_EQUAL;
		if ("greater" == strComparisonFunc) return CF_GREATER;
		if ("not_equal" == strComparisonFunc) return CF_NOT_EQUAL;
		if ("greater_equal" == strComparisonFunc) return CF_GREATER_EQUAL;
		if ("always" == strComparisonFunc) return CF_ALWAYS;
		return CF_LESS;
	}

	enum EnumStencilOperation
	{
		SO_KEEP,
		SO_ZERO,
		SO_REPLACE,
		SO_INCR_SAT,
		SO_DECR_SAT,
		SO_INVERT,
		SO_INCR,
		SO_DECR,
	};

	inline EnumStencilOperation StencilOperation(const std::string& strStencilOp)
	{
		if ("keep" == strStencilOp) return SO_KEEP;
		if ("zero" == strStencilOp) return SO_ZERO;
		if ("replace" == strStencilOp) return SO_REPLACE;
		if ("incr_sat" == strStencilOp) return SO_INCR_SAT;
		if ("decr_sat" == strStencilOp) return SO_DECR_SAT;
		if ("invert" == strStencilOp) return SO_INVERT;
		if ("incr" == strStencilOp) return SO_INCR;
		if ("decr" == strStencilOp) return SO_DECR;
		return SO_KEEP;
	}

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




