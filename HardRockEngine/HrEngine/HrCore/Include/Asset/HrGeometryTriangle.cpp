#include "HrCore/Include/Asset/HrGeometryTriangle.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/IRenderFactory.h"
#include "HrCore/Include/Render/HrPixelFormat.h"
#include "HrCore/Include/Render/HrVertex.h"
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
	BindVertexStream();
}

void HrGeometryTriangle::BindVertexStream()
{
	m_pRenderTechnique = HrResourceManagerFactory::GetInstance().GetEffectManager()->GetRenderEffect("BasicEffect")->GetTechnique("Basic");

	float3 vertices[] =
	{
		float3(0.5f, 0.5f, 0.5f),
		float3(0.5f, -0.5f, 0.5f),
		float3(-0.5f, -0.5f, 0.5f)
	};

	HrVertexElement vertexElementArr[] = {
		HrVertexElement(HrVertexElement::VEU_POSITION, HrVertexElement::VET_FLOAT3),
	};

	m_pRenderLayout->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vertexElementArr
		, HR_ARRAY_SIZE(vertexElementArr) );

}




