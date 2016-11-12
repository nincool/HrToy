#include "Asset/HrMesh.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrMesh::HrMesh()
{
	m_pRenderLayout = new HrRenderLayout();
}

HrMesh::~HrMesh()
{
	SAFE_DELETE(m_pRenderLayout);
}

void HrMesh::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MESH;

	m_nHashID = HrHashValue(m_strFilePath + strFileName + "Hr_Mesh");
}

void HrMesh::Load()
{

}

void HrMesh::Unload()
{

}

HrRenderLayout* HrMesh::GetRenderLayout()
{
	return m_pRenderLayout;
}

