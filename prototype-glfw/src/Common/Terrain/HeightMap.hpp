/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:16:28
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 05:24:42
*/

#ifndef HEIGHT_MAP_HPP
#define HEIGHT_MAP_HPP

namespace amaze{

	class HeightMap{
		friend class HeightMapBuilder;
	public:
		HeightMap(float x_size, float y_size, unsigned int x_resolution, unsigned int y_resolution);
		~HeightMap();

		// float getHeightAt(float x, float y);
		float getHeightAt(unsigned int x, unsigned int y);
		float * getHeightData(){ return _heightMap; }
		float getSizeX();
		float getSizeY();

		int getResolutionX();
		int getResolutionY();
	private:
		unsigned int _x_resolution, _y_resolution;
		float	_x_size, _y_size;
		float * _heightMap;
	};

}

#endif // HEIGHT_MAP_HPP
