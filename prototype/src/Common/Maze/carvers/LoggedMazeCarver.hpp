/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-25 01:03:58
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 01:28:01
*/

#ifndef LOGGED_MAZE_CARVER_HPP
#define LOGGED_MAZE_CARVER_HPP

#include <Maze/MazeCarver.hpp>

namespace amaze{

	class LoggedMazeCarver : public MazeCarver{
		virtual void pathWasCarved(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction, bool border);
	};
}

#endif // LOGGED_MAZE_CARVER_HPP
