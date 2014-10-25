/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 20:54:35
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 01:32:46
*/

#include <Maze/MazeCarver.hpp>

namespace amaze{
	MazeCarver::MazeCarver(){

	}

	MazeCarver::~MazeCarver(){

	}

	void MazeCarver::carvePath(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction){
		unsigned int index = maze->getInternalIndex(node);

		if(direction == Maze::UP){
			maze->m_maze_nodes[index].up = true;
		} else if(direction == Maze::DOWN){
			maze->m_maze_nodes[index].down = true;
		} else if(direction == Maze::LEFT){
			maze->m_maze_nodes[index].left = true;
		} else if(direction == Maze::RIGHT){
			maze->m_maze_nodes[index].right = true;
		}

		bool border = true;

		Maze::MazeNode other = node;
		if(maze->getNeighborNode(other, direction)){
			border = false;
			index = maze->getInternalIndex(other);
			if(direction == Maze::UP){
				maze->m_maze_nodes[index].down = true;
			} else if(direction == Maze::DOWN){
				maze->m_maze_nodes[index].up = true;
			} else if(direction == Maze::LEFT){
				maze->m_maze_nodes[index].right = true;
			} else if(direction == Maze::RIGHT){
				maze->m_maze_nodes[index].left = true;
			}
		}

		this->pathWasCarved(maze, node, direction, border);
	}
}