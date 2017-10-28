// EDPath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[]) // array of pointers to strings (char arrays)
{
	
	if (argc != 4)
	{
		cout << "ERROR: Incorrect number of input arguments." << endl;
		return -1;
	}

	string sstart = string(argv[1]);
	string starget = string(argv[2]);
	string sjumprng = string(argv[3]);
	float fjumprng;
	size_t chars;

	try
	{
		fjumprng = stof(sjumprng, &chars);
	}
	catch (const invalid_argument& ia)
	{
		cout << "ERROR: Cannot convert the jump range: " << ia.what() << endl;
		return -1;
	}
	catch (const out_of_range& oor)
	{
		cout << "ERROR: Cannot convert the jump range: " << oor.what() << endl;
		return -1;
	}
	

	replace(sstart.begin(), sstart.end(), '_', ' ');
	replace(starget.begin(), starget.end(), '_', ' ');
	

	cout << "WELCOME TO EDPATH" << endl;
	cout << "Initiating the program..." << endl;
	navservice *nav = new navservice();
	
	cout << "Calculating the solution..." << endl << endl;
	nav->find_path(sstart, starget, 20);
	nav->print_report();

	delete nav;


	// cout << endl << "Press any key to exit." << endl;
	// getchar();

    return 0;
}

