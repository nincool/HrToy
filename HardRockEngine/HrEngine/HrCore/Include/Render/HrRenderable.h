#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderable : public std::enable_shared_from_this<HrRenderable>
	{
	public:
		HrRenderable(const HrSubMeshPtr& pSubMesh);
		virtual ~HrRenderable();

		const HrRenderLayoutPtr& GetRenderLayout();
		const HrSubMeshPtr& GetSubMesh();

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEff);
		const HrRenderEffectPtr& GetRenderEffect() const;
		const HrRenderTechniquePtr& GetTechnique();

		virtual const HrMaterialPtr& GetMaterial();

		/**
		 @Comment: rendering [7/12/2018 By Hr]
		*/
		virtual void OnRenderBegin();
		virtual void OnRenderEnd();
		
		/**
		 @Comment: axis-aligned bounding box  [10/26/2018 By Hr]
		 @Return: aabb
		*/
		const AABBox& GetAABBox();

		HrRenderCommand* GetRenderCommand();
	protected:
		bool CheckRenderLayoutMatchShader();

		virtual void UpdateRenderEffectParam();
	protected:
		HrRenderEffectPtr m_pRenderEffect;
		HrRenderTechniquePtr m_pTechnique;

		HrSubMeshPtr m_pSubMesh;

		std::shared_ptr<HrRenderCommand> m_pRenderCommand;
	};
}

#endif

