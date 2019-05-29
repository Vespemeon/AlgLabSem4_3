#include "RedBlackNode.h"

template <class Key, class Value>
RedBlackNode<Key, Value>::RedBlackNode() {

}

template <class Key, class Value>
RedBlackNode<Key, Value>::RedBlackNode(Key key, Value val) {
	this->key = key;
	this->val = val;
}

template <class Key, class Value>
RedBlackNode<Key, Value>::~RedBlackNode() {

}

template <class Key, class Value>
Key RedBlackNode<Key, Value>::getKey() {
	return key;
}

template <class Key, class Value>
Value RedBlackNode<Key, Value>::getVal() {
	return val;
}

template <class Key, class Value>
bool RedBlackNode<Key, Value>::isBlack() {
	return black;
}

template <class Key_, class Value_>
std::ostream& operator<<(std::ostream& stream, RedBlackNode<Key_, Value_>& node) {
	stream << "Key: " << node.key << ", Value: " << node.val;
	if (node.black)
		stream << ", Color: black\n";
	else
		stream << ", Color: red\n";

	return stream;
}

template <class Key, class Value>
bool RedBlackNode<Key, Value>::isLeft() {
	if (!upper)
		return false;

	if (upper->left == this)
		return true;
	else
		return false;
}

template <class Key, class Value>
bool RedBlackNode<Key, Value>::isRight() {
	if (!upper)
		return false;

	if (upper->right == this)
		return true;
	else
		return false;
}

template <class Key, class Value>
RedBlackNode<Key, Value> *RedBlackNode<Key, Value>::grandpa() {
	if (upper)
		return upper->upper;

	return nullptr;
}