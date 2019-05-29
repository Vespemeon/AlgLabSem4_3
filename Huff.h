#ifndef HUFF_H
#define HUFF_H

#include <iostream>
#include "HuffTree.h"
#include "RedBlackTree.h"

class Huff {
public:
	Huff();
	~Huff();

	void menu();
	
	void setMsg(const char* ch);
	char *returnHuff();

	void changeLimit();
	void huffmanize();

private:
	RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();
	HuffTree *huffTree = new HuffTree();
	
	size_t limit = 1000;
	size_t msgLength = 0;
	size_t huffMsgLength = 0;

	char *msg = new char[limit];
	char *huffMsg = nullptr;

	void msgToRedBlack();
	void redBlackToHuff();
	void printHuffmanized();
};

#endif HUFF_H