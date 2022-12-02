#include <iostream>
#include <string>

#include "./parsing.h"

using namespace std;

enum columnTypes {text, integer, floatingPoint};

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
	//
	// method for deleting data at index
	//		- takes an index as a parameter
	//		- create a temporary array rows with size noOfRows - 1
	//		- deep copy rows into the temporary array, making sure to skip the value at the index given as a parameter
	//		- dealocate rows
	//		- noOfRows--;
	//		- realocate rows with noOfRows
	//		- deep copy the temporary array into rows
	//		- dealocate the temporary array	
	// 
	// method for adding data
	//		- takes a string value as a parameter
	//		- we increase noOfRows by 1
	//		- inside we create a deep copy of string* rows with the noOfRows (that is now +1 bigger)
	//		- we add the value to the end of the copy (tempRows[noOfRows] = value)
	//		- we dealocate rows
	//		- we realocate rows with the size of now noOfRows
	//		- we deep copy the previously copied rows into the now realocated rows
	//		- we dealocate the copy of rows
	//		
	// method for updating at index
	//		- takes an index and a value
	//		- updates rows[index] = value
	// 
	// method for getting indexes of data given a value
	//		- takes a value (could look something like this get(string value)
	//		- we then return a vector of booleans, or we can use ints doesn't matter that much
	//		- it will look something like [0, 0, 0, 1, 1, 0, 1, ...]
	//		- the size is noOfRows
	//		- 0 means that the parameter value isn't equal to the value of the row at that index, row[i] != value
	//		- 1 means that the parameter value is equal to the value of the row at that index, row[i] == value
	//		
	// method for getting data at index
	//		- takes an index
	//		- returns the value at that index
	//		- could use operator overloading with the [] operator (so we have that as well in the project)
	// 
	// method for getting the noOfRows
	//		- simply returns the noOfRows
	// 
	// dealocator
	//		- dealocates rows
};

class Table {
private: 
	Column* columns; // dynamically allocated
	int noOfColumns; // number to keep count of the number of columns in the database
public: 
	const string name;
	// constructors
	// 
	// method for dropping index (still cant tell what indexes are in sql we we're going to put this off temporarily at least)
	// method for adding index 
	// 
	// method for dropping column (delete the whole column) (**Since we dont have a DROP COLUMN command this is completely optional**)
	//		- takes as a parameter the column name
	//		- if it finds the column it dealocates it
	//		- you will need to do kinda the same thing as the deleting data at index method from the column class except here you search for the index yourself given the column name 
	// 
 	// method for adding columns 
	//		- takes a column name, a type, a size, and a default value
	//		- basically the same as the adding data method in the column class
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
	// method for showing values
	//		- takes as parameters a string* columnNames, a string columnName, a string conditionValue
	//		- use the find indexes method from the column class to find the indexes that satisfie the condition 
	//		- display all of the columns are given in columnNames at the indexes that you got
	// 
	// 
	// dealocator
	//		- deletes all columns
};
	
class Database {
private: 
	Table* tables;
	int noOfTables;
public:
	const string name;

	// constructor
	// 
	// method for creating a new table
	//		- check if that table exists
	// 
	// method for dropping a table
	//  
	// method for showing data in table 
	//		- takes as parameters a string tableName, a string* columnNames, a string columnName, a string conditionValue
	//		- using find the table that satisfies tableName
	//		- call the select method for that table
	// 
	// method for adding data from a table
	//		- takes a string tableName and a string* values
	//		- finds that tableName and calls the method for adding values to the table from the table class
	// 
	// method for deleting data from a given table given condition
	//		- takes a string tableName, a string columnName, a string value
	//		- finds the table with tableName
	//		- uses the method from the table class on that table to delete the data tha satisfies the condition 
	// 
	// -- FOR PHASE 2 --
	// method for writing to the binary files
	// method for reading fromt he binary files (which will be used when the constructor is used at the start of the program)
	// 
	//
	// dealocator
	//		- deletes all tables
};

// CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ’’), (grupa, text,50,’1000’))
//
// DROP TABLE studenti
// 
// DISPLAY TABLE studenti 
// // (this displays the table details not the contents of the table)
// 
// INSERT INTO studenti VALUES (1,”John”,”1001”)
// 
// SELECT (nume) FROM studenti WHERE id = 1 
// SELECT (id,nume,grupa)  FROM  studenti
// SELECT ALL FROM studenti WHERE id = 1
// SELECT ALL FROM studenti
// 
// DELETE FROM studenti WHERE nume = “John”
// 
// UPDATE studenti SET nume = “Alice” WHERE id = 1
// UPDATE studenti SET nume = “Alice” WHERE nume= “Bianca”

void tokenizer(string input, string delimiter, int& currentToken, string* tokens) {
	int pos = 0;

	currentToken = 0;
	while ((pos = input.find(delimiter)) != string::npos) {
		tokens[currentToken] = input.substr(0, pos);
		input.erase(0, pos + delimiter.length());
		currentToken++;
	}
	tokens[currentToken] = input.substr(0, pos);
	currentToken++;

}

int main()
{ 
	string input;
	getline(cin, input);
	
	int noOfTokens;
	string tokens[100];
	tokenizer(input, " ", noOfTokens, tokens);

	cout << "TOKENS VECTOR:" << endl;
	for (int i = 0; i < noOfTokens; i++)
		cout << tokens[i] << endl;
	
	cout << "__END__ ";
	//lexer(tokens, noOfTokens, 0);

	//-i "fisier.txt",
	//-c ASDFASDF

	//./program.exe -c COMANDA
}