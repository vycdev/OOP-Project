#pragma once

#include <iostream>

#include "parsing.h"

using namespace std;



class Column {
private:
	//int size; // this would be useful if we used char arrays intead of string arrays for the rows, we'll see 
	string* rows; // dynamically allocated
	int noOfRows; // variable to keep count of the number of rows
	string defaultValue; // honestly dont know why we need this since it's not used anywhere
	string name;
	columnTypes type;
public:

	// constructors
	Column()
	{
		name = "";
		type = columnTypes::text;
		defaultValue = "";
		rows = nullptr;
		noOfRows = 0;
	}

	Column(string newName, columnTypes newType, string defaultValue)
	{
		name = newName;
		type = newType;
		this->defaultValue = defaultValue;
		noOfRows = 0;
		rows = nullptr;
	}

	Column(string newName, columnTypes newType, string defaultValue, string data)
	{
		name = newName;
		type = newType;
		this->defaultValue = defaultValue;
		noOfRows = 1;
		rows = new string[noOfRows];
		rows[0] = data;
	}

	//copy constructor
	Column(Column& col)
	{
		name = col.getName();
		type = col.getType();
		defaultValue = col.getDefaultValue();
		if (col.getNoOfRows() > 0) {
			noOfRows = col.getNoOfRows();
			rows = new string[noOfRows];
			for (int i = 0; i < noOfRows; i++)
			{
				rows[i] = col[i];
			}
		}
		else {
			rows = nullptr;
			noOfRows = 0;
		}
	}

	void printRows()
	{
		for (int i = 0; i < noOfRows; i++)
		{
			cout << rows[i] << endl;

		}
	}

	// method for deleting data at index
	//		- takes an index as a parameter
	//		- create a temporary array rows with size noOfRows - 1
	//		- deep copy rows into the temporary array, making sure to skip the value at the index given as a parameter
	//		- dealocate rows
	//		- noOfRows--;
	//		- realocate rows with noOfRows
	//		- deep copy the temporary array into rows
	//		- dealocate the temporary array	
	void deleteData(int index)
	{
		noOfRows--;
		string* newRows = new string[noOfRows];
		int j = 0;
		for (int i = 0; i < noOfRows + 1; i++)
		{
			if (i != index)
			{
				newRows[j++] = rows[i];
			}
		}
		delete[] rows;
		rows = new string[noOfRows];
		for (int i = 0; i < noOfRows; i++)
		{
			rows[i] = newRows[i];
		}
		delete[] newRows;
	}



	// method for adding data
	//		- takes a string value as a parameter
	//		- we increase noOfRows by 1
	//		- inside we create a deep copy of string* rows with the noOfRows (that is now +1 bigger)
	//		- we add the value to the end of the copy (tempRows[noOfRows] = value)
	//		- we dealocate rows
	//		- we realocate rows with the size of now noOfRows
	//		- we deep copy the previously copied rows into the now realocated rows
	//		- we dealocate the copy of rows
	void addData(string data)
	{
		noOfRows++;
		string* newRows = new string[noOfRows];
		for (int i = 0; i < noOfRows - 1; i++)
		{
			newRows[i] = rows[i];
		}
		newRows[noOfRows - 1] = data;
		delete[] rows;
		rows = new string[noOfRows];
		for (int i = 0; i < noOfRows; i++)
		{
			rows[i] = newRows[i];
		}
		delete[] newRows;
	}

	// method for updating at index
	//		- takes an index and a value
	//		- updates rows[index] = value
	void updateData(int index, string data)
	{
		rows[index] = data;
	}



	// method for getting indexes of data given a value
	//		- takes a value (could look something like this get(string value)
	//		- we then return a vector of booleans, or we can use ints doesn't matter that much
	//		- it will look something like [0, 0, 0, 1, 1, 0, 1, ...]
	//		- the size is noOfRows
	//		- 0 means that the parameter value isn't equal to the value of the row at that index, row[i] != value
	//		- 1 means that the parameter value is equal to the value of the row at that index, row[i] == value
	bool* getInstances(string value, bool matchAll = false)
	{
		bool* duplicates = new bool[noOfRows];
		for (int i = 0; i < noOfRows; i++)
		{
			if (rows[i] == value || matchAll)
			{
				duplicates[i] = 1;
			}
			else
			{
				duplicates[i] = 0;
			}
		}
		return duplicates;
	}

	string getDefaultValue() {
		return defaultValue;
	}
	string getName() {
		return name;
	}
	columnTypes getType() {
		return type;
	}

	// method for getting data at index
	//		- takes an index
	//		- returns the value at that index
	//		- could use operator overloading with the [] operator (so we have that as well in the project)
	string operator[](int index)
	{
		if (index < 0 || index >= noOfRows)
			throw exception("Index out of bounds.");
		else return rows[index];
	}

	Column& operator=(Column& col)
	{
		name = col.getName();
		type = col.getType();
		defaultValue = col.getDefaultValue();

		if (col.getNoOfRows() > 0) {
			noOfRows = col.getNoOfRows();
			rows = new string[noOfRows];
			for (int i = 0; i < noOfRows; i++)
			{
				rows[i] = col[i];
			}
		}
		else {
			rows = nullptr;
			noOfRows = 0;
		}
		return *this;
	}


	// method for getting the noOfRows
	//		- simply returns the noOfRows
	int getNoOfRows()
	{
		return noOfRows;
	}


	// dealocator
	//		- dealocates rows
	~Column()
	{
		if (rows != nullptr)
		{
			delete[] rows;
		}
	}
	friend ostream& operator<<(ostream& os, Column col);
};

ostream& operator<<(ostream& os, Column col)
{

	os << col.getName() << ":" << enumToString(col.getType()) << endl;
	for (int i = 0; i < col.getNoOfRows(); i++)
	{
		os << col[i] << endl;
	}
	return os;
}