CXX = g++
FLAGS = -g -Wall -std=c++11
EXEC = lab5

all: lab5.o Process.o
	$(CXX) $(FLAGS) -o $(EXEC) lab5.o Process.o

lab5.o: lab5.cpp
	$(CXX) $(FLAGS) -c lab5.cpp

Process.o: Process.cpp
	$(CXX) $(FLAGS) -c Process.cpp

clean:
	$(RM) $(TARGET) rm *.o
