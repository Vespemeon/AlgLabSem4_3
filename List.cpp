#include "List.h"

template <class Data>
List<Data>::List() {

}

template <class Data>
List<Data>::List(std::initializer_list<Data> list) {
	this->head = nullptr;
	this->tail = nullptr;

	for (auto elem : list) {
		this->push_back(elem);
	}

	it->curr = head;
}

template <class Data>
List<Data>::~List() {
	clear();
};

template <class Data>
void List<Data>::push_back(Data data) {
	ListNode<Data> *node = new ListNode<Data>(data);

	if (head == nullptr) {
		head = node;
		tail = node;

		it->curr = node;
	}
	else {
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

template <class Data>
void List<Data>::push_front(Data data) {
	ListNode<Data> *node = new ListNode<Data>(data);

	if (head == nullptr) {
		head = node;
		tail = node;

		it->curr = node;
	}
	else {
		head->prev = node;
		node->next = head;
		head = node;
	}
}

template <class Data>
Data List<Data>::pop_back() {
	if (tail == nullptr) {
		throw(std::out_of_range("Pop back empty list"));
	}

	ListNode<Data> *node = tail->prev;

	if (node != nullptr) {
		node->next = nullptr;

		if (it->curr == tail)
			it->curr = node;
	}
	else {
		head = nullptr;

		it->curr = nullptr;
	}

	Data delData = tail->data;

	delete tail;
	tail = node;

	return delData;
}

template <class Data>
Data List<Data>::pop_front() {
	if (head == nullptr) {
		throw(std::out_of_range("Pop front empty list"));
	}

	ListNode<Data> *node = head->next;

	if (node != nullptr) {
		node->prev = nullptr;

		if (it->curr == head)
			it->curr = node;
	}
	else {
		tail = nullptr;

		it->curr = nullptr;
	}

	Data delData = head->data;

	delete head;
	head = node;

	return delData;
}

template <class Data>
size_t List<Data>::get_size() {
	size_t size = 0;
	ListNode<Data> *node = head;
	while (node != nullptr) {
		node = node->next;
		++size;
	}
	return size;
}

template <class Data>
void List<Data>::insert(Data data, size_t index) {
	if (head == nullptr) {
		throw(std::out_of_range("Insert empty list"));
	}
	if (int(index) < 0) {
		throw(std::invalid_argument("Insert negative argument"));
	}
	if (index + 1 > get_size()) {
		throw(std::out_of_range("Insert nonexistent index"));
	}

	ListNode<Data> *node = head;
	for (size_t currInd = 0; currInd < index; ++currInd) {
		node = node->next;
	}

	ListNode<Data> *addNode = new ListNode<Data>(data);

	addNode->next = node;
	addNode->prev = node->prev;

	if (node->next == nullptr) {
		tail = addNode;
	}
	else if (node->prev == nullptr) {
		head = addNode;
	}
	if (node->prev != nullptr) {
		node->prev->next = addNode;
	}

	node->prev = addNode;
}

template <class Data>
Data List<Data>::at(size_t index) {
	if (head == nullptr) {
		throw(std::out_of_range("At empty list"));
	}
	if (int(index) < 0) {
		throw(std::invalid_argument("At negative argument"));
	}
	if (index + 1 > get_size()) {
		throw(std::out_of_range("At nonexistent index"));
	}

	ListNode<Data> *node = head;
	for (size_t currInd = 0; currInd < index; ++currInd) {
		node = node->next;
	}

	return node->data;
}

template <class Data>
Data List<Data>::remove(size_t index) {
	if (head == nullptr) {
		throw(std::out_of_range("Remove empty list"));
	}
	if (int(index) < 0) {
		throw(std::invalid_argument("Remove negative argument"));
	}
	if (index + 1 > get_size()) {
		throw(std::out_of_range("Remove nonexistent index"));
	}

	ListNode<Data> *node = head;
	for (size_t currInd = 0; currInd < index; ++currInd) {
		node = node->next;
	}

	if (index != 0) {
		node->prev->next = node->next;
	}

	if (node != tail) {
		node->next->prev = node->prev;
	}
	else {
		tail = node->prev;
	}

	if (index == 0) {
		head = node->next;
		it->curr = nullptr;
	}
	else {
		if (it->curr == node)
			if (it->hasPrev())
				it->goPrev();
			else if (it->hasNext())
				it->goNext();
			else
				it = nullptr;
	}

	Data delData = node->data;

	delete node;
	return delData;
}

template <class Data>
void List<Data>::clear() {
	if (head == nullptr) {
		return;
	}

	ListNode<Data> *node = head;
	ListNode<Data> *toDelete = head;

	while (node != nullptr) {
		node = node->next;
		delete toDelete;
		toDelete = node;
	}

	it->curr = nullptr;
}

template <class Data>
void List<Data>::set(Data data, size_t index) {
	if (head == nullptr) {
		throw(std::out_of_range("Set empty list"));
	}
	if (int(index) < 0) {
		throw(std::invalid_argument("Set negative argument"));
	}
	if (index + 1 > get_size()) {
		throw(std::out_of_range("Set nonexistent index"));
	}

	ListNode<Data> *node = head;
	for (size_t currInd = 0; currInd < index; ++currInd) {
		node = node->next;
	}
	node->data = data;
}

template <class Data>
bool List<Data>::isEmpty() {
	if (head == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

template <class Data>
std::ostream& operator<< (std::ostream &out, const List<Data> &list) {
	ListNode<Data> *node = list.head;

	if (!node) {
		out << "An empty list.\n";
		return out;
	}

	while (node != nullptr) {
		out << node->data;
		node = node->next;
		if (node != nullptr) {
			out << ", ";
		}
	}

	return out;
}