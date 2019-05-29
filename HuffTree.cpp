#include "HuffTree.h"

HuffNode::HuffNode() {
}

HuffNode::HuffNode(size_t freq_){
	freq = freq_;
}

HuffNode::HuffNode(char ch_, size_t freq_) {
	ch = ch_;
	freq = freq_;
}

HuffNode::~HuffNode(){
	delete code;
}

HuffTree::HuffTree() {
}

HuffTree::~HuffTree() {
	clear();
}

void HuffTree::recursiveDelete(HuffNode *node) {
	if (!node)
		return;

	recursiveDelete(node->left);
	recursiveDelete(node->right);

	delete node;
	node = nullptr;
}

void HuffTree::clear() {
	recursiveDelete(root);

	root = nullptr;
	treeHeight = 0;
	tempCode = nullptr;
	codeCounter = 0;
}

void HuffTree::addOne(char ch1, size_t freq1) {
	HuffNode *node = new HuffNode(ch1, freq1);
	HuffNode *parentNode = nullptr;
	if (root)
		parentNode = new HuffNode(freq1 + root->freq);
	else
		parentNode = new HuffNode(freq1);

	parentNode->left = root;
	parentNode->right = node;
	node->upper = parentNode;
	if (root)
		root->upper = parentNode;

	root = parentNode;

	char *temp = new char[1];
	temp[0] = '0';

	node->code = temp;
}

void HuffTree::addTwo(char ch1, size_t freq1, char ch2, size_t freq2){
	HuffNode *node1 = new HuffNode(ch1, freq1);
	HuffNode *node2 = new HuffNode(ch2, freq2);
	HuffNode *parentNode = new HuffNode(freq1 + freq2);

	parentNode->left = node1;
	parentNode->right = node2;

	node1->upper = parentNode;
	node2->upper = parentNode;

	if (root) {
		HuffNode *newRoot = new HuffNode(parentNode->freq + root->freq);
		
		newRoot->left = root;
		newRoot->right = parentNode;

		root->upper = newRoot;
		parentNode->upper = newRoot;

		root = newRoot;
	}
	else
		root = parentNode;
}

void HuffTree::recursiveAddCodes(HuffNode * node) {
	if (!node) {
		return;
	}

	if (node->code)
		return;

	recursiveAddCodes(node->left);

	if (node->ch != '\0') {
		if (node->upper && node->upper->left == node)
			tempCode[treeHeight - ((codeCounter > 1) ? codeCounter : 1)] = '1';
		else if (node->upper && node->upper->right == node)
			tempCode[treeHeight - ((codeCounter > 1) ? codeCounter : 1)] = '0';

		char *toNode = new char[treeHeight];
		for (size_t i = 0; i < treeHeight; ++i)
			toNode[i] = tempCode[i];

		node->code = toNode;
	}

	recursiveAddCodes(node->right);

	if (node->upper && node->upper->right == node && node->ch != '\0') {
		tempCode[treeHeight - codeCounter - 2] = '0';
		tempCode[treeHeight - codeCounter - 1] = '1';

		codeCounter++;

		if (codeCounter > 1) {
			tempCode[treeHeight - codeCounter + 1] = '\0';
		}
	}
}

void HuffTree::addCodesToNodes() {
	HuffNode *node = root;

	if (!node)
		return;

	while (node->left) {
		if (node->ch == '\0')
			++treeHeight;

		node = node->left;
	}

	tempCode = new char[treeHeight + 1];
	
	for (size_t i = 0; i < treeHeight; ++i)
		tempCode[i] = '1';

		recursiveAddCodes(root);
}

char * HuffTree::findCode(char ch1) {
	HuffNode *node = root;

	if (!root)
		return nullptr;

	while (node) {
		if (node->right && node->right->left
			&& node->right->left->ch == ch1) {

			return node->right->left->code;
		}
		else if (node->right && node->right->right
			&& node->right->right->ch == ch1) {

			return node->right->right->code;
		}
		else if (node->right && node->right->ch == ch1) {

			return node->right->code;
		}
		else if (node->left && node->left->ch == ch1) {

			return node->left->code;
		}

		node = node->left;
	}

	return nullptr;
}
