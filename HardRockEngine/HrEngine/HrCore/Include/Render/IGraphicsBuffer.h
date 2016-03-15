#ifndef _HR_GRAPHICSBUFFER_H_
#define _HR_GRAPHICSBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IGraphicsBuffer : public RenderSysAllocatedObject
	{
	public:
		/// Enums describing buffer usage; not mutually exclusive
		enum EnumHardwareBufferUsage
		{
			HBU_GPUREAD_GPUWRITE,
			HBU_GPUREAD_CPUWRITE,
			HBU_GPUREAD_IMMUTABLE,
			HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};

		enum EnumHardwareBufferBind
		{
			HBB_VERTEXT,
			HBB_INDEX,
			HBB_CONST
		};
	public:
		IGraphicsBuffer()
		{
		}
		virtual ~IGraphicsBuffer(){}

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, IGraphicsBuffer::EnumHardwareBufferUsage usage
			, IGraphicsBuffer::EnumHardwareBufferBind bindFlag) = 0;
		virtual uint32 GetByteWidth() = 0;
	};
}

#endif
