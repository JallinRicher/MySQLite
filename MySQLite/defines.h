#pragma once

#include <vector>
#include <string>

using namespace std;
struct stTable{
	int column;
	vector<string> ColumnNames;
	vector<string> ColumnValues;

	stTable()
	{
		column = 0;
	}
};
