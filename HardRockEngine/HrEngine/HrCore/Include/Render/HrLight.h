#ifndef _HR_LIGHT_H_
#define _HR_LIGHT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrLight
	{
	public:
		enum EnumLightType
		{
			LT_POINT = 0,
			LT_DIRECTIONAL,
			LT_SPOTLIGHT,

			LT_LIGHTTYPE_NUM,
		};
	public:
		HrLight();
		virtual ~HrLight();

		EnumLightType LightType();

		void SetDirection(const Vector3& v3Direction);
		const Vector3& GetDirection() const;

		void SetDiffuse(const HrColor& diffuse);
		const HrColor& GetDiffuse() const;
		void SetSpecular(const HrColor& specular);
		const HrColor& GetSpecular() const;

		void SetAttenuation(float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2);
		float GetAttenuationRange() const;
		float GetAttenuation0() const;
		float GetAttenuation1() const;
		float GetAttenuation2() const;
		
		void AttachLightNode(HrLightNode* pLightNode);
		HrLightNode* GetAttachLightNode() const;
	protected:
		EnumLightType m_lightType;
		Vector3 m_v3Direction;

		HrColor m_diffuse;
		HrColor m_specular;

		float m_fRange;
		float m_fAttenuation0;
		float m_fAttenuation1;
		float m_fAttenuation2;

		HrLightNode* m_pAttachNode;
	};

	class HrDirectionalLight : public HrLight
	{
	public:
		HrDirectionalLight();
		HrDirectionalLight(const Vector3 v3Direction, const HrColor& diffuse, const HrColor& specular);
		virtual ~HrDirectionalLight();
	};

	class HrPointLight : public HrLight
	{
	public:
		HrPointLight();
		HrPointLight(const HrColor& diffuse, const HrColor& specular, float fRange, float fAttenuation0, float fAttenuation1, float fAttenuation2);
		virtual ~HrPointLight();


	};
}


#endif



