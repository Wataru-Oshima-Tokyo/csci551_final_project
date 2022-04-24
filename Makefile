

CXX = g++



all: astar astar_revised astar2 astar2_revised

clean:
	rm -r astar astar_revised astar2 astar2_revised

astar: astar.cpp
	$(CXX) -o $@ $@.cpp -Wall

astar2: astar2.cpp
	$(CXX) -o $@ $@.cpp -Wall

astar2_revised: astar2_revised.cpp
	$(CXX) -o $@ $@.cpp -Wall


astar_revised: astar_revised.cpp
	$(CXX) -o $@ $@.cpp -Wall -openmp
