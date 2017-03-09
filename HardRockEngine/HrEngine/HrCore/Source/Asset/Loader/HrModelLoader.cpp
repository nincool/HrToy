#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrCore/Include/Asset/Loader/HrFBXLoader.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrMaterial.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Asset/HrTexture.h"
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

	//construct default vertexelement
	std::vector<HrVertexElement> vecVertexElement;
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	vecVertexElement.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));

	m_pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->GetOrAddResource(m_strFileName, HrResource::RT_MESH));
	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.meshInfo.vecSubMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDescInfo::HrSubMeshInfo& subMeshInfo = m_modelDesc.meshInfo.vecSubMeshInfo[nMeshInfoIndex];
		HrStreamData streamVertexBuffer;
		MakeVertexStream(subMeshInfo, streamVertexBuffer, vecVertexElement);
		HrSubMesh* pSubMesh = m_pMesh->AddSubMesh();
		HrRenderLayout* pRenderLayout = pSubMesh->GetRenderLayout();
		pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
		pRenderLayout->SetTopologyType(TT_TRIANGLELIST);

		//所有的模型统一材质
		//BOOST_ASSERT(subMeshInfo.vecMaterialInfo.size() == 1);
		//HrMaterial* pMaterial = HrResourceManager::Instance()->GetDefaultMaterial();//MakeMaterialResource(subMeshInfo.vecMaterialInfo[0]);
		//std::vector<HrTexture*> vecTextures = std::move(MakeTextureResource(subMeshInfo.vecTextureFileName));
		//pSubMesh->SetMaterial(pMaterial);
		//pSubMesh->SetTexture(vecTextures[0]);
	}
}

void HrModelLoader::FillEmptyModelInfo(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	HR_UNUSED(meshInfo);
}

HrMaterial* HrModelLoader::MakeMaterialResource(HrModelDescInfo::HrMaterialInfo& materialInfo)
{
	//换下Material的名字
	std::string strFilePath = HrFileUtils::Instance()->GetFilePath(m_strFileName);
	std::string strFileName = HrFileUtils::Instance()->GetFileName(m_strFileName);
	materialInfo.strMaterialName = strFilePath + "\\" + strFileName + "-" + materialInfo.strMaterialName;
	HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetResource(materialInfo.strMaterialName, HrResource::RT_MATERIAL));
	if (pMaterial == nullptr)
	{
		pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetOrAddResource(materialInfo.strMaterialName, HrResource::RT_MATERIAL));
		pMaterial->FillMaterialInfo(materialInfo.v4Ambient, materialInfo.v4Diffuse, materialInfo.v4Specular, materialInfo.v4Emissive, materialInfo.fOpacity);
	}

	return pMaterial;
}

std::vector<HrTexture*> HrModelLoader::MakeTextureResource(std::vector<std::string>& vecTextureFile)
{
	std::vector<HrTexture*> vecTexture;
	for (size_t nTexIndex = 0; nTexIndex < vecTextureFile.size(); ++nTexIndex)
	{
		std::string strAbsolutePath = HrFileUtils::Instance()->GetFullPathForFileName(vecTextureFile[nTexIndex]);
		HrTexture* pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strAbsolutePath));
		if (pTexture == nullptr)
		{
			pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strAbsolutePath, HrResource::RT_TEXTURE));
		}
		vecTexture.push_back(pTexture);
	} 
	return vecTexture; 
}

void HrModelLoader::MakeVertexStream(HrModelDescInfo::HrSubMeshInfo& subMeshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	//[POSITION,NORMAL,COLOR]
	for (size_t nIndex = 0; nIndex < subMeshInfo.vecVertexPos.size(); ++nIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementUsage)
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
			case VEU_TEXTURECOORD:
			{
				streamData.AddBuffer((Byte*)&(subMeshInfo.vecTexCoord[nIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}
		}
	}
}
