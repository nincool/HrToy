#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderable.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrRenderFrameParameters::HrRenderFrameParameters()
{
	m_pCurrentRenderable = nullptr;

	m_pShareCamera = std::make_shared<HrCamera>();
}

HrRenderFrameParameters::~HrRenderFrameParameters()
{
}

void HrRenderFrameParameters::SetCurrentRenderable(const IRenderable* rend)
{
	m_pCurrentRenderable = rend;
}

const Matrix4& HrRenderFrameParameters::GetWorldViewProjMatrix() const
{
	m_pShareCamera->ProjectParams(Hr::PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	mWorldViewProjMatrix = m_pShareCamera->GetProjectMatrix();

	return mWorldViewProjMatrix;
}





