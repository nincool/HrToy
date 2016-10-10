#ifndef _HR_GRAPHICSBUFFER_H_
#define _HR_GRAPHICSBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrGraphicsBuffer
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
		HrGraphicsBuffer()
		{
		}
		virtual ~HrGraphicsBuffer(){}

		virtual void BindStream(char* pBuffer
			, uint32 nBufferSize
			, HrGraphicsBuffer::EnumHardwareBufferUsage usage
			, HrGraphicsBuffer::EnumHardwareBufferBind bindFlag) = 0;
		
		virtual uint32 GetByteWidth() = 0;
	};
}

#endif
