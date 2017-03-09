#include "Asset/HrMaterial.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

using namespace Hr;

HrMaterial::HrMaterial()
{
	m_fOpacity = 0.0f;
}

HrMaterial::~HrMaterial()
{

}

size_t HrMaterial::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrMaterial::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFileName = strFileName;
	m_strFilePath = strFilePath;
	m_resType = HrResource::RT_MATERIAL;
	m_nHashID = CreateHashName(strFilePath);
}

bool HrMaterial::LoadImpl()
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(m_strFilePath);
	if (strFullPath.length() <= 0)
	{
		HRERROR("HrMaterial::LoadImpl Error! fileName[%s]", m_strFilePath.c_str());
		return false;
	}
	HrStreamDataPtr pStreamData = HrFileUtils::Instance()->GetFileData(strFullPath);
	rapidjson::Document d;
	d.Parse<0>(pStreamData->GetBufferPoint());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrMaterial::LoadImpl Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
		return false;
	}

	const rapidjson::Value& sceneRootInfo = d["MATERIAL_ROOT"];

	std::vector<uint8> vAmbient = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["AMBIENT"].GetString());
	std::vector<uint8> vDiffuse = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["DIFFUSE"].GetString());
	std::vector<uint8> vSpecular = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["SPECULAR"].GetString());
	std::vector<uint8> vEmissive = HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["EMISSIVE"].GetString());
	m_ambient = HrMath::MakeColor(vAmbient).Value();
	m_diffuse = HrMath::MakeColor(vDiffuse).Value();
	m_specular = HrMath::MakeColor(vSpecular).Value();
	m_emissive = HrMath::MakeColor(vEmissive).Value();
	
	m_fOpacity= sceneRootInfo["OPACITY"].GetFloat();

	return true;
}

bool HrMaterial::UnloadImpl()
{
	return true;
}

void HrMaterial::FillMaterialInfo(const float4& ambient, const float4& diffuse, const float4& specular, const float4& emissive, float fOpacity)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_emissive = emissive;
	m_fOpacity = fOpacity;
}

const float4& HrMaterial::GetAmbient() const
{
	return m_ambient;
}

const float4& HrMaterial::GetDiffuse() const
{
	return m_diffuse;
}

const float4& HrMaterial::GetSpecular() const
{
	return m_specular;
}

const float4& HrMaterial::GetEmissive() const
{
	return m_emissive;
}

float HrMaterial::GetOpacity() const
{
	return m_fOpacity;
}
