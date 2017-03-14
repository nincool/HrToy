#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderable
	{
	public:
		HrRenderable();
		virtual ~HrRenderable();

		virtual HrRenderLayout* GetRenderLayout() = 0;
		virtual HrRenderTechnique* GetRenderTechnique();

		virtual void UpdateRenderFrameParameters(HrRenderFrameParameters& renderFrameParameters);
		
		uint32 GetSubRenderableNum() const;
		HrRenderable* GetSubRenderable(uint32 nIndex) const;

		virtual bool CanRender();

		void AttachSceneNode(HrSceneNode* pSceneNode);
		HrSceneNode* GetSceneNode() const;

		HrRenderEffect* GetRenderEffect() const;
	protected:
		virtual void UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters) = 0;
		virtual void UpdateEffectParametersImpl() = 0;
	protected:
		HrRenderEffect* m_pRenderEffect;
		HrRenderTechnique* m_pRenderTechnique;
		HrSceneNode* m_pAttachSceneNode;

		std::vector<HrRenderable*> m_vecSubRenderable;
	};
}

#endif

