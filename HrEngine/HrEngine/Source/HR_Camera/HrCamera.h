#ifndef _HR_CAMERA_H_
#define _HR_CAMERA_H_

#include "HrCommon.h"

namespace HR
{
	class CHrCamera
	{
	public:
		CHrCamera();
		~CHrCamera();

	public:
		void            Initialize(IDirect3DDevice9* pD3DDevice);

		/**
		 *	@Brief:  ����ȡ���任����[7/15/2014 By Hr]
		*/
		void            CalculateViewMatrix(D3DXMATRIX* pViewMatrix);
		/**
		 *	@Brief: ���ù۲췽���λ�� [7/15/2014 By Hr]
		*/
		void            SetTargetPosition(D3DXVECTOR3* pTargetVec3);
	    /**
	     *	@Brief: �����������λ�� [7/16/2014 By Hr]
	    */
		void            SetCameraPosition(D3DXVECTOR3* pCameraPosVec3);
		
		void            SetViewMatrix(D3DXMATRIX* pViewMatrix = NULL);
		void            SetProjMatrix(D3DXMATRIX* pProjMatrix = NULL);

		void            MoveAlongRightVec(float fUnits);
		void            MoveAlongUpVec(float fUnits);
		void            MoveAlongLookVec(float fUnits);

		void            RotationRightAxis(float fAngle);
		void            RotationUpAxis(float fAngle);
		void            RotationLookAxis(float fAngle);

		void            GetLookDir(D3DXVECTOR3& v3Look);
		void            GetCameraPosition(D3DXVECTOR3& v3CameraPos);
	private:
		void            SetupCamera();
		/**
		 *	@Brief: ͶӰ�����Ƶ� [7/21/2014 By Hr]
		*/
		D3DXMATRIX      BuildProjectionMatrix(float fov, float aspect, float zn, float zf);
	private:
		IDirect3DDevice9* m_pD3DDevice;

		D3DXVECTOR3     m_vRightVector;      //�ҷ���
		D3DXVECTOR3     m_vUpVector;         //�Ϸ���
		D3DXVECTOR3     m_vLookVector;       //�۲췽������
		D3DXVECTOR3     m_vCameraPosition;   //�������λ��

		D3DXMATRIX      m_matView;
		D3DXMATRIX      m_matProj;

		int             m_nWndWidth;          //��Ļ�Ŀ��
		int             m_nWndHeight;
	};

}


#endif

