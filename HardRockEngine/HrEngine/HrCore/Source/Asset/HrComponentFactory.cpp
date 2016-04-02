#include "Asset/HrComponentFactory.h"
#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"
#include "Scene/HrCameraNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrComponentFactoryPtr HrComponentFactory::m_s_pUniqueFactory;

HrComponentFactory::HrComponentFactory()
{

}

HrComponentFactory::~HrComponentFactory()
{

}

HrComponentFactory& HrComponentFactory::GetInstance()
{
	if (!m_s_pUniqueFactory)
	{
		m_s_pUniqueFactory = MakeUniquePtr<HrComponentFactory>();
	}

	return *m_s_pUniqueFactory;
}

void HrComponentFactory::ReleaseInstance()
{
	if (m_s_pUniqueFactory)
	{
		m_s_pUniqueFactory.reset();
	}
}

HrCameraNode* HrComponentFactory::CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrCamera* pCamera = HR_NEW HrCamera();
	HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	HrCameraNode* pCameraNode = HR_NEW HrCameraNode(pViewPort);

	return pCameraNode;
}

