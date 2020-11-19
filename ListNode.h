#ifndef CPSC_350_DLL_NODE_H
#define CPSC_350_DLL_NODE_H

template <typename T>
struct ListNode
{
	ListNode(const T & d) : data(d), next(nullptr), prev(nullptr) {}

	T data;
	ListNode* next;
	ListNode* prev;
};

#endif