/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:37:24
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 03:39:03
*/

#ifndef DIAMOND_SQUARE_HEIGHT_MAP_BUILDER_HPP
#define DIAMOND_SQUARE_HEIGHT_MAP_BUILDER_HPP

#include <Terrain/HeightMapBuilder.hpp>

namespace amaze{
	class DiamondSquareHeightMapBuilder : public HeightMapBuilder{
	public:
		DiamondSquareHeightMapBuilder(float noise=1.0);

		virtual HeightMap * buildHeightMap(float x_size, float y_size, unsigned int x_resolution, unsigned int y_resolution);
	
		void setNoise(float noise);

	private:
		float _noise;
	};
}

#endif // DIAMOND_SQUARE_HEIGHT_MAP_BUILDER_HPP