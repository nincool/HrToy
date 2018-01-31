#ifndef _HR_STATICMESHRENDERABLE_H_
#define _HR_STATICMESHRENDERABLE_H_

#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrStaticMeshRenderable : public HrRenderable
	{
	public:
		HrStaticMeshRenderable();
		HrStaticMeshRenderable(const HrSubMeshPtr& pSubMesh, const HrMaterialPtr& pMaterial);
		~HrStaticMeshRenderable();

		virtual const HrRenderLayoutPtr& GetRenderLayout() override;

	protected:
		virtual void UpdateRenderFrameParametersImpl(const HrRenderFrameParametersPtr& renderFrameParameters) override;
		virtual void UpdateEffectParametersImpl() override;
	protected:
		HrSubMeshPtr m_pSubMesh;
	};
}

#endif





