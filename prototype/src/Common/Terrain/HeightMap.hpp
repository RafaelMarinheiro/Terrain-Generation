/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:16:28
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 04:29:18
*/

#ifndef HEIGHT_MAP_HPP
#define HEIGHT_MAP_HPP

namespace amaze{

	class HeightMap{
		friend class HeightMapBuilder;
	public:
		HeightMap(double x_size, double y_size, unsigned int x_resolution, unsigned int y_resolution);
		~HeightMap();

		// double getHeightAt(double x, double y);
		double getHeightAt(unsigned int x, unsigned int y);

		double getSizeX();
		double getSizeY();

		int getResolutionX();
		int getResolutionY();
	private:
		unsigned int _x_resolution, _y_resolution;
		double	_x_size, _y_size;
		double * _heightMap;
	};

}

#endif // HEIGHT_MAP_HPP
