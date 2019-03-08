#pragma once
class Transaction
{
public:
	Transaction();
	~Transaction();
	/// Starts the TX. Illegal to call if the TX already started.
	void start();

	/// Commits a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
	void commit();

	/// Aborts a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
	void abort();
};

