#ifndef LISTNODE_H
#define LISTNODE_H

#include "List.h"

template <class Data>
class ListNode {
public:
	template <class Data> friend class List;

	ListNode(Data data);

	~ListNode();

	ListNode<Data> *prev;
	ListNode<Data> *next;

	Data data;
};

#include "ListNode.cpp"

#endif