CXX = g++
FLAGS = -g -Wall -std=c++11
EXEC = program2
ONE = Program2
TWO = input_gen

all: Program2 input_gen

input_gen: input_gen.o
	$(CXX) $(FLAGS) -o input_gen input_gen.o
	
input_gen.o: input_gen.cpp
	$(CXX) $(FLAGS) -c input_gen.cpp

Program2: Program2.o Process.o
	$(CXX) $(FLAGS) -o program2 Program2.o Process.o
	
Program2.o: Program2.cpp
	$(CXX) $(FLAGS) -c Program2.cpp

Process.o: Process.cpp Process.h
	$(CXX) $(FLAGS) -c Process.cpp

clean:
	$(RM) $(TARGET) rm *.o program2 input_gen
