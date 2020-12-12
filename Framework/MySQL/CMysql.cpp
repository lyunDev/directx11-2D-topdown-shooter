#include "Framework.h"
#include "CMysql.h"


CMysql::CMysql()
{
#ifdef _DEBUG
	rowNum = 0;
	fieldNum = 0;
	currentPos = 0;

	isBof = false;
	isEof = false;
	isConnect = false;
	haveResultQuery = false;

	mysql_init(&conn);
#endif
}

CMysql::~CMysql()
{
#ifdef _DEBUG
	if (&conn != NULL)
	{
		mysql_close(&conn);
	}
#endif
}

bool CMysql::Connect(const char * host, const char * userName, const char * password, const char * database, const unsigned int port, const char * unix_socket, const unsigned int client_flag)
{
#ifdef _DEBUG
	if (mysql_real_connect(&conn, host, userName, password, database, port, unix_socket, client_flag))
	{
		isConnect = true;
		return true;
	}
	isConnect = false;
	return false;
#else
	return true;
#endif
}

void CMysql::Disconnect()
{
#ifdef _DEBUG
	if (&conn != NULL)
	{
		mysql_close(&conn);
		rowNum = 0;
		fieldNum = 0;
		currentPos = 0;
		isBof = false;
		isEof = false;
		isConnect = false;
		haveResultQuery = false;
	}
#endif 
}

bool CMysql::Query(const char * str)
{
#ifdef _DEBUG
	if (mysql_query(&conn, str))
	{
		return false;
	}
	else
	{
		res = mysql_store_result(&conn);
		if (res)
		{
			rowNum = mysql_num_rows(res);
			fieldNum = mysql_num_fields(res);
			row = mysql_fetch_row(res);
			field = mysql_fetch_fields(res);
			isBof = true;
			isEof = false;
			haveResultQuery = true;
			return true;
		}
		else
		{
			// UPDATE, DELETE, INSERT query
			if (mysql_field_count(&conn) == 0)
			{
				rowNum = mysql_affected_rows(&conn);
				haveResultQuery = false;
				return true;
			}
			else
				return false;
		}
	}
	return true;
#else
	return true;
#endif
}

bool CMysql::SelectDB(const char * str)
{
#ifdef _DEBUG
	return !mysql_select_db(&conn, str);
#else
	return true;
#endif

}

void CMysql::First()
{
#ifdef _DEBUG
	isBof = true;
	isEof = false;
	currentPos = 0;
	mysql_data_seek(res, currentPos);
	row = mysql_fetch_row(res);
#endif
}

void CMysql::Last()
{
#ifdef _DEBUG
	isBof = false;
	isEof = true;
	// row의 index는 0부터
	currentPos = rowNum - 1; 
	mysql_data_seek(res, currentPos);
	row = mysql_fetch_row(res);
#endif 
}

void CMysql::Next()
{
#ifdef _DEBUG
	if (!IsEOF())
	{
		Move();
		if (IsBOF())
			isBof = false;
	}
	else
	{
		string errorMsg = "[EXCEPTION] Exception Next(), 다음 레코드셋이 없습니다. ";
		cout << errorMsg << endl;
		throw std::exception(errorMsg.c_str());
	}
#endif
}

void CMysql::Prev()
{
#ifdef _DEBUG
	if (!IsBOF())
	{
		Move(-1);
		if (IsEOF())
			isEof = false;
	}
	else
	{
		cout << "Exception Prev(), 이전 레코드셋이 없습니다." << endl;
		string errorMsg = "[Error : " + to_string(mysql_errno(&conn)) + "]" + mysql_error(&conn);
		cout << "[Error:" << mysql_errno(&conn) << "] " << mysql_error(&conn) << endl;
	}
#endif
}

void CMysql::Move(int n)
{
#ifdef _DEBUG
	my_ulonglong pos = currentPos + n;
	if (pos == -1)
	{
		isBof = true;
		isEof = false;
	}
	else if (pos == rowNum)
	{
		isBof = false;
		isEof = true;
	}
	else if ((pos < 0) || (pos > rowNum))
	{
		cout << "Exception Prev() or Next() or Move(), 레코드셋범위를 넘습니다" << endl;
		string errorMsg = "[Error:" + to_string( mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	currentPos = pos;
	mysql_data_seek(res, currentPos);
	row = mysql_fetch_row(res);
#endif
}

char * CMysql::Field(const char * fieldName)
{
#ifdef _DEBUG
	if (!haveResultQuery)
	{
		cout << "Exception Field() or [], 결과가 없는 쿼리를 실행했습니다" << endl;
		cout << "[Error:" << mysql_errno(&conn) << "] " << mysql_error(&conn) << endl;
		string errorMsg = "[Error:" + to_string(mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	if (rowNum == 0)
	{
		cout << "Exception Field() or [], Query 에 해당하는 레코드셋이 없습니다" << endl;
		string errorMsg = "[Error:" + to_string(mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	for (unsigned int i = 0; i < fieldNum; i++)
	{
		if (strcmp(field[i].name, fieldName) == 0)
			return row[(int)i];
	}
	return row[-1];
#endif
}

char * CMysql::Field(const my_ulonglong fieldIndex)
{
#ifdef _DEBUG
	if (!haveResultQuery)
	{
		cout << "Exception Field() or [], 결과가 없는 쿼리를 실행했습니다" << endl;
		string errorMsg = "[Error:" + to_string(mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	if (rowNum == 0)
	{
		cout << "Exception Field() or [], Query 에 해당하는 레코드셋이 없습니다" << endl;
		string errorMsg = "[Error:" + to_string(mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	if (fieldIndex > fieldNum)
	{
		cout << "Exception field() or [], 필드의 인덱스가 음수이거나 범위를 넘습니다" << endl;
		string errorMsg = "[Error:" + to_string(mysql_errno(&conn)) + "] " + mysql_error(&conn);
		throw std::exception(errorMsg.c_str());
	}
	return row[fieldIndex];
#else
	return nullptr;
#endif
}
