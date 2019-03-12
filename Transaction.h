#pragma once
#include "Database.h"
#include "utils.h"

class Database;
class Transaction
{
public:
	Transaction(Database * db_ptr=nullptr, Access a =read_only);
	~Transaction();
	/// Starts the TX. Illegal to call if the TX already started.
	void start();

	/// Commits a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
	void commit();

	/// Aborts a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
	void abort();
private:
	void remove();
	void setDbAccess();
	Access m_a;
	Database * m_db;
};
