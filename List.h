#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include "ListIterator.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <class Data>
class List {
public:
	template <class Data> friend class ListIterator;

	ListIterator<Data> *it = new ListIterator<Data>();

	List();
	List(std::initializer_list<Data> list);
	~List();

	void push_back(Data data);
	void push_front(Data data);
	Data pop_back();
	Data pop_front();
	size_t get_size();
	void insert(Data data, size_t index);
	Data at(size_t index);
	Data remove(size_t index);
	void clear();
	void set(Data data, size_t index);
	bool isEmpty();

	template <class Data>
	friend std::ostream& operator<< (std::ostream &out, const List<Data> &list);

private:
	ListNode<Data> *head = nullptr;
	ListNode<Data> *tail = nullptr;
};

#include "List.cpp"

#endif