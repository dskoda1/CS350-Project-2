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
		ramTable.push_back(-1);
		lruTable.push_back(-1);
		fifoTable.push_back(-1);
	}
}
//Locate a page in processes page table
//Table parameter: 0 = ram, 1 = lru, 2 = fifo
int Process::locatePageRam(int pageNum)
{
	return(ramTable.at(pageNum));
}
int Process::locatePageLru(int pageNum)
{
	return(lruTable.at(pageNum));
}
int Process::locatePageFifo(int pageNum)
{
	return(fifoTable.at(pageNum));
}

//Get size of address space
int Process::getSize()
{
	return tableSize;
}
//Get pid of process
int Process::getPid()
{
	return pid;
}
//Update the page table to reflect a page being placed in memory
void Process::updateRamTable(int pageNum, int spotInMemory)
{
	ramTable.at(pageNum) = spotInMemory;	

}
//Update the page table to reflect a page being placed in memory
void Process::updateLruTable(int pageNum, int spotInMemory)
{
	lruTable.at(pageNum) = spotInMemory;	

}
//Update the page table to reflect a page being placed in memory
void Process::updateFifoTable(int pageNum, int spotInMemory)
{
	fifoTable.at(pageNum) = spotInMemory;	

}

