#include <iostream>
#include <string>

#include "./parsing.h"

using namespace std;

enum columnTypes { text, integer, floatingPoint };

class Column {
private:
	int size; // this would be useful if we used char arrays intead of string arrays for the rows, we'll see 
	string defaultValue; // honestly dont know why we need this since it's not used anywhere
	string* rows; // dynamically allocated
	int noOfRows; // variable to keep count of the number of rows
public:
	const string name;
	const columnTypes type;

	// constructors
	Column() :name(""), type(text)
	{
		this->size = 0;
		this->defaultValue = "";
		this->rows = nullptr;
		this->noOfRows = 0;
	}

	Column(const string newName, const columnTypes newType, string defaultValue) :name(newName), type(newType)
	{
		this->defaultValue = defaultValue;
		this->noOfRows = 0;
		this->rows = nullptr;
	}	
	
	Column(const string newName, const columnTypes newType, string defaultValue, string data) :name(newName), type(newType)
	{
		this->defaultValue = defaultValue;
		this->noOfRows = 1;
		this->rows = new string[noOfRows];
		this->rows[0] = data;
	}

	Column(const string newName, const columnTypes newType, string defaultValue, int noOfRows) :name(newName), type(newType)
	{
		this->defaultValue = defaultValue;
		this->noOfRows = noOfRows;
		this->rows = new string[noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			this->rows[i] = this->defaultValue;
		}
	}

	//copy constructor
	Column(const Column& col) :name(col.name), type(col.type)
	{
		this->defaultValue = col.defaultValue;
		this->noOfRows = col.noOfRows;
		this->rows = new string[noOfRows];
		for (int i = 0; i < this->noOfRows; i++)
		{
			this->rows[i] = this->defaultValue;
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
	bool* getInstances(string value)
	{
		bool* duplicates = new bool[this->noOfRows];
		for (int i = 0;i < this->noOfRows;i++)
		{
			if (this->rows[i] == value)
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

	Column& operator=(const Column& col)
	{
		this->noOfRows = col.noOfRows;
		for (int i = 0; i < noOfRows+1; i++)
		{
			this->rows[i] = col.rows[i];
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
	for (int i = 0; i < col.noOfRows; i++)
	{
		os << col.rows[i] << endl;
	}
	return os;
}

class Table {
private: 
	Column* columns; // dynamically allocated
	int noOfColumns; // number to keep count of the number of columns in the database
	const string name;
public: 

	// constructors
	Table():name("")
	{
		this->columns = nullptr;
		noOfColumns = 0;
	}

	Table(const string name, int noOfColumns, Column *columns) : name(name)
	{
		this->noOfColumns = noOfColumns;
		this->columns = new Column[noOfColumns];
		for (int i = 0; i < noOfColumns; i++)
		{
			this->columns[i] = columns[i];
		}
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
	void addColumns(Column col)
	{
		this->noOfColumns++;
		Column* newColumns = new Column[this->noOfColumns];
		for (int i = 0; i < this->noOfColumns - 1; i++)
		{
			newColumns[i] = this->columns[i];
		}
		newColumns[this->noOfColumns - 1] = col;
		delete[] this->columns;
		this->columns = new Column[this->noOfColumns];
		for (int i = 0; i < this->noOfColumns; i++)
		{
			this->columns[i] = newColumns[i];
		}
		delete[] newColumns;
	}

// method for dropping column (delete the whole column) (**Since we dont have a DROP COLUMN command this is completely optional**)
//		- takes as a parameter the column name
//		- if it finds the column it dealocates it
//		- you will need to do kinda the same thing as the deleting data at index method from the column class except here you search for the index yourself given the column name 

	void dropColumns(int index)
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
	}

// dealocator
//		- deletes all columns
	~Table()
	{
		delete[] this->columns;
		this->columns = nullptr;
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

int main()
{ 
	Column col ("Varsta", integer, "18");
	col.addData("17");
	col.addData("19");
	col.addData("69");
	col.updateData(1, "69");

	//cout << col[10]; // Exception throwing works as intended 
	//col.getDuplicates("69");

	col.deleteData(2);

	col.printRows();

	Column* colVector = new Column[2];
	Table tab("Studenti", 2, colVector);
	tab.addColumns(col);
	tab.printColumns();

	//string input;
	//getline(cin, input);
	//
	// runCommand(input, 0);

	//-i "fisier.txt",
	//-c ASDFASDF

	//./program.exe -c COMANDA
	return 0;
}