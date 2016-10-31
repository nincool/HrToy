#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrCameraNode::HrCameraNode(HrViewPort* pViewPort)
{
	m_nodeType = HrSceneNode::NT_CAMERA;
	m_pViewPort = pViewPort;
	m_v3LocalPosition = m_pViewPort->GetCamera()->GetEyePos();
}

HrCameraNode::~HrCameraNode()
{
	SAFE_DELETE(m_pViewPort);
}

HrViewPort* HrCameraNode::GetViewPort()
{
	return m_pViewPort;
}

void HrCameraNode::Translate(const Vector3& v3)
{
	Move(v3);
}

void HrCameraNode::Move(const Vector3& v3)
{
	m_v3LocalPosition += v3;

	HrCamera* pCamera = m_pViewPort->GetCamera();
	HrVector3 vNewEyePos = m_v3LocalPosition;
	pCamera->ViewParams(vNewEyePos, vNewEyePos + pCamera->GetForward()*pCamera->GetLookAtDistance(), pCamera->GetUp());
}


