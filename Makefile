CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = main.o

bard: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ main.o 

main.o: main.cpp LinkedList.h LinkedList.cpp
		$(CXX) -g $(CXXFLAGS) -c main.cpp

clean:
	rm *.o
	rm hello
