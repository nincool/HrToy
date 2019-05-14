#ifndef _HR_HRRENDERCORECOMPONENT_H_
#define _HR_HRRENDERCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrModule.h"

namespace Hr
{
	class HR_CORE_API HrRenderModule : public HrModule
	{
	public:
		HrRenderModule(const std::string& strRenderModule);
		~HrRenderModule();

		virtual bool InitComponent() override;

		void AddViewPort(const HrViewPortPtr& pViewPort);

		/**
		 @Comment: 设置RenderTargets [11/15/2018 By Hr]
		 @Param: HrRenderFramePtr 渲染帧指针 
		*/
		void BindFrameBuffer(const HrRenderFramePtr& pRenderFrame);
		/**
		 @Comment: 渲染一帧 [12/10/2018 By Hr]
		*/
		void RenderSceneView(const HrViewPortPtr& pViewPort);
		
		//void VisitRenderableNode(const HrSceneNodePtr& pNode);

		/**
		 @Comment: 渲染函数 [12/10/2018 By Hr]
		 @Param:   pRenderTechnique 渲染效果 RenderLayout 可渲染物体
		*/
		void DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout);
		void DoRender(HrRenderCommand* pCommand);

		/**
		 @Comment: 获取渲染组件工厂 [7/11/2018 By Hr]
		 @Return:  HrRenderFactoryPtr
		*/
		const HrRenderFactoryPtr& GetRenderFactory() const;
		const HrRenderFramePtr& GetRenderFrameBuffer() const;
		/**
		 @Comment: 获取当前的渲染模式 [12/14/2018 By Hr]
		*/
		const HrRenderSystemPtr& GetCurRenderSystem() const;

		void ClearRenderFrame();
		void Present();
		
	protected:
		void RenderFrameForward();
		void RenderFrameDeferred();


	public:










		void RenderDeferredFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam);
		void RenderShadowMapFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam);
		void RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam);




		//todo RenderFrame
	
		void RenderBindFrameBuffer();
		///////////////////////////////////////////////////////////////////


		//todo test
		//void SetViewPort(const HrViewPortPtr& pViewPort);
	private:
		bool CreateRenderFactory(const std::string& strRenderModule);
		




		//void OnRenderFrameBegin();
		//void OnRenderFrameEnd();
	protected:
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;
		HrRenderFactoryPtr m_pRenderFactory;
		HrRenderPtr m_pRender;

		//FrameBuffers
		HrRenderFramePtr m_pCurFrameBuffer;
		
		//RenderSystem
		HrRenderSystemPtr m_pCurRenderSystem;
		HrForwardRenderSystemPtr m_pForwardRenderSystem;
		HrDeferredRenderSystemPtr m_pDeferredRenderSystem;
	};
}

#endif
