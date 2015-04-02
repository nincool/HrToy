/************************************************************************
*
*   @Comment：CAS原子操作——Compare & Set，或是 Compare & Swap
*			   现在几乎所image有的CPU指令都支持CAS的原子操作，X86下对应的是 CMPXCHG 汇编指令
*				C++11 标准库 std::atomic 提供了针对整形(integral)和指针类型的特化实现，分别定义如下：
*
*				针对整形(integal)的特化，其中 integal 代表了如下类型:
*				char, signed char, unsigned char, short, unsigned short, 
*				int, unsigned int, long, unsigned long, long long, 
*				unsigned long long, char16_t, char32_t, wchar_t;
*   @Author: Hr
*   @Date: [3/31/2015 By Hr]
*
************************************************************************/

#ifndef _HR_INTERLOCKED_H_
#define _HR_INTERLOCKED_H_

#include <boost/utility.hpp>

//平台无关
#define STD_ATOMIC
#undef  STD_ATOMIC

#ifdef STD_ATOMIC 
#define NX_STD
#else
#if defined(WINCE) || defined(_WIN32_WCE)
#   define NX_OS_WINCE
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#   define NX_OS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define NX_OS_WIN32
#elif defined(__linux__) || defined(__linux)
#   define NX_OS_LINUX
#else
#   error "This OS is unsupported"
#endif

#endif //STD_ATOMIC

#if defined(NX_OS_WIN32) || defined(NX_OS_WIN64) || defined(NX_OS_WINCE)
#   define NX_OS_WIN
#else
#   define NX_OS_UNIX
#endif


#if defined(_MSC_VER)
#   if (_MSC_VER <= 1200)
#       define NX_CC_MSVC6
#   endif
#   define NX_CC_MSVC
#elif defined(__GNUC__)
#   define NX_CC_GNUC
#else
#   error "This CC is unsupported"
#endif

namespace HrAtomic
{
#if defined(NX_OS_WIN32) || defined(NX_OS_WINCE)
	typedef volatile long   type_t;
	typedef long            norm_t;
#elif defined(NX_OS_WIN64)
	typedef volatile LONG64 type_t;
	typedef LONG64          norm_t;
#elif defined(STD_ATOMIC)
	typedef volatile long   type_t;
	typedef long            norm_t;
#else
	typedef volatile long   type_t;
	typedef long            norm_t;
#endif
}

//////////////////////////////////////////////////////////////////////////

#if defined(NX_CC_GNUC)

#   define nx_atomic_inc(var)           __sync_fetch_and_add        (&(var), 1)
#   define nx_atomic_dec(var)           __sync_fetch_and_sub        (&(var), 1)
#   define nx_atomic_add(var, val)      __sync_fetch_and_add        (&(var), (val))
#   define nx_atomic_sub(var, val)      __sync_fetch_and_sub        (&(var), (val))
#   define nx_atomic_set(var, val)      __sync_lock_test_and_set    (&(var), (val))
#   define nx_atomic_cas(var, cmp, val) __sync_bool_compare_and_swap(&(var), (cmp), (val))

#elif defined(NX_OS_WIN32) || defined(NX_OS_WINCE)

#include <windows.h>

#   define nx_atomic_inc(var)           InterlockedExchangeAdd      (&(var), 1)
#   define nx_atomic_dec(var)           InterlockedExchangeAdd      (&(var),-1)
#   define nx_atomic_add(var, val)      InterlockedExchangeAdd      (&(var), (val))
#   define nx_atomic_sub(var, val)      InterlockedExchangeAdd      (&(var),-(val))
#   define nx_atomic_set(var, val)      InterlockedExchange         (&(var), (val))

/**
 *	@Brief: The function compares the Destination value with the Comparand value.
			 If the Destination value is equal to the Comparand value, 
			 the Exchange value is stored in the address specified by Destination. 
			 Otherwise, no operation is performed [3/31/2015 By Hr]
 *  Parameters

	 Destination [in, out]
		A pointer to the destination value.
	 Exchange [in]
		The exchange value.
	 Comparand [in]
		The value to compare to Destination.
	 Return value
		The function returns the initial value of the Destination parameter.
*/

#   define nx_atomic_cas(var, cmp, val) ((cmp) == InterlockedCompareExchange(&(var), (val), (cmp)))

#elif defined(NX_OS_WIN64)

#include <windows.h>

#   define nx_atomic_inc(var)           InterlockedExchangeAdd64    (&(var), 1)
#   define nx_atomic_dec(var)           InterlockedExchangeAdd64    (&(var),-1)
#   define nx_atomic_add(var, val)      InterlockedExchangeAdd64    (&(var), (val))
#   define nx_atomic_sub(var, val)      InterlockedExchangeAdd64    (&(var),-(val))
#   define nx_atomic_set(var, val)      InterlockedExchange64       (&(var), (val))
#   define nx_atomic_cas(var, cmp, val) ((cmp) == InterlockedCompareExchange64(&(var), (val), (cmp)))

