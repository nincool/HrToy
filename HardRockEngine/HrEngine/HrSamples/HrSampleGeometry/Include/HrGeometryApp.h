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

		virtual void Run() override;

		virtual bool Destroy() override;

	private:
		void OnEnter();
		void LoadAssets();
	private:
		static HrGeometryAppPtr m_s_pUniqueGeometryApp;
	};
}

#endif



