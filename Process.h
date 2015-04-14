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

	//Locate a page
	int locatePage(int pageNum);

	//Size getter
	int getSize();

	//Update page table
	void updateTable(int pageNum, int spotInMemory);

	private:
		int tableSize;
		int pid;
		std::vector<int> pageTable;





};
#endif //PROCESS
