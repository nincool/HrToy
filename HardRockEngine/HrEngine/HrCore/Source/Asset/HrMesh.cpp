#include "Asset/HrMesh.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrSubMesh::HrSubMesh()
{
	//for test
	m_pRenderLayout = HrDirector::Instance()->GetRenderFactory()->CreateRenderLayout();
}

HrSubMesh::~HrSubMesh()
{
	SAFE_DELETE(m_pRenderLayout);
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////


HrMesh::HrMesh()
{

}

HrMesh::~HrMesh()
{
}

void HrMesh::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MESH;

	m_nHashID = HrHashValue(m_strFilePath + strFileName + ".Hr_Mesh");
}

bool HrMesh::LoadImpl()
{
	return true;
}

bool HrMesh::UnloadImpl()
{
	return true;
}

uint32 HrMesh::GetSubMeshNum()
{
	return m_vecSubMesh.size();
}

HrSubMesh* HrMesh::GetSubMesh(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecSubMesh.size());
	return m_vecSubMesh[nIndex];
}

void HrMesh::FinishedBuildMesh()
{
	m_bLoaded = true;
}

