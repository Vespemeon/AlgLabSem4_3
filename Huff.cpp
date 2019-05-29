#include "Huff.h"

Huff::Huff() {
}

Huff::~Huff() {
	delete tree;
	delete huffTree;
	delete msg;
	delete huffMsg;
}

void Huff::menu() {
	char ch = '0';

	while (ch != 'q') {
		std::cout
			<< "1: Enter message and huffmanize\n"
			<< "2: Change limit\n"
			<< "q: Quit\n";

		std::cin.get(ch);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (ch) {
		case '1':
			delete msg;
			msg = new char[limit];

			std::cin.getline(msg, limit);

			huffmanize();
			printHuffmanized();
			break;
		case '2':
			changeLimit();
			break;
		}
	}
}

void Huff::setMsg(const char * ch){
	size_t len = 0;
	for (size_t i = 0; i < strlen(ch); ++i)
		if (ch[i] == '1' || ch[i] == '0')
			++len;

	delete msg;
	msg = new char[len];

	size_t constLen = 0;

	for (size_t i = 0; i < len; ++i) {
		msg[i] = ch[i];
	}
}

char * Huff::returnHuff(){
	return huffMsg;
}

void Huff::changeLimit() {
	std::cout << "Current limit is " << limit << std::endl
		<< "Enter new limit, if it's smaller than the message's "
		<< "length, it will be deleted:" << std::endl;

	std::cin >> limit;
	if (limit < msgLength) {
		delete msg;
		msg = nullptr;
	}		
}

void Huff::huffmanize() {
	msgLength = strlen(msg);

	msgToRedBlack();
	redBlackToHuff();
	char *tempHuff = new char[huffTree->treeHeight * msgLength + 1];

	char *temp = nullptr;
	huffMsgLength = 0;

	for (size_t i = 0; i < msgLength; ++i) {
		temp = huffTree->findCode(msg[i]);
		for (size_t j = 0; j < strlen(temp); ++j) {
			if (temp[j] == '0' || temp[j] == '1') {
				tempHuff[huffMsgLength] = temp[j];
				++huffMsgLength;
			}
		}
	}

	huffMsg = new char[huffMsgLength + 1];
	for (size_t i = 0; i < huffMsgLength; ++i)
		huffMsg[i] = tempHuff[i];

	huffMsg[huffMsgLength] = '\0';
	
	delete tempHuff;
}

void Huff::msgToRedBlack() {
	char ch = '\0';
	size_t pos = 0;
	size_t counter = 0;
	bool letters = true;

	char *temp = new char[msgLength];

	for (size_t i = 0; i < msgLength; ++i)
		temp[i] = msg[i];

	while (letters) {
		counter = 0;
		letters = false;
		ch = '\0';

		for (size_t i = 0; i < msgLength; ++i) {
			if (temp[i] != '\0') {
				ch = temp[i];
				pos = i;
				letters = true;
				break;
			}
		}

		if (ch == '\0') {
			return;
		}

		for (size_t i = pos; i < msgLength; ++i) {
			if (temp[i] == ch) {
				temp[i] = '\0';
				counter++;
			}
		}

		tree->insert(counter, ch);
	}
}

void Huff::redBlackToHuff() {
	List<RedBlackNode<int, char>> *listNodes = tree->get_nodes();

	ListIterator<RedBlackNode<int, char>> *it = listNodes->it;

	if (!it->notNul()) {
		std::cout << "Empty tree.\n";
		return;
	}

	RedBlackNode<int, char> node = it->getData();
	RedBlackNode<int, char> nextNode;

	while (it->notNul()) {
		if (it->hasNext()) {
			node = it->getData();

			it->goNext();
			nextNode = it->getData();

			huffTree->addTwo(node.getVal(), node.getKey(), nextNode.getVal(), nextNode.getKey());

			if (!it->hasNext())
				break;

			it->goNext();
		}
		else {
			node = it->getData();

			huffTree->addOne(node.getVal(), node.getKey());
			break;
		}
	}

	delete listNodes;
	delete it;
	huffTree->addCodesToNodes();
}

void Huff::printHuffmanized() {
	size_t huffMsgSize = 0;
	size_t msgSize = msgLength * sizeof(char);

	std::cout << "\nOriginal message:\n" << msg << std::endl
		<< "Huffmanized message:\n";

	char ch;

	for (size_t i = 0; i < msgLength; ++i) {
		ch = msg[i];

		char* temp = huffTree->findCode(ch);

		for (size_t j = 0; j < strlen(temp); ++j) {
			if (temp[j] == '0' || temp[j] == '1') {
				std::cout << temp[j];
				huffMsgSize++;
			}
		}

		std::cout << " ";
	}

	std::cout << "\n\nOriginal message's size: " << msgSize  << " bytes"
		<< "\nHuffmanized message's size: " << huffMsgSize << " bits or "
		<< float(huffMsgSize / 8.0f) << " bytes, (theoretically), "
		<< float(huffMsgSize * sizeof(char)) << " bits (practically, in memory)\n";

	std::cout << "\nTable of letters and their frequency:\n"
		<< "Letter\tFrequency\n";

	List<RedBlackNode<int, char>> *list = tree->get_nodes();
	ListIterator<RedBlackNode<int, char>> *it = list->it;
	it->goEnd();

	while (it->hasPrev()) {
		std::cout << it->getData().getVal() << "\t " << it->getData().getKey() << std::endl;
		it->goPrev();
	}
	if (it->notNul()) {
		std::cout << it->getData().getVal() << "\t " << it->getData().getKey() << std::endl;
	}

	std::cout << "Compression ratio is " << msgSize << " to "
		<< " " << float(huffMsgSize / 8.0f) << ", "
		<< float(msgSize) / float(huffMsgSize / 8.0f) << std::endl;

	delete list;
	delete it;

	tree->clear();
	huffTree->clear();
	delete msg;
	msg = new char[limit];
	delete huffMsg;
}
