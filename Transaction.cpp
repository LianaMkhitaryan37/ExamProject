#include "Transaction.h"
#include <iostream>

Transaction::Transaction(Database * db_ptr, Access a)
	:m_a(a)
	,m_db(db_ptr)
{
	setDbAccess();
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
	remove();
}

void Transaction::abort()
{
	std::cout << "Abort Called\n" << std::endl;
	remove();
}

void Transaction::remove()
{
	m_db->access_.erase(std::this_thread::get_id());

}

void Transaction::setDbAccess()
{
	if (m_db) {
		if(m_db->access_.find(std::this_thread::get_id()) == m_db->access_.end())
			m_db->access_[std::this_thread::get_id()]=m_a;
	}

}


