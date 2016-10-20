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

		virtual void Translate(const Vector3& v3) override;

		HrViewPort* GetViewPort();
	private:
		HrViewPort* m_pViewPort;
	};
}

#endif