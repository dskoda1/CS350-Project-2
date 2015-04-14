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

	int pid;
	int pageNum;
};

//Helper functions for debugging
void showProcesses(const map<int, Process*>& runningProcs);
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
**	and map used to store processes
**/
	vector<memFrame> memory;
	memory.resize(atoi(argv[1]));
	map<int, Process*> Processes;
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
			//Second number is VPN
			ss >> temp;
			vpn = atoi(temp.c_str());

			//Process exists
			if((rover = Processes.find(pid)) != Processes.end())
			{
				if(rover->second->locatePage(vpn) > -1)
				{
					cout << "Found in memory" << endl;
				}
				else
				{
					cout << "Not found in memory" << endl;
				}
			}
			//Dne
			else
			{
			}	
		}

		ss.clear();
	}

	showProcesses(Processes);
	return 0;
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

