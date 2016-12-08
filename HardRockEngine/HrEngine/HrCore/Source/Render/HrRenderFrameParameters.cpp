#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentRenderable = nullptr;
	m_pCurrentMaterial = nullptr;
	m_pCurrentCamera = nullptr;

	m_bWorldMatrixDirty = true;
	m_bInverseWorldMatrixDirty = true;
	m_bInverseTransposeWorldMatrix = true;
	m_bWorldViewProjMatrixDirty = true;

	m_worldMatrix = Matrix4::Identity();
}

HrRenderFrameParameters::~HrRenderFrameParameters()
{
}

void HrRenderFrameParameters::SetCurrentRenderable(const HrRenderable* rend)
{
	m_pCurrentRenderable = rend;
	m_bWorldViewProjMatrixDirty = true;
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

void HrRenderFrameParameters::SetCurrentMaterial(const HrMaterial* pMaterial)
{
	m_pCurrentMaterial = pMaterial;
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
	if (m_bInverseWorldMatrixDirty)
	{
		m_inverseWorldMatrix = HrMath::Inverse(GetWorldMatrix());
	}
	return m_inverseWorldMatrix;
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
		m_inverseTransposeWorldMatrix = HrMath::Transpose(GetInverseWroldMatrix());
	}
	return m_inverseTransposeWorldMatrix;
}

