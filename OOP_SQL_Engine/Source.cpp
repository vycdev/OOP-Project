#include <iostream>
#include <string>

#include "./parsing.h"

using namespace std;

enum columnTypes { text, integer, floatingPoint };

string enumToString(columnTypes t) {
	switch (t)
	{
	case text:
		return "text";
		break;
	case integer:
		return "integer";
		break;
	case floatingPoint:
		return "float";
		break;
	default:
		return "unknown";
		break;
	}
}

class Column {
private:
	int size; // this would be useful if we used char arrays intead of string arrays for the rows, we'll see 
	string* rows; // dynamically allocated
	int noOfRows; // variable to keep count of the number of rows
public:
	const string defaultValue; // honestly dont know why we need this since it's not used anywhere
	const string name;
	const columnTypes type;

	// constructors
	Column() :name(""), type(text), defaultValue("")
	{
		this->size = 0;
		this->rows = nullptr;
		this->noOfRows = 0;
	}

	Column(const string newName, const columnTypes newType, string defaultValue) :name(newName), type(newType), defaultValue(defaultValue)
	{
		this->noOfRows = 0;
		this->rows = nullptr;
	}	
	
	Column(const string newName, const columnTypes newType, string defaultValue, string data) :name(newName), type(newType), defaultValue(defaultValue)
	{
		this->noOfRows = 1;
		this->rows = new string[noOfRows];
		this->rows[0] = data;
	}

	Column(const string newName, const columnTypes newType, string defaultValue, int noOfRows) :name(newName), type(newType), defaultValue(defaultValue)
	{
		this->noOfRows = noOfRows;
		this->rows = new string[noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			this->rows[i] = this->defaultValue;
		}
	}

	//copy constructor
	Column(Column& col) :name(col.name), type(col.type), defaultValue(col.defaultValue)
	{
		if (col.getNoOfRows() > 0) {
			this->noOfRows = col.getNoOfRows();
			this->rows = new string[noOfRows];
			for (int i = 0; i < noOfRows; i++)
			{
				this->rows[i] = col[i];
			}
		}
		else {
			this->size = 0;
			this->rows = nullptr;
			this->noOfRows = 0;
		}
	}

