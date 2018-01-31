#ifndef _HR_TEXTURE_H_
#define _HR_TEXTURE_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{
	class HR_CORE_API HrTexture : public HrResource
	{
	public:
		enum EnumTextureType
		{
			/// 1D texture, used in combination with 1D texture coordinates
			TEX_TYPE_1D = 1,
			/// 2D texture, used in combination with 2D texture coordinates (default)
			TEX_TYPE_2D = 2,
			/// 3D volume texture, used in combination with 3D texture coordinates
			TEX_TYPE_3D = 3,
			/// 3D cube map, used in combination with 3D texture coordinates
			TEX_TYPE_CUBE_MAP = 4,
			/// 2D texture array
			TEX_TYPE_2D_ARRAY = 5,
			/// 2D non-square texture, used in combination with 2D texture coordinates
			TEX_TYPE_2D_RECT = 6
		};

		/// Enums describing buffer usage; not mutually exclusive
		enum EnumTextureUsage
		{
			TU_GPUREAD_GPUWRITE,
			TU_GPUREAD_CPUWRITE,
			TU_GPUREAD_IMMUTABLE,
			TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};
	public:
		explicit HrTexture(EnumTextureType texType, uint32 nWidth, uint32 nHeight, uint32 nSampleCount, uint32 nSampleQuality);
		virtual ~HrTexture();


		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath);
		/** Returns the height of the texture.
		*/
		uint32 GetHeight(void) const { return m_nHeight; }

		/** Returns the width of the texture.
		*/
		uint32 GetWidth(void) const { return m_nWidth; }

		/** Returns the depth of the texture (only applicable for 3D textures).
		*/
		uint32 GetDepth(void) const { return m_nDepth; }

		EnumPixelFormat GetPixFormat(void) const { return m_format; }
	protected:
		virtual bool LoadImpl();
		virtual bool UnloadImpl();

		//virtual void CreateTexture() = 0;
		//virtual void CreateSRV() = 0;
	protected:
		uint32 m_nHeight;
		uint32 m_nWidth;
		uint32 m_nDepth;

		uint32 m_nSrcPitch;

		EnumTextureType m_textureType;
		uint32 m_nSampleCount;
		uint32 m_nSampleQuality;
		EnumPixelFormat m_format;
		EnumTextureUsage m_textureUsage;

		HrStreamDataPtr m_pTexData;

	};
}

#endif



