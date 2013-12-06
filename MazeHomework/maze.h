//Created by Sheefali Tewari
//Help from Shannon Moore
#ifndef MAZE_H_
#define MAZE_H_
#include <iostream>
class maze
{
	private:
		char* mazeArray;
		int startingIndex;
		int xDim;
		int yDim;
	public:
		maze();
		~maze();
		void init();
		bool solve(int index);

		friend std::ostream& operator <<(std::ostream& outs, const maze& source);
};

#endif