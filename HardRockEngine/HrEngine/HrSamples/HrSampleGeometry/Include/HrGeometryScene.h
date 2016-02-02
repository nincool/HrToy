#ifndef _HR_GEOMETRYSCENE_H_
#define _HR_GEOMETRYSCENE_H_

#include "HrEngine.h"

namespace Hr
{
	class HrGeometryScene : public HrScene
	{
	public:
		HrGeometryScene();
		~HrGeometryScene();

		virtual void OnEnter() override;
	};
}

#endif


