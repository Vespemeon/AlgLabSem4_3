#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "List.h"

template <class Data>
class ListIterator {
private:
	ListNode<Data> *curr = nullptr;
public:
	template <class Data> friend class List;

	ListIterator();
	ListIterator(List<Data> *list) {
		curr = list->head;
	}

	~ListIterator();

	bool notNul();

	bool hasNext();
	bool hasPrev();

	void goBegin();
	void goEnd();

	void goNext();
	void goPrev();
		
	Data getData();
};

#include "ListIterator.cpp"

#endif