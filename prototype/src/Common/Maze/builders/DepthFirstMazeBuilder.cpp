/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-24 21:44:49
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 05:25:46
*/

#include <Maze/builders/DepthFirstMazeBuilder.hpp>
#include <algorithm>

namespace amaze{
	DepthFirstMazeBuilder::DepthFirstMazeBuilder(unsigned int start_x, unsigned int start_y){
		this->m_start_x = start_x;
		this->m_start_y = start_y;
	}

	Maze * DepthFirstMazeBuilder::buildMaze(unsigned int size_x, unsigned int size_y){

		Maze * maze = new Maze(size_x, size_y);

		bool * local_visited = new bool[size_x*size_y];

		{
			Maze::MazeNode startingPoint;
			startingPoint.x = m_start_x < size_x ? m_start_x : size_x-1; 
			startingPoint.y = m_start_y < size_y ? m_start_y : size_y-1;
		
		


			this->depthFirstCarving(maze, startingPoint, local_visited);
		}

		delete[] local_visited;

		return maze;

	}

	void DepthFirstMazeBuilder::depthFirstCarving(Maze * maze, Maze::MazeNode node, bool * visited){
		int index = node.x + maze->getSizeX()*node.y;

		if(visited[index]){
			return;
		}

		visited[index] = true;

		Maze::MazeDirection directions[4] = {Maze::UP, Maze::DOWN, Maze::LEFT, Maze::RIGHT};
		std::random_shuffle(directions, directions+4);

		for(int i = 0; i < 4; i++){
			Maze::MazeNode other = node;
			if(maze->getNeighborNode(other, directions[i])){
				int oindex = other.x + maze->getSizeX()*other.y;
				if(!visited[oindex]){
					this->carvePath(maze, node, directions[i]);
					this->depthFirstCarving(maze, other, visited);
				}
			}
		}
	}
}