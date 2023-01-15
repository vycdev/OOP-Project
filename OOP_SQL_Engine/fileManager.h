#include "database.h"

class FileManager {
private:
	Database* db;

public:

	FileManager(Database* db) {
		this->db = db;

		// read config from file
		// create the tables with the columns in the database from the config
		// import all of the data from the table files 
	}

	void saveConfig() {
		// This will be used for saving the config as well as updating it (so if the config already exists you overwrite it)
		// 
		// using the database we have so far we shoudl create a config file based on that
		// config files should like like this
		// 
		// config.txt
		// ----------------------------------
		// [tableName] [number of columns]
		// [column 1 name] [column 1 type] [column 1 size] [column 1 default value]
		// [column 2 name] [column 2 type] [column 2 size] [column 2 default value]
		// ...
		// [tableName 2] [number of columns]
		// [column 1 name] [column 1 type] [column 1 size] [column 1 default value]
		// [column 2 name] [column 2 type] [column 2 size] [column 2 default value]
		// ...
		// ...
		// ----------------------------------
		// 
		// !!! Without any of the square brackets, only spaces between the values !!!
		// 
		// if we could've used a json library or something for parsing then it wouldve been so much easier to do config files
	}

	void saveDatabase() {
		// Create files for each table and put the data in them
		// If the files exist already you of course ovewrite them
		// Each table file should have its name the same as the name of the table
	}

	void saveSelect(string s) {
		// Saves the output of a select statement in a file
		// 
		// From the requirements file:
		// For example: for a SELECT command the text file SELECT_1.txt, containing the 
		// result of that command, will be generated. For the next SELECT command. 
		// It is  generated SELECT_2.txt The results displayed by commands on the 
		// screen will also be saved in these files.
	}
};