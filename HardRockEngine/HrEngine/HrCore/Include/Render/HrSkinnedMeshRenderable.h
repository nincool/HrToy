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

		void AttachPrefebModel(HrPrefebModel* pPrefebModel);
		void AttachSubMesh(HrSubMesh* pSubMesh);

		virtual HrRenderLayout* GetRenderLayout() override;

		virtual bool CanRender() override;
	protected:
		virtual void UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters) override;
		virtual void UpdateEffectParametersImpl() override;
	private:
		//模型资源
		HrPrefebModel* m_pPrefebModel;
		//持有的SubMesh
		HrSubMesh* m_pSubMesh;
	};
}

#endif



