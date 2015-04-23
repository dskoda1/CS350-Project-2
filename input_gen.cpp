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
	int pattern;//pattern used for locality of reference, 0 for locality of ref, 1 for random,
	//2 for locality but choosing random processes each time
	
	if(argc != 6)
	{
		cerr << "Usage: ./input_gen <num_proc> <proc_addr_size> <#_ref> <pattern> <filename> " << endl;
		exit(0);
	}
	//Parse command line arguments
	numProc = atoi(argv[1]);
	addrSize = atoi(argv[2]);
	numRef = atoi(argv[3]);
	pattern = atoi(argv[4]);


	srand(time(NULL));
	int x,y;//used as random numbers later

	

	std::ofstream testfile;
	testfile.open(argv[5]);
	
	if(pattern == 0)//locality of reference case
	{
		//Pretend like there is 5 times as many processes
		//This way each process issues references 5 times
		int refPerProc = numRef / (numProc*5);
		int remainder = numRef % numProc;		
		
		//write START lines to file
		for(int i = 1; i < numProc + 1; i++)
		{
			testfile << "START " << i << " " << addrSize << "\n";
		}

		//write REFERENCE lines to file
		for(int i = 0; i < numProc*5; i++)
		{	
			for(int j = 0; j < refPerProc; j++)
			{
				y = rand() % addrSize +  1;
				//(i+1)%numProc + 1 ensures valid process number, doesnt always start at 0
				testfile << "REFERENCE " << (i+1)%numProc+1 << " " << y << "\n";
		
			}
		}
		if(remainder != 0)
		{
			for(int i = 0; i < remainder; i++)
			{
				x = rand() % numProc + 1;
				y = rand() % addrSize +  1;
				testfile << "REFERENCE " << x << " " << y << "\n";			
			}
		}
		//write TERMINATE lines to file
		for(int i = 1; i < numProc + 1; i++){
			testfile << "TERMINATE " << i << "\n";

		}
	}
	else if(pattern == 1)//random access case
	{
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
	}
	//Random process issuing references with locality
	else if(pattern == 2)
	{
		//write START lines to file
		for(int i = 1; i < numProc + 1; i++)
		{
			testfile << "START " << i << " " << addrSize << "\n";

		}
		//Each process gets 10 turns to go
		int refsToGo[numProc + 1];
		int process = 0, y = 0;
		int refsPerProc = numRef / (numProc*10);
		for(int i = 1; i < numProc + 1; i++)
		{
			refsToGo[i] = 10;
		}
		//Go until no more references
		while(numRef > 0)
		{
			process = rand() % numProc + 1;
			//Process picked still has some references to go
			if(refsToGo[process] > 0)
			{
				refsToGo[process]--;
				for(int i = 0; i < refsPerProc; i++)
				{
					y = rand() % addrSize;
					testfile << "REFERENCE " << process << " " << y << endl;
					numRef--;
				}
			}
			//else terminate process
			else if(refsToGo[process]  == 0)
			{
				refsToGo[process] = -1;
				testfile << "TERMINATE " << process << "\n";
			}	

		}	
		//Terminate any processes not terminated in loop above
		for(int i = 1; i < numProc + 1; i++)
		{
			if(refsToGo[i] != -1)
			{
				testfile << "TERMINATE " << i << "\n";

			}

		}



	}
	
	
	testfile.close();
	return 0;
}//end main
