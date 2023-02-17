#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "SQLite.h"


SQLite::SQLite(const char* filename) : Database(nullptr), m_IsOpen(false)
{
	int fd = -1;
	errno_t error = _sopen_s(&fd, filename, _O_CREAT | _O_EXCL | _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	if (fd >= 0)
	{
		_close(fd);
	}

	ErrorNum = sqlite3_open(filename, &Database);
	if (ErrorNum != SQLITE_OK)
	{
		printf("Open database [ %s ] failed. ErrorNum = %d\n", filename, ErrorNum);
		Database = nullptr;
		return;
	}

	m_IsOpen = true;
}


bool SQLite::OpenDatabase(const char* filename)
{
	int fd = -1;
	errno_t error = _sopen_s(&fd, filename, _O_CREAT | _O_EXCL | _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
	if (fd >= 0)
	{
		_close(fd);
	}

	ErrorNum = sqlite3_open(filename, &Database);
	if (ErrorNum != SQLITE_OK)
	{
		printf("Open database [ %s ] failed. ErrorNum = %d\n", filename, ErrorNum);
		Database = nullptr;
		return false;
	}

	m_IsOpen = true;
	return true;
}


void SQLite::CloseDatabase()
{
	if (!m_IsOpen)
	{
		return;
	}

	ErrorNum = sqlite3_close(Database);
	if (ErrorNum == SQLITE_BUSY)
	{
		printf("Close database failed. Sqlite busy. ErrorNum = %d\n", ErrorNum);
		return;
	}
	else if (ErrorNum != SQLITE_OK)
	{
		printf("Close database failed. ErrorNum = %d\n", ErrorNum);
		return;
	}

	m_IsOpen = false;
}


bool SQLite::ExecSQL(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


bool SQLite::CreateTable(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


bool SQLite::DeleteTable(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}
	
	sqlite3_free(errorMsg);
	return true;
}


bool SQLite::Select(const char* sql, stTable* table)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, Select_CallBack, table, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


int SQLite::Select_CallBack(void* params, int column, char** column_values, char** column_names)
{
	stTable* table = (stTable*)params;
	table->column = column;
	for (int i = 0; i < column; ++i)
	{
		string ColumnName = column_names[i];
		string ColumnValue = column_values[i];
		table->ColumnNames.push_back(ColumnName);
		table->ColumnValues.push_back(ColumnValue);
	}

	return column;
}


bool SQLite::Insert(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


bool SQLite::Update(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


bool SQLite::Delete(const char* sql)
{
	char* errorMsg = nullptr;
	ErrorNum = sqlite3_exec(Database, sql, nullptr, nullptr, &errorMsg);
	if (ErrorNum != SQLITE_OK)
	{
		ErrorMsg(errorMsg);
		sqlite3_free(errorMsg);
		return false;
	}

	sqlite3_free(errorMsg);
	return true;
}


void SQLite::ErrorMsg(const char* errormsg)
{
	string msg = errormsg + '\n';
	printf(msg.c_str());
}
