#include "SQLite.h"

int main()
{
	SQLite DB("test.db");

	stTable table;

	char CreateTableSQL[] = "create table hello(id int primary key,name varchar(128))";

	DB.ExecSQL(CreateTableSQL);
	DB.Select("select * from hello", &table);

	for (int i = 0; i < table.column; ++i)
	{
		printf("column %d name = %s, value = %s\n", i, table.ColumnNames[i].c_str(), table.ColumnValues[i].c_str());
	}

	return 0;
}
