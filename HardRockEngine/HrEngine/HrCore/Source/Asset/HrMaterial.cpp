#include "Asset/HrMaterial.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrTexture.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"


using namespace Hr;

HrMaterial::HrMaterial()
{
	m_fOpacity = 0.0f;
	m_fMetalness = std::numeric_limits<float>::min();
	m_fRoughness = std::numeric_limits<float>::min();
	m_arrTextures.assign(nullptr);
}

HrMaterial::HrMaterial(const HrMaterial& material)
{
	m_strMaterialName = material.m_strMaterialName;

	m_albedo = material.m_albedo;
	m_emissive = material.m_emissive;
	m_fMetalness = material.m_fMetalness;
	m_fRoughness = material.m_fRoughness;
	m_fOpacity = material.m_fOpacity;
	m_arrTextures = material.m_arrTextures;
	
	DeclareResource(material.m_strFileName, material.m_strFilePath);
}

HrMaterial::HrMaterial(const HrMaterialPtr& pMaterial)
{
	m_strMaterialName = pMaterial->m_strMaterialName;

	m_albedo = pMaterial->m_albedo;
	m_emissive = pMaterial->m_emissive;
	m_fMetalness = pMaterial->m_fMetalness;
	m_fRoughness = pMaterial->m_fRoughness;
	m_fOpacity = pMaterial->m_fOpacity;
	m_arrTextures = pMaterial->m_arrTextures;

	DeclareResource(pMaterial->m_strFileName, pMaterial->m_strFilePath);
}

HrMaterial::~HrMaterial()
{
}

size_t HrMaterial::CreateHashName(const std::string& strHashValue)
{
	return HrHashValue(strHashValue);
}

void HrMaterial::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFileName = strFileName;
	m_strFilePath = strFilePath;
	m_strMaterialName = HrFileUtils::Instance()->GetFileName(m_strFileName);
	m_resType = HrResource::RT_MATERIAL;
	m_resStatus = HrResource::RS_DECLARED;
	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrMaterial::LoadImpl()
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(m_strFilePath);
	if (strFullPath.length() <= 0)
	{
		//Make Default Material
	}
	else
	{
		std::string strContentData = HrFileUtils::Instance()->GetFileString(strFullPath);
		rapidjson::Document d;
		d.Parse<0>(strContentData.c_str());
		if (d.HasParseError())
		{
			int nErrorCode = d.GetParseError();
			size_t nOffset = d.GetErrorOffset();
			HRERROR("HrMaterial::LoadImpl Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
			return false;
		}

		const rapidjson::Value& sceneRootInfo = d["MATERIAL_ROOT"];

		std::vector<uint8> vDiffuse = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["DIFFUSE"].GetString());
		std::vector<uint8> vEmissive = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["EMISSIVE"].GetString());
		m_albedo = HrMath::MakeColor(vDiffuse).Value();
		m_emissive = HrMath::MakeColor(vEmissive).Value();

		m_fOpacity = sceneRootInfo["OPACITY"].GetFloat();
	}
	m_resStatus = HrResource::RS_LOADED;

	return true;
}

bool HrMaterial::UnloadImpl()
{
	return true;
}

void HrMaterial::FillMaterialInfo(const HrModelDataInfo::HrMaterialDataInfo& materialDataInfo)
{
	for (size_t i = 0; i < materialDataInfo.m_arrTexNames.size(); ++i)
	{
		std::string strTextureName = materialDataInfo.m_arrTexNames[i];
		if (strTextureName.size() > 0)
		{
			m_arrTextures[i] = HrDirector::Instance()->GetResourceModule()->RetriveTexture(strTextureName, HrTexture::TEX_TYPE_2D);
		}
	}
}

const float4& HrMaterial::GetAlebdo() const
{
	return m_albedo;
}

const float4& HrMaterial::GetEmissive() const
{
	return m_emissive;
}

float HrMaterial::GetOpacity() const
{
	return m_fOpacity;
}

void HrMaterial::SetTexture(EnumMaterialTexSlot tsSlot, const HrTexturePtr& pTexture)
{
	m_arrTextures[tsSlot] = pTexture;
}

const HrTexturePtr& HrMaterial::GetTexture(EnumMaterialTexSlot tsSlot)
{
	return m_arrTextures[tsSlot];
}

void HrMaterial::SetAlbedo(const float4& albedo)
{
	m_albedo = albedo;
}

void HrMaterial::SetEmissive(const float4& emissive)
{
	m_emissive = emissive;
}

void HrMaterial::CopyFrom(const HrMaterialPtr& pMaterial)
{
	InitMaterialData(pMaterial.get());
}

void HrMaterial::SetMetalness(float fMetalness)
{
	m_fMetalness = fMetalness;
}

float HrMaterial::GetMetalness() const
{
	return m_fMetalness;
}

void HrMaterial::SetRoughness(float fRoughness)
{
	m_fRoughness = fRoughness;
}

float HrMaterial::GetRoughness() const
{
	return m_fRoughness;
}

void HrMaterial::InitMaterialData(const HrMaterial* pMaterial)
{
	m_albedo = pMaterial->m_albedo;
	m_emissive = pMaterial->m_emissive;
	m_fMetalness = pMaterial->m_fMetalness;
	m_fRoughness = pMaterial->m_fRoughness;
	m_fOpacity = pMaterial->m_fOpacity;
	m_arrTextures = pMaterial->m_arrTextures;
}
