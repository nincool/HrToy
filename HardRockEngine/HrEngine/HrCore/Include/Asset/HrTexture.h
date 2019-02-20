#ifndef _HR_TEXTURE_H_
#define _HR_TEXTURE_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Render/HrDataDefine.h"

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
		//Resource  Usage	    Default	    Dynamic	  Immutable	Staging
		//	GPU - Read          yes           yes         yes         yes¹
		//	GPU - Write	      yes                                   yes¹
		//	CPU - Read                                                yes¹
		//	CPU - Write                       yes                     yes¹
		  
		enum EnumTextureUsage
		{
			TU_GPUREAD_GPUWRITE,
			TU_GPUREAD_CPUWRITE,
			TU_GPUREAD_IMMUTABLE,
			TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};

		enum EnumElementAccessHint
		{
			EAH_CPU_READ = 1,
			EAH_CPU_WRITE = 1 << 2,
			EAH_GPU_READ = 1 << 3,
			EAH_GPU_WRITE = 1 << 4,
		};

		enum EnumTextureUsedFor
		{
			TUF_TEX_DEFAULTTEXTURE = 1 << 0,
			TUF_TEX_RENDERTARGETVIEW = 1 << 1,
			TUF_TEX_DEPTHSTENCILVIEW = 1 << 2,
			TUF_TEX_SHADERRESOURCEVIEW = 1 << 3
		};
	public:
		explicit HrTexture(EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality, uint32 nAccessHint, uint32 nUsedFor);
		virtual ~HrTexture();


		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath);

		void SetTextureType(EnumTextureType type);
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

		virtual void CreateHWResource(HrImage* pImage = nullptr);
	protected:
		virtual bool LoadImpl();
		virtual bool UnloadImpl();


		void InitWithImageData();
	protected:
		uint32 m_nWidth;
		uint32 m_nHeight;
		uint32 m_nDepth;


		uint32 m_nMipMapsNum;
		uint32 m_nArraySize;

		EnumTextureType m_textureType;
		uint32 m_nSampleCount;
		uint32 m_nSampleQuality;
		uint32 m_nAccessHint;
		uint32 m_nUsedFor;

		EnumPixelFormat m_format;

		EnumTextureUsage m_textureUsage;
	};
}

#endif



