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

int main()
{
	string input;
	char* inputChar = new char[100];
	for (int i = 0; i < 100; i++)
	{
		inputChar[i] = '\0';
	}
	getline(cin, input);
	strcpy(inputChar, input.c_str());
	cout << inputChar;

}