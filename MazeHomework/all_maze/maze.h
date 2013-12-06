#ifndef MAZE_H_
#define MAZE_H_
class maze
{
	private:
		char* mazeArray;
		int startingIndex;
		int xDim;
		int yDim;
	public:
		maze();
		void init();
		bool solve(int index);
		~maze();

		friend std::ostream& operator <<(std::ostream& outs, const maze& source);
};

#endif