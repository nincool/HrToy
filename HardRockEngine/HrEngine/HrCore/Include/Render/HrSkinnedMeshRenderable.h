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
		HrSkinnedMeshRenderable(HrPrefebModel* pPrefebModel);
		~HrSkinnedMeshRenderable();

		virtual HrRenderLayout* GetRenderLayout() override;

		void  AttachPrefebModel(HrPrefebModel* pPrefebModel);

	protected:
		virtual void UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters) override {}
	private:
		HrPrefebModel* m_pPrefebModel;

	};
}

#endif



