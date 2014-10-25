/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 21:40:15
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 02:17:29
*/

#ifndef DEPTH_FIRST_MAZE_BUILDER_HPP
#define DEPTH_FIRST_MAZE_BUILDER_HPP

#include <Maze/MazeBuilder.hpp>

namespace amaze{
	class DepthFirstMazeBuilder : public MazeBuilder{
	public:
		DepthFirstMazeBuilder(unsigned int start_x=0, unsigned int start_y=0);

		virtual Maze * buildMaze(unsigned int size_x, unsigned int size_y);

	private:
		unsigned int m_start_x;
		unsigned int m_start_y;

		void depthFirstCarving(Maze * m, Maze::MazeNode node, bool * visited);

		bool * m_buffer;
	};
}

#endif // DEPTH_FIRST_MAZE_BUILDER_HPP


#include <Maze/MazeBuilder.hpp>