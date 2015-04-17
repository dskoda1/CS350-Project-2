#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;
//Creates input files to test Program 2

int main(int argc, char ** argv){

	int numProc;//number of processes, change later
	int addrSize;//address space size, change later
	int numRef;//number of references, change later

	cout << "Enter number of processes:\n";
	cin >> numProc;	
	cout << "Enter address space size:\n";
	cin >> addrSize;
	cout << "Enter number of references:\n";
	cin >> numRef;

	srand(time(NULL));
	int x,y;//used as random numbers later

	

	std::ofstream testfile;
	testfile.open("input.txt");
	//write START lines to file
	for(int i = 1; i < numProc + 1; i++)
	{
		testfile << "START " << i << " " << addrSize << "\n";

	}
	//write REFERENCE lines to file
	for(int i = 0; i < numRef; i++){
		
		x = rand() % numProc + 1;
		y = rand() % addrSize +  1;
		testfile << "REFERENCE " << x << " " << y << "\n";

	}
	//write TERMINATE lines to file
	for(int i = 1; i < numProc + 1; i++){
		
		testfile << "TERMINATE " << i << "\n";

	}
	
	
	testfile.close();
	return 0;
}//end main
