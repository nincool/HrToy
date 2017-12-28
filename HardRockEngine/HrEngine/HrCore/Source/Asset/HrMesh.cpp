#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrResourceManager.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

#include "Kernel/HrRenderCoreComponent.h"

#include "Render/HrRenderSystem.h"


using namespace Hr;

HrSubMesh::HrSubMesh()
{
	//for test
	m_pRenderLayout = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderFactory()->CreateRenderLayout();
	//先设置一个默认的材质
	m_pMaterial = HrResourceManager::Instance()->GetDefaultMaterial();
}

HrSubMesh::~HrSubMesh()
{
	SAFE_DELETE(m_pRenderLayout);
}

void HrSubMesh::SetName(const std::string& strName)
{
	m_strName = strName;
}

const std::string& HrSubMesh::GetName()
{
	return m_strName;
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

size_t HrMesh::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath + ".Hr_Mesh");
}

void HrMesh::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MESH;

	m_nHashID = CreateHashName(m_strFilePath);
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

