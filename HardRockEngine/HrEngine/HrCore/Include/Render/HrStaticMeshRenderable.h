#ifndef _HR_STATICMESHRENDERABLE_H_
#define _HR_STATICMESHRENDERABLE_H_

#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrStaticMeshRenderable : public HrRenderable
	{
	public:
		HrStaticMeshRenderable();
		HrStaticMeshRenderable(HrMesh* pMesh, HrMaterial* pMaterial);
		~HrStaticMeshRenderable();

		virtual HrRenderLayout* GetRenderLayout() override;

		void SetMesh(HrMesh* pMesh) { m_pMesh = pMesh; }
		void SetMaterial(HrMaterial* pMaterial) { m_pMaterial = pMaterial; }
	protected:
		virtual void UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters) override;
	protected:
		HrMesh* m_pMesh;
		HrMaterial* m_pMaterial;
	};
}

#endif





