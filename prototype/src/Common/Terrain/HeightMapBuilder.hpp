/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:30:55
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 04:38:31
*/

#ifndef HEIGHT_MAP_BUILDER_HPP
#define HEIGHT_MAP_BUILDER_HPP

#include <Terrain/HeightMap.hpp>

namespace amaze{
	class HeightMapBuilder{
	public:
		HeightMapBuilder();
		virtual ~HeightMapBuilder();

		virtual HeightMap * buildHeightMap(double x_size, double y_size, unsigned int x_resolution, unsigned int y_resolution) = 0;

	protected:
		void setHeightAt(HeightMap * heightMap, unsigned int x, unsigned int y, double height);

	};
}

#endif // HEIGHT_MAP_BUILDER_HPP
