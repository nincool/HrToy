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

		void FillMaterialInfo(const float3& ambient, const float3& diffuse, const float3& specular, const float3& emissive, float fOpacity);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		//the amount of ambient light the surface reflects and absorbs
		float3 m_ambient;
		//the amount of diffuse light the surface reflects and absorbs
		float3 m_diffuse;
		//the amount of specular light the surface reflects and absorbs
		float3 m_specular;
		//The colour of light emitted from the object
		float3 m_emissive;

		float m_fOpacity;
	};
}


#endif



