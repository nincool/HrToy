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
		//开辟对应空间
		char* ResizeBuffer(uint64 nLength);
		char* GetBufferPoint();
		uint64 GetBufferSize();

		void ClearBuffer();
		void AddBuffer(char* pData, uint32 nSize);
	private:
		EnumReadDataType m_readDataType;
		std::vector<uint8> m_vecStreamData;
		char* m_pStreamData;
		uint32 m_nStreamLength;
	};
}

#endif



