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

		virtual void SetSubMesh(const HrSubMeshPtr& pSubMesh);
		
		uint32 GetSubRenderableNum() const;
		const HrRenderablePtr GetSubRenderable(uint32 nIndex) const;

		virtual bool CanRender();

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEff);
		const HrRenderEffectPtr& GetRenderEffect() const;

		virtual const HrMaterialPtr& GetMaterial();
	protected:

	protected:
		HrRenderEffectPtr m_pRenderEffect;
		HrRenderTechniquePtr m_pCurTechnique;
		HrSceneNodePtr m_pAttachSceneNode;
		HrSubMeshPtr m_pSubMesh;

		std::vector<HrRenderablePtr> m_vecSubRenderable;
	};
}

#endif

