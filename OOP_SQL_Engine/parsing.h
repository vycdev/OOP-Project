#include <iostream>
#include <cstring>

#pragma once

using namespace std;

enum class columnTypes
{
	text,
	integer,
	floatingPoint
};

string enumToString(columnTypes t)
{
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

bool hasCharsInString(string str, const char *chr)
{
	bool ok = true;
	for (int i = 0; i < strlen(chr); i++)
		if (str.find(chr[i]) != string::npos)
			ok = false;
	return ok;
}

bool isAlphaNum(string str)
{
	bool ok = true;
	for (int i = 0; i < str.length(); i++)
		if (!isalnum(str[i]))
			ok = false;

	return ok;
}

bool hasValidName(string str)
{
	return isAlphaNum(str) && isalpha(str[0]);
}

void checkToken(string token, string expectedToken, int line)
{
	if (token != expectedToken)
	{
		string err = "Error: Expected token \"" + expectedToken + "\" at line " + to_string(line) + ". Instead got \"" + token + "\".";
		throw err;
	}
}

void checkNoOfTokensMin(int totalNumber, int expectedNumber, int line)
{
	if (totalNumber < expectedNumber)
	{
		string err = "Error: Your command doesn't have the expected number of tokens at line " + to_string(line) + ". Your command might be incomplete.";
		throw err;
	}
}

void checkNoOfTokensMax(int totalNumber, int expectedNumber, int line)
{
	if (totalNumber > expectedNumber)
	{
		string err = "Error: Your command doesn't have the expected number of tokens at line " + to_string(line) + ". Your command might have too many arguments.";
		throw err;
	}
}

void throwUnrecognizedCommand(string token, int line)
{
	string err = "Error: Unrecognized token \"" + token + "\" at line " + to_string(line) + ".";
	throw err;
}

void checkValidName(string str, int line)
{
	if (!hasValidName(str))
	{
		string err = "Error: The following name \"" + str + "\" at line " + to_string(line) + " is not valid.";
		throw err;
	}
}

void checkMaybeValidInput(string str, int line)
{
	if (!hasCharsInString(str, ",()"))
	{
		string err = "Error: The following input \"" + str + "\" at line " + to_string(line) + " is not valid. Please remove any spaces if there are any.";
		throw err;
	}
}

void checkColumnType(string str, int line)
{
	if (!(str == "integer" || str == "text" || str == "float"))
	{
		string err = "Error: The following column type \"" + str + "\" at line " + to_string(line) + " is not valid. Column types can only be one of the following values: integer, text, float.";
		throw err;
	}
}

void checkIfFloat(string str, int line)
{
	string err = "Error: The following token \"" + str + "\" at line " + to_string(line) + " is not a valid integer.";
	if (!isdigit(str[0]) || !isdigit(str[str.length() - 1]))
	{
		throw err; // first and last character needs to be a digit all the time
	}
	for (int i = 1; i < str.length() - 1; i++)
	{
		if (!isdigit(str[i]))
		{ // the rest can be either a digit or a "."
			if (str[i] != '.')
			{
				throw err;
			}
		}
	}
}

void checkIfInt(string str, int line)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			string err = "Error: The following token \"" + str + "\" at line " + to_string(line) + " is not a valid integer.";
			throw err;
		}
	}
}

void checkIfEmpty(string str, string property, int line)
{
	if (str.empty())
	{
		string err = "Error: The following property " + property + "\"" + str + "\" at line " + to_string(line) + " cannot be an empty string.";
		throw err;
	}
}

void tokenizer(string input, string delimiter, int &currentToken, string *tokens)
{
	int pos = 0;

	currentToken = 0;
	while ((pos = input.find(delimiter)) != string::npos)
	{
		tokens[currentToken] = input.substr(0, pos);
		input.erase(0, pos + delimiter.length());
		currentToken++;
	}
	tokens[currentToken] = input.substr(0, pos);
	currentToken++;
}

