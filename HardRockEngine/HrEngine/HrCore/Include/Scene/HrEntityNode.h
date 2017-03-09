#ifndef _HR_CAMERANODE_H_
#define _HR_CAMERANODE_H_

#include "HrCore/Include/Scene/HrSceneNode.h"

namespace Hr
{
	class HrRootNode : public HrSceneNode
	{
	public:
		HrRootNode();
		virtual ~HrRootNode();
	};

	class HR_CORE_API HrCameraNode : public HrSceneNode
	{
	public:
		HrCameraNode(HrViewPort* pViewPort);
		virtual ~HrCameraNode();

		HrViewPort* GetViewPort();

		virtual void UpdateNode() override;

		virtual void OnEnter() override;
		virtual void OnEnterDidFinish() override;
		virtual void OnExist() override;
	private:
		void RecalcCameraView();

	private:
		HrViewPort* m_pViewPort;
		HrCamera* m_pCamera;
	};

	class HR_CORE_API HrLightNode : public HrSceneNode
	{
	public:
		HrLightNode(const HrLightPtr& pLight);
		virtual ~HrLightNode();

		HrLightPtr& GetLight();

		virtual void UpdateNode() override;

		virtual void OnEnter() override;
		virtual void OnEnterDidFinish() override;
		virtual void OnExist() override;

	private:
		HrLightPtr m_pLight;
	};
}

#endif
