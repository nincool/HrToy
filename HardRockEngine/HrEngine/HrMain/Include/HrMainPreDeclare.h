#ifndef _HR_MAINPREDECLARE_H_
#define _HR_MAINPREDECLARE_H_

#include <memory>

namespace Hr
{
	class ICamera;
	typedef std::shared_ptr<ICamera> ICameraPtr;
	class HrCamera;
	typedef std::shared_ptr<HrCamera> HrCameraPtr;
	class HrSceneManager;
	typedef std::shared_ptr<HrSceneManager> HrSceneManagerPtr;
}


#endif // !_HR_MAINPREDECLARE_H_



