#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
   ifstream myIns;
   int xDim, yDim;

   myIns.open("maze.txt");
 
   if (! myIns.is_open()) {
      cerr << "Error while opening maze.txt" << endl;
      return 1;
   }

   // at this point, we know that we could open the file...

   myIns >> xDim >> yDim;

   cout << "xDim = " << xDim << " and yDim = " << yDim << endl;

   myIns.close();

   return 0;
}
