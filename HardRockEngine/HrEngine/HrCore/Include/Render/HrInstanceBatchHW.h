#ifndef _HR_INSTANCEBATCHHW_H_
#define _HR_INSTANCEBATCHHW_H_

#include "HrCore/Include/Render/HrInstanceBatch.h"

namespace Hr
{
	class HR_CORE_API HrInstanceBatchHW : public HrInstanceBatch
	{
	public:
		HrInstanceBatchHW();
		~HrInstanceBatchHW();

		virtual HrSceneObjectPtr CreateInstance() override;

		virtual void OnRenderBegin() override;

		virtual void OnRenderEnd() override;
	protected:
		virtual void BuildVertices(const HrSubMeshPtr& pSubMesh);


	private:


	};
}


#endif
