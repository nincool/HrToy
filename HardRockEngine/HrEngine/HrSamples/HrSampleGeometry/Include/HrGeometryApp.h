#ifndef _HR_GEOMETRYAPP_H_
#define _HR_GEOMETRYAPP_H_

#include "HrSamples/HrSampleCommon/HrSampleCommon.h"

namespace Hr
{
	class HrGeometryApp : public HrApplication
	{
	public:
		HrGeometryApp();
		~HrGeometryApp();

		static HrGeometryApp& GetInstance();

		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual bool Destroy() override;

	private:
		void LoadAssets();
		void CreateScene();
	private:
		static HrGeometryAppPtr m_s_pUniqueGeometryApp;
	};
}

#endif



