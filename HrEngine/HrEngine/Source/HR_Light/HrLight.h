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
		 *	@Brief: �����¹�����ɫ [7/23/2014 By Hr]
		*/
		void            SetDiffuseColor(D3DXCOLOR color);
		void            SetAmbientColor(D3DXCOLOR color);
		void            SetSpecularColor(D3DXCOLOR color);
		/**
		 *	@Brief: ���ù��շ�Χ [7/23/2014 By Hr]
		*/
		void            SetRange(float fRange);
		/**
		 *	@Brief: ���ֵֻ�����ھ۹���ϡ�
					 ������ƹ��ڴ���Բ׶����Բ׶֮���ǿ��˥������
					 ��ֵͨ������Ϊ1.0f [7/23/2014 By Hr]
		*/
		void            SetFalloff(float fFalloff);
		/**
		 *	@Brief:  ֻ���ھ۹�ƣ�ָ����Բ׶�ĽǶȣ���λ�ǻ��� [7/23/2014 By Hr]
		*/
		void            SetTheta(float fTheta);
		/**
		 *	@Brief:  ֻ���ھ۹�ƣ�ָ����Բ׶�ĽǶȣ���λ�ǻ��� [7/23/2014 By Hr]
		*/
		void            SetPhi(float fPhi);
		/**
		 *	@Brief: ��Щ˥����������������ƹ�ǿ�ȵĴ�������˥
					 ��������ֻ�����ڵ��Դ�;۹����
					 Attenuation = 1/(A0 + A1*D + A2*pow(D,2)) [7/23/2014 By Hr]
		*/
		void            SetAttenuation0(float fAttenuation);
		void            SetAttenuation1(float fAttenuation);
		void            SetAttenuation2(float fAttenuation);
		/**
		 *	@Brief: ���õƹ��λ�� [7/23/2014 By Hr]
		*/
		void            SetLightPosition(D3DVECTOR vPos);
		/**
		 *	@Brief: ����ƽ�й���Դ�ĳ��� [7/23/2014 By Hr]
		*/
		void            SetLightDirection(D3DVECTOR vDirection);
	private:
		D3DLIGHT9       m_stLight;
	};

}

#endif

