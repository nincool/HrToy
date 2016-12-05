#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrMaterial.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrGraphicsBuffer.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"

using namespace Hr;

HrModelLoader::HrModelLoader()
{
}

HrModelLoader::~HrModelLoader()
{

}

void HrModelLoader::Load(std::string& strFile)
{
	m_strFileName = strFile;
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
	HrStringUtil::ToLowerCase(strSuffix);
	if (strSuffix == "fbx")
	{
		std::shared_ptr<HrFBXLoader> pFBXLoader = MakeSharedPtr<HrFBXLoader>();
		pFBXLoader->Load(strFile, m_modelDesc);
	}

	//construct default vertexelement
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));

	for (size_t i = 0; i < m_modelDesc.m_vecMeshInfo.size(); ++i)
	{
		HrModelDescInfo::HrMeshInfo& meshInfo = m_modelDesc.m_vecMeshInfo[i];

		FillEmptyModelInfo(meshInfo);

		//Add Material Res
		MakeMaterialResource(meshInfo);

		HrStreamData streamVertexBuffer;
		MakeVertexStream(meshInfo, streamVertexBuffer, vecVertexElement);

		HrMesh* pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(HrFileUtils::Instance()->ReplaceFileName(strFile, meshInfo.strMeshName)));
		m_vecMesh.push_back(pMesh);
		HrRenderLayout* pRenderLayout = pMesh->GetRenderLayout();
		pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
		pRenderLayout->SetTopologyType(TT_TRIANGLELIST);
		if (meshInfo.m_vecIndice.size() > 0)
		{
			pRenderLayout->BindIndexBuffer((const char*)(&meshInfo.m_vecIndice[0]), meshInfo.m_vecIndice.size() * sizeof(meshInfo.m_vecIndice[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);
		}
		ConnectMaterial();
	}
}

void HrModelLoader::FillEmptyModelInfo(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	BOOST_ASSERT(!meshInfo.m_vecPrimaryPos.empty());
	BOOST_ASSERT(!meshInfo.m_vecVertexPos.empty());
	CalculateAverageNormals(meshInfo);
}

void HrModelLoader::MakeMaterialResource(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	for (size_t i = 0; i < meshInfo.m_vecMaterialInfo.size(); ++i)
	{
		HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->AddMaterialResource(HrFileUtils::Instance()->ReplaceFileName(m_strFileName, meshInfo.m_vecMaterialInfo[i].strMaterialName)));
		HrModelDescInfo::HrMaterialInfo&  matInfo = meshInfo.m_vecMaterialInfo[i];
		pMaterial->FillMaterialInfo(matInfo.v3Ambient, matInfo.v3Diffuse, matInfo.v3Specular, matInfo.v3Emissive, matInfo.fOpacity);
		m_vecMaterial.push_back(pMaterial);
	}
}

void HrModelLoader::MakeVertexStream(HrModelDescInfo::HrMeshInfo& meshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < meshInfo.m_vecPrimaryPos.size(); ++nIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementUsage)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&meshInfo.m_vecPrimaryPos[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)&(meshInfo.m_vecNormal[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_COLOR:
			{
				streamData.AddBuffer((Byte*)&(meshInfo.m_vecColor[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}

		}
	}
}

void HrModelLoader::CalculateAverageNormals(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	if (meshInfo.m_vecVertexPos.size() > 0 && meshInfo.m_vecNormal.empty())
	{
		meshInfo.m_vecNormal.reserve(meshInfo.m_vecPrimaryPos.size());
		for (size_t i = 0; i < meshInfo.m_vecPrimaryPos.size(); ++i)
		{
			meshInfo.m_vecNormal.push_back(Vector3::Zero());
		}
		for (size_t i = 0; i < meshInfo.m_vecIndice.size(); i += 3)
		{
			uint16 nIndex1 = meshInfo.m_vecIndice[i];
			uint16 nIndex2 = meshInfo.m_vecIndice[i + 1];
			uint16 nIndex3 = meshInfo.m_vecIndice[i + 2];

			Vector3 vAB = meshInfo.m_vecPrimaryPos[nIndex2] - meshInfo.m_vecPrimaryPos[nIndex1];
			Vector3 vAC = meshInfo.m_vecPrimaryPos[nIndex3] - meshInfo.m_vecPrimaryPos[nIndex1];

			Vector3 vNormal = HrMath::Cross(vAC, vAB);

			meshInfo.m_vecNormal[nIndex1] += vNormal;
			meshInfo.m_vecNormal[nIndex2] += vNormal;
			meshInfo.m_vecNormal[nIndex3] += vNormal;
		}
		for (size_t i = 0; i < meshInfo.m_vecNormal.size(); ++i)
		{
			meshInfo.m_vecNormal[i] = HrMath::Normalize(meshInfo.m_vecNormal[i]);
		}
	}
}

void HrModelLoader::ConnectMaterial()
{
	//for (size_t i = 0; i < m_modelDesc.m_vecMaterialConnectInfo.size(); ++i)
	//{

	//}
}

