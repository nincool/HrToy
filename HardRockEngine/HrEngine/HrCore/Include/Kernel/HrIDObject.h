#ifndef _HR_IDOBJECT_H_
#define _HR_IDOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	typedef uint32 IDType;
	
	class HrRef
	{
	public:
		HrRef() { m_nReferenceCount = 1; }
		
		void Retain() { ++m_nReferenceCount; }
		void Release() { --m_nReferenceCount; }

		uint32 GetReferenceCount() const { return m_nReferenceCount; }
	protected:
		uint32 m_nReferenceCount;
	};

	class HrID
	{
	public:
		template <typename T> static IDType GenerateID()
		{
			static IDType g_currentID = 0;
			return ++g_currentID;
		}
	};

	class HrIDObject : public HrRef
	{
	public:
		HrIDObject(IDType id) : m_nID(id){}

		IDType GetID() const { return m_nID; }
	private:
		IDType m_nID;
	};
}


#endif


