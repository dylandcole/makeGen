#pragma once

#include <string>
#include <vector>
using namespace std;

class Executable{
	public:
	void run();
	
	private:
	void print();
	void clearScreen();
	string getUserInput();
	vector <string> sourceFilesMenu(vector <string>);
	void configMenu(bool&, string&);
	void generateMakefile(string, vector<string>, bool);
	string cppToO(string);
};