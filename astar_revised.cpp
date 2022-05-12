// A C++ Program to implement A* Search Algorithm
#include "stdc++.h"
using namespace std;

#define ROW 3000
#define COL 3000
#define NUM_THREADS 4
#define W
// #define MULTI
#define rep(i,a,b) for (int i=a;i<b;i++)
// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;


// A structure to hold the necessary parameters
struct cell {
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

//variables -----------------------------------------------------------------------
// Declare a 2D array of structure to hold the details
// of that cell
// cell cellDetails[ROW][COL];
cell cellDetails[ROW][COL];
int grid[ROW][COL];
// Create a closed list and initialise it to false which
// means that no cell has been included yet This closed
// list is implemented as a boolean 2D array
bool closedList[ROW][COL];
bool foundDest = false;
double gNew, hNew, fNew;
bool isValid(int row, int col);
// for path structure
struct path_strut{
	int index;
	int i,j;
	Pair dest;
	Pair src;
};

// for initialize
struct arg_struct {
	int idx;
};
set<pPair> openList;

// -------------------------------------------------------------------------------------



//fucntions------------------------------------------------------------------------------

void checkNorthAndSouth(int &i, int &j, Pair &dest, Pair &src);
void checkEastAndWest(int &i, int &j, Pair &dest, Pair &src);
void checkNEandNW(int &i, int &j, Pair &dest, Pair &src);
void checkSEandSW(int &i, int &j, Pair &dest, Pair &src);
bool isUnBlocked(int grid[][COL], int row, int col);
bool isDestination(int row, int col, Pair dest);
double calculateHValue(int row, int col, Pair dest);
void checkEastAndWest();
void tracePath(cell cellDetails[][COL], Pair dest);
//---------------------------------------------------------------------------------------







//check directions--------------------
void checkNorthAndSouth(int &i, int &j, Pair &dest, Pair &src){
	//----------- 1st Successor (South) ------------
	if (isValid(i - 1, j) == true) {
	// If the destination cell is the same as the
	// current successor
	if (isDestination(i - 1, j, dest) == true) {
		// Set the Parent of the destination cell
		cellDetails[i - 1][j].parent_i = i;
		cellDetails[i - 1][j].parent_j = j;
		printf("The destination cell is found\n");
		tracePath(cellDetails, dest);
		foundDest = true;
		return;
	}
	
	// If the successor is already on the closed
	// list or if it is blocked, then ignore it.
	// Else do the following
	else if (closedList[i - 1][j] == false
			&& isUnBlocked(grid, i - 1, j)
					== true) {
						
		gNew = cellDetails[i][j].g + 1.0;
		hNew = calculateHValue(i - 1, j, dest);
		fNew = gNew + hNew;

		// If it isn’t on the open list, add it to
		// the open list. Make the current square
		// the parent of this square. Record the
		// f, g, and h costs of the square cell
		//			 OR
		// If it is on the open list already, check
		// to see if this path to that square is
		// better, using 'f' cost as the measure.
		if (cellDetails[i - 1][j].f == FLT_MAX
			|| cellDetails[i - 1][j].f > fNew) {
				
			openList.insert(make_pair(
				fNew, make_pair(i - 1, j)));

			// Update the details of this cell
			cellDetails[i - 1][j].f = fNew;
			cellDetails[i - 1][j].g = gNew;
			cellDetails[i - 1][j].h = hNew;
			cellDetails[i - 1][j].parent_i = i;
			cellDetails[i - 1][j].parent_j = j;
			
		}
	}


	//----------- 2nd Successor (South) ------------

	// Only process this cell if this is a valid one
	if (isValid(i + 1, j) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i + 1, j, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i + 1][j].parent_i = i;
			cellDetails[i + 1][j].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}
		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i + 1][j] == false
				&& isUnBlocked(grid, i + 1, j)
						== true) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i + 1, j, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i + 1][j].f == FLT_MAX
				|| cellDetails[i + 1][j].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i + 1, j)));
				// Update the details of this cell
				cellDetails[i + 1][j].f = fNew;
				cellDetails[i + 1][j].g = gNew;
				cellDetails[i + 1][j].h = hNew;
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
			}
		}
	}
  }
}

