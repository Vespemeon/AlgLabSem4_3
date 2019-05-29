#include "RedBlackTree.h"

template <class Key, class Value>
void RedBlackTree<Key, Value>::leftRotate(RedBlackNode<Key, Value> *x) {
	RedBlackNode<Key, Value> *y = x->right;

	x->right = y->left;
	if (x->right)
		x->right->upper = x;

	y->upper = x->upper;

	if (x == root) {
		root = y;
	}
	else if (x->isLeft()) {
		y->upper->left = y;
	}
	else {
		y->upper->right = y;
	}

	x->upper = y;
	y->left = x;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::rightRotate(RedBlackNode<Key, Value> *x) {
	RedBlackNode<Key, Value> *y = x->left;

	x->left = y->right;
	if (x->left)
		x->left->upper = x;

	y->upper = x->upper;

	if (x == root) {
		root = y;
	}
	else if (x->isLeft()) {
		y->upper->left = y;
	}
	else {
		y->upper->right = y;
	}

	x->upper = y;
	y->right = x;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertCase1(RedBlackNode<Key, Value> *node) {
	if (!node->upper)
		node->black = true;
	else
		insertCase2(node);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertCase2(RedBlackNode<Key, Value> *node) {
	if (node->upper->black)
		return;
	else
		insertCase3(node);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertCase3(RedBlackNode<Key, Value> *node) {
	RedBlackNode<Key, Value>
		*uncle = nullptr,
		*grandpa = node->grandpa();

	uncle = node->upper->isLeft() ? grandpa->right : grandpa->left;

	if (uncle && !uncle->black) {
		node->upper->black = true;
		uncle->black = true;
		grandpa->black = false;
		insertCase1(grandpa);
	}
	else {
		insertCase4(node);
	}
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertCase4(RedBlackNode<Key, Value> *node) {
	RedBlackNode<Key, Value>
		*grandpa = node->grandpa();

	if (node->isRight() && node->upper->isLeft()) {
		leftRotate(node->upper);
		node = node->left;
	}
	else if (node->isLeft() && node->upper->isRight()) {
		rightRotate(node->upper);
		node = node->right;
	}

	insertCase5(node);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertCase5(RedBlackNode<Key, Value> *node) {
	RedBlackNode<Key, Value>
		*grandpa = node->grandpa();

	node->upper->black = true;
	grandpa->black = false;
	if (node->isLeft() && node->upper->isLeft())
		rightRotate(grandpa);
	else
		leftRotate(grandpa);
}

template <class Key, class Value>
RedBlackNode<Key, Value> *RedBlackTree<Key, Value>::findToInsert(Key key) {
	RedBlackNode<Key, Value> *node = root;
	bool found = false;

	while (!found) {
		if (key >= node->key) {
			if (node->right)
				node = node->right;
			else
				found = true;
		}
		else if (key < node->key) {
			if (node->left)
				node = node->left;
			else
				found = true;
		}
	}

	return node;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::fixDelete(RedBlackNode<Key, Value> *node) {
	
	RedBlackNode<Key, Value> *bro = nullptr;

	while (node != root && node->black) {
		if (node->isLeft()) {
			bro = node->upper->right;
			if (!bro->black) {
				bro->black = true;
				node->upper->black = false;
				leftRotate(node->upper);
				bro = node->upper->right;
			}
			if ((bro->left->black) && (bro->right->black))	{
				bro->black = false;
				node = node->upper;
			}
			else if (bro->right->black) {
				bro->left->black = true;
				bro->black = false;
				rightRotate(bro);
				bro = node->upper->right;
			}
			bro->black = node->upper->black;
			node->upper->black = true;
			leftRotate(node->upper);
			node = root;
		}
		else {
			bro = node->upper->left;
			if (bro->black == false) {
				bro->black = true;
				node->upper->black = false;
				leftRotate(node->upper);
				bro = node->upper->left;
			}
			if (bro->right->black && bro->left->black) {
				bro->black = false;
				node = node->upper;
			}
			else if (bro->left->black) {
				bro->right->black = true;
				bro->black = false;
				rightRotate(bro);
				bro = node->upper->left;
			}
			bro->black = node->upper->black;
			node->upper->black = true;
			leftRotate(node->upper);
			node = root;
		}
	}

	node->black = true;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::postorderDelete(RedBlackNode<Key, Value> *node) {
	if (!node)
		return;

	postorderDelete(node->left);
	postorderDelete(node->right);

	delete node;
	node = nullptr;

	root = nullptr;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::LNRKey(List<Key> *list, RedBlackNode<Key, Value> *node) {
	if (!node)
		return;

	LNRKey(list, node->left);
	list->push_back(node->key);
	LNRKey(list, node->right);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::LNRValue(List<Value> *list, RedBlackNode<Key, Value> *node) {
	if (!node)
		return;

	LNRValue(list, node->left);
	list->push_back(node->val);
	LNRValue(list, node->right);
}

template<class Key, class Value>
void RedBlackTree<Key, Value>::LNRNode(List<RedBlackNode<Key, Value>>* list, RedBlackNode<Key, Value>* node){
	if (!node)
		return;

	LNRNode(list, node->left);
	list->push_back(*node);
	LNRNode(list, node->right);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::printFromNode(RedBlackNode<Key, Value> *node, size_t level, bool left_or_right) {
	if (node != nullptr) {
		printFromNode(node->left, level + 3, true);

		bool strokes = false;

		for (size_t i = 0; i < level; ++i) {
			if (i + 2 == level) {
				strokes = true;
			}

			if (strokes) {
				std::cout << "---";
			}
			else {
				std::cout << "   ";
			}
		}


		if (left_or_right && node != root) {
			std::cout << "L, ";

		}
		else if (node != root) {
			std::cout << "R, ";
		}

		if (node->black) {
			std::cout << "Blk:";
		}
		else {
			std::cout << "Red:";
		}

		std::cout << node->key << ", " << node->val << std::endl;
		printFromNode(node->right, level + 3, false);
	}
}

template <class Key, class Value>
RedBlackTree<Key, Value>::RedBlackTree() {

}

template <class Key, class Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
	clear();
}

template <class Key, class Value>
RedBlackTree<Key, Value>::RedBlackTree(std::initializer_list<Key> list, Value val) {
	for (auto elem : list)
		this->insert(elem, val);
}

template <class Key, class Value>
RedBlackTree<Key, Value>::RedBlackTree(List<Key> *list, Value val) {
	ListIterator<Key> *it = new ListIterator<Key>(list);

	while (it->notNul()) {
		this->insert(it->getData(), val);
		it->goNext();
	}

	delete it;
	it = nullptr;
}

template <class Key, class Value>
std::ostream& operator<<(std::ostream& stream, RedBlackTree<Key, Value>& tree) {
	RedBlackNode<Key, Value> *node = tree.root;
	if (!node) {
		std::cout << "An empty tree.\n";
		return stream;
	}

	tree.printFromNode(tree.root, 0, true);
	return stream;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insert(Key key, Value val) {
	if (!root) {
		root = new RedBlackNode<Key, Value>(key, val);
		insertCase1(root);
		return;
	}

	RedBlackNode<Key, Value> *toInsert = findToInsert(key);

	if (!toInsert)
		return;

	RedBlackNode<Key, Value> *newNode = new RedBlackNode<Key, Value>(key, val);

	if (key >= toInsert->key)
		toInsert->right = newNode;
	else
		toInsert->left = newNode;

	newNode->upper = toInsert;

	insertCase1(newNode);
}

template <class Key, class Value>
RedBlackNode<Key, Value> *RedBlackTree<Key, Value>::find(Key key) {
	RedBlackNode<Key, Value> *node = root;

	if (!node)
		return nullptr;

	bool found = false;

	while (!found) {
		if (key > node->key) {
			if (node->right)
				node = node->right;
			else
				return nullptr;
		}
		else if (key < node->key) {
			if (node->left)
				node = node->left;
			else
				return nullptr;
		}
		else if (key == node->key)
			found = true;
	}

	return node;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::remove(Key key) {
	RedBlackNode<Key, Value> *toRemove = find(key);
	RedBlackNode<Key, Value> *fixNode = nullptr;
	bool blackWasDeleted = false;

	if (!toRemove) {
		return;
	}

	if (toRemove->left && toRemove->right) {
		RedBlackNode<Key, Value>* oldNode = toRemove;
		toRemove = toRemove->right;

		while (toRemove->left)
			toRemove = toRemove->left;

		oldNode->key = toRemove->key;
		oldNode->val = toRemove->val;

		if (toRemove->isLeft())
			toRemove->upper->left = toRemove->right;
		else
			toRemove->upper->right = toRemove->right;
		
		if (toRemove->right) {
			fixNode = toRemove->right;

			toRemove->right->upper = toRemove->upper;

			if (toRemove->black)
				blackWasDeleted = true;
			
			delete toRemove;
			toRemove = nullptr;
		}
		else {
			if (toRemove->black)
				blackWasDeleted = true;

			delete toRemove;
			toRemove = nullptr;
		}
	}
	else if (!toRemove->left && !toRemove->right) {
		if (toRemove->isLeft())
			toRemove->upper->left = nullptr;
		else if (toRemove->isRight())
			toRemove->upper->right = nullptr;

		fixNode = toRemove->upper;

		if (toRemove->black)
			blackWasDeleted = true;

		delete toRemove;
		toRemove = nullptr;
	}

	else {
		RedBlackNode<Key, Value> *child = toRemove->right ? toRemove->right : toRemove->left;

		if (toRemove->isLeft())
			toRemove->upper->left = child;
		else if (toRemove->isRight())
			toRemove->upper->right = child;

		child->upper = toRemove->upper;
		fixNode = child;

		if (toRemove == root) {
			root = child;
			root->black = true;
		}

		if (toRemove->black)
			blackWasDeleted = true;

		delete toRemove;
		toRemove = nullptr;
	}

	if (toRemove)
		fixDelete(toRemove);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::clear() {
	postorderDelete(root);
}

template <class Key, class Value>
List<Key> *RedBlackTree<Key, Value>::get_keys() {
	List<Key> *list = new List<Key>();

	LNRKey(list, root);
	return list;
}

template <class Key, class Value>
List<Value> *RedBlackTree<Key, Value>::get_values() {
	List <Value> *list = new List<Value>();

	LNRValue(list, root);
	return list;
}

template <class Key, class Value>
List<RedBlackNode<Key, Value>> *RedBlackTree<Key, Value>::get_nodes() {
	List <RedBlackNode<Key, Value>> *list = new List<RedBlackNode<Key, Value>>();

	LNRNode(list, root);
	return list;
}