void lexer(string *tokens, int noOfTokens, int line, Database& db)
{

	checkNoOfTokensMin(noOfTokens, 1, line);

	if (tokens[0] == "CREATE")
	{
		// CREATE TABLE students ((id,integer,1000,0),(nume,text,128,��),(grupa,text,50,�1000�))

		// check number of tokens then check if the next token exists
		checkNoOfTokensMin(noOfTokens, 2, line);
		checkToken(tokens[1], "TABLE", line);

		// check number of tokens then check if the next token which is the name of the table is valid.
		checkNoOfTokensMin(noOfTokens, 3, line);
		checkValidName(tokens[2], line);
		checkIfEmpty(tokens[2], "table name", line);
		// save tableName for easier access.
		string tableName = tokens[2];

		// check number of tokens then check if the table data has the correct formatting
		// tokens[3] should looks like this: ((id,integer,1000,0),(nume,text,128,��),(grupa,text,50,�1000�))
		// decided to not accept spaces in between the data for easier parsing.
		checkNoOfTokensMin(noOfTokens, 4, line);
		checkMaybeValidInput(tokens[3], line);
		// save the input for the tables for easier access
		string *tableColumns = new string[100]; // assuming a table will not have more than 100 columns.
		int noOfColumns = 0;

		tokenizer(tokens[3], "),(", noOfColumns, tableColumns);

		// check to see if we have at least one column in the table
		checkNoOfTokensMin(noOfColumns, 1, line);
		// check to see if the start and end of the input are ((...))
		if (tableColumns[0].length() >= 2)
		{
			if (!(tableColumns[0][0] == '(' && tableColumns[0][1] == '('))
			{
				string err = "Error: Invalid table formatting at line " + to_string(line) + ". Expected \"((\" but instead got \"" + tableColumns[0][0] + tableColumns[0][1] + "\".";
				throw err;
			}
		}
		if (tableColumns[noOfColumns - 1].length() >= 2)
		{
			int lastPos = tableColumns[noOfColumns - 1].length() - 1;
			if (!(tableColumns[noOfColumns - 1][lastPos] == ')' && tableColumns[noOfColumns - 1][lastPos - 1]))
			{
				string err = "Error: Invalid table formatting at line " + to_string(line) + ". Expected \"))\" but instead got \"" + tableColumns[noOfColumns - 1][lastPos] + tableColumns[noOfColumns - 1][lastPos - 1] + "\".";
				throw err;
			}
		}

		// assuming now we have an array that looks like this: tableColumns = ["id,integer,1000,0", "nume,text,128,��", "grupa,text,50,�1000�" ]
		for (int i = 0; i < noOfColumns; i++)
		{
			string *tableProperties = new string[100];
			int noOfProperties = 0;

			tokenizer(tableColumns[i], ",", noOfProperties, tableProperties);

			// check if we have the exact number of properties
			checkNoOfTokensMin(noOfProperties, 4, line);
			checkNoOfTokensMax(noOfProperties, 4, line);

			// separate the properties in their own variables to be easier to use
			string columnName = tableProperties[0], columnType = tableProperties[1], columnSize = tableProperties[2], columnDefaultValue = tableProperties[3];

			// check if they are not empty
			checkIfEmpty(columnName, "column name", line);
			checkIfEmpty(columnType, "column type", line);
			checkIfEmpty(columnSize, "column size", line);
			checkIfEmpty(columnDefaultValue, "column default value", line);

			// we can dealocate the tableProperties
			if (tableProperties != nullptr)
				delete[] tableProperties;

			// we check to see if the name is valid
			checkValidName(columnName, line);

			// we check to see if the columnType is correct
			checkColumnType(columnType, line);

			// we check if the size is a valid integer
			checkIfInt(columnSize, line);

			// we now check the default value
			if (columnType == "integer")
				checkIfInt(columnDefaultValue, line);
			if (columnType == "float")
				checkIfFloat(columnDefaultValue, line);
			// if its text it can be whatever

			// Here call the methods to execute the command



			// --------------------------------------------
		}
		return;
	}
	if (tokens[0] == "DROP")
	{
		// DROP TABLE studenti

		// check number of tokens then check if the next token exists
		checkNoOfTokensMin(noOfTokens, 3, line);
		checkNoOfTokensMax(noOfTokens, 3, line);
		checkToken(tokens[1], "TABLE", line);

		// check name of table is valid
		checkIfEmpty(tokens[2], "table name", line);
		checkValidName(tokens[2], line);

		// Here call the methods to execute the command

		// --------------------------------------------

		return;
	}
	if (tokens[0] == "DISPLAY")
	{
		// DISPLAY TABLE studenti
		//		 (this displays the table details not the contents of the table)

		checkNoOfTokensMin(noOfTokens, 3, line);
		checkNoOfTokensMax(noOfTokens, 3, line);
		checkToken(tokens[1], "TABLE", line);

		// check name of table is valid
		checkIfEmpty(tokens[2], "table name", line);
		checkValidName(tokens[2], line);

		// Here call the methods to execute the command

		// --------------------------------------------

		return;
	}
	if (tokens[0] == "INSERT")
	{
		// INSERT INTO studenti VALUES (1,�John�,�1001�)
		//   |
		//   |   The quotes are unnecessary and make the parsing harder. :)
		//   V
		// INSERT INTO studenti VALUES (1,John,1001)

		// Check number of tokens
		checkNoOfTokensMin(noOfTokens, 5, line);
		checkNoOfTokensMax(noOfTokens, 5, line);

		// Check second token
		checkToken(tokens[1], "INTO", line);

		// check name of table is valid
		checkIfEmpty(tokens[2], "table name", line);
		checkValidName(tokens[2], line);

		// check 4th token
		checkToken(tokens[3], "VALUES", line);

		// check the last token which has the input for the table
		// parse the tokens
		int noOfInputValues = 0;
		string *inputValues = new string[100]; // assuming no more than 100 columns
		tokenizer(tokens[5], ",", noOfInputValues, inputValues);

		// check the paranthesis
		if (tokens[5].length() >= 2)
		{
			int lastPos = inputValues[noOfInputValues - 1].length() - 1;
			if (!(tokens[5][lastPos] == ')' && tokens[5][0]) == '(')
			{
				string err = "Error: Invalid table formatting at line " + to_string(line) + ". Expected \"()\" but instead got \"" + tokens[5][0] + tokens[5][lastPos] + "\".";
				throw err;
			}
		}

		// check the number of tokens
		// Call the db methods to find the number of columns in the table with the name tokens[2]
		//checkNoOfTokensMin(noOfInputValues, ..., line);
		//checkNoOfTokensMax(noOfInputValues, ..., line);

		// check the validity of the tokens according to their respective columns in the database

		// do the insertion

		return;
	}
	if (tokens[0] == "SELECT")
	{
		// SELECT (nume) FROM studenti WHERE id = 1
		// SELECT (id,nume,grupa)  FROM  studenti
		// SELECT ALL FROM studenti WHERE id = 1
		// SELECT ALL FROM studenti

		checkNoOfTokensMin(noOfTokens, 4, line);

		return;
	}
	if (tokens[0] == "DELETE")
	{
		// DELETE FROM studenti WHERE nume = �John�
		// |
		// |
		// V
		// DELETE FROM studenti WHERE nume=John
		checkNoOfTokensMin(noOfTokens, 5, line);
		checkNoOfTokensMax(noOfTokens, 5, line);

		checkToken(tokens[1], "FROM", line);

		checkValidName(tokens[2], line);

		checkToken(tokens[3], "WHERE", line);

		int noOfCompValues = 0;
		string *compValues = new string[2];

		tokenizer(tokens[4], "=", noOfCompValues, compValues);

		checkNoOfTokensMin(noOfCompValues, 2, line);
		checkNoOfTokensMax(noOfCompValues, 2, line);

		checkValidName(compValues[0], line);
		// check the type of the column and verify if the second value is comparable

		// call the methods

		return;
	}
	if (tokens[0] == "UPDATE")
	{
		// UPDATE studenti SET nume = �Alice� WHERE id = 1
		// UPDATE studenti SET nume = �Alice� WHERE nume= �Bianca�
		// |
		// |
		// V
		// UPDATE studenti SET nume=Alice WHERE nume=Bianca

		return;
	}
	// If none match then throw error
	throwUnrecognizedCommand(tokens[0], line);
}

void runCommand(string input, int line)
{
	try
	{
		int noOfTokens = 0;
		string *tokens = new string[100]; // assuming the maximum number of tokens a command is going to have is 100

		Database* db = new Database("test");

		tokenizer(input, " ", noOfTokens, tokens);
		lexer(tokens, noOfTokens, line, db);

		delete[] tokens;
	}
	catch (const string e)
	{
		cout << e;
	}

	return;
}

//class Token {
//public: 
//	enum class Kind {
//		Number,		
//		Indentifier,
//		LeftParen, 
//		RightParen, 
//		LessThan,
//		GreaterThan,
//		Equal,
//		Quote, 
//		SemiColon,
//		Dot,
//		Comment, 
//		End, 
//		Unexpected
//	};
//
//	Kind kind; 
//	string content;
//
//	Token(Kind kind, string content) {
//		this->kind = kind;
//		this->content = content;
//	}
//};

