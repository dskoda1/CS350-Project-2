#ifndef PROCESS
#define PROCESS

#include <vector>
#include <iterator>

class Process{

	public:

	//Default constructor
	Process();

	//Destructor
	~Process();

	//Constructor
	Process(int id, int size);

	//Locate a page in ram
	int locatePageRam(int pageNum);
	//Locate a page in lru
	int locatePageLru(int pageNum);
	//Locate a page in fifo
	int locatePageFifo(int pageNum);

	//Size getter
	int getSize();

	//Pid getter
	int getPid();

	//Update Ram page table
	void updateRamTable(int pageNum, int spotInMemory);
	
	//Update LRU page table
	void updateLruTable(int pageNum, int spotInMemory);
	
	//Update Fifo page table
	void updateFifoTable(int pageNum, int spotInMemory);

	private:
		int tableSize;
		int pid;
		std::vector<int> ramTable;
		std::vector<int> lruTable;
		std::vector<int> fifoTable;





};
#endif //PROCESS
