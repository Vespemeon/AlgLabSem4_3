#ifndef HUFFTREE_H
#define HUFFTREE_H

class HuffNode {
private:
	friend class HuffTree;

	HuffNode();
	HuffNode(size_t freq_);
	HuffNode(char ch_, size_t freq_);
	~HuffNode();
	
	char ch = '\0';
	size_t freq = 0;
	char *code = nullptr;

	HuffNode *left = nullptr;
	HuffNode *right = nullptr;
	HuffNode *upper = nullptr;
};

class HuffTree {
private:
	friend class Huff;

	HuffTree();
	~HuffTree();

	HuffNode *root = nullptr;
	size_t treeHeight = 0;
	char *tempCode = nullptr;
	size_t codeCounter = 0;
	bool zero = true;

	void recursiveDelete(HuffNode *node);
	void clear();
	void addOne(char ch1, size_t freq1);
	void addTwo(char ch1, size_t freq1, char ch2, size_t freq2);
	void recursiveAddCodes(HuffNode *node);
	void addCodesToNodes();
	char *findCode(char ch);
};

#endif