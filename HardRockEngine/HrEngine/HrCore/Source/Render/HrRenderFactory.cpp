#include "Render/HrRenderFactory.h"
#include "Render/HrRasterizerState.h"

using namespace Hr;

HrRenderFactory::~HrRenderFactory()
{
}

void HrRenderFactory::CreateBuildInRasterizerState()
{
	//HrRasterizerState::HrRasterizerStateDesc desc;
	//memset(&desc, 0, sizeof(desc));
	//desc.fillMode = RFM_WIREFRAME;
	//desc.cullMode = RCM_CULL_BACK;
	//desc.bfrontCounterClockWise = true;
	//desc.bDepthClipEnable = true;
	//size_t nKey = HrRasterizerState::GetRasterizerStateKey(desc);
	//if (m_mapRasterizerStatePool.find(nKey) == m_mapRasterizerStatePool.end())
	//{
	//	HrRasterizerState* pRasterizerState = CreateRasterizerState(desc);
	//	m_mapRasterizerStatePool[nKey] = pRasterizerState;
	//}

	//memset(&desc, 0, sizeof(desc));
	//desc.fillMode = RFM_WIREFRAME;
	//desc.cullMode = RCM_CULL_BACK;
	//desc.bfrontCounterClockWise = false;
	//desc.bDepthClipEnable = true;
	//nKey = HrRasterizerState::GetRasterizerStateKey(desc);
	//if (m_mapRasterizerStatePool.find(nKey) == m_mapRasterizerStatePool.end())
	//{
	//	HrRasterizerState* pRasterizerState = CreateRasterizerState(desc);
	//	m_mapRasterizerStatePool[nKey] = pRasterizerState;
	//}

	//memset(&desc, 0, sizeof(desc));
	//desc.fillMode = RFM_SOLD;
	//desc.cullMode = RCM_CULL_BACK;
	//desc.bfrontCounterClockWise = true;
	//desc.bDepthClipEnable = true;
	//nKey = HrRasterizerState::GetRasterizerStateKey(desc);
	//if (m_mapRasterizerStatePool.find(nKey) == m_mapRasterizerStatePool.end())
	//{
	//	HrRasterizerState* pRasterizerState = CreateRasterizerState(desc);
	//	m_mapRasterizerStatePool[nKey] = pRasterizerState;

	//}

	//memset(&desc, 0, sizeof(desc));
	//desc.fillMode = RFM_SOLD;
	//desc.cullMode = RCM_CULL_BACK;
	//desc.bfrontCounterClockWise = false;
	//desc.bDepthClipEnable = true;
	//nKey = HrRasterizerState::GetRasterizerStateKey(desc);
	//if (m_mapRasterizerStatePool.find(nKey) == m_mapRasterizerStatePool.end())
	//{
	//	HrRasterizerState* pRasterizerState = CreateRasterizerState(desc);
	//	m_mapRasterizerStatePool[nKey] = pRasterizerState;
	//}
}

void HrRenderFactory::CreateBuildInBlendState()
{

}

