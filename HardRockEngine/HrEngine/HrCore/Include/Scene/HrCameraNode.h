#ifndef _HR_CAMERANODE_H_
#define _HR_CAMERANODE_H_

#include "HrCore/Include/Scene/HrSceneNode.h"

namespace Hr
{
	class HrCameraNode : public HrSceneNode
	{
	public:
		HrCameraNode(HrViewPort* pViewPort);
		~HrCameraNode();

		HrViewPort* GetViewPort();
	private:
		HrViewPort* m_pViewPort;
	};
}

#endif