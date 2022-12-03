#include <iostream>
#include <cstring>

#pragma once

using namespace std;

void checkToken(string token, string expectedToken, int line) {
	if (token != expectedToken) {
		string err = "Error: Expected token \"TABLE\" at line " + to_string(line) + ". Instead got \"" + token + "\".";
		throw err;
	}
}

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

void lexer(string* tokens, int noOfTokens, int line) {
	// executes commands
	// throws errors

	if (noOfTokens <= 0) return;
	
	if (tokens[0] == "CREATE") {
		// CREATE TABLE students ((id,integer,1000,0), (nume,text,128,’’), (grupa,text,50,’1000’))
		checkToken(tokens[1], "TABLE", line);

		return;
	}
	if (tokens[0] == "DROP"){
		// DROP TABLE studenti
		checkToken(tokens[1], "TABLE", line);


		return;
	}
	if (tokens[0] == "DISPLAY") {
		// DISPLAY TABLE studenti
		//		 (this displays the table details not the contents of the table)
		checkToken(tokens[1], "TABLE", line);


		return;
	}
	if (tokens[0] == "INSERT") {
		// INSERT INTO studenti VALUES (1,”John”,”1001”)


		return;
	}
	if (tokens[0] == "SELECT") {
		// SELECT (nume) FROM studenti WHERE id = 1 
		// SELECT (id,nume,grupa)  FROM  studenti
		// SELECT ALL FROM studenti WHERE id = 1
		// SELECT ALL FROM studenti


		return;
	}
	if (tokens[0] == "DELETE") {
		// DELETE FROM studenti WHERE nume = “John”


		return;
	}
	if (tokens[0] == "UPDATE") {
		// UPDATE studenti SET nume = “Alice” WHERE id = 1
		// UPDATE studenti SET nume = “Alice” WHERE nume= “Bianca”

		return;
	}

	cout << "Syntax error: Unrecognized command at line " << line << endl;
}

void runCommand(string input, int line) {
	int noOfTokens = 0;
	string* tokens = new string[100]; // assuming the maximum number of tokens a command is going to have is 100

	tokenizer(input, " ", noOfTokens, tokens);
	lexer(tokens, noOfTokens, line);
	
	delete[] tokens;

	return;
}