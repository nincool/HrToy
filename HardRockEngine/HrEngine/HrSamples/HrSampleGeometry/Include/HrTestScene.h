#ifndef _HR_TESTSCENE_H_
#define _HR_TESTSCENE_H_

#include "HrCore/Include/Scene/HrSceneImported.h"

namespace Hr
{
	class HrTestScene : public HrSceneImported
	{
	public:
		HrTestScene();
		~HrTestScene();

	protected:
		virtual void CreateSceneFromData() override;
	
	};
}


#endif


