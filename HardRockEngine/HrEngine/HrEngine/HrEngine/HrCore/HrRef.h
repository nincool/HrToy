#ifndef _HR_REF_H_
#define _HR_REF_H_

#include "HrEngineCommon.h"

namespace Hr
{
	class CHrRef
	{
	protected:
		CHrRef();
	public:
		virtual ~CHrRef();

	public:
		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 * 
		 * Retains the ownership.
		 * 
		 * This increase the Ref's reference count.
		*/
		void Retain();

		/**
		*	@Brief:  [3/22/2015 By Hr]
		*
		* Releases the ownership immediately.
		*
		* This decrements the Ref's reference count.
		*
		* If the reference count reaches 0 after the descrement, this Ref is destructed.
		*/
		void Release();

		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 * Releases the ownership sometime soon automatically.
		 *
		 * This descrements the Ref's reference count at the end of current
		 * autorelease pool block.
		 *
		 * If the reference count reaches 0 after the descrement, this Ref is
		 * destructed.
		*/
		CHrRef* AutoRelease();

		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 *
		 * Returns the Ref's current reference count.
		*/
		uint GetReferenceCount() const;

	protected:
		uint m_nReferenceCount;
	};

}

#endif


