/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:16:40
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 03:38:38
*/

#include <Terrain/HeightMap.hpp>

#include <assert.h>

namespace amaze{
	HeightMap::HeightMap(float x_size, float y_size, unsigned int x_resolution, unsigned int y_resolution){
		_x_resolution = x_resolution;
		_y_resolution = y_resolution;
		_x_size = x_size;
		_y_size = y_size;

		_heightMap = new float[x_resolution*y_resolution];
	}
	
	HeightMap::~HeightMap(){
		delete[] _heightMap;
	}

	// float HeightMap::getHeightAt(float x, float y){
	// 	float dx = getSizeX()/getResolutionX();
	// 	float dy
	// }

	float HeightMap::getHeightAt(unsigned int x, unsigned int y){
		assert(x < _x_resolution && y < _y_resolution);
		return _heightMap[x + _x_resolution*y];
	}

	float HeightMap::getSizeX(){
		return _x_size;
	}

	float HeightMap::getSizeY(){
		return _y_size;
	}

	int HeightMap::getResolutionX(){
		return _x_resolution;
	}

	int HeightMap::getResolutionY(){
		return _y_resolution;
	}
}

