#ifndef _HR_RENDERPROCESSING_H_
#define _HR_RENDERPROCESSING_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderProcessing
	{
	public:
		HrRenderProcessing();
		~HrRenderProcessing();

		enum EnumRenderProcessingResult
		{
			RPR_DO_NOTHING = 1 << 0,
			RPR_NEED_PRESENT = 1 << 1,
		};

		virtual uint32 Run(HrRenderSystem* pRenderSystem) = 0;
		virtual void VisitRenderable(const HrRenderablePtr& pRenderable);
		virtual void VisitRenderCommand(HrRenderCommand* pRenderCommand);
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HrForwardProcessing : public HrRenderProcessing
	{
	public:
		HrForwardProcessing();
		~HrForwardProcessing();

		virtual uint32 Run(HrRenderSystem* pRenderSystem) override;
		virtual void VisitRenderCommand(HrRenderCommand* pRenderCommand) override;
	private:
		HrRenderEffectPtr m_pDefaultEffect;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HrDeferredGBufferProcessing : public HrRenderProcessing
	{
	public:
		HrDeferredGBufferProcessing();
		~HrDeferredGBufferProcessing();

		virtual uint32 Run(HrRenderSystem* pRenderSystem) override;
		virtual void VisitRenderable(const HrRenderablePtr& pRenderable) override;
	protected:
		void CreateGBuffers(const HrViewPortPtr& pViewPort, HrDeferredRenderSystem* pDeferredSystem);
		void RenderSceneToGBuffers(HrDeferredRenderSystem* pDeferredSystem);

	private:
		HrRenderEffectPtr m_pMakeGBuffers;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HrFinalMappingProcessing : public HrRenderProcessing
	{
	public:
		HrFinalMappingProcessing();
		~HrFinalMappingProcessing();

		virtual uint32 Run(HrRenderSystem* pRenderSystem) override;
	
	private:
		HrRenderEffectPtr m_pFinalPresentEffect;
	

	};
}


#endif
