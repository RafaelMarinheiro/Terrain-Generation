/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:38:16
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 05:27:35
*/

#include <Terrain/HeightMapBuilder.hpp>
#include <assert.h>

namespace amaze{
	HeightMapBuilder::HeightMapBuilder(){

	}

	HeightMapBuilder::~HeightMapBuilder(){

	}

	void HeightMapBuilder::setHeightAt(HeightMap * heightMap, unsigned int x, unsigned int y, float height){
		assert(x < heightMap->getResolutionX() && y < heightMap->getResolutionY());
		heightMap->_heightMap[x + heightMap->getResolutionX()*y] = height;
	}
}
