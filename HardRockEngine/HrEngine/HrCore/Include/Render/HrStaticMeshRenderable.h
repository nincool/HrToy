#ifndef _HR_STATICMESHRENDERABLE_H_
#define _HR_STATICMESHRENDERABLE_H_

#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrStaticMeshRenderable : public HrRenderable
	{
	public:
		HrStaticMeshRenderable();
		HrStaticMeshRenderable(HrSubMesh* pSubMesh, HrMaterial* pMaterial);
		~HrStaticMeshRenderable();

		virtual HrRenderLayout* GetRenderLayout() override;

		void SetSubMesh(HrSubMesh* pMesh) { m_pSubMesh = pMesh; }
		void SetMaterial(HrMaterial* pMaterial) { m_pMaterial = pMaterial; }
	protected:
		virtual void UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters) override;
		virtual void UpdateEffectParametersImpl() override;
	protected:
		HrSubMesh* m_pSubMesh;
		HrMaterial* m_pMaterial;
	};
}

#endif





