#include "Process.h"
using namespace std;


//Constructor
Process::Process(int size)
{
	tableSize = size;
	pageTable.resize(tableSize);
}