void checkEastAndWest(int &i, int &j, Pair &dest, Pair &src){
	//----------- 3rd Successor (East) ------------

	// Only process this cell if this is a valid one
	if (isValid(i, j + 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i, j + 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i][j + 1].parent_i = i;
			cellDetails[i][j + 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i][j + 1] == false
				&& isUnBlocked(grid, i, j + 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i, j + 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i][j + 1].f == FLT_MAX
				|| cellDetails[i][j + 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i, j + 1)));

				// Update the details of this cell
				cellDetails[i][j + 1].f = fNew;
				cellDetails[i][j + 1].g = gNew;
				cellDetails[i][j + 1].h = hNew;
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
			}
		}
	}

	//----------- 4th Successor (West) ------------

	// Only process this cell if this is a valid one
	if (isValid(i, j - 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i, j - 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i][j - 1].parent_i = i;
			cellDetails[i][j - 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i][j - 1] == false
				&& isUnBlocked(grid, i, j - 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i, j - 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i][j - 1].f == FLT_MAX
				|| cellDetails[i][j - 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i, j - 1)));

				// Update the details of this cell
				cellDetails[i][j - 1].f = fNew;
				cellDetails[i][j - 1].g = gNew;
				cellDetails[i][j - 1].h = hNew;
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
			}
		}
	}
}
void checkNEandNW(int &i, int &j, Pair &dest, Pair &src){
	// puts("NEandNW");


	//----------- 5th Successor (North-East)
	//------------

	// Only process this cell if this is a valid one
	if (isValid(i - 1, j + 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i - 1, j + 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i - 1][j + 1].parent_i = i;
			cellDetails[i - 1][j + 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i - 1][j + 1] == false
				&& isUnBlocked(grid, i - 1, j + 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.414;
			hNew = calculateHValue(i - 1, j + 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i - 1][j + 1].f == FLT_MAX
				|| cellDetails[i - 1][j + 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i - 1, j + 1)));

				// Update the details of this cell
				cellDetails[i - 1][j + 1].f = fNew;
				cellDetails[i - 1][j + 1].g = gNew;
				cellDetails[i - 1][j + 1].h = hNew;
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
			}
		}
	}

	//----------- 6th Successor (North-West)
	//------------

	// Only process this cell if this is a valid one
	if (isValid(i - 1, j - 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i - 1, j - 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i - 1][j - 1].parent_i = i;
			cellDetails[i - 1][j - 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i - 1][j - 1] == false
				&& isUnBlocked(grid, i - 1, j - 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.414;
			hNew = calculateHValue(i - 1, j - 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i - 1][j - 1].f == FLT_MAX
				|| cellDetails[i - 1][j - 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i - 1, j - 1)));
				// Update the details of this cell
				cellDetails[i - 1][j - 1].f = fNew;
				cellDetails[i - 1][j - 1].g = gNew;
				cellDetails[i - 1][j - 1].h = hNew;
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
			}
		}
	}
}
void checkSEandSW(int &i, int &j, Pair &dest, Pair &src){
	// puts("SEandSW");
	//----------- 7th Successor (South-East)
	//------------

	// Only process this cell if this is a valid one
	if (isValid(i + 1, j + 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i + 1, j + 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i + 1][j + 1].parent_i = i;
			cellDetails[i + 1][j + 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i + 1][j + 1] == false
				&& isUnBlocked(grid, i + 1, j + 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.414;
			hNew = calculateHValue(i + 1, j + 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i + 1][j + 1].f == FLT_MAX
				|| cellDetails[i + 1][j + 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i + 1, j + 1)));

				// Update the details of this cell
				cellDetails[i + 1][j + 1].f = fNew;
				cellDetails[i + 1][j + 1].g = gNew;
				cellDetails[i + 1][j + 1].h = hNew;
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
			}
		}
	}

	//----------- 8th Successor (South-West)
	//------------

	// Only process this cell if this is a valid one
	if (isValid(i + 1, j - 1) == true) {
		// If the destination cell is the same as the
		// current successor
		if (isDestination(i + 1, j - 1, dest) == true) {
			// Set the Parent of the destination cell
			cellDetails[i + 1][j - 1].parent_i = i;
			cellDetails[i + 1][j - 1].parent_j = j;
			printf("The destination cell is found\n");
			tracePath(cellDetails, dest);
			foundDest = true;
			return;
		}

		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (closedList[i + 1][j - 1] == false
				&& isUnBlocked(grid, i + 1, j - 1)
						== true) {
			gNew = cellDetails[i][j].g + 1.414;
			hNew = calculateHValue(i + 1, j - 1, dest);
			fNew = gNew + hNew;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//			 OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (cellDetails[i + 1][j - 1].f == FLT_MAX
				|| cellDetails[i + 1][j - 1].f > fNew) {
				openList.insert(make_pair(
					fNew, make_pair(i + 1, j - 1)));

				// Update the details of this cell
				cellDetails[i + 1][j - 1].f = fNew;
				cellDetails[i + 1][j - 1].g = gNew;
				cellDetails[i + 1][j - 1].h = hNew;
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
			}
		}
	}
}	




