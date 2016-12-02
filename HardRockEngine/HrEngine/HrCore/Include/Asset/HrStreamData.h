#ifndef _HR_STREAMDATA_H_
#define _HR_STREAMDATA_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrStreamData
	{
	public:
		HrStreamData();
		HrStreamData(uint32 nStreamLength);
		~HrStreamData();

		HrStreamData& operator=(HrStreamData& streamData);
		
		void CopyFrom(HrStreamData& streamData);

		Byte* ResizeBuffer(uint64 nLength);
		Byte* GetBufferPoint();
		const Byte* GetBufferPoint() const;
		
		uint64 GetBufferSize();
		uint64 GetBufferSizeWithoutNULLTerminator();

		void ClearBuffer();
		void AddBuffer(Byte* pData, uint32 nSize);
	private:
		std::vector<Byte> m_vecStreamData;
	};
}

#endif



