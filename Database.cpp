#include "Database.h"
#include <iostream>


void Database::write(size_t key, double  elem)
{
	if (access_[std::this_thread::get_id()] == write_able) {
		auto it = content_.find(key);
		if (it == content_.end()) {
			std::cout << elem << "inserted to db" << std::endl;
			content_.insert({ key,elem });
		}
		else {
			std::cout << elem << " elem with this key "<< key << " Updated in db" << std::endl;
			it->second = elem;
		}
		return;
	}
	throw std::runtime_error("Transaction is READ ONLY" );
}

void Database::read(size_t key)
{
	auto it = content_.find(key);
	if (it == content_.end()) {
		std::cout << "There is not such element in db"<< std::endl;
	}
	else {
		std::cout << '{'<<key<<','<<it->second<<'}'<< std::endl;
	}
}