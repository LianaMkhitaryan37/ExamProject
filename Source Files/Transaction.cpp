#include "stdafx.h"
#include "Transaction.h"
#include <iostream>

Transaction::Transaction()
{
	std::cout << "Transaction Created";
}


Transaction::~Transaction()
{
	std::cout << "Transaction Destroyed";
}

void Transaction::start()
{
	std::cout << "Start Called";
}

void Transaction::commit()
{
	std::cout << "Commit Called";
}

void Transaction::abort()
{
	std::cout << "Abort Called";
}
