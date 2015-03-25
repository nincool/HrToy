#ifndef _HR_AUTORELEASEPOOL_H_
#define _HR_AUTORELEASEPOOL_H_

#include "HrEngineCom.h" 
#include <vector>

namespace Hr
{
	class CHrRef;
	class CHrAutoReleasePool
	{
	public:
		CHrAutoReleasePool();
		CHrAutoReleasePool( const std::string& name );
		~CHrAutoReleasePool();
		
		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 * Add a given object to this pool.
		 *
		 * The same object may be added several times to the same pool; When the
		 * pool is destructed, the object's Ref::release() method will be called
		 * for each time it was added.
		*/
		void AddObject( CHrRef* pRef );

		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 *
		 * Clear the autorelease pool.
		 *
		 * Ref::release() will be called for each time the managed object is
		 * added to the pool
		*/
		void Clear();

		/*
			@brief	Whether the pool is doing `clear` operation. [3/22/2015 By Hr] 	
		*/
		bool isClearing() const { return m_bIsClearing; }

		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 * Checks whether the pool contains the specified object.
		*/
		bool Contains( CHrRef* pRef ) const;

		/**
		 *	@Brief:  [3/22/2015 By Hr]
		 *
		 * Dump the objects that are put into autorelease pool. It is used for debugging.
		 *
		 * The result will look like:
		 * Object pointer address     object id     reference count
		*/
		void Dump();
	private:
		
		std::vector<CHrRef*> m_vecManagedObject;
		
		/*
			@brief	The flag for checking whether the pool is doing `clear` operation. [3/22/2015 By Hr] 	
		*/
		bool m_bIsClearing;

		std::string m_strName;
	};


	class CHrReleaseManager
	{
	public:

		static CHrReleaseManager* Instance();

		/**
		* Get current auto release pool, there is at least one auto release pool that created by engine.
		* You can create your own auto release pool at demand, which will be put into auto releae pool stack.
		*/
		CHrAutoReleasePool* GetCurrentPool() const;

		bool IsObjectInPools( CHrRef* pRef ) const;

		static void DestroyInstance();


		//friend--
		friend class CHrAutoReleasePool;
	private:
		CHrReleaseManager();
		~CHrReleaseManager();

		void Push(CHrAutoReleasePool* pReleasePool);
		void Pop();

		static CHrReleaseManager* m_s_instance;

		std::vector<CHrAutoReleasePool*> m_vecReleaseStack;

	};

}


#endif



