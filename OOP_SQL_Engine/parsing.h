#include <iostream>
#include <cstring>

#pragma once

using namespace std;

void lexer(char** tokens, int noOfTokens, int line) {
	// executes commands
	// throws errors

	char* firstToken = new char[strlen(tokens[0]) + 1];

	strcpy_s(firstToken, strlen(tokens[0]) + 1, tokens[0]);
	cout << "First token detected:" << endl;

	if (!strcmp(firstToken, "CREATE")) {
		//cout << "CREATE";

		return;
	}
	if (!strcmp(firstToken, "DROP")) {
		//cout << "DROP";

		return;
	}
	if (!strcmp(firstToken, "DISPLAY")) {
		//cout << "DISPLAY";

		return;
	}
	if (!strcmp(firstToken, "INSERT")) {
		//cout << "INSERT";

		return;
	}
	if (!strcmp(firstToken, "SELECT")) {
		//cout << "SELECT";

		return;
	}
	if (!strcmp(firstToken, "DELETE")) {
		//cout << "DELETE";

		return;
	}
	if (!strcmp(firstToken, "UPDATE")) {
		//cout << "UPDATE";

		return;
	}
	cout << "Syntax error: Unrecognized command at line " << line << endl;
}
