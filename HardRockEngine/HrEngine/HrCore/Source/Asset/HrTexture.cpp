#include "Asset/HrTexture.h"

using namespace Hr;

HrTexture::HrTexture(EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality):
	m_textureType(texType), m_nSampleCount(nSampleCount), m_nSampleQuality(nSampleQuality)
{
}

HrTexture::~HrTexture()
{

}


