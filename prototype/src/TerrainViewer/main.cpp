/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 05:18:02
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 06:37:49
*/

#include "TerrainViewer.hpp"
#include <qapplication.h>
#include <cstdio>

#include <Terrain/builders/all.hpp>

int main(int argc, char** argv)
{
	
	amaze::HeightMapBuilder * builder = new amaze::DiamondSquareHeightMapBuilder(0.2);
	
	amaze::HeightMap * heightMap = builder->buildHeightMap(1000.0, 1000.0, 513, 513);

	// Read command lines arguments.
	QApplication application(argc,argv);
		
	// Instantiate the viewer.
	TerrainViewer viewer(heightMap);

	// Make the viewer window visible on screen.
	viewer.show();

	// Run main loop.
	return application.exec();
}