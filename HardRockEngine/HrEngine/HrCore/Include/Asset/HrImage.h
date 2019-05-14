#ifndef _HR_IMAGE_H_
#define _HR_IMAGE_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HR_CORE_API HrImage 
	{
	public:
		HrImage(const std::string& strFilePath);
		~HrImage();

		bool IsLoaded();

		const HrStreamDataPtr& GetData();
		EnumPixelFormat GetFormat();
		uint32 GetWidth();
		uint32 GetHeight();
		uint32 GetSrcPitch();
	protected:
		bool LoadFromFile(const std::string& strFilePath);
		bool Release();


	protected:
		bool m_bLoaded;

		uint32 m_nWidth;
		uint32 m_nHeight;
		uint32 m_nSrcPitch;
		EnumPixelFormat m_format;

		HrStreamDataPtr m_pTexData;
	};
}

#endif