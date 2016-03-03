#ifndef _HR_HARDWAREBUFFER_H_
#define _HR_HARDWAREBUFFER_H_

#include "HrCore/Include/Render/IGraphicsBuffer.h"

namespace Hr
{
	class HR_CORE_API HrHardwareBuffer : public IGraphicsBuffer
	{
	public:
		/// Enums describing buffer usage; not mutually exclusive
		enum _HBUSAGE_
		{
			HBU_GPUREAD_GPUWRITE,
			HBU_GPUREAD_CPUWRITE,
			HBU_GPUREAD_IMMUTABLE,
			HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE,
		};
	public:
		HrHardwareBuffer();
		HrHardwareBuffer(uint32 nByteWidth);
		virtual void CreateHardwareBuffer(const void* pResourceData) override{}

	protected:
		uint32 m_nByteWidth;

	};
}


#endif




