#ifndef _HR_LIGHT_H_
#define _HR_LIGHT_H_

#include "HrCommon.h"

namespace HR
{
	class CHrLight
	{
	public:
		CHrLight();
		~CHrLight();

	public:
		void            ResetLight();
		D3DLIGHT9*      GetLight();

		void            SetLightType(D3DLIGHTTYPE lightType);
		/**
		 *	@Brief: 设置下光照颜色 [7/23/2014 By Hr]
		*/
		void            SetDiffuseColor(D3DXCOLOR color);
		void            SetAmbientColor(D3DXCOLOR color);
		void            SetSpecularColor(D3DXCOLOR color);
		/**
		 *	@Brief: 设置光照范围 [7/23/2014 By Hr]
		*/
		void            SetRange(float fRange);
		/**
		 *	@Brief: 这个值只能用在聚光灯上。
					 它定义灯光在从内圆锥到外圆锥之间的强度衰减。它
					 的值通常设置为1.0f [7/23/2014 By Hr]
		*/
		void            SetFalloff(float fFalloff);
		/**
		 *	@Brief:  只用于聚光灯；指定内圆锥的角度，单位是弧度 [7/23/2014 By Hr]
		*/
		void            SetTheta(float fTheta);
		/**
		 *	@Brief:  只用于聚光灯；指定外圆锥的角度，单位是弧度 [7/23/2014 By Hr]
		*/
		void            SetPhi(float fPhi);
		/**
		 *	@Brief: 这些衰减变量被用来定义灯光强度的传播距离衰
					 减。它们只被用于点光源和聚光灯上
					 Attenuation = 1/(A0 + A1*D + A2*pow(D,2)) [7/23/2014 By Hr]
		*/
		void            SetAttenuation0(float fAttenuation);
		void            SetAttenuation1(float fAttenuation);
		void            SetAttenuation2(float fAttenuation);
		/**
		 *	@Brief: 设置灯光的位置 [7/23/2014 By Hr]
		*/
		void            SetLightPosition(D3DVECTOR vPos);
		/**
		 *	@Brief: 设置平行光点光源的朝向 [7/23/2014 By Hr]
		*/
		void            SetLightDirection(D3DVECTOR vDirection);
	private:
		D3DLIGHT9       m_stLight;
	};

}

#endif

