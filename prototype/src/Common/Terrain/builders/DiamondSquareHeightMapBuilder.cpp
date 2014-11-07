/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:37:39
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 06:36:20
*/

#include <Terrain/builders/DiamondSquareHeightMapBuilder.hpp>

#include <algorithm>
#include <random>

// #include <cstdio>

namespace amaze{
	DiamondSquareHeightMapBuilder::DiamondSquareHeightMapBuilder(double noise){
		_noise = noise;
	}

	HeightMap * DiamondSquareHeightMapBuilder::buildHeightMap(double x_size, double y_size,
																	  unsigned int x_resolution, unsigned int y_resolution){

		HeightMap * heightMap = new HeightMap(x_size, y_size, x_resolution, y_resolution);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(-_noise, _noise);

		int w = x_resolution;
		int stepSize = w-1;
		double scale = x_size/(stepSize+1);

		setHeightAt(heightMap, 0, 0, dis(gen)*scale*stepSize);
		setHeightAt(heightMap, 0, w-1, dis(gen)*scale*stepSize);
		setHeightAt(heightMap, w-1, 0, dis(gen)*scale*stepSize);
		setHeightAt(heightMap, w-1, w-1, dis(gen)*scale*stepSize);

		while(stepSize >= 2){
			int half = stepSize/2;

			for(int x = 0; x < w-1; x += stepSize){
				for(int y = 0; y < w-1; y += stepSize){
					double middle = (  heightMap->getHeightAt(x,y)
									 + heightMap->getHeightAt(x, y+stepSize)
									 + heightMap->getHeightAt(x+stepSize, y)
									 + heightMap->getHeightAt(x+stepSize, y+stepSize))/4
									+ dis(gen)*scale*stepSize;

					setHeightAt(heightMap, x+half, y+half, middle);
				}
			}

			for(int x = 0; x < w-1; x += stepSize){
				for(int y = 0; y < w-1; y += stepSize){
					double a = heightMap->getHeightAt(x, y);
					double b = heightMap->getHeightAt(x, y+stepSize);
					double c = heightMap->getHeightAt(x+stepSize, y);
					double d = heightMap->getHeightAt(x+stepSize, y+stepSize);
					double e = heightMap->getHeightAt(x+half, y+half);

					setHeightAt(heightMap, x+half, y, (a+c+e)/3 + dis(gen)*scale*stepSize);
					setHeightAt(heightMap, x, y+half, (a+b+e)/3 + dis(gen)*scale*stepSize);
					setHeightAt(heightMap, x+stepSize, y+half, (c+d+e)/3 + dis(gen)*scale*stepSize);
					setHeightAt(heightMap, x+half, y+stepSize, (b+c+e)/3 + dis(gen)*scale*stepSize);
				}
			}

			stepSize = half;
			scale *= 0.9;
		}

		for(int x = 0; x < w-1; x++){
			for(int y = 0; y < w-1; y++){
				int times = 0;
				double sum = 0;

				for(int i = -1; i <= 1; i++){
					for(int j = -1; j <= 1; j++){
						if(x+i >= 0 && x + i < w && y+j >= 0 && y+j < w){
							times++;
							sum += heightMap->getHeightAt(x+i, y+j);
						}
					}
				}

				setHeightAt(heightMap, x, y, sum/times);
			}
		}

		return heightMap;
	}



}