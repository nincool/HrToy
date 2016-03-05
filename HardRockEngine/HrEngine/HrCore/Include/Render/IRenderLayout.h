#ifndef _I_RENDERLAYOUT_H_
#define _I_RENDERLAYOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrCore/Include/Render/HrPixelFormat.h"
#include "HrCore/Include/Render/IGraphicsBuffer.h"

namespace Hr
{
	class IRenderLayout : public RenderSysAllocatedObject
	{
	public:
		enum EnumTopologyType
		{
			TT_POINTLIST,
			TT_LINELIST,
			TT_LINETRIP,
			TT_TRIANGLELIST,
			TT_TRIANGLETRIP,
		};
	public:

		virtual ~IRenderLayout(){}

		virtual void SetTopologyType(EnumTopologyType topologyType) = 0;

		virtual uint32 GetVertextSize() = 0;

		virtual void BindVertextBuffer(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrVertextElement* pVertexElementArr
			, uint32 nVertexElementLength) = 0;
	};
}

#endif