#pragma once
#include "utils.h"
#include <map>
#include <thread>
#include "Transaction.h"

class Database
{
public:
	 void write(size_t key, double elem);
	 void read(size_t key);
	 friend class Transaction;
private:
	std::map<std::thread::id, Access> access_;
	std::map<size_t, double > content_;
};


