CXX = g++-4.9
FLAGS = -g -Wall -std=c++11
EXEC = lab5
TARGET = lab5

all: $(TARGET).o
	$(CXX) $(FLAGS) -o $(EXEC) $(TARGET).o

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(FLAGS) -c $(TARGET).cpp

clean:
	$(RM) $(TARGET) rm *.o
