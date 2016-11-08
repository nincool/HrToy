#ifndef _HR_CAMERANODE_H_
#define _HR_CAMERANODE_H_

#include "HrCore/Include/Scene/HrSceneNode.h"

namespace Hr
{
	class HR_CORE_API HrCameraNode : public HrSceneNode
	{
	public:
		HrCameraNode(HrViewPort* pViewPort);
		~HrCameraNode();

		HrViewPort* GetViewPort();

		virtual void UpdateNode() override;
	private:
		void RecalcCameraView();

	private:
		HrViewPort* m_pViewPort;
		HrCamera* m_pCamera;
	};
}

#endif