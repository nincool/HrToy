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
	m_pCurrentCamera->ViewParams(Vector3(0.0f, 2.0, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_pCurrentCamera->ProjectParams(Hr::PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	HrMatrix4 matProj = m_pCurrentCamera->GetProjectMatrix();
	Matrix4 matView = m_pCurrentCamera->GetViewMatrix();
	mWorldViewProjMatrix = matView * matProj;

	return mWorldViewProjMatrix;
}




