#include <iostream>
#include <string>

#include "./parsing.h"

using namespace std;

enum class columnTypes { text, integer, floatingPoint };

string enumToString(columnTypes t) {
	switch (t)
	{
	case columnTypes::text:
		return "text";
		break;
	case columnTypes::integer:
		return "integer";
		break;
	case columnTypes::floatingPoint:
		return "float";
		break;
	default:
		return "unknown";
		break;
	}
}

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
		for (int i = 0;i < noOfRows;i++)
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
		for (int i = 0;i < noOfRows+1;i++)
		{
			if (i != index)
			{
			newRows[j++] = rows[i];
			}
		}
		delete[] rows;
		rows = new string[noOfRows];
		for (int i = 0;i < noOfRows;i++)
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
		for (int i = 0;i < noOfRows-1;i++)
		{
			newRows[i] = rows[i];
		}
		newRows[noOfRows - 1] = data;
		delete[] rows;
		rows = new string[noOfRows];
		for (int i = 0;i < noOfRows;i++)
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
		for (int i = 0;i < noOfRows;i++)
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

	// method for adding columns 
	//		- takes a column name, a type, a size, and a default value
	//		- basically the same as the adding data method in the column class
	void addColumn(Column& col)
	{
		noOfColumns++;
		Column* newColumns = new Column[noOfColumns];

		for (int i = 0; i < noOfColumns-1; i++)
		{
			newColumns[i] = columns[i];
		}
		newColumns[noOfColumns-1] = col;
		
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
	string GetData(string tableName, string* columnNames, string columnName, string conditionValue)
	{
		
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

int main()
{ 
	Column col ("Varsta", columnTypes::integer, "18");
	col.addData("17");
	col.addData("19");
	col.addData("69");

	//cout << col[10]; // Exception throwing works as intended 
	//col.getDuplicates("69");

	//col.printRows();

	Column* colVector = new Column[2];

	Column aux("Id", columnTypes::integer, "0");
	colVector[0] = aux;
	colVector[0].addData("2");
	colVector[0].addData("0");
	colVector[0].addData("1");

	Column aux2("Nume", columnTypes::text, "Unnamed");
	colVector[1] = aux2;
	colVector[1].addData("Gigel");
	colVector[1].addData("Florica");
	colVector[1].addData("Ion");

	Table* tab = new Table("test", col);
	tab->addColumn(colVector[0]);
	tab->addColumn(colVector[1]);
	tab->dropColumn(0);
	tab->addColumn(col);

	tab->deteleDataAtIndex(0);
	tab->deleteData("Nume", "Ion");

	string dataValues[3] = { "10", "Costel", "40" };
	tab->addData(dataValues, 3);
	tab->addData(dataValues, 3);
	tab->addData(dataValues, 3);

	tab->updateData("Nume", "Costel", "Nea Nicu");

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