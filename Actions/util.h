#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//*********************************************************
// Definition of function openFileIn. Accepts a reference
// to an fstream object as an argument. The file is opened
// for input. The function returns true upon success, false
// upon failure.
//*********************************************************
bool openFileIn(fstream &file, string name)
{
	file.open(name, ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

//*********************************************************
// Definition of function showContents. Accepts an fstream
// reference as its argument. Uses a loop to read each name
// from the file and displays it on the screen.
//*********************************************************
void showContents(fstream &file)
{
	string line;

	while (file >> line)
	{
		cout << line << endl;
	}
}