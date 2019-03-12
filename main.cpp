#include "Database.h"
#include "TxRunner.h"
#include <iostream>

int main() {
	Database db;
	TxRunner tx_runner(db);
	std::cout << "First test.\n In lambda function we calculate a + b function on every recursive call until 'a' is not 0.\n";
	std::function<void(TxRunner* tx, int a, double b)> func = [&func](TxRunner* tx, int a, double b) {
		if (a == 0)
			return;
		std::cout << "In lambda func: a+b=" << a + b << std::endl;

		// Call some write method on transaction database	
		tx->get_db().write(1, a + b);
		tx->runTransactional(func, read_only, a - 1, b);
	};
	tx_runner.runTransactional(func, write_able, 5, 8.5);
	
	std::cout << "\nSecond test.\n Here we submit a function that throws an exception\n";
	std::function<void(TxRunner* tx, int a, int b)> func_error = [&func_error](TxRunner* tx, int a,  int b) {
		if (b == 0)
			throw std::runtime_error("Division to zero");

		// Call some write method on transaction database
		tx->get_db().write(2,a / b);
	};
	tx_runner.runTransactional(func_error,read_only, 10, 0);

	system("pause");
	return 0;
}