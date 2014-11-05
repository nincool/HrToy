#include "HrCamera.h"

using namespace HR;
CHrCamera::CHrCamera()
{
	SetupCamera();
}

CHrCamera::~CHrCamera()
{
}

void CHrCamera::Initialize(IDirect3DDevice9* pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

void CHrCamera::CalculateViewMatrix(D3DXMATRIX* pViewMatrix)
{
	//先把3个向量都规范化并使其相互垂直,成为正交矩阵
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);

	//创建出取景变换矩阵
	pViewMatrix->_11 = m_vRightVector.x;
	pViewMatrix->_12 = m_vUpVector.x;
	pViewMatrix->_13 = m_vLookVector.x;
	pViewMatrix->_14 = 0.0f;

	pViewMatrix->_21 = m_vRightVector.y;
	pViewMatrix->_22 = m_vUpVector.y;
	pViewMatrix->_23 = m_vLookVector.y;
	pViewMatrix->_24 = 0.0f;

	pViewMatrix->_31 = m_vRightVector.z;
	pViewMatrix->_32 = m_vUpVector.z;
	pViewMatrix->_33 = m_vLookVector.z;
	pViewMatrix->_34 = 0.0f;

	pViewMatrix->_41 = -D3DXVec3Dot(&m_vCameraPosition, &m_vRightVector);
	pViewMatrix->_42 = -D3DXVec3Dot(&m_vCameraPosition, &m_vUpVector);
	pViewMatrix->_43 = -D3DXVec3Dot(&m_vCameraPosition, &m_vLookVector);
	pViewMatrix->_44 = 1.0f;
}

void CHrCamera::SetTargetPosition(D3DXVECTOR3* pTargetVec3)
{
}

void CHrCamera::SetCameraPosition(D3DXVECTOR3* pCameraPosVec3)
{
}

void CHrCamera::SetupCamera()
{
	m_pD3DDevice = NULL;

	m_nWndWidth = 800;
	m_nWndHeight = 600;

	m_vLookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vRightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vCameraPosition = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
}

void CHrCamera::SetViewMatrix(D3DXMATRIX* pViewMatrix)
{
	if (pViewMatrix == NULL)
	{
		CalculateViewMatrix(&m_matView);
		m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	}
	else
	{
		m_matView = *pViewMatrix;
	}
}

void CHrCamera::SetProjMatrix(D3DXMATRIX* pProjMatrix)
{
	if (pProjMatrix == NULL)
	{
		D3DXMATRIX m_persMatrix;
		D3DXMatrixPerspectiveFovLH(&m_persMatrix, D3DX_PI / 4.0f, (float)m_nWndWidth / m_nWndHeight, 1.0f, 1000.0f);
		//m_persMatrix = BuildProjectionMatrix(D3DX_PI / 4.0f, (float)m_nWndWidth / m_nWndHeight, 1.0f, 1000.0f);
		m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_persMatrix);
	}
	else
	{
	}
}

void CHrCamera::MoveAlongRightVec(float fUnits)
{
	m_vCameraPosition += m_vRightVector * fUnits;
}

void CHrCamera::MoveAlongUpVec(float fUnits)
{
	m_vCameraPosition += m_vUpVector * fUnits;
}

void CHrCamera::MoveAlongLookVec(float fUnits)
{
	m_vCameraPosition += m_vLookVector * fUnits;
}

void CHrCamera::RotationRightAxis(float fAngle)
{
	D3DXMATRIX roteMatrix;
	D3DXMatrixRotationAxis(&roteMatrix, &m_vRightVector, fAngle);
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &roteMatrix);
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &roteMatrix);
}

void CHrCamera::RotationUpAxis(float fAngle)
{
	D3DXMATRIX roteMatrix;
	D3DXMatrixRotationAxis(&roteMatrix, &m_vUpVector, fAngle);
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &roteMatrix);
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &roteMatrix);
}

void CHrCamera::RotationLookAxis(float fAngle)
{
	D3DXMATRIX roteMatrix;
	D3DXMatrixRotationAxis(&roteMatrix, &m_vLookVector, fAngle);
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &roteMatrix);
	
}

D3DXMATRIX CHrCamera::BuildProjectionMatrix(float fov, float aspect, float zn, float zf)
{
	D3DXMATRIX proj;
	ZeroMemory(&proj, sizeof(proj));

	proj.m[0][0] = 1 / (tan(fov * 0.5f) *aspect);
	proj.m[1][1] = 1 / tan(fov * 0.5f);
	proj.m[2][2] = zf / (zf - zn);
	proj.m[2][3] = 1.0f;
	proj.m[3][2] = (zn * zf) / (zn - zf);

	return proj;
}

void CHrCamera::GetLookDir(D3DXVECTOR3& v3Look)
{
	v3Look = m_vLookVector;
}

void CHrCamera::GetCameraPosition(D3DXVECTOR3& v3CameraPos)
{
	v3CameraPos = m_vCameraPosition;
}
