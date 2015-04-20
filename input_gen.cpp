#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;
/**	Creates input files to test Program 2
**	USAGE: ./input_gen <num_proc> <proc_addr_size> <#_ref> <pattern>
**	Where pattern could be random, ... (Need more patterns)
**
**/
int main(int argc, char ** argv){

	int numProc;//number of processes, change later
	int addrSize;//address space size, change later
	int numRef;//number of references, change later

	if(argc != 5)
	{
		cerr << "Usage: ./input_gen <num_proc> <proc_addr_size> <#_ref> <pattern> " << endl;
		exit(0);
	}
	//Parse command line arguments
	numProc = atoi(argv[1]);
	addrSize = atoi(argv[2]);
	numRef = atoi(argv[3]);
	//TODO: parse pattern string


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
