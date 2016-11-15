#ifndef _HR_RENDERMODEL_H_
#define _HR_RENDERMODEL_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrRenderModel : public HrRenderable
	{
	public:
		HrRenderModel();
		HrRenderModel(HrPrefebModel* pPrefebModel);
		~HrRenderModel();

		virtual HrRenderLayout* GetRenderLayout() override;

		void  AttachPrefebModel(HrPrefebModel* pPrefebModel);
	private:
		HrPrefebModel* m_pPrefebModel;

	};
}

#endif



