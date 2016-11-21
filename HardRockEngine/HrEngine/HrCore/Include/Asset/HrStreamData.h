#ifndef _HR_STREAMDATA_H_
#define _HR_STREAMDATA_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrStreamData
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

		byte_t* ResizeBuffer(uint64 nLength);
		byte_t* GetBufferPoint();
		const byte_t* GetBufferPoint() const;
		
		uint64 GetBufferSize();
		uint64 GetBufferSizeWithoutNULLTerminator();

		void ClearBuffer();
		void AddBuffer(uint8* pData, uint32 nSize);
	private:
		EnumReadDataType m_readDataType;
		std::vector<byte_t> m_vecStreamData;
		uint8* m_pStreamData;
		uint32 m_nStreamLength;
	};
}

#endif



