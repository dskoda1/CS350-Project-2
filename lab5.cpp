#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <array>
#include <sstream>
#include <string>
#include <fstream>
#include "Process.h"
using namespace std;
struct memFrame{

	int id;
	int pageNum;
};

//Helper functions for debugging
void showProcesses(const map<int, Process*>& runningProcs);
void showMemory(const vector<memFrame *>& mem);
//Cross check that requested data is in memory
void checkReference(const vector<memFrame>& physicalMemory, int pid, int page);
int main(int argc, char ** argv)
{

/*	Check for appropriate arguments
**	Must be in the form ./program2 <frames-of-memory> <input-file>
*/
	if(argc != 3)
	{
		cerr << "Invalid arguments passed: Must be in the form" << endl;
		cerr << "   ./program2 <frames-of-memory> <input-file>" << endl;
	}

/**
**	Allocate the initial physical memory available,
**	and map used to store processes. Also bool to determine
**	if space is available in memory.
**/
	vector<memFrame *> memory;
	//initialize memory to be empty
	for(int i = 0; i < atoi(argv[1]); i++)
	{
		memFrame * a = new memFrame;
		a->id = -1;
		a->pageNum = -1;
		memory.push_back(a);
	}
	map<int, Process*> Processes;
	bool memNotFull = true;
/*
**	Begin Processing of Input file.
*/
	stringstream ss;
	string temp, line;
	int pid = 0, memSize = 0, vpn = 0;
	ifstream in;

	in.open(argv[2], ifstream::in);
	auto rover = Processes.begin();
	while(in.good() && getline(in, line))
	{
		ss << line;
		ss >> temp;
		
		//Check which type of command new line is
		//Start: create a new process and add to map
		if(!temp.compare("START"))
		{
			//First number is process number
			ss >> temp;
			pid = atoi(temp.c_str());
			//Second is Address space size
			ss >> temp;
			memSize = atoi(temp.c_str());
			Processes.insert(make_pair(pid, new Process(pid, memSize)));
		}
		//Reference: access the process to see if the requested
		//frame is in memory or not
		if(!temp.compare("REFERENCE"))
		{	
			//First number is process number
			ss >> temp;
			pid = atoi(temp.c_str());
			//Second number is VPN- page number in address space of process
			ss >> temp;
			vpn = atoi(temp.c_str());

			//Process exists
			if((rover = Processes.find(pid)) != Processes.end())
			{
				//Check if frame is in memory from process information
				if(rover->second->locatePage(vpn)  > -1)
				{
					//cout << "Found in memory" << endl;
				}
				//If not in memory, Check if space to place in mem
				else if(memNotFull)
				{	
					//Iterate through memory 
					for(int i = 0; i < memory.size(); i++)
					{
						//Check for an open spot
						if(memory.at(i)->id == -1)
						{
							//Update the open memory frame
							cerr << "Found an open spot in memory" << endl;
							memory.at(i)->id = pid;
							memory.at(i)->pageNum = vpn;
							//Update the process as well to reflect a page
							//being placed in memory
							rover->second->updateTable(vpn, i);
							break;
						}
					
					}
					


				}
				//Else deal with page fault and evict some other page
				//Not needed till final project submission
				else
				{
					//cout << "Not found in memory" << endl;
				}
			}
			//Dne
			else
			{
			}	
		}

		ss.clear();
	}
	showMemory(memory);
	showProcesses(Processes);
	return 0;
}
void checkReference(const vector<memFrame>& physicalMemory, int id, int page)
{
	
	

}

void showMemory(const vector<memFrame *>& mem)
{

	for(auto rover : mem)
	{
		cout << "Process " << rover->id << ", page number: " << rover->pageNum << endl;

	}
}

void showProcesses(const map<int, Process*>&  runningProcs)
{

	for(auto rover : runningProcs)
	{
		cout << "Process " << rover.first << endl;
		for (int i = 1; i < rover.second->getSize(); i++)
		{
			cout << "Page " << i << " in memory location: " << rover.second->locatePage(i) << endl;
		}
		cout << endl;
	}



}

