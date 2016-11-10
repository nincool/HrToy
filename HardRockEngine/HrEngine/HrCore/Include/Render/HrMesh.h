#ifndef _HR_MESH_H_
#define _HR_MESH_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrMesh
	{
	public:
		HrMesh();
		virtual ~HrMesh();

	protected:
		HrRenderLayout* m_pRenderLayout;


	};
}


#endif