#elif defined(STD_ATOMIC)



#define nx_atomic_inc(var) 

#else
#   error "This platform is unsupported"
#endif

/* Win API
while(1)
{
	LONG lOldSize = g_lSize;
	if (lOldSize  == InterlockedCompareExchange(&g_lSize, lOldSize + lAdd, lOldSize))
	{
		break;
	}
}
//////////////////////////////////////////////////////////////////////////////
STL Atomic
// atomic::compare_exchange_weak example:
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector

// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head( nullptr );

void append( int val ) {     // append an element to the list
	Node* oldHead = list_head;
	Node* newNode = new Node{ val, oldHead };

	// what follows is equivalent to: list_head = newNode, but in a thread-safe way:
	while (!list_head.compare_exchange_weak( oldHead, newNode ))
		newNode->next = oldHead;
}

int main()
{
	// spawn 10 threads to fill the linked list:
	std::vector<std::thread> threads;
	for (int i = 0; i < 10; ++i) threads.push_back( std::thread( append, i ) );
	for (auto& th : threads) th.join();

	// print contents:
	for (Node* it = list_head; it != nullptr; it = it->next)
		std::cout << ' ' << it->value;
	std::cout << '\n';

	// cleanup:
	Node* it; while (it = list_head) { list_head = it->next; delete it; }

	return 0;
}
*/

#ifndef STD_ATOMIC

static inline HrAtomic::norm_t atomic_inc( HrAtomic::type_t& v )
{
	return nx_atomic_inc( v );
}
static inline HrAtomic::norm_t atomic_inc( HrAtomic::type_t& v, HrAtomic::norm_t n )
{
	return nx_atomic_add( v, n );
}
static inline HrAtomic::norm_t atomic_dec( HrAtomic::type_t& v )
{
	return nx_atomic_dec( v );
}
static inline HrAtomic::norm_t atomic_dec( HrAtomic::type_t& v, HrAtomic::norm_t n )
{
	return nx_atomic_sub( v, n );
}
static inline HrAtomic::norm_t atomic_set( HrAtomic::type_t& v, HrAtomic::norm_t n )
{
	return nx_atomic_set( v, n );
}
static inline bool atomic_cas( HrAtomic::type_t& v, HrAtomic::norm_t c, HrAtomic::norm_t n )
{
	return nx_atomic_cas( v, c, n );
}


////////////////////////////////////////////////////////////////////////////
//Lock
namespace HrAtomic
{
	static inline void yield( void )
	{
#   if defined(NX_OS_WINCE)
		Sleep( 5 );
#   elif defined(NX_OS_WIN)
		SwitchToThread();
#   else 
		pthread_yield();
#   endif
	}
}

#endif STD_ATOMIC


#endif


