#ifndef _HR_SCENEMANAGER_H_
#define _HR_SCENEMANAGER_H_

#include "HrMainPrerequisiters.h"
#include <boost/noncopyable.hpp>

namespace Hr
{
	class HrCamera;

	class HR_MAIN_API HrSceneManager : boost::noncopyable
	{
	public:
		HrCameraPtr& CreateCamera(HrString strCameName);


	private:
		HrCameraPtr m_pShareMainCamera;
	};
}

#endif



