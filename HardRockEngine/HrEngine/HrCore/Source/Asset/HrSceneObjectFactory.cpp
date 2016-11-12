#include "HrCore/Include/Asset/HrSceneObjectFactory.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;


HrSceneObjectFactory::HrSceneObjectFactory()
{
	m_pGeometryFactory = MakeSharedPtr<HrGeometryFactory>();
}

HrSceneObjectFactory::~HrSceneObjectFactory()
{
}

HrCameraNode* HrSceneObjectFactory::CreateCamera()
{
	return CreateCamera(0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
}

HrCameraNode* HrSceneObjectFactory::CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrCamera* pCamera = HR_NEW HrCamera();
	HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	HrCameraNode* pCameraNode = HR_NEW HrCameraNode(pViewPort);

	return pCameraNode;
}


HrSceneNode* HrSceneObjectFactory::CreateBox()
{
	return m_pGeometryFactory->CreateBox(10, 10, 10);
}

