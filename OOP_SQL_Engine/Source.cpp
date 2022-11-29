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