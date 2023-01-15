#include <iostream>
#include <string>
#include <fstream>

#include "./parsing.h"

#include "database.h"

using namespace std;


int main()
{ 
	ofstream Output("filename.txt");

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
		
	//Database* db = new Database();
	
	Output << "______________" << endl;
	tab->printColumns();
	//db->CreateTable(*tab);
	//string vectorString[2];
	//vectorString[0] = "Nume";
	//db->GetData("test", vectorString, 1, "a", "b");
	Output << "______________" << endl;

	delete tab; // the deconstructor doesn't explode fortunately 
	

	//string input;
	//getline(cin, input);
	//
	// runCommand(input, 0);

	//-i "fisier.txt",
	//-c ASDFASDF

	//./program.exe -c COMANDA


	// !!!!!!!!!!! THERE MIGHT BE A PROBLEM WITH VISUAL STUDIO, IT MIGHT NOT HAVE OPENED IN THE SOLUTION EXPLORER THE FOLLOWING FILES: column.h database.h and tableh. !!!!!!!!!!!!!!!!!
	// !!!!!!!!!!! THERE MIGHT BE A PROBLEM WITH VISUAL STUDIO, IT MIGHT NOT HAVE OPENED IN THE SOLUTION EXPLORER THE FOLLOWING FILES: column.h database.h and tableh. !!!!!!!!!!!!!!!!!
	// !!!!!!!!!!! THERE MIGHT BE A PROBLEM WITH VISUAL STUDIO, IT MIGHT NOT HAVE OPENED IN THE SOLUTION EXPLORER THE FOLLOWING FILES: column.h database.h and tableh. !!!!!!!!!!!!!!!!!
	// !!!!!!!!!!! THERE MIGHT BE A PROBLEM WITH VISUAL STUDIO, IT MIGHT NOT HAVE OPENED IN THE SOLUTION EXPLORER THE FOLLOWING FILES: column.h database.h and tableh. !!!!!!!!!!!!!!!!!
	// !!!!!!!!!!! THERE MIGHT BE A PROBLEM WITH VISUAL STUDIO, IT MIGHT NOT HAVE OPENED IN THE SOLUTION EXPLORER THE FOLLOWING FILES: column.h database.h and tableh. !!!!!!!!!!!!!!!!!
	return 0;
}