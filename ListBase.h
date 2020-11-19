#ifndef CPSC_350_LIST_BASE_H
#define CPSC_350_LIST_BASE_H
#include <cstddef>
template <typename T>
class ListBase
{
public:

	ListBase() : size(0) {}
	virtual ~ListBase() { size = 0; }

	virtual void insertFront(const T& d) = 0;
	virtual void insertBack(const T& d) = 0;
	virtual T removeFront() = 0;	// Assumes size >= 1
	virtual T removeBack() = 0;	// Assumes size >= 1
	virtual T deletePos(size_t pos) = 0;	// Assumes pos < size.
	virtual void clear() = 0;

	bool empty() const { return size == 0; }

	size_t getSize() const { return size; }

protected:

	size_t size;

};

#endif
