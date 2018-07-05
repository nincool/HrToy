#ifndef _HR_BLENDSTATE_H_
#define _HR_BLENDSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"


namespace Hr
{
	enum EnumBlendOperation
	{
		BO_UNKNOW,
		BO_ADD,
		BO_SUB,
		BO_REV_SUB,
		BO_MIN,
		BO_MAX,
	};

	enum EnumAlphaBlendFactor
	{
		ABF_UNKNOW,
		ABF_ZERO,
		ABF_ONE,
		ABF_SCR_ALPHA,
		ABF_DST_ALPHA,
		ABF_INV_SRC_ALPHA,
		ABF_INV_DST_ALPHA,
		ABF_SRC_COLOR,
		ABF_DST_COLOR,
		ABF_INV_SRC_COLOR,
		ABF_INV_DST_COLOR,
		ABF_SRC_ALPHA_SAT,
		ABF_BLEND_FACTOR,
		ABF_INV_BLEND_FACTOR,
		ABF_SRC1_ALPHA,
		ABF_INV_SRC1_ALPHA,
		ABF_SRC1_COLOR,
		ABF_INV_SRC1_COLOR,
	};

	enum EnumColorMask
	{
		CMASK_RED = 1UL << 0,
		CMASK_GREEN = 1UL << 1,
		CMASK_BLUE = 1UL << 2,
		CMASK_ALPHA = 1UL << 3,
		CMASK_ALL = CMASK_RED | CMASK_GREEN | CMASK_BLUE | CMASK_ALPHA,
	};

	inline EnumAlphaBlendFactor AlphaBlendFactor(const std::string& strAlphaBlendFactor)
	{
		if ("zero" == strAlphaBlendFactor) return ABF_ZERO;
		if ("one" == strAlphaBlendFactor) return ABF_ONE;
		if ("src_alpha" == strAlphaBlendFactor) return ABF_SCR_ALPHA;
		if ("dst_alpha" == strAlphaBlendFactor) return ABF_DST_ALPHA;
		if ("inv_src_alpha" == strAlphaBlendFactor) return ABF_INV_SRC_ALPHA;
		if ("inv_dst_alpha" == strAlphaBlendFactor) return ABF_INV_DST_ALPHA;
		if ("src_color" == strAlphaBlendFactor) return ABF_SRC_COLOR;
		if ("dst_color" == strAlphaBlendFactor) return ABF_DST_COLOR;
		if ("inv_src_color" == strAlphaBlendFactor) return ABF_INV_SRC_COLOR;
		if ("inv_dst_color" == strAlphaBlendFactor) return ABF_INV_DST_COLOR;
		if ("src_alpha_sat" == strAlphaBlendFactor) return ABF_SRC_ALPHA_SAT;
		if ("blend_factor" == strAlphaBlendFactor) return ABF_BLEND_FACTOR;
		if ("inv_blend_factor" == strAlphaBlendFactor) return ABF_INV_BLEND_FACTOR;
		if ("src1_alpha" == strAlphaBlendFactor) return ABF_SRC1_ALPHA;
		if ("inv_src1_alpha" == strAlphaBlendFactor) return ABF_INV_SRC1_ALPHA;
		if ("src1_color" == strAlphaBlendFactor) return ABF_SRC1_COLOR;
		if ("inv_src1_color" == strAlphaBlendFactor) return ABF_INV_SRC1_COLOR;
		return ABF_UNKNOW;
	}

	inline EnumBlendOperation BlendOperation(const std::string& strBlendOP)
	{
		if ("add" == strBlendOP) return BO_ADD;
		if ("sub" == strBlendOP) return BO_SUB;
		if ("rev_sub" == strBlendOP) return BO_REV_SUB;
		if ("min" == strBlendOP) return BO_MIN;
		if ("max" == strBlendOP) return BO_MAX;
		return BO_UNKNOW;
	}

	inline uint8 ColorMask(const std::vector<std::string>& vecColorMask)
	{
		if (vecColorMask.size() == 4)
		{
			return CMASK_ALL;
		}

		uint8 nColorMask = 0;
		for (size_t i = 0; i < vecColorMask.size(); ++i)
		{
			if (vecColorMask[i] == "r")
				nColorMask |= CMASK_RED;
			else if (vecColorMask[i] == "g")
				nColorMask |= CMASK_GREEN;
			else if (vecColorMask[i] == "b")
				nColorMask |= CMASK_BLUE;
			else if (vecColorMask[i] == "a")
				nColorMask |= CMASK_ALPHA;
		}

		return nColorMask;
	}



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
			uint8 colorMask;
			HrColor blendFactor;
			uint32 nSampleMask;
		};
	public:
		HrBlendState();
		virtual ~HrBlendState();
		
		virtual void Accept(const HrRenderPtr& pRender) = 0;

		size_t HashName() { return m_nHashName; }
	protected:
		size_t m_nHashName;
	};
}

#endif