/*
* 单生产者-单消费者模型
*
	
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize = 10; // Item buffer size.
static const int kItemsToProduce = 1000;   // How many items we plan to produce.

struct ItemRepository {
	int item_buffer[kItemRepositorySize]; // 产品缓冲区, 配合 read_position 和 write_position 模型环形队列.
	size_t read_position; // 消费者读取产品位置.
	size_t write_position; // 生产者写入产品位置.
	std::mutex mtx; // 互斥量,保护产品缓冲区
	std::condition_variable repo_not_full; // 条件变量, 指示产品缓冲区不为满.
	std::condition_variable repo_not_empty; // 条件变量, 指示产品缓冲区不为空.
} gItemRepository; // 产品库全局变量, 生产者和消费者操作该变量.
typedef struct ItemRepository ItemRepository;

void ProduceItem( ItemRepository *ir, int item )
{
	std::unique_lock<std::mutex> lock( ir->mtx );
	while (((ir->write_position + 1) % kItemRepositorySize)
		== ir->read_position) { // item buffer is full, just wait here.
		std::cout << "Producer is waiting for an empty slot...\n";
		(ir->repo_not_full).wait( lock ); // 生产者等待"产品库缓冲区不为满"这一条件发生.
	}

	(ir->item_buffer)[ir->write_position] = item; // 写入产品.
	(ir->write_position)++; // 写入位置后移.

	if (ir->write_position == kItemRepositorySize) // 写入位置若是在队列最后则重新设置为初始位置.
		ir->write_position = 0;

	(ir->repo_not_empty).notify_all(); // 通知消费者产品库不为空.
	lock.unlock(); // 解锁.
}

int ConsumeItem( ItemRepository *ir )
{
	int data;
	std::unique_lock<std::mutex> lock( ir->mtx );
	// item buffer is empty, just wait here.
	while (ir->write_position == ir->read_position) {
		std::cout << "Consumer is waiting for items...\n";
		(ir->repo_not_empty).wait( lock ); // 消费者等待"产品库缓冲区不为空"这一条件发生.
	}

	data = (ir->item_buffer)[ir->read_position]; // 读取某一产品
	(ir->read_position)++; // 读取位置后移

	if (ir->read_position >= kItemRepositorySize) // 读取位置若移到最后，则重新置位.
		ir->read_position = 0;

	(ir->repo_not_full).notify_all(); // 通知消费者产品库不为满.
	lock.unlock(); // 解锁.

	return data; // 返回产品.
}


void ProducerTask() // 生产者任务
{
	for (int i = 1; i <= kItemsToProduce; ++i) {
		// sleep(1);
		std::cout << "Produce the " << i << "^th item..." << std::endl;
		ProduceItem( &gItemRepository, i ); // 循环生产 kItemsToProduce 个产品.
	}
}

void ConsumerTask() // 消费者任务
{
	static int cnt = 0;
	while (1) {
		std::this_thread::yield();
		int item = ConsumeItem( &gItemRepository ); // 消费一个产品.
		std::cout << "Consume the " << item << "^th item" << std::endl;
		if (++cnt == kItemsToProduce) break; // 如果产品消费个数为 kItemsToProduce, 则退出.
	}
}

void InitItemRepository( ItemRepository *ir )
{
	ir->write_position = 0; // 初始化产品写入位置.
	ir->read_position = 0; // 初始化产品读取位置.
}

int main()
{
	InitItemRepository( &gItemRepository );
	std::thread producer( ProducerTask ); // 创建生产者线程.
	std::thread consumer( ConsumerTask ); // 创建消费之线程.
	producer.join();
	consumer.join();
}

****************多生产者-多消费者模型

#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize  = 4; // Item buffer size.
static const int kItemsToProduce  = 10;   // How many items we plan to produce.

struct ItemRepository {
    int item_buffer[kItemRepositorySize];
    size_t read_position;
    size_t write_position;
    size_t produced_item_counter;
    size_t consumed_item_counter;
    std::mutex mtx;
    std::mutex produced_item_counter_mtx;
    std::mutex consumed_item_counter_mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} gItemRepository;

typedef struct ItemRepository ItemRepository;


void ProduceItem(ItemRepository *ir, int item)
{
    std::unique_lock<std::mutex> lock(ir->mtx);
    while(((ir->write_position + 1) % kItemRepositorySize)
        == ir->read_position) { // item buffer is full, just wait here.
        std::cout << "Producer is waiting for an empty slot...\n";
        (ir->repo_not_full).wait(lock);
    }

    (ir->item_buffer)[ir->write_position] = item;
    (ir->write_position)++;

    if (ir->write_position == kItemRepositorySize)
        ir->write_position = 0;

    (ir->repo_not_empty).notify_all();
    lock.unlock();
}

int ConsumeItem(ItemRepository *ir)
{
    int data;
    std::unique_lock<std::mutex> lock(ir->mtx);
    // item buffer is empty, just wait here.
    while(ir->write_position == ir->read_position) {
        std::cout << "Consumer is waiting for items...\n";
        (ir->repo_not_empty).wait(lock);
    }

    data = (ir->item_buffer)[ir->read_position];
    (ir->read_position)++;

    if (ir->read_position >= kItemRepositorySize)
        ir->read_position = 0;

    (ir->repo_not_full).notify_all();
    lock.unlock();

    return data;
}

void ProducerTask()
{
    bool ready_to_exit = false;
    while(1) {
        sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.produced_item_counter_mtx);
        if (gItemRepository.produced_item_counter < kItemsToProduce) {
            ++(gItemRepository.produced_item_counter);
            ProduceItem(&gItemRepository, gItemRepository.produced_item_counter);
            std::cout << "Producer thread " << std::this_thread::get_id()
                << " is producing the " << gItemRepository.produced_item_counter
                << "^th item" << std::endl;
        } else ready_to_exit = true;
        lock.unlock();
        if (ready_to_exit == true) break;
    }
    std::cout << "Producer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void ConsumerTask()
{
    bool ready_to_exit = false;
    while(1) {
        sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.consumed_item_counter_mtx);
        if (gItemRepository.consumed_item_counter < kItemsToProduce) {
            int item = ConsumeItem(&gItemRepository);
            ++(gItemRepository.consumed_item_counter);
            std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is consuming the " << item << "^th item" << std::endl;
        } else ready_to_exit = true;
        lock.unlock();
        if (ready_to_exit == true) break;
    }
    std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void InitItemRepository(ItemRepository *ir)
{
    ir->write_position = 0;
    ir->read_position = 0;
    ir->produced_item_counter = 0;
    ir->consumed_item_counter = 0;
}

int main()
{
    InitItemRepository(&gItemRepository);
    std::thread producer1(ProducerTask);
    std::thread producer2(ProducerTask);
    std::thread producer3(ProducerTask);
    std::thread producer4(ProducerTask);

    std::thread consumer1(ConsumerTask);
    std::thread consumer2(ConsumerTask);
    std::thread consumer3(ConsumerTask);
    std::thread consumer4(ConsumerTask);

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();

    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
}


*/

