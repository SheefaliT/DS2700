//Created by Sheefali Tewari
//Help from Shannon Moore
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

    myIns >> yDim >> xDim; // Reads in the x Dimension and y Dimension into xDim, yDim variables respectively

    cout << " xDim = " << xDim << " and yDim = " << yDim << endl;

        mazeArray = new char [xDim*yDim]; // allocates a char array and points mazeArray pointer to it
            for (int i=0; i < xDim*yDim; i++) {
                // if((i % yDim) + 1 <yDim)
                // {
                myIns >> mazeArray[i];
                //}
            
        }

    myIns.close();
}

maze::~maze()
{
    delete [] mazeArray;
}

void maze::init() {
    bool solved;

    for (int i=0; i < xDim*yDim; i++) 
    {
        if (mazeArray[i] == '*') 
        {
            startingIndex = i;
            break;
        }

    }

    solved = solve(startingIndex);

}

bool maze::solve(int index) {
    int i = index;
    mazeArray [i] = 'v' ; //mark current spot as visited

    if ((i < ((xDim*yDim) - xDim))) //down
    //if((i+yDim) <= (xDim*yDim)-xDim) //down
    {
        if(mazeArray[i+xDim] == '$')
        {
            mazeArray[i] = '*';
            return true;
        }
    
    }
    if ((i < ((xDim*yDim) - xDim))) // down
    {
        if (mazeArray[i + xDim] == '-')
        {
            if(solve(i + xDim))
            {
                mazeArray[i] = '*';
                return true;
            }
        }
    } 


    if((i >= xDim)) //up
    {
        if (mazeArray[i - xDim] == '$')
        {
            mazeArray[i] = '*';
            return true;
        }   
    }
    if((i >= xDim)) //up
    {
        if(mazeArray[i - xDim] == '-')
        {
            if(solve(i - xDim))
            {
                mazeArray[i] = '*';
                return true;
            }
        }
    }
    
    if(!(i % xDim == (xDim - 1))) //right
    {
        if (mazeArray[i + 1] == '$')
        {
            mazeArray[i] = '*';
            return true;
        }
    }
    if (!(i % xDim == (xDim - 1))) //right 
    {
        if(mazeArray[i + 1] == '-')
        {
            if (solve(i + 1))
            {
                mazeArray[i] = '*';
                return true;
            }
        }
    }
    
    if (!(i % xDim == 0))// left
    {
        if (mazeArray[i + 1] == '$')
        {
            mazeArray[i] = '*';
            return true;
        } 
    } 
    if (!(i % xDim == 0))// left
    {
        if(mazeArray[i - 1] == '-')
        {
            if(solve(i - 1))
            {
                mazeArray[i] = '*';
                return true;
            }
        }
    }

    mazeArray[i] = '-';
    return false;
}

ostream& operator <<(ostream& outs, const maze& source) {
    for (int i=0; i < source.xDim*source.yDim; i++) {
            if((i!=0) && (i % source.xDim == 0)) //((i % source.yDim) + 1 < source.yDim))
            {
                outs << "\n";
            }
            
            outs << source.mazeArray[i];
        }
    return outs;
}

