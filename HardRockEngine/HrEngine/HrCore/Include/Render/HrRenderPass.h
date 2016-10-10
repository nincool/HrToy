#ifndef _HR_RENDERPASS_H_
#define _HR_RENDERPASS_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderPass 
	{
	public:
		HrRenderPass(std::string strPassName);
		~HrRenderPass();

		void SetVSEntryPoint(std::string strVSEntryPoint);
		void SetPSEntryPoint(std::string strPSEntryPoint);
		
		void StreamIn(HrStreamData& streamData);

		void BindPass(HrRender* pRender);
		void UnBindPass(HrRender* pRender);

		HrShader* GetVertexShader();
		HrShader* GetPixelShader();

		void UpdateShaderParams(HrRenderFrameParameters& renderFrameParameters);
	private:
		std::string m_strPassName;

		HrShader* m_pVertexShader;
		HrShader* m_pPixelShader;
	};
}

#endif

