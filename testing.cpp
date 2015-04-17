#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
//Creates input files to test Program 2

int main(int argc, char ** argv){

	srand(time(NULL));
	int x,y;//used as random numbers later

	int procNum = 5;//number of processes, change later
	int addrSize = 5;//address space size, change later
	int numRef = 10;//number of references, change later

	std::ofstream testfile;
	testfile.open("input.txt");
	//write START lines to file
	for(int i = 1; i < procNum + 1; i++)
	{
		testfile << "START " << i << " " << addrSize << "\n";

	}
	//write REFERENCE lines to file
	for(int i = 0; i < numRef; i++){
		
		x = rand() % procNum + 1;
		y = rand() % addrSize +  1;
		testfile << "REFERENCE " << x << " " << y << "\n";

	}
	//write TERMINATE lines to file
	for(int i = 1; i < procNum + 1; i++){
		
		testfile << "TERMINATE " << i << "\n";

	}
	
	
	testfile.close();
	return 0;
}//end main
