/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-23 01:58:35
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 18:53:42
*/

#include <Atmosphere/AtmosphereNode.hpp>

#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <iostream>
#include <cstdio>

namespace amaze{

	const int TRANSMITTANCE_WIDTH = 256;
	const int TRANSMITTANCE_HEIGHT = 64;
	const int TRANSMITTANCE_CHANNELS = 3;
	
	const int INSCATTER_WIDTH = 256;
	const int INSCATTER_HEIGHT = 128;
	const int INSCATTER_DEPTH = 32;
	const int INSCATTER_CHANNELS = 4;

	void AtmosphereNode::init(){
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			float arr[8] = {-1, -1,	1, -1, 		1, 1, 	-1, 1};
			glBufferData(GL_ARRAY_BUFFER, sizeof(arr), &arr[0], GL_STATIC_DRAW);
		}

		{
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Lighting/OrenNayar.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SkyMap.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SunLight.glsl"));

			sunLightShader.loadFromFiles(files);

			sunLightShader.addUniform("modelMatrix");
			sunLightShader.addUniform("viewMatrix");
			sunLightShader.addUniform("projectionMatrix");

			sunLightShader.addUniform("gPositionMap");
			sunLightShader.addUniform("gNormalMap");
			sunLightShader.addUniform("gAlbedoMap");
			sunLightShader.addUniform("gMaterialMap");

			sunLightShader.addUniform("skyTexture");


			sunLightShader.addUniform("lightDirection");

			sunLightShader.addAttribute("position");


			glBindVertexArray(vao);
			sunLightShader.use();

			glEnableVertexAttribArray(sunLightShader["position"]);
			glVertexAttribPointer(sunLightShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);

			sunLightShader.unUse();
			glBindVertexArray(0);
		}

		{
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/Atmosphere.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SkyMap.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SkyMap.main.glsl"));

			skyMapShader.loadFromFiles(files);

			skyMapShader.addUniform("modelMatrix");
			skyMapShader.addUniform("viewMatrix");
			skyMapShader.addUniform("projectionMatrix");

			skyMapShader.addUniform("transmittanceSampler");
			skyMapShader.addUniform("inscatterSampler");

			skyMapShader.addUniform("lightDirection");

			skyMapShader.addAttribute("position");


			glBindVertexArray(vao);
			skyMapShader.use();

			glEnableVertexAttribArray(skyMapShader["position"]);
			glVertexAttribPointer(skyMapShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);

			skyMapShader.unUse();
			glBindVertexArray(0);
		}

		//textures
		{
			glGenTextures(1, &transmittance_texture);
			glGenTextures(1, &inscatter_texture);
			float *data = new float[TRANSMITTANCE_WIDTH*TRANSMITTANCE_HEIGHT*TRANSMITTANCE_CHANNELS];
			FILE *f = fopen(core::Resources::pathForResource("Shaders/Atmosphere/textures/transmittance.raw").c_str(), "rb");
			fread(data, 1, TRANSMITTANCE_WIDTH*TRANSMITTANCE_HEIGHT*TRANSMITTANCE_CHANNELS*sizeof(float), f);
			fclose(f);
			glBindTexture(GL_TEXTURE_2D, transmittance_texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F_ARB, TRANSMITTANCE_WIDTH, TRANSMITTANCE_HEIGHT, 0, GL_RGB, GL_FLOAT, data);
			delete[] data;

			f = fopen(core::Resources::pathForResource("Shaders/Atmosphere/textures/inscatter.raw").c_str(), "rb");
			data = new float[INSCATTER_WIDTH*INSCATTER_HEIGHT*INSCATTER_DEPTH*INSCATTER_CHANNELS];
			fread(data, 1, INSCATTER_WIDTH*INSCATTER_HEIGHT*INSCATTER_DEPTH*INSCATTER_CHANNELS*sizeof(float), f);
			fclose(f);
			glBindTexture(GL_TEXTURE_3D, inscatter_texture);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA16F_ARB, INSCATTER_WIDTH, INSCATTER_HEIGHT, INSCATTER_DEPTH, 0, GL_RGBA, GL_FLOAT, data);
			delete[] data;
		}

	}

	void AtmosphereNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		sunLightShader = gl::Shader();
	}

	void AtmosphereNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_LIGHT_PASS){

			// std::cout << "Damnit" << std::endl;

			glBindVertexArray(vao);

			// std::cerr << "oi";
			sunLightShader.use();
			glUniformMatrix4fv(sunLightShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(sunLightShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(sunLightShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			glUniform3fv(sunLightShader("lightDirection"), 1, glm::value_ptr(viewer.sunPosition)); //For testing
			
			glUniform1i(sunLightShader("gPositionMap"), 0);
			glUniform1i(sunLightShader("gNormalMap"), 1);
			glUniform1i(sunLightShader("gAlbedoMap"), 2);
			glUniform1i(sunLightShader("gMaterialMap"), 3);
			glUniform1i(sunLightShader("skyTexture"), 4);

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			sunLightShader.unUse();

			glBindVertexArray(0);
		}

		if(renderPass == render::DEFERRED_SKY_PASS){
			// std::cout << "Hey";
			glBindVertexArray(vao);

			skyMapShader.use();
			glUniformMatrix4fv(skyMapShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(skyMapShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(skyMapShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			glUniform3fv(skyMapShader("lightDirection"), 1, glm::value_ptr(viewer.sunPosition)); //For testing
			
			// printf("SUN: (%f, %lf, %lf)\n", sunPosition[0], sunPosition[1], sunPosition[2]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, transmittance_texture);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_3D, inscatter_texture);

			glUniform1i(skyMapShader("transmittanceSampler"), 0);
			glUniform1i(skyMapShader("inscatterSampler"), 1);

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			skyMapShader.unUse();
			glBindVertexArray(0);

		}
	}
}