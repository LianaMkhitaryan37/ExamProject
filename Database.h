#pragma once

class Database
{
public:
	template <typename T>
	void write(const T& elem);

};

template<typename T>
inline void Database::write(const T & elem)
{
	std::cout << elem << "inserted to db" << std::endl;
}
