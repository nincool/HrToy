#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderable : public std::enable_shared_from_this<HrRenderable>
	{
	public:
		HrRenderable();
		virtual ~HrRenderable();

		virtual const HrRenderLayoutPtr& GetRenderLayout();
		virtual const HrRenderTechniquePtr& GetRenderTechnique();

		virtual void UpdateRenderFrameParameters(const HrRenderFrameParametersPtr& pRenderFrameParameters);
		
		uint32 GetSubRenderableNum() const;
		const HrRenderablePtr GetSubRenderable(uint32 nIndex) const;

		virtual bool CanRender();

		void AttachSceneNode(const HrSceneNodePtr& pSceneNode);
		const HrSceneNodePtr& GetSceneNode() const;

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEff);
		const HrRenderEffectPtr& GetRenderEffect() const;
	protected:
		virtual void UpdateRenderFrameParametersImpl(const HrRenderFrameParametersPtr& renderFrameParameters) = 0;
		virtual void UpdateEffectParametersImpl() = 0;
	protected:
		HrRenderEffectPtr m_pRenderEffect;
		HrRenderTechniquePtr m_pCurTechnique;
		HrSceneNodePtr m_pAttachSceneNode;

		std::vector<HrRenderablePtr> m_vecSubRenderable;
	};
}

#endif

