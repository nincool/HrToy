#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrVertex.h"

namespace Hr
{
	class HR_CORE_API HrRenderTechnique
	{
	public:
		HrRenderTechnique(std::string strTechniqueName, int nLod);
		~HrRenderTechnique();

		size_t HashName();
		int LOD();
		
		size_t GetRenderPassNum() { return m_vecPass.size(); }
		const HrRenderPassPtr& GetRenderPass(uint32 nIndex);

		HrRenderPassPtr AddPass(const std::string& strPassName);

		bool IsVertexInputSimanticInit();
		bool IsVertexInputSimanticSame(const std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >& vecVertexInputSimantic);
		void SetVertexInputSimantic(std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >&& vecVertexInputSimantic);
		void SetVertexOutputSimantic(std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >&& vecVertexOutputSimantic);

		bool IsVertexElementMatch(const std::vector<HrVertexDataPtr>& vecVertexData);

	private:
		size_t CreateInputSimanticHashValue(const std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >& vecVertexInputSimantic);
	protected:
		size_t m_nHashName;
		std::string m_strTechniqueName;
		int m_nLod;
		std::vector<HrRenderPassPtr> m_vecPass;

		std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> > m_vecVertexInputSimantic;
		size_t m_nInputSimanticHash;
		std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> > m_vecVertexOutputSimantic;

	};
}

#endif


