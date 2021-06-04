CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = nqueens.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ nqueens.o

nqueens.o: nqueens.cpp
	$(CXX) -g $(CXXFLAGS) -c nqueens.cpp

clean:
	rm *.o
	rm nqueens
