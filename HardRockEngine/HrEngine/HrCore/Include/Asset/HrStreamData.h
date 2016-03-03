#ifndef _HR_STREAMDATA_H_
#define _HR_STREAMDATA_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API HrStreamData : public ResourceAllocatedObject
	{
	public:
		HrStreamData();
		~HrStreamData();

		enum _READ_DATA_TYPE_
		{
			RDT_TXT,
			RDT_BINARY,
		};

		void SetReadDataType(_READ_DATA_TYPE_ readDataType);
		//开辟对应空间
		char* ResizeBuffer(uint64 nLength);
		char* GetBufferPoint();
		uint64 GetBufferSize();
	private:
		_READ_DATA_TYPE_ m_readDataType;
		std::vector<uint8> m_vecStreamData;
	};
}

#endif



