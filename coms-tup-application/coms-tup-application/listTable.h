#pragma once

#include "User.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct TABLE_COLUMN {
	size_t width;
	std::string label;
};

std::vector<TABLE_COLUMN> getColumnData(const std::map<int32_t, User> &tableRows);

void printItem(const std::vector<TABLE_COLUMN> &tableColumns, const User &item);

template <typename T>
void listTable(std::function<std::map<int32_t, T>()> getItems)
{
	auto tableRows = getItems();

	listTable(tableRows);
}

template <typename T>
void listTable(const std::map<int32_t, T> &tableRows)
{
	using namespace std;

	ios initialState(nullptr);

	if (tableRows.empty()) {
		cout << "There is nothing to list." << endl;
		return;
	}

	auto columns = getColumnData(tableRows);

	initialState.copyfmt(cout);

	{
		size_t totalWidth = 0;
		cout << left;
		for (auto &column : columns) {
			cout << setw(column.width) << column.label;
			totalWidth += column.width;
		}
		cout << endl;

		cout << string(totalWidth, '-') << endl;
	}

	{
		size_t i = 1;
		for (auto &row : tableRows) {
			const T &curr = row.second;

			cout << left;
			cout << setw(columns[0].width) << i;
			printItem(columns, curr);
			cout << endl;

			i++;
		}
	}

	cout.copyfmt(initialState);
}
