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
	template <typename FUNCTION>
	void runTransactional(FUNCTION fun);
private:
	Database & m_db;
	std::map<std::thread::id, Transaction> data_;
	std::mutex safe_Tread;
};

template<typename FUNCTION>
inline void TxRunner::runTransactional(FUNCTION fun)
{
	auto index = std::this_thread::get_id();
	bool removeFromMap = false;
	Transaction * ptr;
	std::atomic<bool> is_done{ false };

	if (data_.find(index) == data_.end()) {
		std::lock_guard<std::mutex> lock(safe_Tread);
		data_[index] = Transaction();
		ptr = &data_[index];
		ptr->start();
	}
	else {
		ptr = &data_[index];
	}
	try {
		fun(m_db);
		ptr->commit();
	}
	catch (...) {
		ptr->abort();
	}
}
