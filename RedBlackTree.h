#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "RedBlackNode.h"
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <class Key, class Value>
class RedBlackTree {
private:
	RedBlackNode<Key, Value> *root = nullptr;

	void leftRotate(RedBlackNode<Key, Value> *x);
	void rightRotate(RedBlackNode<Key, Value> *x);

	void insertCase1(RedBlackNode<Key, Value> *node);
	void insertCase2(RedBlackNode<Key, Value> *node);
	void insertCase3(RedBlackNode<Key, Value> *node);
	void insertCase4(RedBlackNode<Key, Value> *node);
	void insertCase5(RedBlackNode<Key, Value> *node);
	RedBlackNode<Key, Value> *findToInsert(Key key);

	void fixDelete(RedBlackNode<Key, Value> *node);

	void postorderDelete(RedBlackNode<Key, Value> *node);
	void LNRKey(List<Key> *list, RedBlackNode<Key, Value> *node);
	void LNRValue(List<Value> *list, RedBlackNode<Key, Value> *node);
	void LNRNode(List<RedBlackNode<Key, Value>> *list, RedBlackNode<Key, Value> *node);
	void printFromNode(RedBlackNode<Key, Value> *node, size_t level, bool left_or_right);

public:
	RedBlackTree();
	~RedBlackTree();

	RedBlackTree(std::initializer_list<Key> list, Value val);
	RedBlackTree(List<Key> *list, Value val);

	template <class Key_, class Value_>
	friend std::ostream& operator<<(std::ostream& stream, RedBlackTree<Key_, Value_>& tree);

	void insert(Key key, Value val);
	RedBlackNode<Key, Value> *find(Key key);
	void remove(Key key);
	void clear();
	List<Key> *get_keys();
	List<Value> *get_values();
	List<RedBlackNode<Key, Value>> *get_nodes();
};

#include "RedBlackTree.cpp"

#endif