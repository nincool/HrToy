#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
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

HrRenderLayout* HrSubMesh::GetRenderLayout() const
{
	return m_pRenderLayout;
}

void HrSubMesh::SetMaterial(HrMaterial* pMaterial)
{
	m_pMaterial = pMaterial;
}

HrMaterial* HrSubMesh::GetMaterial() const
{
	return m_pMaterial;
}

void HrSubMesh::SetTexture(HrTexture* pTexture)
{
	m_pTexture = pTexture;
}

HrTexture* HrSubMesh::GetTexture() const
{
	return m_pTexture;
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////


HrMesh::HrMesh()
{

}

HrMesh::~HrMesh()
{
	for (auto& item : m_vecSubMesh)
	{
		SAFE_DELETE(item);
	}
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

HrSubMesh* HrMesh::AddSubMesh()
{
	HrSubMesh* pSubMesh = HR_NEW HrSubMesh();
	m_vecSubMesh.push_back(pSubMesh);
	return pSubMesh;
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

