#include "Database.h"
#include <iostream>


void Database::write(size_t key, double  elem)
{
	if (access_[std::this_thread::get_id()] == write_able) {
		auto it = content_.find(key);
		if (content_.find(key) == content_.end()) {
			std::cout << elem << "inserted to db" << std::endl;
			content_.insert({ key,elem });
		}
		else {
			std::cout << elem << " elem with this key"<< key << "Updated in db" << std::endl;
			it->second = elem;
		}
		return;
	}
	throw "Transaction is READ ONLY" ;
}

void Database::read(size_t key)
{
	std::cout << "Read Called" <<  std::endl;
}