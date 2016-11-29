#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderTechnique
	{
	public:
		HrRenderTechnique(std::string strTechniqueName);
		~HrRenderTechnique();

		size_t GetHashName();
		
		size_t GetRenderPassNum() { return m_vecPass.size(); }
		HrRenderPass* GetRenderPass(uint32 nIndex);

		void CollectShaderParameters();
		
		void UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters);

		HrRenderPass* AddPass(std::string strPassName);

	protected:
		void UpdateOneEffectParameter(HrRenderEffectParameter& renderEffectParameter, HrRenderFrameParameters& renderFrameParameters);
	protected:
		size_t m_nHashName;
		std::string m_strTechniqueName;
		std::vector<HrRenderPass*> m_vecPass;

		//technique中需要的paramer 链接着effect的parameter
		std::vector<HrRenderEffectParameter*> m_vecTechNeedParameter;
		std::vector<HrRenderEffectStructParameter*> m_vecTechNeedStruct;
		std::vector<HrRenderEffectConstantBuffer*> m_vecTechNeedConstBuffer;
	};
}

#endif


