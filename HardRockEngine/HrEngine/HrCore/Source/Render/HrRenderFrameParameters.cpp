#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentRenderable = nullptr;
	m_pCurrentCamera = nullptr;
	m_worldMatrix = Matrix4::Identity();
}

HrRenderFrameParameters::~HrRenderFrameParameters()
{
}

void HrRenderFrameParameters::SetCurrentRenderable(const HrRenderable* rend)
{
	m_pCurrentRenderable = rend;
	//m_bWorldViewProjMatrixDirty = true;
}

void HrRenderFrameParameters::SetCurrentCamera(HrCamera* pCamera)
{
	if (m_pCurrentCamera != pCamera)
	{
		m_pCurrentCamera = pCamera;
		m_bWorldViewProjMatrixDirty = true;
	}
	else if (m_pCurrentCamera->ViewProjDirty())
	{
		m_bWorldViewProjMatrixDirty = true;
	}
}

const Matrix4& HrRenderFrameParameters::GetWorldMatrix()
{
	if (m_bWorldMatrixDirty)
	{
		
	}
	return Matrix4::Identity();
}

const Matrix4& HrRenderFrameParameters::GetInverseWroldMatrix()
{
	return HrMath::Inverse(GetWorldMatrix());
}

const Matrix4& HrRenderFrameParameters::GetViewProjMatrix() const
{
	return m_pCurrentCamera->GetViewProjMatrix();
}

const Matrix4& HrRenderFrameParameters::GetWorldViewProjMatrix()
{
	if (m_bWorldViewProjMatrixDirty)
	{
		m_worldViewProjMatrix = m_worldMatrix * m_pCurrentCamera->GetViewProjMatrix();
		m_bWorldViewProjMatrixDirty = false;
	}
	
	return m_worldViewProjMatrix;
}

const Matrix4& HrRenderFrameParameters::GetInverseTransposeWorldMatrix()
{
	if (m_bInverseTransposeWorldMatrix)
	{
		//m_inverseTransposeWorldMatrix = 
	}
	return HrMath::Transpose(GetInverseWroldMatrix());
}

