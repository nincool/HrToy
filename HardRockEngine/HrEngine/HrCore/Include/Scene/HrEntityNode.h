#ifndef _HR_CAMERANODE_H_
#define _HR_CAMERANODE_H_

#include "HrCore/Include/Scene/HrSceneNode.h"

namespace Hr
{


	//class HR_CORE_API HrCameraNode : public HrSceneNode
	//{
	//public:
	//	HrCameraNode(const HrViewPortPtr& pViewPort);
	//	virtual ~HrCameraNode();

	//	HrViewPortPtr GetViewPort();

	//	virtual void UpdateNode() override;

	//	virtual void OnEnter() override;
	//	virtual void OnExist() override;
	//private:
	//	void RecalcCameraView();

	//private:
	//	HrViewPortPtr m_pViewPort;
	//	HrCameraPtr m_pCamera;
	//};

	class HR_CORE_API HrLightNode : public HrSceneNode
	{
	public:
		HrLightNode(const HrLightPtr& pLight);
		virtual ~HrLightNode();

		HrLightPtr& GetLight();

		virtual void UpdateNode(float fDt) override;

		virtual void OnEnter() override;
		virtual void OnExist() override;

	private:
		HrLightPtr m_pLight;
	};
}

#endif
