#include "Render/HrInstanceBatchManager.h"
#include "Render/HrInstanceBatch.h"
#include "Render/HrInstanceBatchHW.h"
#include "Asset/HrModel.h"
#include "Asset/HrMesh.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneNode.h"

using namespace Hr;


HrInstanceBatchManager::HrInstanceBatchManager(const HrSubMeshPtr& pModel)
{
	m_pSubMesh = pModel;
}

HrInstanceBatchManager::~HrInstanceBatchManager()
{

}

const HrInstanceBatchPtr& HrInstanceBatchManager::GetInstanceBatch()
{
	if (!m_pInstanceBatch)
	{
		m_pInstanceBatch = CreateBatch();
	}

	return m_pInstanceBatch;
}

HrInstanceBatchPtr HrInstanceBatchManager::CreateBatch()
{
	return HrMakeSharedPtr<HrInstanceBatchHW>();
}

