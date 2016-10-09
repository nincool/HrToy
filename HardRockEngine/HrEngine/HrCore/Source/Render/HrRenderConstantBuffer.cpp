#include "Render/HrRenderConstantBuffer.h"
#include "Render/HrHardwareBuffer.h"
#include "Render/HrRenderParameter.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderFactory.h"
#include "Asset/HrStreamData.h"
#include "HrMath/Include/HrMath.h"
#include "HrDirector.h"

using namespace Hr;

HrRenderConstantBuffer::HrRenderConstantBuffer()
{
	m_pStreamData = nullptr;
	m_pRenderHardwareBuffer = nullptr;
	m_pStreamData = HR_NEW HrStreamData();
	m_pRenderHardwareBuffer = HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();
}

HrRenderConstantBuffer::~HrRenderConstantBuffer()
{
	SAFE_DELETE(m_pStreamData);
	SAFE_DELETE(m_pRenderHardwareBuffer);
	for (auto& item : m_vecRenderParameter)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderParameter.clear();
}

uint64 HrRenderConstantBuffer::GetSize()
{
	return m_pStreamData->GetBufferSize();
}

void HrRenderConstantBuffer::SetSize(uint64 nSize)
{

}

void HrRenderConstantBuffer::AddParameter(const std::string& strName
	, HrRenderParameter::EnumRenderParamType rpt
	, HrRenderParameter::EnumRenderParamDataType rpdt
	, uint32 nStartOffset)
{
	HrRenderParameter* pRenderParameter = HR_NEW HrRenderParameter();
	pRenderParameter->SetName(strName);
	pRenderParameter->SetParamType(rpt);
	pRenderParameter->SetRenderParamDataType(rpdt);
	pRenderParameter->SetStartOffset(nStartOffset);
	m_vecRenderParameter.push_back(pRenderParameter);
}

IGraphicsBuffer* HrRenderConstantBuffer::GetConstBuffer()
{
	return m_pRenderHardwareBuffer;
}

void HrRenderConstantBuffer::UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters)
{
	m_pStreamData->ClearBuffer();

	HrRenderParameter* pRenderParameter = nullptr;
	for (auto& item : m_vecRenderParameter)
	{
		pRenderParameter = item;
		switch (pRenderParameter->GetParamType())
		{
		case HrRenderParameter::RPT_WORLDVIEWPROJ_MATRIX:
			const Matrix4& worldViewProjMatrix = renderFrameParameters.GetWorldViewProjMatrix();
			Matrix4 transposeWorldVewProjMatrix = HrMath::Transpose(worldViewProjMatrix);
			m_pStreamData->AddBuffer((char*)&transposeWorldVewProjMatrix[0][0], transposeWorldVewProjMatrix.size() * sizeof(REAL));
			break;
		}
	}
	m_pRenderHardwareBuffer->BindStream(m_pStreamData->GetBufferPoint(), m_pStreamData->GetBufferSize(), IGraphicsBuffer::HBU_GPUREAD_CPUWRITE, IGraphicsBuffer::HBB_CONST);
}




