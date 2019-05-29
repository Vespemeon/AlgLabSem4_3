#include "ListIterator.h"

template <class Data>
ListIterator<Data>::ListIterator() {

}

template <class Data>
ListIterator<Data>::~ListIterator() {

}

template <class Data>
bool ListIterator<Data>::notNul() {
	return (curr ? true : false);
}

template<class Data>
bool ListIterator<Data>::hasNext()
{
	if (notNul())
		if (curr->next)
			return true;

	return false;
}

template<class Data>
bool ListIterator<Data>::hasPrev()
{
	if (notNul())
		if (curr->prev)
			return true;

	return false;
}

template<class Data>
void ListIterator<Data>::goBegin() {
	while (hasPrev())
		curr = curr->prev;
}

template<class Data>
void ListIterator<Data>::goEnd() {
	while (hasNext())
		curr = curr->next;
}

template<class Data>
void ListIterator<Data>::goNext() {
	if (hasNext())
		curr = curr->next;
}

template<class Data>
void ListIterator<Data>::goPrev() {
	if (hasPrev())
		curr = curr->prev;
}

template <class Data>
Data ListIterator<Data>::getData() {
	return curr->data;
}