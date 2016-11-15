#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Asset/HrColor.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrMath/Include/HrMath.h"

using namespace Hr;

HrGeometryBox::HrGeometryBox(uint32 nLength, uint32 nWidth, uint32 nHeight)
{
	m_nLength = nLength;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_pMesh = HR_NEW HrMesh();

	InitRenderLayout();
}

HrGeometryBox::~HrGeometryBox()
{
	SAFE_DELETE(m_pMesh);
}

HrRenderLayout* Hr::HrGeometryBox::GetRenderLayout()
{
	return m_pMesh->GetRenderLayout();
}

void HrGeometryBox::InitRenderLayout()
{
	m_pMesh->GetRenderLayout()->SetTopologyType(TT_TRIANGLELIST);
	BindVertexStream();
}

void HrGeometryBox::BindVertexStream()
{
	HrRenderEffect* pRenderEffect = static_cast<HrRenderEffect*>(HrResourceManager::Instance()->GetResource("HrBasicEffect.effectxml", HrResource::RT_EFFECT));
	m_pRenderTechnique = pRenderEffect->GetTechnique("Basic");
	
	struct Vertex
	{
		float3 position;
		float4 color;
	};

	Vertex vertices[8] =
	{
		{ float3(-1.0f, -1.0f, 4.0f),  HrColor::F4Blue },
		{ float3(-1.0f, 1.0f, 4.0f), HrColor::F4Cyan },
		{ float3(1.0f, 1.0f, 4.0f), HrColor::F4Red },
		{ float3(1.0f, -1.0f, 4.0f), HrColor::F4Yellow },
		{ float3(-1.0f, -1.0f, 5.0f), HrColor::F4Green },
		{ float3(-1.0f, 1.0f, 5.0f), HrColor::F4Silver },
		{ float3(1.0f, 1.0f, 5.0f), HrColor::F4Black },
		{ float3(1.0f, -1.0f, 5.0f), HrColor::F4Magenta }
	};

	HrVertexElement vertexElementArr[] = {
		HrVertexElement(VEU_POSITION, VET_FLOAT3),
		HrVertexElement(VEU_COLOR, VET_FLOAT4)
	};

	m_pMesh->GetRenderLayout()->BindVertexBuffer((char*)vertices
		, sizeof(vertices)
		, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
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
	m_pMesh->GetRenderLayout()->BindIndexBuffer((char*)indices, sizeof(indices), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_16BIT);
}

