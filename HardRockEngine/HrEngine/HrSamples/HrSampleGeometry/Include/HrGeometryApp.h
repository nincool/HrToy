#ifndef _HR_GEOMETRYAPP_H_
#define _HR_GEOMETRYAPP_H_

#include "HrSamples/HrSampleCommon/HrSampleCommon.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HrGeometryApp : public HrApplicationWin, 
		public HrSingleTon<HrGeometryApp>
	{
	public:
		HrGeometryApp();
		~HrGeometryApp();

		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual bool Destroy() override;

	private:
		void LoadAssets();
		void CreateScene();
		void CreateInputEvent();

	};
}

#endif



