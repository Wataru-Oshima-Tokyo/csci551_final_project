

CXX = g++



all: astar

clean:
	rm -r astar

astar: astar.cpp
	$(CXX) -o $@ $@.cpp -Wall