	void printRows()
	{
		for (int i = 0;i < this->noOfRows;i++)
		{
			cout << this->rows[i] << endl;
			
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
		this->noOfRows--;
		string* newRows = new string[this->noOfRows];
		int j = 0;
		for (int i = 0;i < this->noOfRows+1;i++)
		{
			if (i != index)
			{
			newRows[j++] = this->rows[i];
			}
		}
		delete[] this->rows;
		this->rows = new string[this->noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			this->rows[i] = newRows[i];
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
		this->noOfRows++;
		string* newRows = new string[this->noOfRows];
		for (int i = 0;i < this->noOfRows-1;i++)
		{
			newRows[i] = this->rows[i];
		}
		newRows[this->noOfRows - 1] = data;
		delete[] this->rows;
		this->rows = new string[this->noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			this->rows[i] = newRows[i];
		}
		delete[] newRows;
	}

	// method for updating at index
	//		- takes an index and a value
	//		- updates rows[index] = value
	void updateData(int index, string data)
	{
		this->rows[index] = data;
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
		bool* duplicates = new bool[this->noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			if (this->rows[i] == value || matchAll)
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
		if (col.getNoOfRows() > 0) {
			this->noOfRows = col.getNoOfRows();
			this->rows = new string[noOfRows];
			for (int i = 0; i < noOfRows; i++)
			{
				this->rows[i] = col[i];
			}
		}
		else {
			this->size = 0;
			this->rows = nullptr;
			this->noOfRows = 0;
		}
		return *this;
	}


	// method for getting the noOfRows
	//		- simply returns the noOfRows
	int getNoOfRows()
	{
		return this->noOfRows;
	}


	// dealocator
	//		- dealocates rows
	~Column()
	{
		if (this->rows != nullptr)
		{
			delete[] this->rows;
		}
	}
	friend ostream& operator<<(ostream& os, Column col);
};

ostream& operator<<(ostream& os, Column col)
{

	os << col.name << ":" << enumToString(col.type) << endl;
	for (int i = 0; i < col.getNoOfRows(); i++)
	{
		os << col[i] << endl;
	}
	return os;
}

class Table {
private: 
	Column** columns; // dynamically allocated
	int noOfColumns; // number to keep count of the number of columns in the database
	const string name;
public: 

	// constructors
	Table():name("")
	{
		this->columns = nullptr;
		noOfColumns = 0;
	}

	Table(const string name, Column column) : name(name) // initialise the table with 1 column
	{
		this->noOfColumns = 1;
		this->columns = new Column*[1];
		this->columns[0] = new Column(column); // U gotta assign it like this since its dynamically allocated and stuff 
	}
	

	// method for showing values
	//		- takes as parameters a string* columnNames, a string columnName, a string conditionValue
	//		- use the find indexes method from the column class to find the indexes that satisfie the condition 
	//		- display all of the columns are given in columnNames at the indexes that you got
	void printColumns()
	{
		for (int i = 0; i < noOfColumns; i++)
		{
			cout << *columns[i] << endl;
		}
	}

	// method for adding columns 
	//		- takes a column name, a type, a size, and a default value
	//		- basically the same as the adding data method in the column class
	void addColumn(Column& col)
	{
		Column** newColumns = new Column*[noOfColumns + 1];
		for (int i = 0; i < noOfColumns; i++)
		{
			newColumns[i] = new Column(*columns[i]);
		}

		newColumns[noOfColumns] = new Column(col);
		noOfColumns++;

		delete[] columns;
		columns = new Column*[noOfColumns];

		for (int i = 0; i < noOfColumns; i++)
		{
			columns[i] = new Column(*newColumns[i]);
		}
		delete[] newColumns;
	}

// method for dropping column (delete the whole column) (**Since we dont have a DROP COLUMN command this is completely optional**)
//		- takes as a parameter the column name
//		- if it finds the column it dealocates it
//		- you will need to do kinda the same thing as the deleting data at index method from the column class except here you search for the index yourself given the column name 

	/*void dropColumns(int index)
	{
		this->noOfColumns--;
		Column* newColumns = new Column[this->noOfColumns];
		int j = 0;
		for (int i = 0; i < this->noOfColumns + 1; i++)
		{
			if (i != index)
			{
				newColumns[j++] = this->columns[i];
			}
		}
		delete[] this->columns;
		this->columns = new Column[this->noOfColumns];
		for (int i = 0; i < this->noOfColumns; i++)
		{
			this->columns[i] = newColumns[i];
		}
		delete[] newColumns;
	}*/

// dealocator
//		- deletes all columns
	~Table()
	{
		if (columns != nullptr) {
			delete[] columns;
		}
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
	//		
	// method for deleting data at index 
	//		- takes an index	
	//		- it will call the method of deleting data at index of each Column class allocated in the table
	//		- columns[i].deleteAtIndex(index)
	//		- idk something like that	
	//		- could be private since this will be used with the next method only
	// 
	// method for deleting data given a column name and a value
	//		- find the column with the given name
	//		- use the "method for getting indexes of data given a value" from the column class to get the index that need to be deleted 
	//		- use the method for the deleting data at index from this class (the table class not the column class) using the indexes that you got 
	//		- something like if(indexes[i] == 1) this->deleteRowAtIndex(i) or something similar
	// 
	// method for update at index given a value and a column name
	//		- find the column with the given column name
	//		- use the update at index method from the column class on that column with the index and value
	//		- ---(also here if you want to torture yourself you can check the type of value) ---
	//	
	// method for updating data given a column name and a value and a new value for the rows that meet the condition 
	//		- find the column with the given name
	//		- use the "method for getting indexes of data given a value" from the column class to get the indexes that need to be updated
	//		- use the method for the updating data at index from this class (the table class not the column class) using the indexes that you got 
	//		- sommething like if(indexes[i] == 1) this->updateRowAtIndex(rowName, i, value) or something similar 
	// 
};

//class Database {
//private:
//	Table* tables;
//	int noOfTables;
//public:
//	const string name;
//
//	// constructor
//	Database() :name("")
//	{
//		this->tables = nullptr;
//		this->noOfTables = 0;
//	}
//
//	Database(const string newName) :name(newName)
//	{
//		this->tables = nullptr;
//		this->noOfTables = sizeof(tables);
//	}
//
//	/*Database(const Database& z)
//	{
//		this->noOfTables = z.noOfTables;
//		if (z.tables != nullptr)
//		{
//			this->tables = new Table[z.noOfTables];
//			for (int i; i < z.noOfTables; i++)
//			{
//				this->tables[i] = z.tables[i];
//			}
//		}
//	}*/
//
//	/*Database operator=(const Database& y)
//	{
//		if (this == &y)
//		{
//			return *this;
//		}
//		if (this->tables != nullptr)
//		{
//			delete[] tables;
//			this->tables = new Table[sizeof(y.tables) + 1];
//			for (int i = 0; i < sizeof(y.tables); i++)
//			{
//				Table.columns = tables.y.colums;
//				Table.noOfColumns = Table.y.noOfColums;
//				this->name = y.name;
//			}
//		}
//	}*/
//
//	// method for creating a new table
//	//		- check if that table exists
//	void CreateTable(Table table, string defaultValue, int noOfRows)
//	{
//		this->noOfTables++;
//		Table* tableCpy;
//		tableCpy = new Table[noOfTables];
//		for (int i = 0; i < noOfTables - 1; i++)
//		{
//			tableCpy[i] = this->tables[i];
//		}
//		tableCpy[this->noOfTables] = table;
//		delete[] this->tables;
//		this->tables = new Table[this->noOfTables];
//		for (int i = 0; i < noOfTables; i++)
//		{
//			this->tables[i] = tableCpy[i];
//		}
//		delete[] tableCpy;
//	}
//
//	// method for dropping a table
//	//  
//	void DeleteTable(Table table)
//	{
//		for (int i; i < noOfTables; i++)
//		{
//			if (tables[i] == table)
//			{
//				delete[] tables[i];
//			}
//		}
//		this->noOfTables--;
//	}
//
//
//	// method for showing data in table 
//	//		- takes as parameters a string tableName, a string* columnNames, a string columnName, a string conditionValue
//	//		- using find the table that satisfies tableName
//	//		- call the select method for that table
//	string GetData(string tableName, string* columnNames, string columnName, string conditionValue)
//	{
//		for (int i = 0; i < noOfTables; i++)
//		{
//			if (tableName == Table.name[i])
//			{
//				for (int j = 0; j < Table.noOfColumns; j++)
//				{
//					if (columnName == Table.columns[i])
//					{
//						return Table.columns[i];
//					}
//				}
//			}
//		}
//	}
//
//	// method for adding data from a table
//	//		- takes a string tableName and a string* values
//	//		- finds that tableName and calls the method for adding values to the table from the table class
//	void AddData(string tableName, string* values)
//	{
//		for (int i = 0; i < noOfTables; i++)
//		{
//			//if (tableName == name[i])
//			{
//				//insert values
//			}
//		}
//	}
//
//
//	// method for deleting data from a given table given condition
//	//		- takes a string tableName, a string columnName, a string value
//	//		- finds the table with tableName
//	//		- uses the method from the table class on that table to delete the data tha satisfies the condition 
//	// 
//	// -- FOR PHASE 2 --
//	// method for writing to the binary files
//	// method for reading fromt he binary files (which will be used when the constructor is used at the start of the program)
//	// 
//	//
//	// dealocator
//	//		- deletes all tables
//	~Database()
//	{
//		if (tables != nullptr)
//		{
//			delete[] tables;
//			this->tables = nullptr;
//		}
//	}
//};

int main()
{ 
	Column col ("Varsta", integer, "18");
	col.addData("17");
	col.addData("19");
	col.addData("69");

	//cout << col[10]; // Exception throwing works as intended 
	//col.getDuplicates("69");

	//col.printRows();

	Column** colVector = new Column*[2];

	colVector[0] = new Column("Id", integer, "0");
	colVector[0]->addData("2");
	colVector[0]->addData("0");
	colVector[0]->addData("1");


	colVector[1] = new Column("Nume", text, "Unnamed");
	colVector[1]->addData("Gigel");
	colVector[1]->addData("Florica");
	colVector[1]->addData("Ion");

	Column col2("Varsta2", integer, "18");
	col2.addData("17");
	col2.addData("19");
	col2.addData("69");
	col2.updateData(1, "69");


	Table* tab = new Table("test", col);
	tab->addColumn(*colVector[0]);
	tab->addColumn(*colVector[1]);




	/*Column** newColumns = new Column * [noOfColumns + 1];
	for (int i = 0; i < noOfColumns; i++)
	{
		newColumns[i] = new Column(*(columns[i]));
	}

	newColumns[noOfColumns] = new Column(col);
	noOfColumns++;

	delete[] columns;
	columns = new Column * [noOfColumns];

	for (int i = 0; i < noOfColumns; i++)
	{
		columns[i] = new Column(*(newColumns[i]));
	}
	delete[] newColumns;*/
	Column** test3 = new Column* [2];
	test3[0] = new Column(*colVector[0]);
	test3[1] = new Column(col2);

	Column** newTest3 = new Column * [3];
	for (int i = 0; i < 2; i++)
	{
		newTest3[i] = new Column(*test3[i]);
	}
	newTest3[2] = new Column(*colVector[1]);
	delete[] test3;
	test3 = new Column*[3];
	for (int i = 0; i < 3; i++)
	{
		test3[i] = new Column(*newTest3[i]);
	}
	delete[] newTest3;

	cout << test3[0]->name << endl;
	cout << test3[1]->name << endl;
	cout << test3[2]->name << endl;
		 





	//tab.addColumns(col);
	cout << "______________" << endl;
	tab->printColumns();
	cout << "______________" << endl;

	delete tab; // the deconstructor doesn't explode fortunately 
	

	//string input;
	//getline(cin, input);
	//
	// runCommand(input, 0);

	//-i "fisier.txt",
	//-c ASDFASDF

	//./program.exe -c COMANDA
	return 0;
}