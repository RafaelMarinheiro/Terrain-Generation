/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 20:03:00
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-06 20:28:28
*/

#ifndef MAZE_HPP
#define MAZE_HPP

namespace amaze{

	class MazeCarver;

	class Maze{
		
		friend class MazeCarver;
	
	public:

		enum MazeDirection{
			UP,
			RIGHT,
			DOWN,
			LEFT
		};

		struct MazeNode{
			unsigned short int x;
			unsigned short int y;
		};

		struct MazeNodeData{
			bool up:2;
			bool down:2;
			bool left:2;
			bool right:2;
		};
	
	public:

		Maze(unsigned int size_x, unsigned int size_y);
		~Maze();

		MazeNodeData getDataAt(const MazeNode & node);

		unsigned int getSizeX();
		unsigned int getSizeY();
		bool getNeighborNode(Maze::MazeNode & node, const Maze::MazeDirection & direction);
		bool moveNode(Maze::MazeNode & node, const Maze::MazeDirection & direction);
	private:
		unsigned int m_size_x;
		unsigned int m_size_y;

		unsigned int getInternalIndex(const MazeNode & node);

		MazeNodeData * m_maze_nodes;
	};
}


#endif // MAZE_HPP