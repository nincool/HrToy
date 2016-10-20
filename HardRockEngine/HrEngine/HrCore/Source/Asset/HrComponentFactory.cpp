#include "HrCore/Include/Asset/HrComponentFactory.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;


HrComponentFactory::HrComponentFactory()
{
	m_pGeometryFactory = MakeSharedPtr<HrGeometryFactory>();
}

HrComponentFactory::~HrComponentFactory()
{
}


HrCameraNode* HrComponentFactory::CreateCamera(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrCamera* pCamera = HR_NEW HrCamera();
	HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	HrCameraNode* pCameraNode = HR_NEW HrCameraNode(pViewPort);

	return pCameraNode;
}

HrSceneNode* HrComponentFactory::CreateBox()
{
	return m_pGeometryFactory->CreateBox(10, 10, 10);
}

