#ifndef _HR_GEOMETRYBOX_H_
#define _HR_GEOMETRYBOX_H_

#include "HrCore/Include/Render/IRenderable.h"

namespace Hr
{
	class HrGeometryBox : public IRenderable
	{
	public:
		HrGeometryBox(uint32 nLength, uint32 nWidth, uint32 nHeight);
		~HrGeometryBox();


	};
}

#endif



