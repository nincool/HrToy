#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrResourceManager.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

#include "Kernel/HrCoreComponentRender.h"

#include "Render/HrRenderSystem.h"


using namespace Hr;


HrSubMesh::HrSubMesh(int nSubIndex, const HrMeshPtr& pParent, const std::string& strName)
{
	m_nSubIndex = nSubIndex;
	m_pParentMesh = pParent;
	m_strName = strName;
}

HrSubMesh::~HrSubMesh()
{
}

void HrSubMesh::SetName(const std::string& strName)
{
	m_strName = strName;
}

const std::string& HrSubMesh::GetName()
{
	return m_strName;
}

const HrRenderLayoutPtr& HrSubMesh::GetRenderLayout()
{
	if (!m_pRenderLayout) 
	{
		m_pRenderLayout = HrDirector::Instance()->GetRenderComponent()->GetRenderFactory()->CreateRenderLayout();
	}

	return m_pRenderLayout;
}

void HrSubMesh::SetMaterial(const HrMaterialPtr& pMaterial)
{
	m_pMaterial = pMaterial;
}

const HrMaterialPtr& HrSubMesh::GetMaterial()
{
	return m_pMaterial;
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

size_t HrMesh::CreateHashName(const std::string& strHashValue)
{
	return HrHashValue(strHashValue + ".Hr_Mesh");
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
	m_resStatus = HrResource::RS_LOADED;
	return true;
}

bool HrMesh::UnloadImpl()
{
	m_resStatus = HrResource::RS_DECLARED;
	return true;
}

const HrSubMeshPtr& HrMesh::AddSubMesh(const std::string& strName)
{
	HrSubMeshPtr pSubMesh = HrMakeSharedPtr<HrSubMesh>(static_cast<int>(m_vecSubMesh.size()), shared_from_this(), strName);
	m_vecSubMesh.push_back(pSubMesh);

	return m_vecSubMesh.back();
}

uint32 HrMesh::GetSubMeshNum()
{
	return m_vecSubMesh.size();
}

const HrSubMeshPtr& HrMesh::GetSubMesh(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecSubMesh.size());
	return m_vecSubMesh[nIndex];
}

void HrMesh::FinishedBuildMesh()
{
}