//--------------------------------------
void *checkDirection(void *arguments){
	path_strut _path = *((struct path_strut*)arguments);
	int idx = _path.index;
	// pPair p = _path.openList;
	// int i = _path.i;
	// int j = _path.j;
	// Pair dest = _path.dest;
	// Pair src = _path.src;
	// cout << p.second.first <<endl;
	if(idx == 0){
		checkNorthAndSouth(_path.i,_path.j, _path.dest, _path.src);
	}else if(idx == 1){
		checkEastAndWest(_path.i,_path.j, _path.dest, _path.src);
	}else if (idx== 2){
		checkNEandNW(_path.i,_path.j, _path.dest, _path.src);
	}else if(idx== 3){
		checkSEandSW(_path.i,_path.j, _path.dest, _path.src);
	}
	// free(arguments);
	// pthread_exit((void **)0);
	return 0;
}


void *_initialize(void *arguments){
  arg_struct args = *((struct arg_struct*)arguments);
  int idx = args.idx;
  int p_start = (idx*(ROW/NUM_THREADS));
  int p_end = p_start + (ROW/NUM_THREADS);
//   cell cellDetails[ROW][COL];
//   memcpy(cellDetails, ((struct arg_struct*)arguments)->cellDetails, ROW*COL*sizeof(int));

  int i,j;
  for (i = p_start; i < p_end; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}
	// puts("end");
	// cout << p_start << " " << p_end <<endl;
	
	// pthread_exit((void **)0);
	// free(arguments);
	return 0;
}


// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) && (col >= 0)
		&& (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
	// puts("here");
	// cout << "row: " << row << " col: " << col << " value: " << grid[row][col]<<endl;
	
	// Returns true if the cell is not blocked else false
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
	// Return using the distance formula
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COL], Pair dest)
{
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
	}

	return;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	// If the source is out of range
	if (isValid(src.first, src.second) == false) {
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid(dest.first, dest.second) == false) {
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false
		|| isUnBlocked(grid, dest.first, dest.second)
			== false) {
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest)
		== true) {
		printf("We are already at the destination\n");
		return;
	}


// 

int i,j;
#ifdef MULTI
	int numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Number of processors: %d\n", numberOfProcessors);
	pthread_t threads[numberOfProcessors];    
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	int rc;
   cpu_set_t cpus;
   arg_struct args[NUM_THREADS];
   for (i = 0; i < numberOfProcessors; i++) {
       CPU_ZERO(&cpus);
       CPU_SET(i, &cpus);
       pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpus);
    //    pthread_create(&threads[i], &attr, DoWork, NULL);


	    args[i].idx =i;

	//  memcpy(args->cellDetails, cellDetails, ROW*COL*sizeof(int));
		rc = pthread_create(&threads[i], &attr, _initialize, (void *)&args[i]);
		// puts("pthread finished\n");
		if(rc){
			std::cout << "Error: unable to create thread, " << rc <<std::endl;
			exit(-1);
		}
    }

