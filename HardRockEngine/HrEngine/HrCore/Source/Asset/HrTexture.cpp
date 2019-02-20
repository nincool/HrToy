#include "Asset/HrTexture.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrImage.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "ThirdParty/FreeImage/Include/FreeImage.h"

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
	m_strFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFilePath);
	HRASSERT(!m_strFilePath.empty(), "HrTexture::DeclareResource");
	m_strFileName = strFileName;
	m_resStatus = HrResource::RS_DECLARED;

	m_nHashID = CreateHashName(m_strFilePath);
}

void HrTexture::SetTextureType(EnumTextureType type)
{
	m_textureType = type;
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

void HrTexture::CreateHWResource(HrImage* pImage)
{
}

void HrTexture::InitWithImageData()
{
	std::shared_ptr<HrImage> m_pImage = HrMakeSharedPtr<HrImage>(m_strFilePath);
	if (m_pImage->IsLoaded())
	{
		m_format = m_pImage->GetFormat();
		CreateHWResource(m_pImage.get());
	}
}

