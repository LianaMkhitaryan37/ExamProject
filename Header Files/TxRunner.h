#pragma once
#include "Database.h"
#include "Transaction.h"
#include <map>

class TxRunner
{
public:
	TxRunner(Database& db);
	~TxRunner();
	template <typename FUNCTION>
	void runTransactional(FUNCTION fun);
private:
	Database & m_db;
	std::map<std::string, Transaction> data_;

};

template<typename FUNCTION>
inline void TxRunner::runTransactional(FUNCTION fun)
{
	static TxRunner::i = 0;
	std::string index = "tread_" + std::to_string(i);
	if (data_.find(index) != data_.end()) {
		data_[index] = Transaction();
		data_[index].start();
	}
	try {
		fun(m_db);
		data_[index].commit();
	}
	catch (...) {
		data_[index].abort();
	}
	
}
