#pragma once

#include "column.h"


using namespace std;


class Table {
private:
	Column* columns; // dynamically allocated
	int noOfColumns; // number to keep count of the number of columns in the database
	string name;
public:

	// constructors
	Table()
	{
		name = "";
		columns = nullptr;
		noOfColumns = 0;
	}

	Table(const string name, Column column)// initialise the table with 1 column
	{
		this->name = name;
		this->noOfColumns = 1;
		this->columns = new Column[1];
		this->columns[0] = column; // U gotta assign it like this since its dynamically allocated and stuff 
	}


	// method for showing values
	//		- takes as parameters a string* columnNames, a string columnName, a string conditionValue
	//		- use the find indexes method from the column class to find the indexes that satisfie the condition 
	//		- display all of the columns are given in columnNames at the indexes that you got
	void printColumns()
	{
		for (int i = 0; i < noOfColumns; i++)
		{
			cout << columns[i] << endl;
		}
	}

	string* getAllColumnsNames()
	{
		string* getColumnsNames = new string[noOfColumns];
		for (int i = 0; i < noOfColumns; i++)
		{
			getColumnsNames[i] = columns[i].getName();
		}

		return getColumnsNames;
	}

	Column* getAllColumns()
	{
		Column* getColumns = new Column[noOfColumns];
		for (int i = 0; i < noOfColumns; i++)
		{
			getColumns[i] = columns[i];
		}

		return getColumns;
	}

	// method for adding columns 
	//		- takes a column name, a type, a size, and a default value
	//		- basically the same as the adding data method in the column class
	void addColumn(Column& col)
	{
		noOfColumns++;
		Column* newColumns = new Column[noOfColumns];

		for (int i = 0; i < noOfColumns - 1; i++)
		{
			newColumns[i] = columns[i];
		}
		newColumns[noOfColumns - 1] = col;

		delete[] columns;

		columns = new Column[noOfColumns];

		for (int i = 0; i < noOfColumns; i++)
		{
			columns[i] = newColumns[i];
		}
		delete[] newColumns;
	}

	// method for dropping column (delete the whole column) (**Since we dont have a DROP COLUMN command this is completely optional**)
	//		- takes as a parameter the column name
	//		- if it finds the column it dealocates it
	//		- you will need to do kinda the same thing as the deleting data at index method from the column class except here you search for the index yourself given the column name 

	void dropColumn(int index)
	{
		noOfColumns--;
		Column* newColumns = new Column[noOfColumns];
		int j = 0;

		for (int i = 0; i < noOfColumns + 1; i++)
		{
			if (i != index)
			{
				newColumns[j] = columns[i];
				j++;
			}
		}

		delete[] columns;
		columns = new Column[noOfColumns];

		for (int i = 0; i < noOfColumns; i++)
		{
			columns[i] = newColumns[i];
		}
		delete[] newColumns;
	}


	// method for dropping index (still cant tell what indexes are in sql we we're going to put this off temporarily at least)
	// method for adding index 
	// 
	// method for adding data (it will call the method of adding data for each Column class allocated in the table)
	//		- needs to take as parameter an array of strings (string* values)
	//		- the values will each be added to their respective columns (something like columns[i].addData(values[i]) where addData is a method of the columns class)
	//		-
	//		- ---(if you feel like torturing yourself you can try doing the following as well)---
	//		- it needs to check if the type is correct, if it's not it should throw an error, 
	//		- this can be done by checkng the type of the column with the converted type of the given value in the parameter
	//		- i honestly dont know how this can be properly done but i think this check can be something to worry about later 
	//		- (might have to use void vectors instead of string vectors in the column class for the rows)
	void addData(string* data, int length) {
		if (length != noOfColumns) return;

		for (int i = 0; i < noOfColumns; i++)
		{
			columns[i].addData(data[i]);
		}
	}

	//		
	// method for deleting data at index 
	//		- takes an index	
	//		- it will call the method of deleting data at index of each Column class allocated in the table
	//		- columns[i].deleteAtIndex(index)
	//		- idk something like that	
	//		- could be private since this will be used with the next method only
	// 
	void deteleDataAtIndex(int index) {
		for (int i = 0; i < noOfColumns; i++)
		{
			columns[i].deleteData(index);
		}
	}
	// method for deleting data given a column name and a value
	//		- find the column with the given name
	//		- use the "method for getting indexes of data given a value" from the column class to get the index that need to be deleted 
	//		- use the method for the deleting data at index from this class (the table class not the column class) using the indexes that you got 
	//		- something like if(indexes[i] == 1) this->deleteRowAtIndex(i) or something similar
	void deleteData(string name, string value) {
		Column targetColumn;
		for (int i = 0; i < noOfColumns; i++)
		{
			if (columns[i].getName() == name) {
				targetColumn = columns[i];
			}
		}

		bool* indexes = targetColumn.getInstances(value);
		for (int i = 0; i < targetColumn.getNoOfRows(); i++)
		{
			if (indexes[i]) {
				deteleDataAtIndex(i);
			}
		}
		delete[] indexes;
	}

	// method for updating data given a column name and a value and a new value for the rows that meet the condition 
	//		- find the column with the given name
	//		- use the "method for getting indexes of data given a value" from the column class to get the indexes that need to be updated
	//		- use the method for the updating data at index from this class (the table class not the column class) using the indexes that you got 
	//		- sommething like if(indexes[i] == 1) this->updateRowAtIndex(rowName, i, value) or something similar 

	void updateData(string name, string value, string data) {
		int targetColumnIndex;
		for (int i = 0; i < noOfColumns; i++)
		{
			if (columns[i].getName() == name) {
				targetColumnIndex = i;
			}
		}

		bool* indexes = columns[targetColumnIndex].getInstances(value);
		for (int i = 0; i < columns[targetColumnIndex].getNoOfRows(); i++)
		{
			if (indexes[i]) {
				columns[targetColumnIndex].updateData(i, data);
			}
		}
		delete[] indexes;
	}
	string getName() {
		return name;
	}
	int getNoOfColumns() {
		return noOfColumns;
	}

	// dealocator
	//		- deletes all columns
	~Table()
	{
		if (columns != nullptr) {
			delete[] columns;
		}
	}

};