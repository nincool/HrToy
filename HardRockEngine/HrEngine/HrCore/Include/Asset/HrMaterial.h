#ifndef _HR_MATERIAL_H_
#define _HR_MATERIAL_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HrMaterial : public HrResource
	{
	public:
		HrMaterial();
		~HrMaterial();

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		void BuildToDefultMaterial();

		void FillMaterialInfo(const float4& ambient, const float4& diffuse, const float4& specular, const float4& emissive, float fOpacity);

		const float4& GetAmbient() const;
		const float4& GetDiffuse() const;
		const float4& GetSpecular() const;
		const float4& GetEmissive() const;
		float GetOpacity() const;
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		//the amount of ambient light the surface reflects and absorbs
		float4 m_ambient;
		//the amount of diffuse light the surface reflects and absorbs
		float4 m_diffuse;
		//the amount of specular light the surface reflects and absorbs
		float4 m_specular;
		//The colour of light emitted from the object
		float4 m_emissive;

		float m_fOpacity;
	};
}


#endif



