#ifndef _I_RENDERLAYOUT_H_
#define _I_RENDERLAYOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderLayout : public RenderSysAllocatedObject
	{
	public:
		IRenderLayout()
		{
			m_topologyType = TOPOLOGY_TYPE_TRAINGLELIST;
		}
		virtual ~IRenderLayout(){}

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