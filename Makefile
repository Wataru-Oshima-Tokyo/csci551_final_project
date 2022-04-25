

CXX = g++



all: astar astar_revised astar2 astar2_revised simple_pthread set_affinity_example

clean:
	rm -r astar astar_revised astar2 astar2_revised simple_pthread set_affinity_example

astar: astar.cpp
	$(CXX) -o $@ $@.cpp -Wall

astar2: astar2.cpp
	$(CXX) -o $@ $@.cpp -Wall

astar2_revised: astar2_revised.cpp
	$(CXX) -o $@ $@.cpp -Wall

simple_pthread: simple_pthread.cpp
	$(CXX) -o $@ $@.cpp -Wall -lpthread

astar_revised: astar_revised.cpp
	$(CXX) -o $@ $@.cpp -Wall -fopenmp -lpthread
set_affinity_example: set_affinity_example.cpp
	$(CXX) -o $@ $@.cpp -Wall -lpthread
