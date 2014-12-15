/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-23 01:58:28
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 02:49:16
*/

#ifndef CLOUD_NODE_HPP
#define CLOUD_NODE_HPP

#include <Core/GL/Shader.hpp>
#include <Core/Render/RenderNode.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/GL/OpenGL.hpp>

namespace amaze{
	class CloudNode : public render::RenderNode{
	public:

		void init();
		void destroy();

		virtual void render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix);
	

	private:



		//noise generator, function takes in a random integer to generate different noise patterns
		float Noise(int x, int y, int random);
		void SetNoise(float* map);

		//used to make the noise less blocky looking
		//could probably improve this for better clouds
		float Interpolate(float x, float y, float  *map);

		//Overlap the octaves
		//Now we will make a couple of noise layers called octaves. The first octave is a blowup of a single 32*32 
		//noise map to a 256*256 map. The second octave is a blowup of four 32*32 maps to four
		//128*128 maps which are tiled together. This process goes on for higher octaves.
		//The octaves are then overlapped together to give our cloud more turbulence. We will use four octaves 
		//for our cloud. You can use more octaves if you like.
		void OverlapOctaves(float  *map32, float  *map256);

		//Filter the noise with exponential function
		void ExpFilter(float  *map);

		void LoopForever();

		float map32[32 * 32];
		float map256[256 * 256];

		GLuint vao;
		GLuint vbo;
		GLuint cloudTexture;
		gl::Shader cloudShader;
	};
}

#endif // CLOUD_NODE_HPP
    