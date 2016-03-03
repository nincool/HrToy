#ifndef _HR_GEOMETRYTRIANGLE_H_
#define _HR_GEOMETRYTRIANGLE_H_

#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrGeometryTriangle : public HrRenderable
	{
	public:
		HrGeometryTriangle();
		~HrGeometryTriangle();

	private:
		void InitRenderLayout();
		void BindVertextStream();
	private:
	};
}


#endif


