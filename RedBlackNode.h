#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

#include <iostream>

template <class Key, class Value>
class RedBlackNode {
public:
	RedBlackNode();
	RedBlackNode(Key key, Value val);
	~RedBlackNode();

	Key getKey();
	Value getVal();
	bool isBlack();

	template <class Key_, class Value_>
	friend std::ostream& operator<<(std::ostream& stream, RedBlackNode<Key_, Value_>& node);

private:
	template <class Key, class Value> friend class RedBlackTree;
	template <class Key, class Value> friend class RedBlackIterator;

	bool black = false;

	RedBlackNode *left = nullptr;
	RedBlackNode *right = nullptr;
	RedBlackNode *upper = nullptr;

	Key key;
	Value val;

	bool isLeft();
	bool isRight();

	RedBlackNode<Key, Value> *grandpa();
};

#include "RedBlackNode.cpp"

#endif