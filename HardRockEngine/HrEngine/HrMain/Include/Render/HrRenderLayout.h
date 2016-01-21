#ifndef _HR_RENDERLAYOUT_H_
#define _HR_RENDERLAYOUT_H_

#include "HrMain/Include/Render/IRenderLayout.h"

namespace Hr
{
	class HR_MAIN_API HrRenderLayout : public IRenderLayout
	{
	public:
		HrRenderLayout();

	public:
		enum Enum_Topology_Type
		{
			TOPOLOGY_TYPE_TRAINGLELIST,
		};

		Enum_Topology_Type GetTopolotyType()
		{
			return m_topologyType;
		}


	private:
		Enum_Topology_Type m_topologyType;
	};
}

#endif
