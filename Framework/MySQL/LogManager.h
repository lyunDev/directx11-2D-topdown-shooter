#pragma once
#include "CMysql.h"

struct Log
{
	uint account_id;
	string logMsg;
public:
	Log(uint account_id, string logMsg)
	{
		this->account_id = account_id;
		this->logMsg = logMsg;
	}
	uint GetAccountID() { return account_id; }
	string GetLogMessage() { return logMsg; }
};

class LogManager : public SingletonBase<LogManager>
{
	friend class SingletonBase<LogManager>;
	CMysql mysql;
public :
	bool InsertLog(Log log);

private :
	LogManager();
	~LogManager();
};

