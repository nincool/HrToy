#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/IRenderFactory.h"
#include "HrCore/Include/Render/HrPixelFormat.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Render/HrHardwareBuffer.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Asset/HrResourceManagerFactory.h"
#include "HrCore/Include/Asset/HrRenderEffectManager.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrColor.h"
#include "HrCore/Include/HrDirector.h"
#include "HrMath/Include/HrMath.h"

using namespace Hr;

HrGeometryBox::HrGeometryBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	m_nLength = nLength;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	InitRenderLayout();
}

HrGeometryBox::~HrGeometryBox()
{

}

void HrGeometryBox::InitRenderLayout()
{
	m_pRenderLayout->SetTopologyType(HrRenderLayout::TT_TRIANGLELIST);
	BindVertexStream();
}

void HrGeometryBox::BindVertexStream()
{
	m_pRenderTechnique = HrResourceManagerFactory::GetInstance().GetEffectManager()->GetRenderEffect("BasicEffect")->GetTechnique("Basic");

	struct Vertex
	{
		float3 position;
		float4 color;
	};

	Vertex vertices[8] = 
	{
		{ float3(-1.0f, -1.0f, -1.0f),  HrColor::F4Blue },
		{ float3(-1.0f, 1.0f, -1.0f), HrColor::F4Cyan },
		{ float3(1.0f, 1.0f, -1.0f), HrColor::F4Red },
		{ float3(1.0f, -1.0f, -1.0f), HrColor::F4Yellow },
		{ float3(-1.0f, -1.0f, 1.0f), HrColor::F4Green },
		{ float3(-1.0f, 1.0f, 1.0f), HrColor::F4Silver },
		{ float3(1.0f, 1.0f, 1.0f), HrColor::F4Black },
		{ float3(1.0f, -1.0f, 1.0f), HrColor::F4Magenta }
	};
	
	HrVertexElement vertexElementArr[] = {
		HrVertexElement(HrVertexElement::VEU_POSITION, HrVertexElement::VET_FLOAT3),
		HrVertexElement(HrVertexElement::VEU_COLOR, HrVertexElement::VET_FLOAT4)
	};

	m_pRenderLayout->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
		, vertexElementArr
		, HR_ARRAY_SIZE(vertexElementArr));

	uint16 indices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 1, 4, 1, 0,
		7, 6, 5, 7, 5, 4,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};
	m_pRenderLayout->BindIndexBuffer((char*)indices, sizeof(indices), IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE);


}

