#ifndef _HR_STACK_H_
#define _HR_STACK_H_

#include <stdexcept>

template <typename T, int MAXSIZE>
class HrStack
{
private:
	T elems[MAXSIZE];
	int nNumElems;

public:
	HrStack();
	void push( const T& );
	void pop();
	T top() const;
	bool empty() const
	{
		return nNumElems == 0;
	}
	bool full() const
	{
		return nNumElems == MAXSIZE;
	}
};

template<typename T, int MAXSIZE>
HrStack<T, MAXSIZE>::HrStack() :nNumElems(0)
{
}

template <typename T, int MAXSIZE>
void HrStack<T, MAXSIZE>::push( const T& elem )
{
	if (nNumElems == MAXSIZE)
	{
		throw std::out_of_range( "Stack<>::push:stack is full" );
	}
	elems[nNumElems] = elem;
	++nNumElems;
}

template <typename T, int MAXSIZE>
void HrStack<T, MAXSIZE>::pop()
{
	if (nNumElems <= 0)
	{
		throw std::out_of_range( "Stack<>::pop():empty stack." );
	}
	--nNumElems;
}

template <typename T, int MAXSIZE>
T HrStack<T, MAXSIZE>::top() const
{
	if (nNumElems <= 0)
	{
		throw std::out_of_range( "Stack<>::pop():empty stack." );
	}
	return elems[nNumElems - 1];
}

#endif




