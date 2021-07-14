#pragma once

#include "listTable.h"

#include "utils.h"

using namespace std;

vector<TABLE_COLUMN> getColumnData(const map<int32_t, User> &tableRows)
{
	vector<TABLE_COLUMN> columns(10);

	columns[0].label = "No. ";
	columns[1].label = "ID";
	columns[2].label = "Username";
	columns[3].label = "Name";
	columns[4].label = "Surname";
	columns[5].label = "Access Level";
	columns[6].label = "Created on";
	columns[7].label = "Created by";
	columns[8].label = "Modified on";
	columns[9].label = "Modified by";

	columns[0].width = max((size_t)ceil(log10(tableRows.size())), columns[0].label.size());
	for (size_t i = 1; i < 10; i++) {
		columns[i].width = columns[i].label.size();
	}

	for (auto &row : tableRows) {
		const User &curr = row.second;

		columns[2].width = max(columns[2].width, curr.getUsername().size());
		columns[3].width = max(columns[3].width, curr.getFirstName().size());
		columns[4].width = max(columns[4].width, curr.getLastName().size());
		columns[5].width = max(columns[5].width, curr.getUsername().size());
		columns[6].width = max(columns[6].width, to_string(curr.getCreatedOn(), false).size());
		columns[8].width = max(columns[8].width, to_string(curr.getLastChangedOn()).size());
	}

	for (auto &column : columns) {
		column.width += 2;
	}

	return columns;
}

void printItem(const vector<TABLE_COLUMN> &tableColumns, const User &item)
{
	cout << setw(tableColumns[1].width) << item.getID();
	cout << setw(tableColumns[2].width) << item.getUsername();
	cout << setw(tableColumns[3].width) << item.getFirstName();
	cout << setw(tableColumns[4].width) << item.getLastName();
	cout << setw(tableColumns[5].width) << to_string(item.getAccessLevel());
	cout << setw(tableColumns[6].width) << to_string(item.getCreatedOn(), false);
	cout << setw(tableColumns[7].width) << item.getCreatedBy();
	cout << setw(tableColumns[8].width) << to_string(item.getLastChangedOn());
	cout << setw(tableColumns[9].width) << item.getLastChangedBy();
}
