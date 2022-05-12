
INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib

MPICC = mpicc
MPICXX = mpicxx
CXX = g++
CC =gcc

CFLAGS= -O3 $(INCLUDE_DIRS) $(CDEFS)
# all: astar astar_revised astar_revised_waypoints astar2 astar2_revised simple_pthread set_affinity_example astar_waypoints temp
all: astar_waypoints_pthread astar_waypoints_mpi  

clean:
	rm -r astar astar_revised astar2 astar2_revised simple_pthread set_affinity_example astar_revised_waypoints astar_waypoints temp

astar: astar.cpp
	$(CXX)$(LDFLAGS)  -o $@ $@.cpp -Wall

astar2: astar2.cpp
	$(CXX) $(LDFLAGS) -o $@ $@.cpp -Wall

astar2_revised: astar2_revised.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall

simple_pthread: simple_pthread.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -lpthread

astar_revised: astar_revised.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -fopenmp -lpthread

astar_revised_waypoints: astar_revised_waypoints.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -lpthread

set_affinity_example: set_affinity_example.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -lpthread

astar_waypoints_pthread: astar_waypoints_pthread.cpp
	$(CXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -lpthread

astar_waypoints_mpi: astar_waypoints_mpi.cpp
	$(MPICXX) $(LDFLAGS)  -o $@ $@.cpp -Wall -lpthread
# temp: temp.c
# 	$(CC) -o $@ $@.c -Wall -fopenmp 
