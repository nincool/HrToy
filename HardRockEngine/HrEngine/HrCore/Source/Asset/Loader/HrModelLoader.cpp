#include "Asset/Loader/HrModelLoader.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentResource.h"
#include "Asset/Loader/HrFBXLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrMesh.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrTexture.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrVertex.h"
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
	m_strFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	if (m_strFileName.empty())
	{
		HRERROR("HrModelLoader::Load Error! Can not find the file. FileName[%s]", strFile.c_str());
		return;
	}
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(m_strFileName);
	HrStringUtil::ToLowerCase(strSuffix);
	if (strSuffix == "fbx")
	{
		std::shared_ptr<HrFBXLoader> pFBXLoader = HrMakeSharedPtr<HrFBXLoader>();
		pFBXLoader->Load(m_strFileName, m_modelDesc);
	}
	else
	{
		TRE("unsuported types!");
		return;
	}

	//construct default vertexelement
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));

	m_pMesh = HrDirector::Instance()->GetResCoreComponent()->RetriveResource<HrMesh>(m_strFileName);
	BOOST_ASSERT(!m_pMesh->IsLoaded());
	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.vecSubMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDescInfo::HrSubMeshInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nMeshInfoIndex];
		HrStreamData streamVertexBuffer;
		MakeVertexStream(subMeshInfo, streamVertexBuffer, vecVertexElement);
		
		HrSubMeshPtr pSubMesh = m_pMesh->AddSubMesh(subMeshInfo.strMeshName);
		pSubMesh->GetRenderLayout()->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);

		//todo material
		HrMaterialPtr pMaterial = HrDirector::Instance()->GetResCoreComponent()->RetriveResource<HrMaterial>("");
		pSubMesh->SetMaterial(pMaterial);
	}
}

void HrModelLoader::FillEmptyModelInfo()
{

}

HrMaterial* HrModelLoader::MakeMaterialResource(HrModelDescInfo::HrMaterialInfo& materialInfo)
{
	//»»ÏÂMaterialµÄÃû×Ö
	//std::string strFilePath = HrFileUtils::Instance()->GetFilePath(m_strFileName);
	//std::string strFileName = HrFileUtils::Instance()->GetFileName(m_strFileName);
	//materialInfo.strMaterialName = strFilePath + "\\" + strFileName + "-" + materialInfo.strMaterialName;
	//HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetResource(materialInfo.strMaterialName, HrResource::RT_MATERIAL));
	//if (pMaterial == nullptr)
	//{
	//	pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetOrAddResource(materialInfo.strMaterialName, HrResource::RT_MATERIAL));
	//	pMaterial->FillMaterialInfo(materialInfo.v4Ambient, materialInfo.v4Diffuse, materialInfo.v4Specular, materialInfo.v4Emissive, materialInfo.fOpacity);
	//}

	//return pMaterial;
	return nullptr;
}

std::vector<HrTexture*> HrModelLoader::MakeTextureResource(std::vector<std::string>& vecTextureFile)
{
	std::vector<HrTexture*> vecTexture;
	//for (size_t nTexIndex = 0; nTexIndex < vecTextureFile.size(); ++nTexIndex)
	//{
	//	std::string strAbsolutePath = HrFileUtils::Instance()->GetFullPathForFileName(vecTextureFile[nTexIndex]);
	//	HrTexture* pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strAbsolutePath));
	//	if (pTexture == nullptr)
	//	{
	//		pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strAbsolutePath, HrResource::RT_TEXTURE));
	//	}
	//	vecTexture.push_back(pTexture);
	//} 
	return vecTexture; 
}

void HrModelLoader::MakeVertexStream(HrModelDescInfo::HrSubMeshInfo& subMeshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < subMeshInfo.vecVertexPos.size(); ++nIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementSemantic)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecVertexPos[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.vecNormal[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_COLOR:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.vecColor[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_TEXTURE_COORDINATES:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.vecUV[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}
		}
	}
}
