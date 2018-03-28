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

		virtual const HrRenderLayoutPtr& GetRenderLayout() override;

		virtual void SetSubMesh(const HrSubMeshPtr& pSubMesh) override;

		virtual bool CanRender() override;

		virtual const HrMaterialPtr& GetMaterial() override;
	protected:

	private:
		HrSubMeshPtr m_pSubMesh;
	};
}

#endif



