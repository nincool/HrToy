#ifndef _HR_HRRENDERCORECOMPONENT_H_
#define _HR_HRRENDERCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"

namespace Hr
{
	class HR_CORE_API HrCoreComponentRender : public HrCoreComponent
	{
	public:
		HrCoreComponentRender(const std::string& strRenderModule);
		~HrCoreComponentRender();

		virtual bool InitComponent() override;

		void AddViewPort(const HrViewPortPtr& pViewPort);

		void BindFrameBuffer(const HrRenderFramePtr& pRenderFrame);

		void OnRenderFrameBegin();
		void OnRenderFrameEnd();

		void RenderShadowMapFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam);
		void RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam);

		void Present();

		void DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout);

		///////////////////////////////////////////////////////////////////
		/**
		 @Comment: 获取渲染组件工厂 [7/11/2018 By Hr]
		 @Return:  HrRenderFactoryPtr
		*/
		const HrRenderFactoryPtr& GetRenderFactory() const;
		const HrRenderFramePtr& GetRenderFrameBuffer() const;
	private:
		bool CreateRenderFactory(const std::string& strRenderModule);

		void CreateRenderSystem();		
		void ClearRenderFame();
	protected:
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;
		HrRenderFactoryPtr m_pRenderFactory;
		HrRenderSystemPtr m_pRenderSystem;
	};
}

#endif
