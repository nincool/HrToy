#include "HrCore/Include/Asset/Loader/HrModelLoader.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
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
	vecVertexElement.push_back(HrVertexElement(VEU_TEXTURECOORD, VET_FLOAT2));


	m_pMesh = static_cast<HrMesh*>(HrResourceManager::Instance()->AddMeshResource(strFile));
	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.meshInfo.vecSubMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDescInfo::HrSubMeshInfo& subMeshInfo = m_modelDesc.meshInfo.vecSubMeshInfo[nMeshInfoIndex];
		HrStreamData streamVertexBuffer;
		MakeVertexStream(subMeshInfo, streamVertexBuffer, vecVertexElement);
		HrSubMesh* pSubMesh = m_pMesh->AddSubMesh();
		HrRenderLayout* pRenderLayout = pSubMesh->GetRenderLayout();
		pRenderLayout->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);
		pRenderLayout->SetTopologyType(TT_TRIANGLELIST);

		BOOST_ASSERT(subMeshInfo.vecMaterialInfo.size() == 1);
		HrMaterial* pMaterial = MakeMaterialResource(subMeshInfo.vecMaterialInfo[0]);
		std::vector<HrTexture*> vecTextures = std::move(MakeTextureResource(subMeshInfo.vecTextureFileName));
		pSubMesh->SetMaterial(pMaterial);
		pSubMesh->SetTexture(vecTextures[0]);
	}
}

void HrModelLoader::FillEmptyModelInfo(HrModelDescInfo::HrMeshInfo& meshInfo)
{
	HR_UNUSED(meshInfo);
}

HrMaterial* HrModelLoader::MakeMaterialResource(HrModelDescInfo::HrMaterialInfo& materialInfo)
{
	//»»ÏÂMaterialµÄÃû×Ö
	std::string strFilePath = HrFileUtils::Instance()->GetFilePath(m_strFileName);
	std::string strFileName = HrFileUtils::Instance()->GetFileName(m_strFileName);
	materialInfo.strMaterialName = strFilePath + "\\" + strFileName + "-" + materialInfo.strMaterialName;
	HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->AddMaterialResource(materialInfo.strMaterialName));
	pMaterial->FillMaterialInfo(materialInfo.v4Ambient, materialInfo.v4Diffuse, materialInfo.v4Specular, materialInfo.v4Emissive, materialInfo.fOpacity);
	return pMaterial;
}

std::vector<HrTexture*> HrModelLoader::MakeTextureResource(std::vector<std::string>& vecTextureFile)
{
	std::vector<HrTexture*> vecTexture;
	for (size_t nTexIndex = 0; nTexIndex < vecTextureFile.size(); ++nTexIndex)
	{
		std::string strAbsolutePath = HrFileUtils::Instance()->ReplaceFileName(m_strFileName, vecTextureFile[nTexIndex]);
		HrTexture* pRes = static_cast<HrTexture*>(HrResourceManager::Instance()->LoadResource(strAbsolutePath, HrResource::RT_TEXTURE));
		vecTexture.push_back(pRes);
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
