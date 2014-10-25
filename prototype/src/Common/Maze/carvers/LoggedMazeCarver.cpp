/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-25 01:05:35
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 02:27:08
*/

#include <Maze/carvers/LoggedMazeCarver.hpp>

#include <cstdio>

namespace amaze{
	void LoggedMazeCarver::pathWasCarved(Maze * maze, const Maze::MazeNode & node, Maze::MazeDirection direction, bool border){
		if(direction == Maze::UP){
			printf("Carved path from (%d, %d, up, %d)\n", node.x, node.y, border);
		} else if(direction == Maze::DOWN){
			printf("Carved path from (%d, %d, down, %d)\n", node.x, node.y, border);
		} else if(direction == Maze::LEFT){
			printf("Carved path from (%d, %d, left, %d)\n", node.x, node.y, border);
		} else if(direction == Maze::RIGHT){
			printf("Carved path from (%d, %d, right, %d)\n", node.x, node.y, border);
		}
	}
}