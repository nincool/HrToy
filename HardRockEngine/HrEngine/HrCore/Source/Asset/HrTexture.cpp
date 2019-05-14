#include "Asset/HrTexture.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrImage.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/FreeImage/Include/FreeImage.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"


using namespace Hr;

HrTexture::HrTexture(EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality, uint32 nAccessHint, uint32 nUsedFor):
	m_nWidth(0)
	, m_nHeight(0)
	, m_nDepth(0)
	, m_nMipMapsNum(1)
	, m_nArraySize(1)
	, m_textureType(texType)
	, m_nSampleCount(nSampleCount)
	, m_nSampleQuality(nSampleQuality)
	, m_nAccessHint(nAccessHint)
	, m_format(PF_R8G8B8A8)
	, m_textureUsage(TU_GPUREAD_IMMUTABLE)
	, m_nUsedFor(nUsedFor)
{
	if (m_nAccessHint & EAH_GPU_READ)
	{
		if (m_nAccessHint & EAH_CPU_WRITE)
		{
			if ((m_nAccessHint & EAH_GPU_WRITE) && (m_nAccessHint & EAH_GPU_WRITE))
			{
				m_textureUsage = HrTexture::TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE;
			}
			else
			{
				m_textureUsage = HrTexture::TU_GPUREAD_CPUWRITE;
			}
		}
		else if (m_nAccessHint & EAH_GPU_WRITE)
		{
			m_textureUsage = HrTexture::TU_GPUREAD_GPUWRITE;
		}
		else
		{
			m_textureUsage = HrTexture::TU_GPUREAD_IMMUTABLE;
		}
	}
}

HrTexture::~HrTexture()
{
}

size_t HrTexture::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrTexture::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resStatus = HrResource::RS_DECLARED;

	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrTexture::LoadImpl()
{
	if (m_nUsedFor & HrTexture::TUF_TEX_DEFAULTTEXTURE)
	{
		InitWithImageData();
	}


	return true;
}

bool HrTexture::UnloadImpl()
{
	return true;
}

void HrTexture::CreateHWResource(std::vector<std::shared_ptr<HrImage> >& vecImage)
{
}

void HrTexture::InitWithImageData()
{

	switch (m_textureType)
	{
	case HrTexture::TEX_TYPE_2D:
	{
		std::shared_ptr<HrImage> pImage = HrMakeSharedPtr<HrImage>(m_strFilePath);
		std::vector<std::shared_ptr<HrImage> > vecImage(1, pImage);
		if (pImage->IsLoaded())
		{
			CreateHWResource(vecImage);
		}
		break;
	}
	case HrTexture::TEX_TYPE_CUBE_MAP:
	{
		std::string strContentData = HrFileUtils::Instance()->GetFileString(m_strFilePath);
		rapidjson::Document d;
		d.Parse<0>(strContentData.c_str());
		if (d.HasParseError())
		{
			int nErrorCode = d.GetParseError();
			size_t nOffset = d.GetErrorOffset();
			HRERROR("HrTexture::InitWithImageData Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
			return;
		}

		std::array<std::string, 6> vecTextureFile;
		vecTextureFile[0] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_POS_X"].GetString());
		vecTextureFile[1] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_NEG_X"].GetString());
		vecTextureFile[2] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_POS_Y"].GetString());
		vecTextureFile[3] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_NEG_Y"].GetString());
		vecTextureFile[4] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_POS_Z"].GetString());
		vecTextureFile[5] = HrFileUtils::Instance()->GetFullPathForFileName(d["SKY_TEX_NEG_Z"].GetString());

		std::vector<std::shared_ptr<HrImage> > vecImage;
		for (int i = 0; i < vecTextureFile.size(); ++i)
		{
			std::shared_ptr<HrImage> pIamge = HrMakeSharedPtr<HrImage>(vecTextureFile[i]);
			vecImage.push_back(pIamge);
		}
		CreateHWResource(vecImage);
		break;
	}
	}
}

