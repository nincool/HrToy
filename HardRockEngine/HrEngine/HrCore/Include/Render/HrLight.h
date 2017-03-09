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

	protected:
		EnumLightType m_lightType;
		Vector3 m_v3Direction;

		HrColor m_diffuse;
		HrColor m_specular;
	};

	class HrDirectionalLight : public HrLight
	{
	public:
		HrDirectionalLight();
		HrDirectionalLight(const Vector3 v3Direction, const HrColor& diffuse, const HrColor& specular);
		virtual ~HrDirectionalLight();
	};
}


#endif



