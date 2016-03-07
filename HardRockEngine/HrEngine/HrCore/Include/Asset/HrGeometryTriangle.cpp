#include "HrCore/Include/Asset/HrGeometryTriangle.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/IRenderFactory.h"
#include "HrCore/Include/Render/HrPixelFormat.h"
#include "HrCore/Include/Render/HrVertext.h"
#include "HrCore/Include/Render/HrHardwareBuffer.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Asset/HrResourceManagerFactory.h"
#include "HrCore/Include/Asset/HrRenderEffectManager.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/HrDirector.h"
#include "HrMath/Include/HrMath.h"

using namespace Hr;

HrGeometryTriangle::HrGeometryTriangle()
{
	InitRenderLayout();
}

HrGeometryTriangle::~HrGeometryTriangle()
{
}

void HrGeometryTriangle::InitRenderLayout()
{
	m_pRenderLayout->SetTopologyType(HrRenderLayout::TT_TRIANGLELIST);
	BindVertextStream();
}

void HrGeometryTriangle::BindVertextStream()
{
	m_pRenderTechnique = HrResourceManagerFactory::GetInstance().GetEffectManager()->GetRenderEffect("BasicEffect")->GetTechnique("Basic");

	float3 trianglePoint[] =
	{
		float3(0.5f, 0.5f, 0.5f),
		float3(0.5f, -0.5f, 0.5f),
		float3(-0.5f, -0.5f, 0.5f)
	};

	HrVertextElement vertexElementArr[] = {
		HrVertextElement(HrVertextElement::VEU_POSITION, HrVertextElement::VET_FLOAT3),
	};

	m_pRenderLayout->BindVertextBuffer((char*)trianglePoint
		, sizeof(trianglePoint)
		, IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vertexElementArr
		, HR_ARRAY_SIZE(vertexElementArr) );

}




