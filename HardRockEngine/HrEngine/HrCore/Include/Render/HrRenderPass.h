#ifndef _HR_RENDERPASS_H_
#define _HR_RENDERPASS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IShader;
	class IRender;

	class HR_CORE_API HrRenderPass : public RenderSysAllocatedObject
	{
	public:
		HrRenderPass(std::string strPassName);
		~HrRenderPass();

		void SetVSEntryPoint(std::string strVSEntryPoint);
		void SetPSEntryPoint(std::string strPSEntryPoint);
		
		void StreamIn(HrStreamData& streamData);

		void BindPass(IRender* pRender);
		void UnBindPass(IRender* pRender);

		IShader* GetVertexShader();
		IShader* GetPixelShader();

		void UpdateShaderParams(HrRenderFrameParameters& renderFrameParameters);
	private:
		std::string m_strPassName;
		IShader* m_pVertexShader;
		IShader* m_pPixelShader;
	};
}

#endif

