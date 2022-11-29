#include <iostream>
#include <string>

#include "./parsing.h"

using namespace std;

class COLUMN {
private: 
	string name;
	string type; // text, integer, float
	int size;
	char* data; // we will store everything as a char array and convert them later if required 
public:


};
	// atributes (name, type, data array)
	//
	// method for deleting data at index
	// method for adding data at index
	// dealocators
	// constructors

class TABLE;
	// atributes (name, columns array, indexes array)
	// 
	// method for dropping column (delete the whole column/dealocate it)
	// method for dropping index
	// method for adding columns
	// method for adding index 
	// method for inserts (at index i, insert in each column data)
	// method for updates 
	// dealocators
	// constructors
	

class DATABASE;
	// atributes (name, tables array)
	// 
	// dealocators
	// constructors
	// the tables
	// method for the binary file writing 
	// method for creating tables
	// method for dropping tables
	// ... 

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

int main()
{ 
	string input;
	char* tokens[100];
	char* inputChar = new char[100];
	
	getline(cin, input);
	strcpy_s(inputChar, input.length() + 1, input.c_str());


	int currentToken = 0;
	char* token;
	token = strtok_s(inputChar, " ", &inputChar);

	while(token!=NULL){
		tokens[currentToken] = new char[strlen(token) + 1];
		strcpy_s(tokens[currentToken],strlen(token)+1, token);
		currentToken++; 
		token = strtok_s(NULL, " ", &inputChar);
	}
	cout << "TOKENS VECTOR:" << endl;
	for(int i = 0; i<currentToken; i++)
		cout << tokens[i] << endl;
	

	lexer(tokens);

	/*
	token1 token2 toekn3 <- INPUT
	token1
	token2
	toekn3
	*/

	//1.	CREATE TABLE table_name [IF NOT EXISTS] 
	//					(
	//						(column_1_name,type,default_value), (column_2_name,type,default_value), …
	//					) - the command should receive at least 1 column

	// EXEMPLE
	// 
	//CREATE TABLE students ((id, integer, 1000, 0), (nume, text, 128, ’’), (grupa, text,50,’1000’))

	//CREATE TABLE students IF NOT EXISTS((id, integer, 1000, 0), (nume, text, 128, ’’), (grupa, text, 50, ’1000’))

	//cout << inputChar;

	//-i "fisier.txt",
	//-c ASDFASDF

	//./program.exe -c COMANDA
}