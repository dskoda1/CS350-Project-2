#include "Process.h"
using namespace std;
//Changing this

//Constructor
Process::Process(int id, int size)
{
	pid = id;
	tableSize = size+1;
	for(int i = 0; i < tableSize; i++)
	{
		pageTable.push_back(-1);
	}
}

//Locate a page in processes page table
int Process::locatePage(int pageNum)
{
	return(pageTable.at(pageNum));
}

//Get size of address space
int Process::getSize()
{
	return tableSize;
}


