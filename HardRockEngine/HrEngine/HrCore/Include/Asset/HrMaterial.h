#ifndef _HR_MATERIAL_H_
#define _HR_MATERIAL_H_

#include "HrCore/Include/Asset/HrResource.h"
#include "HrCore/Include/Asset/Loader/HrModelLoader.h"

namespace Hr
{
	class HR_CORE_API HrMaterial : public HrResource
	{
	public:
		enum EnumMaterialTexSlot
		{
			//NormalTexture
			TS_ALBEDO,
			TS_METALNESS,
			TS_GLOSSINESS,
			TS_EMISSIVE,
			TS_NORMAL,
			TS_HEIGHT,
			TS_BUMP,
			TS_NUMTEXTURESLOTS,
		};
	public:
		HrMaterial();
		HrMaterial(const HrMaterial& material);
		HrMaterial(const HrMaterialPtr& pMaterial);
		~HrMaterial();

		static size_t CreateHashName(const std::string& strHashValue);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		void FillMaterialInfo(const HrModelDataInfo::HrMaterialDataInfo& materialDataInfo);

		const float4& GetAlebdo() const;
		const float4& GetEmissive() const;
		void SetGlossiness(float fGls);
		float GetGlossiness() const;
		float GetOpacity() const;


		void SetTexture(EnumMaterialTexSlot tsSlot, const HrTexturePtr& pTexture);
		const HrTexturePtr& GetTexture(EnumMaterialTexSlot stSlot);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		std::string m_strMaterialName;

		//the amount of light the surface reflects and absorbs
		float4 m_albedo;
		//The colour of light emitted from the object
		float4 m_emissive;

		float m_fGlossiness;

		float m_fOpacity;

		std::array<HrTexturePtr, TS_NUMTEXTURESLOTS> m_arrTextures;
	};
}


#endif



