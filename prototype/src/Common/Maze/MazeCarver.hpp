/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 20:36:00
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 01:14:49
*/

#ifndef MAZE_CARVER_HPP
#define MAZE_CARVER_HPP

#include <Maze/Maze.hpp>

namespace amaze{

	class MazeBuilder;

	class MazeCarver{
		friend class MazeBuilder;

	public:
		MazeCarver();
		virtual ~MazeCarver();

	protected:
		//We can overwrite this to log the construction of the maze
		virtual void pathWasCarved(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction, bool border){
			//Default does nothing
		}
	private:
		void carvePath(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction);
	};

}

#endif // MAZE_CARVER_HPP
