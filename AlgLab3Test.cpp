#include "CppUnitTest.h"
#include "../AlgLab3_/Huff.h"
#include "../AlgLab3_/Huff.cpp"
#include "../AlgLab3_/HuffTree.h"
#include "../AlgLab3_/HuffTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgLab3Test
{		
	TEST_CLASS(AlgLab3Test)
	{
	public:
		Huff *huff = nullptr;

		AlgLab3Test() {
			huff = new Huff();
		}

		~AlgLab3Test() {
			delete huff;
		}

		TEST_METHOD(oneSymbol)
		{
			huff->setMsg("a");
			huff->huffmanize();
			char* ch = huff->returnHuff();
			const char *res = "1";

			for (size_t i = 0; i < strlen(res); ++i)
				Assert::AreEqual(ch[i], res[i]);
		}

		TEST_METHOD(oneWord)
		{
			huff->setMsg("test");
			huff->huffmanize();
			char* ch = huff->returnHuff();
			//0 11 10 0
			const char *res = "011100";
			for (size_t i = 0; i < strlen(res); ++i)
				Assert::AreEqual(ch[i], res[i]);
		}

		TEST_METHOD(russianText)
		{
			huff->setMsg("привет");
			huff->huffmanize();
			char* ch = huff->returnHuff();
			//111 110 101 100 01 00
			const char *res = "1111101011000100";
			for (size_t i = 0; i < strlen(res); ++i)
				Assert::AreEqual(ch[i], res[i]);
		}

	};
}