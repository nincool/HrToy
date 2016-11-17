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

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		float4 m_ambient;
		float4 m_diffuse;
		float4 m_specular;
		float4 m_emissive;

		float m_fOpacity;
		float m_fPower;
	};
}


#endif



