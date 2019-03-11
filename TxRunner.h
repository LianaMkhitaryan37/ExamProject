#pragma once
#include "Database.h"
#include "Transaction.h"
#include <map>
#include <thread>
#include <mutex>

class TxRunner
{
public:
	TxRunner(Database& db) :
		m_db(db) {}
	;
	~TxRunner() {};
	Database& get_db() {
		return m_db;
	}
	template<typename FUNCTION, typename... Args>
	void runTransactional(FUNCTION fun, Args... arg);
private:
	Database & m_db;
	std::map<std::thread::id, Transaction> data_;
	std::mutex safe_Tread;
};

template<typename FUNCTION,typename... Args>
inline void TxRunner::runTransactional(FUNCTION fun,Args... arg)
{
	auto index = std::this_thread::get_id();
	Transaction * ptr;
	bool c = false;
	if (data_.find(index) == data_.end()) {
		std::lock_guard<std::mutex> lock(safe_Tread);
		data_[index] = Transaction();
		ptr = &data_[index];
		ptr->start();
		c = true;
	}
	else {
		ptr = &data_[index];
	}
	try {
		fun(this,arg...);
		if (c) {
			ptr->commit();
			data_.erase(index);
		}
	}
	catch (...) {
		ptr->abort();
	}
}
