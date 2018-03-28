#ifndef _HR_INSTANCEBATCH_H_
#define _HR_INSTANCEBATCH_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{

#define HR_MAX_INSTANCE_NUM 80

	class HR_CORE_API  HrInstanceBatch : public HrRenderable
	{
	public:
		HrInstanceBatch();
		~HrInstanceBatch();

		virtual const HrRenderLayoutPtr& GetRenderLayout() override;

		virtual void SetSubMesh(const HrSubMeshPtr& pSubMesh) override;

		bool IsBatchFull();
	protected:
		virtual void BuildVertices(const HrSubMeshPtr& pSubMesh);
	protected:
		HrMaterialPtr m_pMaterial;
		
		HrSubMeshPtr m_pSubMesh;

		HrRenderLayoutPtr m_pBatchRenderLayout;
	};
}



#endif
