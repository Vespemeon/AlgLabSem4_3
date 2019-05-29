#include "ListNode.h"

template <class Data>
ListNode<Data>::ListNode(Data data) {
	this->data = data;
	this->prev = nullptr;
	this->next = nullptr;
}

template <class Data>
ListNode<Data>::~ListNode() {
	prev = nullptr;
	next = nullptr;
}