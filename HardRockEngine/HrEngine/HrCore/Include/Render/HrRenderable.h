#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderable : public std::enable_shared_from_this<HrRenderable>
	{
	public:
		HrRenderable();
		HrRenderable(const HrSubMeshPtr& pSubMesh);
		virtual ~HrRenderable();

		virtual const HrRenderLayoutPtr& GetRenderLayout();
		virtual const HrRenderTechniquePtr& GetRenderTechnique();

		//virtual void SetSubMesh(const HrSubMeshPtr& pSubMesh);
		const HrSubMeshPtr& GetSubMesh();

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEff);
		const HrRenderEffectPtr& GetRenderEffect() const;
		
		virtual const HrMaterialPtr& GetMaterial();

		/**
		 @Comment: attach sceneobject [7/12/2018 By Hr]
		*/
		void SetAttachSceneObject(HrSceneObject* pSceneObj);
		HrSceneObject* GetAttachSceneObject() const;

		/**
		 @Comment: rendering [7/12/2018 By Hr]
		*/
		virtual void OnRenderBegin();
		virtual void Render(const HrRenderTechniquePtr& pRenderTech = nullptr);
		virtual void OnRenderEnd();
		
		/**
		 @Comment: axis-aligned bounding box  [10/26/2018 By Hr]
		 @Return: aabb
		*/
		const AABBox& GetAABBox();
	protected:
		bool CheckRenderLayoutMatchShader();

		virtual void UpdateRenderEffectParam();
	protected:
		HrRenderEffectPtr m_pRenderEffect;
		HrRenderTechniquePtr m_pCurTechnique;
		HrSubMeshPtr m_pSubMesh;

		//todo
		//std::weak_ptr<HrSceneObject> m_pAttachSceneObj;
		HrSceneObject* m_pSceneObj;
	};
}

#endif

