#include "Transaction.h"
#include <iostream>

Transaction::Transaction()
{
}
Transaction::~Transaction()
{
}

void Transaction::start()
{
	std::cout << "Start Called\n";
}

void Transaction::commit()
{
	std::cout << "Commit Called\n";
}

void Transaction::abort()
{
	std::cout << "Abort Called\n" << std::endl;
}
