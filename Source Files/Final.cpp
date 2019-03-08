// Final.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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
	std::function<void(Database &)> recursion = [&recursion,&test](Database & b) {
		static int count = 0;
		++count;
		if (count > 2) {
			throw "With Exception";
		}
		if (count < 5) {
			test.runTransactional(recursion, "tread_3");

		}
	};

	test.runTransactional(recursion, "tread_3");

	std::future<void> f1 = std::async([&](){
		test.runTransactional(simplefunc, "tread_1");
	});
	std::future<void> f2 = std::async([&]() {
		test.runTransactional(simpleException, "tread_2");
	});

    return 0;
}

void simplefunc(Database & b)
{
	std::cout << "Without recursion,Without Exception\n";
}
void simpleException(Database & b) {
	throw "With Exception";
}