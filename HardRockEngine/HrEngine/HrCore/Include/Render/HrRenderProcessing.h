#ifndef _HR_RENDERPROCESSING_H_
#define _HR_RENDERPROCESSING_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderProcessing
	{
	public:
		HrRenderProcessing();
		~HrRenderProcessing();

		virtual void Run() = 0;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HrForwardProcessing : public HrRenderProcessing
	{
	public:
		HrForwardProcessing();
		~HrForwardProcessing();

		virtual void Run() override;
	};
}


#endif
