#include "Scene/HrEntityNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneManager.h"
#include "Render/HrViewPort.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderTarget.h"
#include "Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

#include <boost/cast.hpp>

using namespace Hr;

HrRootNode::HrRootNode()
{
}

HrRootNode::~HrRootNode()
{
}


/////////////////////////////////////////////
//
/////////////////////////////////////////////

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

void HrCameraNode::OnEnter()
{
	HrSceneNode::OnEnter();

	HrDirector::Instance()->GetRenderTarget()->AddViewPort(m_pViewPort);
}

void HrCameraNode::OnEnterDidFinish()
{
	HrSceneNode::OnEnterDidFinish();

}

void HrCameraNode::OnExist()
{
	HrSceneNode::OnExist();

}

//////////////////////////////////////////////
//
/////////////////////////////////////////////

HrLightNode::HrLightNode(const HrLightPtr& pLight)
{
	m_nodeType = HrSceneNode::NT_LIGHT;
	m_pLight = pLight;
	m_pLight->AttachLightNode(this);
}

HrLightNode::~HrLightNode()
{
}

HrLightPtr& HrLightNode::GetLight()
{
	return m_pLight;
}

void HrLightNode::UpdateNode()
{

}

void HrLightNode::OnEnter()
{
	HrSceneNode::OnEnter();

	HrDirector::Instance()->GetSceneManager()->GetRunningScene()->AddLight(m_pLight);
}

void HrLightNode::OnEnterDidFinish()
{
	HrSceneNode::OnEnterDidFinish();

}

void HrLightNode::OnExist()
{
	HrSceneNode::OnExist();

	HrDirector::Instance()->GetSceneManager()->GetRunningScene()->DeleteLight(m_pLight);
}

