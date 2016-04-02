#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentRenderable = nullptr;
	m_pCurrentCamera = nullptr;
}

HrRenderFrameParameters::~HrRenderFrameParameters()
{
}

void HrRenderFrameParameters::SetCurrentRenderable(const IRenderable* rend)
{
	m_pCurrentRenderable = rend;
}

void HrRenderFrameParameters::SetCurrentCamera(HrCamera* pCamera)
{
	m_pCurrentCamera = pCamera;
}

const Matrix4& HrRenderFrameParameters::GetWorldViewProjMatrix() const
{
	HrMatrix4 matProj = m_pCurrentCamera->GetProjectMatrix();
	Matrix4 matView = m_pCurrentCamera->GetViewMatrix();
	mWorldViewProjMatrix = matView * matProj;

	return mWorldViewProjMatrix;
}




