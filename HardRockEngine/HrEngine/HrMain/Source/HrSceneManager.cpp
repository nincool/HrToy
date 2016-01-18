#include "HrSceneManager.h"
#include "Render/HrCamera.h"
#include "HrLog.h"

using namespace Hr;

HrCameraPtr& HrSceneManager::CreateCamera(HrString strCameName)
{
	HRASSERT((m_pShareMainCamera == nullptr), _T("CreateCameError! [%s]"), strCameName.c_str());
	m_pShareMainCamera = std::make_shared<HrCamera>();

	return m_pShareMainCamera;
}



