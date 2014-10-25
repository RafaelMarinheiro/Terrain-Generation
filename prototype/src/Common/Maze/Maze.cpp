/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 20:26:40
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 05:08:30
*/

#include <assert.h>
#include <Maze/Maze.hpp>
#include <cstdio>

namespace amaze{

	Maze::Maze(unsigned int size_x, unsigned int size_y){
		this->m_size_x = size_x;
		this->m_size_y = size_y;
		this->m_maze_nodes = new MazeNodeData[size_x*size_y];
	}

	Maze::~Maze(){
		assert(this->m_maze_nodes != NULL);
		delete[] this->m_maze_nodes;
	}

	unsigned int Maze::getSizeX(){
		return this->m_size_x;
	}
	
	unsigned int Maze::getSizeY(){
		return this->m_size_y;
	}

	Maze::MazeNodeData Maze::getDataAt(const Maze::MazeNode & node){
		unsigned int index = this->getInternalIndex(node);
		return this->m_maze_nodes[index];
	}

	bool Maze::getNeighborNode(Maze::MazeNode & node, const Maze::MazeDirection & direction){
		if(direction == UP){
			if(node.y + 1 < m_size_y){
				node.y++;
				return true;
			}
		} else if(direction == DOWN){
			if(node.y > 0){
				node.y--;
				return true;
			}
		} else if(direction == RIGHT){
			if(node.x + 1 < m_size_x){
				node.x++;
				return true;
			}
		} else{
			if(node.x > 0){
				node.x--;
				return true;
			}
		}
		return false;
	}

	unsigned int Maze::getInternalIndex(const Maze::MazeNode & node){
		assert(node.x < m_size_x && node.y < m_size_y);
		return node.x + m_size_x*node.y;
	}
}