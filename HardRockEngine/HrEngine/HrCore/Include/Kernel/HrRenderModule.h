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
		 @Comment: ����RenderTargets [11/15/2018 By Hr]
		 @Param: HrRenderFramePtr ��Ⱦָ֡�� 
		*/
		void BindFrameBuffer(const HrRenderFramePtr& pRenderFrame);
		/**
		 @Comment: ��Ⱦһ֡ [12/10/2018 By Hr]
		*/
		void RenderSceneView(const HrViewPortPtr& pViewPort);
		
		//void VisitRenderableNode(const HrSceneNodePtr& pNode);

		/**
		 @Comment: ��Ⱦ���� [12/10/2018 By Hr]
		 @Param:   pRenderTechnique ��ȾЧ�� RenderLayout ����Ⱦ����
		*/
		void DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout);
		void DoRender(HrRenderCommand* pCommand);

		/**
		 @Comment: ��ȡ��Ⱦ������� [7/11/2018 By Hr]
		 @Return:  HrRenderFactoryPtr
		*/
		const HrRenderFactoryPtr& GetRenderFactory() const;
		const HrRenderFramePtr& GetRenderFrameBuffer() const;
		/**
		 @Comment: ��ȡ��ǰ����Ⱦģʽ [12/14/2018 By Hr]
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
