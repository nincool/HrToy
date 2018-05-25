#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{
	class HR_CORE_API HrRenderTechnique
	{
	public:
		HrRenderTechnique(std::string strTechniqueName);
		~HrRenderTechnique();

		size_t HashName();
		
		size_t GetRenderPassNum() { return m_vecPass.size(); }
		const HrRenderPassPtr& GetRenderPass(uint32 nIndex);

		HrRenderPassPtr AddPass(const std::string& strPassName);

		bool IsVertexInputSimanticInit();
		bool IsVertexInputSimanticSame(const std::vector<std::pair<EnumVertexElementSemantic, uint32> >& vecVertexInputSimantic);
		void SetVertexInputSimantic(std::vector<std::pair<EnumVertexElementSemantic, uint32> >&& vecVertexInputSimantic);
		void SetVertexOutputSimantic(std::vector<std::pair<EnumVertexElementSemantic, uint32> >&& vecVertexOutputSimantic);

	protected:
		size_t m_nHashName;
		std::string m_strTechniqueName;
		std::vector<HrRenderPassPtr> m_vecPass;

		std::vector<std::pair<EnumVertexElementSemantic, uint32> > m_vecVertexInputSimantic;
		std::vector<std::pair<EnumVertexElementSemantic, uint32> > m_vecVertexOutputSimantic;
	};
}

#endif


