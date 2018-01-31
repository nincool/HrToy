#include "Asset/HrTexture.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "ThirdParty/FreeImage/Include/FreeImage.h"

using namespace Hr;

HrTexture::HrTexture(EnumTextureType texType, uint32 nWidth, uint32 nHeight, uint32 nSampleCount, uint32 nSampleQuality):
	m_textureType(texType)
	, m_nWidth(nWidth)
	, m_nHeight(nHeight)
	, m_nSampleCount(nSampleCount)
	, m_nSampleQuality(nSampleQuality)
	, m_pTexData(HrMakeSharedPtr<HrStreamData>())
{
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
	m_resType = HrResource::RT_TEXTURE;

	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrTexture::LoadImpl()
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	fif = FreeImage_GetFileType(m_strFilePath.c_str());

	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(m_strFilePath.c_str());
	}
	else if (FreeImage_FIFSupportsReading(fif))
	{
		FIBITMAP* dib = FreeImage_Load(fif, m_strFilePath.c_str());

		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(dib);
		BOOST_ASSERT(imageType == FIT_BITMAP);
		unsigned int nBPP = FreeImage_GetBPP(dib);
		if (nBPP != 32)
		{
			FIBITMAP* newDib = FreeImage_ConvertTo32Bits(dib);
			FreeImage_Unload(dib);
			dib = newDib;
			nBPP = FreeImage_GetBPP(dib);
		}
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
		m_format = PF_R8G8B8A8;
#else
		m_format = PF_B8G8R8A8;
#endif
		m_nWidth = FreeImage_GetWidth(dib);
		m_nHeight = FreeImage_GetHeight(dib);

		unsigned char* pSrcData = FreeImage_GetBits(dib);
		m_nSrcPitch = FreeImage_GetPitch(dib);

		m_pTexData->ClearBuffer();
		for (size_t y = 0; y < m_nHeight; ++y)
		{
			unsigned char* pSrc = pSrcData + (m_nHeight - y - 1) * m_nSrcPitch;
			m_pTexData->AddBuffer((Byte*)pSrc, m_nSrcPitch);
		}

		FreeImage_Unload(dib);

		//CreateTexture();
		//CreateSRV();
	}

	return true;
}

bool HrTexture::UnloadImpl()
{
	return true;
}

