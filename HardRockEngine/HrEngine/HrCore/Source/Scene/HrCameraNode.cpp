#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Scene/HrTransform.h"

using namespace Hr;

HrCameraNode::HrCameraNode(HrViewPort* pViewPort)
{
	m_nodeType = HrSceneNode::NT_CAMERA;
	m_pViewPort = pViewPort;
	m_pCamera = m_pViewPort->GetCamera();
	m_pCamera->AttachCameraNode(this);
	m_bDirtyTransform = false;
	
	m_pTransform->SetPosition(Vector3::Zero());
}

HrCameraNode::~HrCameraNode()
{
	SAFE_DELETE(m_pViewPort);
}

HrViewPort* HrCameraNode::GetViewPort()
{
	return m_pViewPort;
}

void HrCameraNode::UpdateNode()
{
	HrSceneNode::UpdateNode();
	
	RecalcCameraView();
}

void HrCameraNode::RecalcCameraView()
{
	if (m_bDirtyTransform)
	{
		m_pCamera->ViewParams(m_pTransform->GetPosition()
			, m_pTransform->GetPosition() + m_pTransform->GetForward() * m_pCamera->GetLookAtDistance()
			, m_pTransform->GetUp());
		m_bDirtyTransform = false;
	}
}

