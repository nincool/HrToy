#ifndef _HR_RENDERSYSTEM_H_
#define _HR_RENDERSYSTEM_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderSystem
	{
	public:
		HrRenderSystem(HrRenderFactoryPtr& pRenderFactory);
		virtual ~HrRenderSystem();

		const HrRenderFactoryPtr& GetRenderFactory();
		const HrRenderPtr& GetRender();
		const HrRenderFramePtr& GetScreenFrameBuffer();

		void BindFrameBuffer(const HrRenderFramePtr& pRenderFrame);
		void BindScreenFrameBuffer();

		void RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam);

		const HrRenderFramePtr& GetBindFrameBuffer();
		
		void ClearRenderTarget();
		void ClearDepthStencil();

		void Present();
	private:
		void CreateRender();
		void CreateScreenFrameBuffer(uint32 nWidth, uint32 nHeight);

	public:
		//define const string key
		static const std::string m_sc_strScreenFrameBufferKey;
	private:
		HrRenderFactoryPtr m_pRenderFactory;
		HrRenderPtr m_pRender;
		
		HrRenderFramePtr m_pScreenFrameBuffer;
		std::unordered_map<std::string, HrRenderFramePtr> m_mapRenderFrames;
	};
}


#endif
