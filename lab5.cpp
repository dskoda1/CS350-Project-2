#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <array>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
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
//Functions to reference for specific algorithms
void ramRef(map<int, Process*>& runningProcs, Process * process, vector<memFrame *>& ram, int vpn);
//Global variables
bool ramNotFull, lruNotFull, fifoNotFull;
int ramHit, lruHit, fifoHit, totalRef;
int main(int argc, char ** argv)
{
		srand(time(NULL));

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
	 **	and map used to store processes. Need three vectors
	 **  for each different algorithm. Also bool to determine
	 **	if space is available in memory.
	 **/
	vector<memFrame *> ram;
	vector<memFrame *> lru;
	vector<memFrame *> fifo;	

	/**	Initialize counters for hit rates **/
	ramHit = 0;
	lruHit = 0;
	fifoHit = 0;
	int totalRef = 0;

	/**Initialize global bools for memory **/
	ramNotFull = true;
	lruNotFull = true;
	fifoNotFull = true;
	//initialize memory to be empty
	for(int i = 0; i < atoi(argv[1]); i++)
	{
		memFrame * a = new memFrame;
		a->id = -1;
		a->pageNum = -1;
		ram.push_back(a);
		memFrame * b = new memFrame;
		b->id = -1;
		b->pageNum = -1;
		lru.push_back(b);
		memFrame * c = new memFrame;
		c->id = -1;
		c->pageNum = -1;
		fifo.push_back(c);
	}
	map<int, Process*> Processes;
	//made iterator for use with map
	map<int, Process*>:: iterator iter;
	/*
	 **	Begin Processing of Input file.
	 */
	stringstream ss;
	string temp, line;
	int pid = 0, memSize = 0, vpn = 0;
	ifstream in;

	in.open(argv[2], ifstream::in);
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
		//Terminate: erase the process with a matching pid to that of input
		else if(!temp.compare("TERMINATE"))
		{
			//Setting pid to id of terminating process
			ss >> temp;
			pid = atoi(temp.c_str());
			//Set iterator to terminating process and erase it
			if((iter = Processes.find(pid)) != Processes.end())
			{
				//Reassign memory values to -1
				//And set bools to reflect open spots
				//IFF some are opened up
				//TODO: add support for lru and fifo
				bool ramOpenedUp = false;
				for(u_int i = 0; i < ram.size(); i++)
				{
					if(ram.at(i)->id == pid)
					{
						ram.at(i)->id = -1;
						ram.at(i)->pageNum = -1;
						ramOpenedUp = true; 
					}				
				}
				if(ramOpenedUp)
				{
					ramNotFull = true;
				}

				Processes.erase(iter);
			}
		}
		//Reference: access the process to see if the requested
		//frame is in memory or not
		else if(!temp.compare("REFERENCE"))
		{	
			//First number is process number
			ss >> temp;
			pid = atoi(temp.c_str());
			//Second number is VPN- page number in address space of process
			ss >> temp;
			vpn = atoi(temp.c_str());

			//Process exists
			if((iter = Processes.find(pid)) != Processes.end())
			{
				totalRef++;
				//Call ram reference function
				ramRef(Processes, iter->second, ram, vpn);			


				//TODO: Call lru reference function
				//Actually listened in class for a 
				//second..lets use a stack for this
				//lruRef(iter->second, lru, vpn);

				//TODO: Call fifo reference function
				//fifoRef(iter->second, fifo, vpn);


			}
			//Dne
			else
			{
				cerr << "Process " << pid << " currently does not exist. Error." << endl;
			}	
		}

		ss.clear();
	}
	//showMemory(ram);
	//showProcesses(Processes);
	//Hit rate for ram
	cout << "Page Fault Rates:" << endl;
	cout << "RANDOM: " << (float)ramHit / float(totalRef) << endl;


	return 0;
}
void ramRef(map<int, Process*> & runningProcs, Process * process, vector<memFrame *>& ram, int vpn)
{
	//Check if frame is in memory from process information
	if(process->locatePageRam(vpn)  > -1)
	{
		ramHit++;
	}
	//If not in memory, Check if space to place in mem
	else if(ramNotFull)
	{	
		//Iterate through memory 
		for(u_int i = 0; i < ram.size(); i++)
		{
			//Check for an open spot
			if(ram.at(i)->id == -1)
			{
				//Update the open memory frame
				//cerr << "Found an open spot in memory" << endl;
				ram.at(i)->id = process->getPid();
				ram.at(i)->pageNum = vpn;
				//Update the process as well to reflect a page
				//being placed in memory
				process->updateRamTable(vpn, i);
				break;
			}
			else if(i + 1 == ram.size())
				ramNotFull = false;

		}

	}
	//Third case, memory full, evict a random page
	else if(!ramNotFull)
	{
		auto iter = runningProcs.begin();
		int randomPage = rand() % ram.size();
		cout << "Evicting a random page at slot: " << randomPage << endl;
		//Update processes page table
		//Protect against acessing a process which does not exist for some reason
		if((iter = runningProcs.find(ram.at(randomPage)->id)) != runningProcs.end())
		{
			iter->second->updateRamTable(ram.at(randomPage)->pageNum, -1);
		}
		//Update process which is placing page into spot just evicted
		process->updateRamTable(vpn, randomPage);
	}


}

void checkReference(const vector<memFrame *>& physicalMemory, int id, int page)
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
			cout << "Page " << i << " in memory location: " << rover.second->locatePageRam(i) << endl;
		}
		cout << endl;
	}



}

