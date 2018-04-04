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
		const HrSubMeshPtr& GetSubMesh();

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEff);
		const HrRenderEffectPtr& GetRenderEffect() const;

		virtual const HrMaterialPtr& GetMaterial();

		void SetAttachSceneObject(const HrSceneObjectPtr& pSceneObj);
		HrSceneObjectPtr GetAttachSceneObject();

		virtual void OnRenderBegin();
		virtual void Render();
		virtual void OnRenderEnd();
		
	protected:

	protected:
		HrRenderEffectPtr m_pRenderEffect;
		HrRenderTechniquePtr m_pCurTechnique;
		HrSubMeshPtr m_pSubMesh;

		std::weak_ptr<HrSceneObject> m_pAttachSceneObj;
	};
}

#endif

