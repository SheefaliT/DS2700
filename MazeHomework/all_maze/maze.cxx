#include <iostream>  
#include <cstdlib> 
#include <fstream>
#include "maze.h" 

using namespace std; 

maze::maze(void) {
	ifstream myIns; //Creates an ifStream myIns and opens “maze.txt”
	// int xDim, yDim;

	myIns.open("maze.txt");

	if (myIns.fail()) { //If maze.txt doesn’t open (check with myIns.is_open()) the program stops.
		cerr << "Error while opening maze.txt" << endl;
		exit (1);
	}

	// file can be opened

	myIns >> xDim >> yDim; // Reads in the x Dimension and y Dimension into xDim, yDim variables respectively

	cout << " xDim = " << xDim << " and yDim = " << yDim << endl;

	mazeArray = new char [xDim*yDim]; // allocates a char array and points mazeArray pointer to it
		for (int i=0; i < xDim*yDim; i++) {
			if((i % yDim) + 1 <yDim)
			{
				myIns >> mazeArray[i];
			}
			
		}

	myIns.close();
}

maze::~maze()
{
	delete [] mazeArray;
}

void maze::init() {
	for (int i=0; i < xDim*yDim; i++) {
		if (mazeArray[i] == '*') {
			startingIndex = i;
			break;
		}

	}

}

bool maze::solve(int index) {
	int i = index;
	mazeArray [i] = 'v' ; //mark current spot as visited

	if((i+yDim) <= (xDim*yDim)-1) //down
	{
		char down = mazeArray[i + yDim];
	
		if (down == '$')
		{
			mazeArray[i] = '*';
			solve(i + yDim);
			return (true);
		}
		
		if (down == '-')
		{
			mazeArray[i] = '*';
			solve(i + yDim);
			return (true);
		}
		return (false);		
	}

	if((i-yDim > 0)) //up
	{
		char up = mazeArray[i - yDim];
		
		if(up == '$')
		{
			mazeArray[i] = '*';
			solve(i - yDim);
			return (true);
		}	

		if (up == '-')
		{
			mazeArray[i] = '*';
			solve(i - yDim);
			return(true);
		}
		return (false);
	}
	
	if((i + yDim > 0)) // right
	{
		char right = mazeArray[i + 1];

		if (right == '$')
		{
			mazeArray[i] = '*';
			solve(i + 1);
			return (true);
		}

		if (right == '-')
		{
			mazeArray[i] = '*';
			solve(i+1);
			return (true);
		}
		return (false);
	}

	if ((i - yDim > 0)) // left
	{
		char left = mazeArray[i - 1];
		if (left == '$')
		{
			mazeArray[i] = '*';
			solve(i - 1);
			return (true);
		}

		if (left == '-')
		{
			mazeArray[i] = '*';
			solve(i - 1);
			return (true);
		}
		return (false);
	} 
		
// need to check my returns


	mazeArray[i] = '-';
	return (false);
}

ostream& operator <<(ostream& outs, const maze& source) {
	for (int i=0; i < source.xDim*source.yDim; i++) {
			if(i!=0 && ((i % source.yDim) + 1 <source.yDim))
			{
				outs << "/n";
			}
			
			outs << source.mazeArray[i];
		}
	return outs;
}

