/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 21:28:00
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-06 20:21:05
*/

#ifndef MAZE_BUILDER_HPP
#define MAZE_BUILDER_HPP

#include <Maze/Maze.hpp>
#include <Maze/MazeCarver.hpp>

namespace amaze{

	class MazeBuilder{
	public:
		MazeBuilder();
		virtual ~MazeBuilder();

		virtual Maze * buildMaze(unsigned int size_x, unsigned int size_y) = 0;

		void setCarver(MazeCarver * carver);
	protected:
		void carvePath(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction);

	private:
		MazeCarver * m_carver;
	};

}

#endif // MAZE_BUILDER_HPP