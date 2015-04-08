#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <array>

#include "Process.h"
using namespace std;

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

	return 0;
}
