#include "pch.h"
#include "CppUnitTest.h"
#include "../ap_12.10/Source.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::ofstream outputFile("input1.txt");
			outputFile << "3 4 + 5 *";
			outputFile.close();

			std::ifstream inputFile("input1.txt");
			Node* root = buildExpressionTree(inputFile);
			inputFile.close();

			Assert::IsNotNull(root);

			std::string expectedExpression = "+ 3 * 4 5 ";
			std::ostringstream stream;
			printTree(root);
			Assert::AreEqual(expectedExpression, stream.str());

			deleteTree(root);
		}
	};
}
