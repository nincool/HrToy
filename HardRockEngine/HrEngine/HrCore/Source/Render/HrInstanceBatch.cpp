#include "Render/HrInstanceBatch.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrRenderModule.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrVertex.h"
#include "Asset/HrMesh.h"
#include "Asset/HrStreamData.h"

using namespace Hr;

HrInstanceBatch::HrInstanceBatch()
{

}

HrInstanceBatch::~HrInstanceBatch()
{

}

void HrInstanceBatch::BuildVertices(const HrSubMeshPtr& pSubMesh)
{
}

const HrRenderLayoutPtr& HrInstanceBatch::GetRenderLayout()
{
	return m_pBatchRenderLayout;
}

void HrInstanceBatch::SetSubMesh(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;
	BuildVertices(pSubMesh);
}


