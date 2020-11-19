#ifndef CPSC_350_QUEUE_H
#define CPSC_350_QUEUE_H

#include "DoublyLinkedList.h"
#include <cstddef>
template <typename T>
class Queue
{
public:

	Queue() : list() {}

	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;

	void push(const T& item) { list.insertBack(item); }
	void pop() { list.removeFront(); }
	T& front() { return list.getFront(); }
	void clear() { list.clear(); }
	bool empty() const { return list.empty(); }
	size_t getSize() const { return list.getSize(); }

private:

	DoublyLinkedList<T> list;
};

#endif
