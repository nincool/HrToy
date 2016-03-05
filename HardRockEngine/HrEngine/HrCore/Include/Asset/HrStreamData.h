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

		enum EnumReadDataType
		{
			RDT_TXT,
			RDT_BINARY,
		};

		void SetReadDataType(EnumReadDataType readDataType);
		//���ٶ�Ӧ�ռ�
		char* ResizeBuffer(uint64 nLength);
		char* GetBufferPoint();
		uint64 GetBufferSize();
	private:
		EnumReadDataType m_readDataType;
		std::vector<uint8> m_vecStreamData;
	};
}

#endif



