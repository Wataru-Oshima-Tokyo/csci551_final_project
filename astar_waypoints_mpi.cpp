#include <iostream>
#include <mpi.h>
#include "stdc++.h"
using namespace std;

#define ROW 1000
#define COL 1000
// #define WAYPOINTS // if you uncomment this, the programm only finds the start and goal points
// #define PARALLEL // if you uncomment this, the programm runs seaquentially


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
//variables-----------------------------------
int _grid[ROW][COL];
struct timespec start, stop;
double fstart, fstop;
int waypoints[6][2];
const int waypoints_size = sizeof(waypoints)/sizeof(waypoints[0]);
int r = ROW;
int c = COL;
const string map_name = "./maps/map" + to_string(r) + "x" +to_string(c) + ".txt";
bool closedList[ROW][COL];
cell cellDetails[ROW][COL];
vector<int> gloablPath[waypoints_size][2];
vector<int> Path[2];
//---------------------------------------------
	
//prototypes------------------------------------------------------------------------------
bool isValid(int row, int col);
bool isUnBlocked(int grid[][COL], int row, int col);
bool isDestination(int row, int col, Pair dest);
double calculateHValue(int row, int col, Pair dest);
void tracePath(cell cellDetails[][COL], Pair dest, int index);
void printFoundsMsg(int index);
void aStarSearch(int grid[][COL], Pair src, Pair dest, int index, bool closedList[][COL], cell cellDetails[][COL]);
//---------------------------------------------------------------------------------------



//------------------------------




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
void tracePath(cell cellDetails[][COL], Pair dest, int index)
{
	
	int row = dest.first;
	int col = dest.second;

	// stack<Pair> Path;
	
	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col)) {
		Path[0].insert(Path[0].begin(), row);
		Path[1].insert(Path[1].begin(), col);
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	// gloablPath[index].insert(gloablPath[index].begin(), make_pair(row, col));
	Path[0].insert(Path[0].begin(), row);
	Path[1].insert(Path[1].begin(), col);
	// printf("the size of path is :%d\n ", (int)Path[0].size());
	// gloablPath[index].push_back(Path);
	// while (!Path.empty()) {
	// 	pair<int, int> p = Path.top();
	// 	Path.pop();
	// 	printf("-> {%d,%d} ", p.first, p.second);
	// }
	// printf("\n\n\n");

	return;
}

void printFoundsMsg(int index){
	string foundmsg = "\nThe " + to_string(index) + " th path is found.";
	cout << foundmsg;
}
// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest, int index, bool closedList[][COL], cell cellDetails[][COL])
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

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array

	// memset(closedList, false, sizeof(closedList));



	int i, j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of pair of
	pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

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
		double gNew, hNew, fNew;

		//----------- 1st Successor (North) ------------

		// Only process this cell if this is a valid one
		if (isValid(i - 1, j) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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

		//----------- 3rd Successor (East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j + 1) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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
				// printf("The destination cell is found\n");
				printFoundsMsg(index);
				tracePath(cellDetails, dest, index);
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

				// If it isn???t on the open list, add it to
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

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}

int main(void)
{
  int comm_sz, my_rank;
  MPI_Status status;
  double start, end;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  if(my_rank==0){
    
    ifstream ifile;
	ifile.open(map_name);
	int tempint=0;
	int x = 0, y =0;
	while(ifile >> tempint){
		// printf("%d\n", tempint);
		_grid[x][y] = tempint;
		y++;
		if(y==COL){
			y=0;
			x++;
		} 
	}
	ifile.close();
	// clock_gettime(CLOCK_MONOTONIC, &start); fstart=(double)start.tv_sec + ((double)start.tv_nsec/1000000000.0);
	//{row, col}
	start = MPI_Wtime();
	if(ROW==100){
		// //for 100x100-----
		int _waypoints[6][2] = 
		{{0,0},
		{16,13},
		{48,8},
		{82,17},
		{92,58},
		{ROW-1,COL-1}
		};
		// //-------------------
		memcpy(&waypoints, _waypoints, sizeof(_waypoints));
	}
	else if(ROW==200){
		// for 200x200
		int _waypoints[6][2] = 
			{ {0,0},
			{64,89},
			{114,130},
			{136,143},
			{158,159},
			{ROW-1,COL-1}
		};
		memcpy(&waypoints, _waypoints, sizeof(_waypoints));
	}
	else if(ROW==300){
		// for 300x300
		int _waypoints[6][2] = 
		{{0,0},
		  {42,36},
		  {111,107},
		  {171,192},
		  {233,247},
		 {ROW-1,COL-1}
		};
		memcpy(&waypoints, _waypoints, sizeof(_waypoints));
	}else if(ROW==501){
		// for 501x400
		int _waypoints[6][2] = 
		{ {0,0},
		  {85,44},
		  {191,121},
		  {363,246},
		  {403,296},
		  {ROW-1,COL-1}
		};
		memcpy(&waypoints, _waypoints,sizeof(_waypoints));
	}else if(ROW==1000){
		//for 1000x1000
		int _waypoints[6][2] =
		{
		 {0,0},
		//  {195,191},
		 {352,304},
		 {448,437},
		//  {505,492},
		 {615,588},
		//  {719,702},
		 {824,810},
		//  {951,950},
		 {ROW-1,COL-1}
		};
		memcpy(&waypoints, _waypoints, sizeof(_waypoints));
	}
	// int len = sizeof(_grid);

  }
  

  int total_size = sizeof(waypoints)/sizeof(waypoints[0][0]);
	MPI_Bcast(&_grid, ROW*COL, MPI_INT, 0, MPI_COMM_WORLD );
	MPI_Bcast(&waypoints, total_size, MPI_INT,0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
  if(my_rank != 0 && my_rank < waypoints_size) 
  {
	  int idx = my_rank-1;

		Pair src = make_pair(waypoints[idx][0], waypoints[idx][1]);
		Pair dest = make_pair(waypoints[idx+1][0], waypoints[idx+1][1]);
		aStarSearch(_grid, src, dest, idx, closedList,cellDetails);		
		int path_size = (int)Path[0].size();
		MPI_Send(&path_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		for(int i=0;i<path_size;i++){
			MPI_Send(&Path[0][i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Send(&Path[1][i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
  } 

  MPI_Barrier(MPI_COMM_WORLD);
  int number;
  if(my_rank==0){
    for(int q=1; q < waypoints_size; q++) 
    {  
		 
		MPI_Recv(&number, 1, MPI_INT, q, 0, MPI_COMM_WORLD,&status);
		for(int i=0;i<number;i++){
			int row; int col;
			MPI_Recv(&row, 1, MPI_INT, q, 0, MPI_COMM_WORLD,&status);
			MPI_Recv(&col, 1, MPI_INT, q, 0, MPI_COMM_WORLD,&status);
			gloablPath[q-1][0].push_back(row);
			gloablPath[q-1][1].push_back(col);
		}
		// printf("Process %d received number %d from process 0\n", q, number);
    }
		end = MPI_Wtime();
		for(int i=0;i<waypoints_size-1;i++ ){
			printf("The %d th is ",i+1);
			for(int j=0;j<(int)gloablPath[i][0].size();j++){
				if(j!=(int)gloablPath[i][0].size()-1)
					printf("{%d,%d} -> ",gloablPath[i][0][j],gloablPath[i][1][j]);
				else
					printf("{%d,%d}", gloablPath[i][0][j],gloablPath[i][1][j]);
			}
		printf("\n\n");
		}
	std::cout << "The process took " << end - start << " seconds to run." << std::endl;
  }

  MPI_Finalize();

  return 0;
}