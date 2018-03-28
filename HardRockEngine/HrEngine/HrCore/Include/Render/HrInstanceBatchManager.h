#ifndef _HR_INSTANCEBATCHMANAGER_H_
#define _HR_INSTANCEBATCHMANAGER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrInstanceBatchManager
	{
	public:
		HrInstanceBatchManager(const HrSubMeshPtr& pModel);
		~HrInstanceBatchManager();

		const HrInstanceBatchPtr& GetInstanceBatch();

	protected:
		HrInstanceBatchPtr CreateBatch();
	protected:
		HrSubMeshPtr m_pSubMesh;
		HrMeshPtr m_pMesh;

		HrInstanceBatchPtr m_pInstanceBatch;

	};
}


#endif
