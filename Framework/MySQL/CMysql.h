#pragma once

#define DB_HOST "127.0.0.1"
#define DB_USER "shooter_user"
#define DB_NAME "shooter_db"
#define DB_PASSWORD "1234"

class CMysql
{
private:
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	my_ulonglong rowNum; // 레코드셋 개수
	unsigned int fieldNum; // 필드 개수
	my_ulonglong currentPos; // 현재 rwoow의 offset

	bool haveResultQuery;
	bool isEof;
	bool isBof;
	bool isConnect;
public:
	CMysql();
	virtual ~CMysql();

	bool Connect(
		const char * host,
		const char * userName,
		const char * password,
		const char * database,
		const unsigned int port = 0,
		const char * unix_socket = nullptr,
		const unsigned int client_flag = 0);
	void Disconnect();
	bool IsConnect() { return isConnect; }
	bool Query(const char * str);
	bool SelectDB(const char * str);


	bool IsBOF() { return isBof; }
	bool IsEOF() { return isEof; }
	void First();
	void Last();
	void Next();
	void Prev();
	void Move(int n = 1);

	char * Field(const char * fieldName);
	char * Field(const my_ulonglong fieldIndex);

	char * operator[](const my_ulonglong fieldIndex)
	{
		return Field(fieldIndex);
	}
	char * operator[](const char * fieldName)
	{
		return Field(fieldName);
	}
};