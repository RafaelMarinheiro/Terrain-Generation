/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-18 22:58:16
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 05:41:55
*/
#include "MazeViewer.hpp"
#include <qapplication.h>
#include <cstdio>

#include <Maze/builders/all.hpp>
#include <Maze/carvers/all.hpp>

int main(int argc, char** argv)
{
	
	amaze::MazeBuilder * builder = new amaze::DepthFirstMazeBuilder();
	builder->setCarver(new amaze::LoggedMazeCarver());

	amaze::Maze * maze = builder->buildMaze(64, 64);

	// Read command lines arguments.
	QApplication application(argc,argv);
		
	// Instantiate the viewer.
	amaze::MazeViewer viewer(maze);

	// Make the viewer window visible on screen.
	viewer.show();

	// Run main loop.
	return application.exec();
}