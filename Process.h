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
	Process(int size);






	private:
		int tableSize;
		std::vector<int> pageTable;





};
#endif //PROCESS
