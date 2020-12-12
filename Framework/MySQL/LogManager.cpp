#include "Framework.h"
#include "LogManager.h"

bool LogManager::InsertLog(Log log)
{
	char str[256];
	snprintf(str, 256, "insert into logs values(null, %d, '%s')", log.GetAccountID(), log.GetLogMessage().c_str());
	return mysql.Query(str);
}

LogManager::LogManager()
{
	// todo : 연결 실패 시 예외처리
	if (mysql.Connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME))
	{
		// 성공
		mysql.SelectDB(DB_NAME);
	}
	else
	{
		assert(false);
	}
}

LogManager::~LogManager()
{
	mysql.Disconnect();
}
