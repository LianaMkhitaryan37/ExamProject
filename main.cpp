#include <iostream>
#include <map>
#include "TxRunner.h"
#include <future>


void simplefunc(Database & b);
void simpleException(Database & b);

int main()
{

	Database a;
	TxRunner test(a);
	std::function<void(Database &)> recursion = [&recursion, &test](Database & b) {
		static int count = 0;
		++count;
	/*	std::cout << "\nRecursion" << count<<std::endl;*/
		if (count > 2) {
			throw "With Exception";
		}
		if (count < 5) {
			test.runTransactional(recursion);

		}
	};
	{
		std::future<void> f0 = std::async([&]() {
			test.runTransactional(recursion);
		});

		//std::future<void> f1 = std::async([&]() {
		//	test.runTransactional(simplefunc);
		//});
		//std::future<void> f2 = std::async([&]() {
		//	test.runTransactional(simpleException);
		//});
	}
	std::cout << "Enter char for Exist\n";

	getchar();
	return 0;
}

void simplefunc(Database & b)
{
	std::cout << "Without recursion,Without Exception\n";
}
void simpleException(Database & b) {
	throw "With Exception";
}