#ifndef _HR_RENDERMODEL_H_
#define _HR_RENDERMODEL_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrSkinnedMeshRenderable : public HrRenderable
	{
	public:
		HrSkinnedMeshRenderable();
		~HrSkinnedMeshRenderable();

		void AttachSubMesh(HrSubMeshPtr pSubMesh);

		virtual const HrRenderLayoutPtr& GetRenderLayout() override;

		virtual bool CanRender() override;
	protected:
		virtual void UpdateRenderFrameParametersImpl(const HrRenderFrameParametersPtr& renderFrameParameters) override;
		virtual void UpdateEffectParametersImpl() override;
	private:
		//³ÖÓÐµÄSubMesh
		HrSubMeshPtr m_pSubMesh;
	};
}

#endif



