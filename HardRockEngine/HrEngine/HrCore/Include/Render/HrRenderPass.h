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
		HrRenderPass();
		~HrRenderPass();

		void BindPass(IRender* pRender);
		void UnBindPass(IRender* pRender);
	private:
		IShader* m_pShader;
	};
}

#endif

