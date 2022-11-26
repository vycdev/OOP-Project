#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

class SQL
{
private:

public:
	SQL()
	{
	}

	~SQL()
	{
	}

};

class COLUMN; 
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

void lexer(char** tokens) {
	// executes commands
	// throws errors

	char* firstToken = new char[strlen(tokens[0]) + 1];
		
	strcpy(firstToken, tokens[0]);
	cout << "First token detected:" << endl;

	if (!strcmp(firstToken, "CREATE")){
		cout << "CREATE";

		return;
	}
	if (!strcmp(firstToken, "DROP")) {
		cout << "DROP";

		return;
	}
	if (!strcmp(firstToken, "DISPLAY")) {
		cout << "DISPLAY";

		return;
	}
	if (!strcmp(firstToken, "INSERT")) {
		cout << "INSERT";

		return;
	}
	if (!strcmp(firstToken, "SELECT")) {
		cout << "SELECT";

		return;
	}
	if (!strcmp(firstToken, "DELETE")) {
		cout << "DELETE";

		return;
	}
	if (!strcmp(firstToken, "UPDATE")) {
		cout << "UPDATE";

		return;
	}

}

int main()
{ 
	string input;
	char* tokens[100];
	char* inputChar = new char[100];
	
	getline(cin, input);
	strcpy(inputChar, input.c_str());


	int currentToken = 0;
	char* token;
	token = strtok(inputChar, " ");

	while(token!=NULL){
		tokens[currentToken] = new char[strlen(token) + 1];
		strcpy(tokens[currentToken], token);
		currentToken++; 
		token = strtok(NULL, " ");
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