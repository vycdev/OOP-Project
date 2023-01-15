#include "table.h"

using namespace std;


#pragma once




class Database {
private:
	Table* tables;
	int noOfTables;
	string name;
public:

	// constructor
	Database()
	{
		name = "";
		tables = nullptr;
		noOfTables = 0;
	}

	Database(const string newName)
	{
		name = newName;
		tables = nullptr;
		noOfTables = 0;
	}

	// method for creating a new table
	//		- check if that table exists
	void CreateTable(Table table)
	{
		this->noOfTables++;
		Table* tableCpy = new Table[noOfTables];

		for (int i = 0; i < noOfTables - 1; i++)
		{
			tableCpy[i] = tables[i];
		}
		tableCpy[noOfTables] = table;

		delete[] tables;
		tables = new Table[noOfTables];

		for (int i = 0; i < noOfTables; i++)
		{
			tables[i] = tableCpy[i];
		}

		delete[] tableCpy;
	}

	// method for dropping a table
	//  
	void DeleteTable(string name)
	{
		int index = -1;
		for (int i = 0; i < noOfTables; i++)
		{
			if (tables[i].getName() == name) index = i;
		}

		if (index != -1)
		{
			Table* newTables = new Table[noOfTables - 1];
			int j = 0;
			for (int i = 0; i < noOfTables; i++) {
				if (i != index) {
					newTables[j] = tables[i];
					j++;
				}
			}

			delete[] tables;
			noOfTables--;
			tables = new Table[noOfTables];
			for (int i = 0; i < noOfTables; i++)
			{
				tables[i] = newTables[i];
			}

			delete[] newTables;
		}
	}


	// method for showing data in table 
	//		- takes as parameters a string tableName, a string* columnNames, a string columnName, a string conditionValue
	//		- using find the table that satisfies tableName
	//		- call the select method for that table
	void GetData(string tableName, string* columnNames, int noColumns, string columnName, string conditionValue)
	{
		for (int i = 0; i < this->noOfTables; i++)
		{
			if (tableName == tables[i].getName())
			{
				cout << "Name:" << tableName;
				for (int j = 0; j < tables[i].getNoOfColumns(); j++)
				{
					for (int k = 0; k < noColumns; k++)
					{
						if (columnNames[k] == tables[i].getAllColumnsNames()[j])
						{
							cout << tables[i].getAllColumns()[j];
						}

					}
				}
			}
		}
	}

	// method for adding data to a table
	//		- takes a string tableName and a string* values
	//		- finds that tableName and calls the method for adding values to the table from the table class
	void AddData(string tableName, string* values, int length)
	{
		for (int i = 0; i < noOfTables; i++)
		{
			if (tables[i].getName() == tableName) tables[i].addData(values, length);
		}
	}


	// method for deleting data from a given table given condition
	//		- takes a string tableName, a string columnName, a string value
	//		- finds the table with tableName
	//		- uses the method from the table class on that table to delete the data that satisfies the condition 
	void deleteData(string tableName, string columnName, string value) {
		for (int i = 0; i < noOfTables; i++) {
			if (tables[i].getName() == tableName) tables[i].deleteData(columnName, value);
		}
	}

	// -- FOR PHASE 2 --
	// method for writing to the binary files
	// method for reading fromt he binary files (which will be used when the constructor is used at the start of the program)
	// 
	//
	// dealocator
	//		- deletes all tables
	~Database()
	{
		if (tables != nullptr)
		{
			delete[] tables;
			tables = nullptr;
		}
	}
};
