/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:16:40
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 05:25:23
*/

#include <Terrain/HeightMap.hpp>

#include <assert.h>

namespace amaze{
	HeightMap::HeightMap(double x_size, double y_size, unsigned int x_resolution, unsigned int y_resolution){
		_x_resolution = x_resolution;
		_y_resolution = y_resolution;
		_x_size = x_size;
		_y_size = y_size;

		_heightMap = new double[x_resolution*y_resolution];
	}
	
	HeightMap::~HeightMap(){
		delete[] _heightMap;
	}

	// double HeightMap::getHeightAt(double x, double y){
	// 	double dx = getSizeX()/getResolutionX();
	// 	double dy
	// }

	double HeightMap::getHeightAt(unsigned int x, unsigned int y){
		assert(x < _x_resolution && y < _y_resolution);
		return _heightMap[x + _x_resolution*y];
	}

	double HeightMap::getSizeX(){
		return _x_size;
	}

	double HeightMap::getSizeY(){
		return _y_size;
	}

	int HeightMap::getResolutionX(){
		return _x_resolution;
	}

	int HeightMap::getResolutionY(){
		return _y_resolution;
	}
}

