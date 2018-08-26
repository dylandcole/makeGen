#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "executable.h"
using namespace std;

/*
Future Expansions:
- Import from/export to existing makefile elsewhere in the filesystem
- Add capacity for multiple executable generation from single makefile
*/

void Executable::run() {
	int userChoice;
	
	vector <string> sourceFiles;
	bool keepObjectFiles = false;
	string programName = "default";

	while(true) {
		print();
		userChoice = stoi(getUserInput());
		switch(userChoice) {
			case 0:
				sourceFiles = sourceFilesMenu(sourceFiles);
				break;
			case 1:
				configMenu(keepObjectFiles, programName);
				break;
			case 2:
				generateMakefile(programName, sourceFiles, keepObjectFiles);
				return;
				break;
			case 3:
				return;
				break;
			default:
				cout << "Menu choice not recognized" << endl;
				break;
		}
	}
	return;
}


//Fuction definitions
void Executable::print() {
	clearScreen();
	cout << "___________________________________________" << endl;
	cout << "  __  __       _         _____            " << endl;
	cout << " |  \\/  |     | |       / ____|           " << endl;
	cout << " | \\  / | __ _| | _____| |  __  ___ _ __  " << endl;
	cout << " | |\\/| |/ _` | |/ / _ \\ | |_ |/ _ \\ '_ \\ " << endl;
	cout << " | |  | | (_| |   <  __/ |__| |  __/ | | |" << endl;
	cout << " |_|  |_|\\__,_|_|\\_\\___|\\_____|\\___|_| |_|" << endl;
	cout << "___________________________________________" << endl;
	cout << endl;
	cout << "[0] Source Files" << endl;
	cout << endl;
	cout << "[1] Configuration" << endl;
	cout << endl;
	cout << "[2] Generate Makefile" << endl;
	cout << endl;
	cout << "[3] Quit" << endl;
	cout << endl << endl;
}

void Executable::clearScreen() { //Outputs 100 empty lines to console to clear
		for (int i = 0; i < 100; i++) {
		cout << endl;
	}
}

string Executable::getUserInput() { //Gets user input as a single string (only works for single digits or words)
	string userInput = "";
	cin >> userInput;
	cout << endl << endl;
	return userInput;
}

vector <string> Executable::sourceFilesMenu(vector <string> sourceFiles) { //Runs source file addition/removal processes
	while(true) {
		clearScreen();
		cout << "------------------" << endl;
		cout << "Source Files" << endl;
		cout << "------------------" << endl;
		
		cout << "Current Files: ";
		if(sourceFiles.empty()) {
			cout << "none" << endl;
		}
		else {
			for (string file : sourceFiles) {
				cout << file << " ";
			}
			cout << endl;
		}
		
		cout << endl;
		cout << "[0] Add file" << endl;
		cout << endl;
		cout << "[1] Remove file" << endl;
		cout << endl;
		cout << "[2] Back" << endl;
		cout << endl;
		
		int userInput = stoi(getUserInput());
		string filename;
		
		switch(userInput) {
			case 0:
				cout << "File to be added: ";
				filename = getUserInput();
				if (filename.rfind(".cpp") != string::npos) {
					sourceFiles.push_back(filename);
				}
				break;
			case 1:
				cout << "File to be removed: ";
				filename = getUserInput();
				for(int i = 0; i < sourceFiles.size(); i++) {
					if (sourceFiles.at(i) == filename) {
						sourceFiles.erase(sourceFiles.begin() + i);
					}
				}
				break;
			case 2:
				return sourceFiles;
			default:
				break;
		}
	}
	return sourceFiles;
}
	
void Executable::configMenu(bool& keepObjectFiles, string& programName) {
	while (true) {
		clearScreen();
		cout << "------------------" << endl;
		cout << "Configuration" << endl;
		cout << "------------------" << endl;
		
		cout << endl;
		cout << "[0] Program Name: " << programName << endl;
		cout << endl;
		cout << "[1] Keep Object Files After Make: ";
		if (keepObjectFiles) {
			cout << "true";
		}
		else {
			cout << "false";
		}
		cout << endl;
		cout << endl;
		cout << "[2] Back" << endl;
		cout << endl;
		
		int userInput = stoi(getUserInput());
		switch(userInput) {
			case 0:
				cout << "New Program Name: ";
				programName = getUserInput();
				break;
			case 1:
				if (keepObjectFiles) {
					keepObjectFiles = false;
				}
				else {
					keepObjectFiles = true;
				}
				break;
			case 2:
				return;
			default:
				break;
		}
	}
	return;
}
	
string Executable::cppToO(string cppFilename) {
	return cppFilename.replace (cppFilename.find(".cpp"),4,".o");
}
	
void Executable::generateMakefile(string programName, vector<string> sourceFiles, bool keepObjectFiles) {
	ofstream out;
	out.open("./generated/makefile");
	out << "all : " << programName << "\n";
	out << "\n";
	out << programName << " :";
	for(string sourceFile : sourceFiles) {
		out << " " << cppToO(sourceFile);
	}
	out << "\n";
	out << "\tg++";
	for(string sourceFile : sourceFiles) {
		out << " " << cppToO(sourceFile);
	}
	out << " -o " << programName << "\n";
	if (!keepObjectFiles) {
		out << "\trm -f *o\n";
	}
	for(string sourceFile : sourceFiles) {
		out << "\n";
		out << cppToO(sourceFile) << " : " << sourceFile << "\n";
		out << "\tg++ -c " << sourceFile << "\n";
	}
	out << "\n";
	out << "clean :" << "\n";
	out << "\trm -f *o makeGen";
	out.close();
	return;
}



