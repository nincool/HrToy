#include "HrCore/Include/Asset/HrGeometryTriangle.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Render/HrHardwareBuffer.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Kernel/HrDirector.h"
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
	//m_pRenderLayout->SetTopologyType(TT_TRIANGLELIST);
	//BindVertexStream();
}

void HrGeometryTriangle::BindVertexStream()
{
	//m_pRenderTechnique = HrResourceManagerFactory::GetInstance().GetEffectManager()->GetRenderEffect("BasicEffect")->GetTechnique("Basic");

	//float3 vertices[] =
	//{
	//	float3(0.5f, 0.5f, 0.5f),
	//	float3(0.5f, -0.5f, 0.5f),
	//	float3(-0.5f, -0.5f, 0.5f)
	//};

	//HrVertexElement vertexElementArr[] = {
	//	HrVertexElement(VEU_POSITION, VET_FLOAT3),
	//};

	//m_pRenderLayout->BindVertexBuffer((char*)vertices
	//	, sizeof(vertices)
	//	, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
	//	, vertexElementArr
	//	, HR_ARRAY_SIZE(vertexElementArr) );

}




