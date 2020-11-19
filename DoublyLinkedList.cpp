#include "DoublyLinkedList.h"
#include <cstddef>
#ifndef CPSC_350_DLL_CPP
#define CPSC_350_DLL_CPP

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : ListBase<T>()
{
    front = nullptr;
    back = nullptr;
}
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
template <typename T>
void DoublyLinkedList<T>::insertFront(const T& d) {
    ListNode<T>* node = new ListNode<T>(d);
    if (this->empty()) {
        back = node;
    }
    else {
        front->prev = node;
        node->next = front;
    }
    front = node;
    ++this->size;
}
template <typename T>
void DoublyLinkedList<T>::insertBack(const T& d) {
    ListNode<T>* node = new ListNode<T>(d);
    if (this->empty()) {
        front = node;
    }
    else {
        back->next = node;
        node->prev = back;
    }
    back = node;
    ++this->size;
}
template <typename T>
T DoublyLinkedList<T>::removeFront() {
    ListNode<T>* node = front;
    front = front->next;
    node->next = nullptr;

    if (this->getSize() == 1) {
        back = nullptr;
    } else {
        front->prev = nullptr;
    }

    T temp = node->data;
    this->size--;
    delete node;
    node = nullptr;
    return temp;
}
template <typename T>
T DoublyLinkedList<T>::removeBack() {
    ListNode<T>* node = back;
    back = back->prev;
    node->prev = nullptr;

    if (this->getSize() == 1) {
        front = nullptr;
    } else {
        back->next = nullptr;
    }

    T temp = node->data;
    this->size--;
    delete node;
    node = nullptr;
    return temp;
}
template<typename T>
T& DoublyLinkedList<T>::getFront()
{
    return front->data;
}
template<typename T>
T& DoublyLinkedList<T>::getBack()
{
    return back->data;
}
template <typename T>
T DoublyLinkedList<T>::deletePos(size_t pos) {

    if (pos == 0) {
        return removeFront();
    }
    if (pos == this->getSize() - 1) {
        return removeBack();
    }

    ListNode<T>* curr = front;
    while (pos > 0) {
        curr = curr->next;
        pos--;
    }

    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    curr->next = nullptr;
    curr->prev = nullptr;
    T temp = curr->data;
    this->size--;
    delete curr;
    curr = nullptr;
    return temp;
}
template <typename T>
void DoublyLinkedList<T>::clear()
{
    while (!this->empty()) {
        removeFront();
    }
}

#endif
