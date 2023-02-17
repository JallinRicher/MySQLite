#pragma once

#include "defines.h"
#include "../include/sqlite3.h"



class SQLite
{
public:
	SQLite() = default;
	SQLite(const char* filename);

	bool OpenDatabase(const char* filename);
	void CloseDatabase();

	bool IsInvalid() const
	{
		return m_IsOpen;
	}

	bool ExecSQL(const char* sql);

	bool CreateTable(const char* sql);
	bool DeleteTable(const char* sql);
	
	bool Select(const char* sql, stTable* table);
	bool Insert(const char* sql);
	bool Update(const char* sql);
	bool Delete(const char* sql);
	
	void ErrorMsg(const char* errormsg);

	int GetErrorNum() const
	{
		return ErrorNum;
	}

private:
	static int Select_CallBack(void* params, int column, char** column_values, char** colume_names);

private:
	struct sqlite3* Database;

	int ErrorNum;
	bool m_IsOpen;
};

