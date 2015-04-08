CXX=g++
FLAGS= -g -Wall -std=c++11
EXEC = lab5
TARGET = lab5

all: $(TARGET).o
	$(CXX) $(FLAGS) -o $(EXEC) $(TARGET).o

$(TARGET): $(TARGET)
	$(CXX) $(FLAGS) -c $(TARGET).cpp

clean:
	$(RM) $(TARGET) rm *.o
