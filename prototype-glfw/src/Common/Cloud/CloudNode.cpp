/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-23 01:58:35
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 23:35:52
*/

#include <Cloud/CloudNode.hpp>

#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <iostream>

namespace amaze{
	void CloudNode::init(){
		// std::cout <<"maybeHere";		
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			float arr[8] = {-1, -1,	1, -1, 		1, 1, 	-1, 1};
			glBufferData(GL_ARRAY_BUFFER, sizeof(arr), &arr[0], GL_STATIC_DRAW);
		}

		// std::cout <<"Here";

		{
			SetNoise(map32);
			LoopForever();
			float texture[256][256][3];       //Temporary array to hold texture RGB values 

			for(int i=0; i<256; i++){         //Set cloud color value to temporary array
				for(int j=0; j<256; j++){
					float color = map256[i*256+j]/256; 
					// std::cout << color << std::endl;
					texture[i][j][0]=color;
					texture[i][j][1]=color;
					texture[i][j][2]=color;
				}
			}
			glGenTextures(1, &cloudTexture);           //Texture binding 
			glBindTexture(GL_TEXTURE_2D, cloudTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 256, 256, 0, GL_RGB, GL_FLOAT, texture);
			// glGenerateMipMap(GL_TEXTURE_2D);

		}
		// std::cout <<"or Here";
		{
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SkyMap.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Util/Noise2d.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Cloud/main.glsl"));

			cloudShader.loadFromFiles(files);

			cloudShader.addUniform("modelMatrix");
			cloudShader.addUniform("time");
			
			cloudShader.addUniform("viewMatrix");
			cloudShader.addUniform("projectionMatrix");

			cloudShader.addUniform("inverseMVP");
			cloudShader.addUniform("skyTexture");

			cloudShader.addUniform("cloudTexture");
			cloudShader.addAttribute("position");

			glBindVertexArray(vao);
			cloudShader.use();

			glEnableVertexAttribArray(cloudShader["position"]);
			glVertexAttribPointer(cloudShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);
		
			cloudShader.unUse();
			glBindVertexArray(0);
		}

	}

	void CloudNode::LoopForever(){
		OverlapOctaves(map32, map256);
		ExpFilter(map256);
	}

	float CloudNode::Noise(int x, int y, int random){
		int n = x + y * 57 + random * 131;

		n = (n<<13) ^ n;

		return (1.0f - ( (n * (n * n * 15731 + 789221) +
        	1376312589)&0x7fffffff)* 0.000000000931322574615478515625f);
	}

	void CloudNode::SetNoise(float* map){
		//we declare a larger array to hold extra elements for side and corner mirroring
		float temp[34][34];

		int random=rand() % 5000;

		//Set Noise to Map
		for(int y = 1; y < 33; y++){
			for(int x=1; x<33; x++){
				temp[x][y] = 128.0f + Noise(x,  y,  random)*128.0f;
			}
		}
		//Seamless clouds (removes seems created by different noise)
		for (int x=1; x<33; x++){
			temp[0][x] = temp[32][x];
			temp[33][x] = temp[1][x];
			temp[x][0] = temp[x][32];
			temp[x][33] = temp[x][1];
		}
		//adds additional points to end to remove end seems
		temp[0][0] = temp[32][32];
		temp[33][33] = temp[1][1];
		temp[0][33] = temp[32][1];
		temp[33][0] = temp[1][32];

		//Smoothing (smoothes out the noise)
		for (int y=1; y<33; y++){
			for (int x=1; x<33; x++){
		      float center = temp[x][y]/4.0f;
		      float sides = (temp[x+1][y] + temp[x-1][y] + temp[x][y+1] + temp[x][y-1])/8.0f;
		      float corners = (temp[x+1][y+1] + temp[x+1][y-1] + temp[x-1][y+1] + temp[x-1][y-1])/16.0f;

		      map32[((x-1)*32) + (y-1)] = center + sides + corners;
		    }
		}
	}

	//used to make the noise less blocky looking
	//could probably improve this for better clouds
	float CloudNode::Interpolate(float x, float y, float  *map){
		int Xint = (int)x;
		int Yint = (int)y;

		float Xfrac = x - Xint;
		float Yfrac = y - Yint;

		int X0 = Xint % 32;
		int Y0 = Yint % 32;
		int X1 = (Xint + 1) % 32;
		int Y1 = (Yint + 1) % 32;

		float bot = map[X0*32 + Y0] + Xfrac * (map[X1*32 + Y0] - map[X0*32 + Y0]);
		float top = map[X0*32 + Y1] + Xfrac * (map[X1*32 +  Y1] - map[X0*32 + Y1]);

		return (bot + Yfrac * (top - bot));
	}


	//Overlap the octaves
	//Now we will make a couple of noise layers called octaves. The first octave is a blowup of a single 32*32 
	//noise map to a 256*256 map. The second octave is a blowup of four 32*32 maps to four
	//128*128 maps which are tiled together. This process goes on for higher octaves.
	//The octaves are then overlapped together to give our cloud more turbulence. We will use four octaves 
	//for our cloud. You can use more octaves if you like.
	void CloudNode::OverlapOctaves(float  *map32, float  *map256){
		for (int x=0; x<256*256; x++){
			map256[x] = 0;
		}

		// We start working with the 256*256 map by clearing its old values
		for (int octave=0; octave<4; octave++){
			for (int x=0; x<256; x++){
				for (int y=0; y<256; y++){
					float scale = 1 / pow(2, 3-octave);
					float noise = Interpolate(x*scale, y*scale , map32);
					//Here we scale the x and y indices with the values of 1/8, 1/4, 1/2 and 1 consisting of 
					//four octaves. The scaled x, y indices and 32*32 map are then sent as parameters for interpolation to return a
					//smoother noise value.
					map256[(y*256) + x] += noise / pow(2, octave);
				}
			}
		}
	}

	//Filter the noise with exponential function
	void CloudNode::ExpFilter(float  *map){
		float cover = 1.0f;
		float sharpness = 0.99f;
		for (int x=0; x<256*256; x++){
		    float c = map[x] - (255.0f-cover);
		    if (c<0){
	    	    c = 0;
	    	}
	    map[x] = 255.0f - ((float)(pow(sharpness, c))*255.0f);
		}
	}

	void CloudNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_SKY_PASS){
			// std::cout << "Hey";
			glBindVertexArray(vao);

			cloudShader.use();
			glUniformMatrix4fv(cloudShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(cloudShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(cloudShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			
			glm::mat4x4 inverseMVP = viewer.camera.projectionMatrix()*viewer.camera.viewMatrix()*worldMatrix;
			inverseMVP = glm::inverse(inverseMVP);

			glUniformMatrix4fv(cloudShader("inverseMVP"), 1, GL_FALSE, glm::value_ptr(inverseMVP));

			// glUniform3fv(cloudShader("lightDirection"), 1, glm::value_ptr(viewer.sunPosition)); //For testing
			
			// printf("SUN: (%f, %lf, %lf)\n", sunPosition[0], sunPosition[1], sunPosition[2]);

			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, cloudTexture);

			// glActiveTexture(GL_TEXTURE1);
			// glBindTexture(GL_TEXTURE_3D, inscatter_texture);

			glUniform1i(cloudShader("skyTexture"), 4);
			glUniform1i(cloudShader("cloudTexture"), 7);
			glUniform1f(cloudShader("time"), viewer.time);
			
			// glUniform1i(cloudShader("inscatterSampler"), 1);

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			cloudShader.unUse();
			glBindVertexArray(0);

		}
	}


	
}