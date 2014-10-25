/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 21:28:11
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 01:41:29
*/

#include <Maze/MazeBuilder.hpp>

namespace amaze{
	MazeBuilder::MazeBuilder(){
		this->m_carver = new MazeCarver();
	}

	MazeBuilder::~MazeBuilder(){
		delete this->m_carver;
	}

	void MazeBuilder::setCarver(MazeCarver * carver){
		delete this->m_carver;
		this->m_carver = carver;
	}

	void MazeBuilder::carvePath(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction){
		this->m_carver->carvePath(maze, node, direction);
	}
}