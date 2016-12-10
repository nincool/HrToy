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

	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.m_vecMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDescInfo::HrMeshInfo& meshInfo = m_modelDesc.m_vecMeshInfo[nMeshInfoIndex];

		FillEmptyModelInfo(meshInfo);

		//Add Material Res
		MakeMaterialResource(meshInfo);

		HrMesh* pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(HrFileUtils::Instance()->ReplaceFileName(strFile, meshInfo.strMeshName)));
		m_vecMesh.push_back(pMesh);
		for (size_t i = 0; i < meshInfo.m_vecSubMeshInfo.size(); ++i)
		{
			HrStreamData streamVertexBuffer;
			MakeVertexStream(meshInfo.m_vecSubMeshInfo[i], streamVertexBuffer, vecVertexElement);

			HrSubMesh* pSubMesh = pMesh->AddSubMesh();
			HrRenderLayout* pRenderLayout = pSubMesh->GetRenderLayout();
			pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
			pRenderLayout->SetTopologyType(TT_TRIANGLELIST);
			if (meshInfo.m_vecSubMeshInfo[i].m_vecIndice.size() > 0)
			{
				pRenderLayout->BindIndexBuffer((const char*)(&meshInfo.m_vecSubMeshInfo[i].m_vecIndice[0]), meshInfo.m_vecSubMeshInfo[i].m_vecIndice.size() * sizeof(meshInfo.m_vecSubMeshInfo[i].m_vecIndice[0]), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);
			}
			pSubMesh->SetMaterial(m_vecMaterial[meshInfo.m_vecSubMeshInfo[i].nMaterialIndex]);
		}
	}
}

void HrModelLoader::FillEmptyModelInfo(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	HR_UNUSED(meshInfo);
}

void HrModelLoader::MakeMaterialResource(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	for (size_t i = 0; i < meshInfo.m_vecMaterialInfo.size(); ++i)
	{
		HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->AddMaterialResource(HrFileUtils::Instance()->ReplaceFileName(m_strFileName, meshInfo.m_vecMaterialInfo[i].strMaterialName)));
		HrModelDescInfo::HrMaterialInfo&  matInfo = meshInfo.m_vecMaterialInfo[i];
		pMaterial->FillMaterialInfo(matInfo.v4Ambient, matInfo.v4Diffuse, matInfo.v4Specular, matInfo.v4Emissive, matInfo.fOpacity);
		m_vecMaterial.push_back(pMaterial);
	}
}

void HrModelLoader::MakeVertexStream(HrModelDescInfo::HrSubMeshInfo& subMeshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < subMeshInfo.m_vecPrimaryPos.size(); ++nIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementUsage)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.m_vecPrimaryPos[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.m_vecNormal[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_COLOR:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.m_vecColor[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}

		}
	}
}
