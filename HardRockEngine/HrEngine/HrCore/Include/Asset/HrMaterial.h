#ifndef _HR_MATERIAL_H_
#define _HR_MATERIAL_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HrMaterial : public HrResource
	{
	public:
		enum EnumMaterialTexSlot
		{
			TS_SLOT_0,
			TS_SLOT_1,
			TS_SLOT_2,
			TS_SLOT_3,
			TS_SLOT_4,
			TS_SLOT_5,
			TS_SLOT_6,
			TS_SLOT_7,

			TS_SLOT_NUM
		};
	public:
		HrMaterial();
		HrMaterial(const HrMaterial& material);
		HrMaterial(const HrMaterialPtr& pMaterial);
		~HrMaterial();

		static size_t CreateHashName(const std::string& strHashValue);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		void FillMaterialInfo(const float4& ambient, const float4& diffuse, const float4& specular, const float4& emissive, float fOpacity);

		const float4& GetAmbient() const;
		const float4& GetDiffuse() const;
		const float4& GetSpecular() const;
		const float4& GetEmissive() const;
		float GetOpacity() const;

		void SetTexture(EnumMaterialTexSlot tsSlot, const HrTexturePtr& pTexture);
		const HrTexturePtr& GetTexture(EnumMaterialTexSlot stSlot);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		std::string m_strMaterialName;

		//the amount of ambient light the surface reflects and absorbs
		float4 m_ambient;
		//the amount of diffuse light the surface reflects and absorbs
		float4 m_diffuse;
		//the amount of specular light the surface reflects and absorbs
		float4 m_specular;
		//The colour of light emitted from the object
		float4 m_emissive;

		float m_fOpacity;

		std::array<HrTexturePtr, TS_SLOT_NUM> m_arrTextures;
	};
}


#endif



