/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 04:37:39
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-15 00:05:34
*/

#include <Terrain/builders/DiamondSquareHeightMapBuilder.hpp>

#include <algorithm>
#include <random>

// #include <cstdio>

namespace amaze{
	DiamondSquareHeightMapBuilder::DiamondSquareHeightMapBuilder(float noise){
		_noise = noise;
	}

	HeightMap * DiamondSquareHeightMapBuilder::buildHeightMap(float x_size, float y_size,
																	  unsigned int x_resolution, unsigned int y_resolution){

		HeightMap * heightMap = new HeightMap(x_size, y_size, x_resolution, y_resolution);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(-_noise, _noise);

		int w = x_resolution;
		int stepSize = w-1;
		float scale = x_size/(stepSize+1);

		// setHeightAt(heightMap, 0, 0, dis(gen)*scale*stepSize);
		// setHeightAt(heightMap, 0, w-1, dis(gen)*scale*stepSize);
		// setHeightAt(heightMap, w-1, 0, dis(gen)*scale*stepSize);
		// setHeightAt(heightMap, w-1, w-1, dis(gen)*scale*stepSize);

		setHeightAt(heightMap, 0, 0, -_noise);
		setHeightAt(heightMap, 0, w-1, -_noise);
		setHeightAt(heightMap, w-1, 0, -_noise);
		setHeightAt(heightMap, w-1, w-1, -_noise);
		setHeightAt(heightMap, w/2, w/2, _noise);

		while(stepSize >= 2){
			int half = stepSize/2;

			for(int x = 0; x < w-1; x += stepSize){
				for(int y = 0; y < w-1; y += stepSize){
					float middle = (  heightMap->getHeightAt(x,y)
									 + heightMap->getHeightAt(x, y+stepSize)
									 + heightMap->getHeightAt(x+stepSize, y)
									 + heightMap->getHeightAt(x+stepSize, y+stepSize))/4
									+ dis(gen)*scale*stepSize;

					setHeightAt(heightMap, x+half, y+half, middle);
				}
			}

			for(int x = 0; x < w-1; x += stepSize){
				for(int y = 0; y < w-1; y += stepSize){
					float a = heightMap->getHeightAt(x, y);
					float b = heightMap->getHeightAt(x, y+stepSize);
					float c = heightMap->getHeightAt(x+stepSize, y);
					float d = heightMap->getHeightAt(x+stepSize, y+stepSize);
					float e = heightMap->getHeightAt(x+half, y+half);

					float ddx = ((x+half + 0.0)/x_resolution) - 0.5;
					float ddy = ((y+half + 0.0)/y_resolution) - 0.5;

					float dist = ddx*ddx + ddy*ddy;
					float cscale = scale * (1/(3.3-dist));

					setHeightAt(heightMap, x+half, y, (a+c+e)/3 + dis(gen)*cscale*stepSize);
					setHeightAt(heightMap, x, y+half, (a+b+e)/3 + dis(gen)*cscale*stepSize);
					setHeightAt(heightMap, x+stepSize, y+half, (c+d+e)/3 + dis(gen)*cscale*stepSize);
					setHeightAt(heightMap, x+half, y+stepSize, (b+c+e)/3 + dis(gen)*cscale*stepSize);
				}
			}

			stepSize = half;
			scale *= 0.9;
		}

		for(int x = 0; x < w; x++){
			for(int y = 0; y < w; y++){
				int times = 0;
				float sum = 0;

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

		float maxi = heightMap->getHeightAt(0, 0);
		float mini = maxi;

		for(int x = 0; x < w; x++){
			for(int y = 0; y < w; y++){
				float r = heightMap->getHeightAt(x, y);
				if(r > maxi){
					maxi = r;
				}
				if(r < mini){
					mini = r;
				}
			}
		}

		for(int x = 0; x < w; x++){
			for(int y = 0; y < w; y++){
				float ddx = ((x + 0.0)/x_resolution) - 0.5;
				float ddy = ((y + 0.0)/y_resolution) - 0.5;

				float dist = ddx*ddx + ddy*ddy;
				float cscale = exp(-10*dist*dist);

				if(x == 0 || y == 0 || x == w-1 || y == w-1){
					setHeightAt(heightMap, x, y, 0.0);
				} else{
					float r = heightMap->getHeightAt(x, y);
					setHeightAt(heightMap, x, y, cscale*(r-mini)/(maxi-mini));
				}
			}
		}

		return heightMap;
	}



}