#include "Render/HrRenderConstantBuffer.h"
#include "Render/HrRenderParameter.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrGraphicsBuffer.h"
#include "Asset/HrStreamData.h"
#include "HrMath/Include/HrMath.h"
#include "Kernel/HrDirector.h"

using namespace Hr;

HrRenderConstantBuffer::HrRenderConstantBuffer()
{
	m_pStreamData = nullptr;
	m_pRenderBuffer = nullptr;
	m_pStreamData = HR_NEW HrStreamData();
	m_pRenderBuffer = nullptr;//HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();
}

HrRenderConstantBuffer::~HrRenderConstantBuffer()
{
	SAFE_DELETE(m_pStreamData);
	SAFE_DELETE(m_pRenderBuffer);
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

void HrRenderConstantBuffer::MakeConstBuffer(uint32 nSize)
{
	BOOST_ASSERT(!m_pRenderBuffer);
	m_pRenderBuffer = HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();
	m_pRenderBuffer->BindStream(nullptr, nSize, HrGraphicsBuffer::HBU_GPUREAD_CPUWRITE, HrGraphicsBuffer::HBB_CONST);
}

HrGraphicsBuffer* HrRenderConstantBuffer::GetConstBuffer()
{
	return m_pRenderBuffer;
}

void HrRenderConstantBuffer::UpdateParams(HrRenderFrameParameters& renderFrameParameters)
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
			m_pStreamData->AddBuffer((char*)&transposeWorldVewProjMatrix(0, 0), transposeWorldVewProjMatrix.size() * sizeof(REAL));
			break;
		}
	}
	{
		HrGraphicsBuffer::Mapper mapper(*m_pRenderBuffer, HrGraphicsBuffer::HBA_WRITE_ONLY);
		std::memcpy(mapper.Pointer<uint8>(), m_pStreamData->GetBufferPoint(), m_pStreamData->GetBufferSize());
	}
}