// 	for (int i = 0; i < numberOfProcessors; i++) {
//         pthread_join(threads[i], NULL);
//     }
//    for(i=0; i<NUM_THREADS; i++){
//     //  struct arg_struct *args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
//      std::cout << "cretae a thread no." << i << std::endl;
//      args[i].idx =i;
// 	//  memcpy(args->cellDetails, cellDetails, ROW*COL*sizeof(int));
//      rc = pthread_create(&threads[i], NULL, _initialize, (void *)&args[i]);
// 	puts("pthread finished\n");
//      if(rc){
//        std::cout << "Error: unable to create thread, " << rc <<std::endl;
//        exit(-1);
//      }
//    }
//    for(int i=0; i<NUM_THREADS;i++)
//          pthread_join(threads[i], NULL);
// 	puts("pthread finsied");
#else
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}
#endif




	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;
	memset(closedList, false, sizeof(closedList));
	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of pair of
	pair.*/
	

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	

	while (!openList.empty()) {
		pPair p = *openList.begin();


		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		/*
		Generating all the 8 successor of this cell

			N.W N N.E
			\ | /
				\ | /
			W----Cell----E
				/ | \
				/ | \
			S.W S S.E

		Cell-->Popped Cell (i, j)
		N --> North	 (i-1, j)
		S --> South	 (i+1, j)
		E --> East	 (i, j+1)
		W --> West		 (i, j-1)
		N.E--> North-East (i-1, j+1)
		N.W--> North-West (i-1, j-1)
		S.E--> South-East (i+1, j+1)
		S.W--> South-West (i+1, j-1)*/

		// To store the 'g', 'h' and 'f' of the 8 successors
		
		//multiple threads idea's here
		//divie up each direction to threads so that they can check their task simulteniously
		//ex N,S = thread 1, S,E thread 2, N.E,N.W = thread 3, S.E,S.W = thread 4
		#ifdef MULTI
			path_strut _path[NUM_THREADS];
			int n;
			for(n=0; n<NUM_THREADS; n++){
				_path[n].index =n;
				// _path[n].openList = p;
				_path[n].i = i;
				_path[n].j = j;
				_path[n].dest = dest;
				_path[n].src = src;
				// _path[n].grid = grid;
				// memcpy(_path[n].grid, grid, ROW*COL*sizeof(int));
				// cout << "_path[n].grid[1][5] " <<_path[n].grid[1][5] <<endl;
				rc = pthread_create(&threads[n], NULL, checkDirection, (void *)&_path[n]);
				if(rc){
					std::cout << "Error: unable to create thread, " << rc <<std::endl;
					exit(-1);
				}
				
			}
			for(n=0; n<NUM_THREADS;n++)
					pthread_join(threads[n], NULL);
			
		#else
		checkNorthAndSouth(i, j,dest, src);
		checkEastAndWest(i, j,dest, src);
		checkNEandNW(i, j, dest, src);
		checkSEandSW(i, j, dest, src);
		#endif
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}

// Driver program to test above function
int main()
{
	/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked */
	struct timespec start, stop;
	double fstart, fstop;

	// 	//default ----------
	// int grid[ROW][COL]
	// 	= { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
	// 		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
	// 		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
	// 		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
	// 		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
	// 		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
	// 		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	// 		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
	// 		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

	// // Source is the left-most bottom-most corner
	// Pair src = make_pair(8, 0);

	// // Destination is the left-most top-most corner
	// Pair dest = make_pair(0, 0);
	// //------------

	// int grid[ROW][COL]; // make an array = map
	grid[0][0] = 1; //start point
	grid[ROW-1][COL-1]=1; //end point
	int r = ROW;
	int c = COL;
	string map_name = "./maps/map" + to_string(r) + "x" +to_string(c) + ".txt";

#ifdef W


	//random number generater
	/* generate secret number between 1 and 10: */
	srand (time(NULL));
	
	rep(i,0,ROW)
		rep(j,0,COL) {
			int  rtemp= rand() % 100 + 1;
			if((i==0 && j==0) || (i==ROW-1 && j==COL-1)){
				continue;
			}else{
				if(rtemp%2==0) grid[i][j] = 1;
				else grid[i][j] =0;	
			}
		}
	ofstream wfile;
	wfile.open (map_name);
	rep(i,0,ROW){
		rep(j,0,COL){
			wfile << grid[i][j] << " ";
		} 
		wfile << "\n";
	}
	wfile.close();
#else
	ifstream ifile;
	ifile.open(map_name);
	int tempint=0;
	int x = 0, y =0;
	while(ifile >> tempint){
		// printf("%d\n", tempint);
		grid[x][y] = tempint;
		y++;
		if(y==COL){
			y=0;
			x++;
		} 
	}
	ifile.close();
#endif	
	// rep(i,0,ROW){
	// 	rep(j,0,COL) printf("%d", grid[i][j]);
	// 	printf("\n");
	// }	
		
	// Source is the left-most bottom-most corner
	Pair src = make_pair(0, 0);

	// Destination is the right-most bottom-most corner
	Pair dest = make_pair(ROW-1, COL-1);

	clock_gettime(CLOCK_MONOTONIC, &start); fstart=(double)start.tv_sec + ((double)start.tv_nsec/1000000000.0);

	aStarSearch(grid, src, dest);
	clock_gettime(CLOCK_MONOTONIC, &stop); fstop=(double)stop.tv_sec + ((double)stop.tv_nsec/1000000000.0);
    printf("\nThe toatal time is %f\n", (fstop-fstart));
	return 0;
}

