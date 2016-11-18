#include "Render/HrStaticMeshRenderable.h"
#include "Asset/HrMesh.h"

using namespace Hr;

HrStaticMeshRenderable::HrStaticMeshRenderable()
{

}

HrStaticMeshRenderable::HrStaticMeshRenderable(HrMesh* pMesh)
{
	m_pMesh = pMesh;
}

HrStaticMeshRenderable::~HrStaticMeshRenderable()
{

}

HrRenderLayout* HrStaticMeshRenderable::GetRenderLayout()
{
	BOOST_ASSERT(m_pMesh);
	return m_pMesh->GetRenderLayout();
}

void HrStaticMeshRenderable::UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters)
{

}


