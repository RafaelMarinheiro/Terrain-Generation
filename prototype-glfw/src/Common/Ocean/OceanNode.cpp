/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 05:54:33
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 09:57:53
*/

#include <Ocean/OceanNode.hpp>

#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <random>

#include <cstdio>
#include <iostream>

namespace amaze{
	void OceanNode::init(float _height){
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
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SkyMap.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Util/Noise2D.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Water/Water.main.glsl"));

			materialShader.loadFromFiles(files);

			materialShader.addUniform("modelMatrix");
			materialShader.addUniform("viewMatrix");
			materialShader.addUniform("projectionMatrix");

			materialShader.addUniform("inverseMVP");
			materialShader.addUniform("skyTexture");

			materialShader.addUniform("eyePosition");
			materialShader.addUniform("lightDirection");

			materialShader.addUniform("gPositionMap");
			materialShader.addUniform("gNormalMap");
			materialShader.addUniform("gAlbedoMap");
			materialShader.addUniform("gMaterialMap");

			materialShader.addUniform("waterHeight");
			materialShader.addUniform("time");
			materialShader.addUniform("numWaves");
			materialShader.addUniform("amplitude");
			materialShader.addUniform("wavelength");
			materialShader.addUniform("speed");
			materialShader.addUniform("direction");

			materialShader.addAttribute("position");

			glBindVertexArray(vao);
			materialShader.use();

			glEnableVertexAttribArray(materialShader["position"]);
			glVertexAttribPointer(materialShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);
		
			materialShader.unUse();
			glBindVertexArray(0);
		}

		{
			height = _height;
			numberWaves = 7;
		    std::random_device rd;
		    std::mt19937 gen(rd());
		    std::uniform_real_distribution<> dis(-M_PI/3, M_PI/3);

			for (int i = 0; i < numberWaves; ++i) {
				float amplitude = 0.5f / (i + 1);
				_amplitudes[i] = amplitude;

				float wavelength = 10 * M_PI / (i*0.7 + 2.3);
				_wavelength[i] = wavelength;

				float speed = 1.0f + 2*i;
				_speed[i] = speed*0.2;

				float angle = dis(gen);
				_direction[2*i + 0] = cos(angle); _direction[2*i + 1] = sin(angle);
			}
		}
	}

	void OceanNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		materialShader = gl::Shader();
	}

	void OceanNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_LIGHT_PASS){
			glBindVertexArray(vao);

			// printf("Calling me\n");

			materialShader.use();
			glUniformMatrix4fv(materialShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(materialShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(materialShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			glUniform3fv(materialShader("lightDirection"), 1, glm::value_ptr(viewer.sunPosition));

			glm::mat4x4 inverseMVP = viewer.camera.projectionMatrix()*viewer.camera.viewMatrix()*worldMatrix;
			inverseMVP = glm::inverse(inverseMVP);

			// for(int i = 0; i < 4; i++){
			// 	std::cerr << "|";
			// 	for(int j = 0; j < 4; j++){
			// 		std::cerr << " " << inverseMVP[i][j];
			// 	}
			// 	std::cerr << " |" << std::endl;
			// }
			// std::cerr << std::endl;

			glm::vec4 test = inverseMVP*glm::vec4(0.0, 0.0, 1.0, 1.0);
			glm::vec4 tt = float(2.0)*test;
			glm::vec3 pixelPosition = glm::vec3(test[0]/test[3], test[1]/test[3], test[2]/test[3]);

			pixelPosition = pixelPosition - viewer.camera.position;
			pixelPosition = glm::normalize(pixelPosition);

			printf("TEST: (%f, %f)\n", pixelPosition[0]/(1+pixelPosition[1]), pixelPosition[2]/(1+pixelPosition[1]));

			// glm::vec4 

			// printfinverseMVP*()

			glUniformMatrix4fv(materialShader("inverseMVP"), 1, GL_FALSE, glm::value_ptr(inverseMVP));


			glUniform3fv(materialShader("eyePosition"), 1, glm::value_ptr(viewer.camera.position)); //For testing
			
			// printf("POSITION: (%f, %f, %f)\n", viewer.camera.position.x, viewer.camera.position.y, viewer.camera.position.z);


			glUniform1i(materialShader("gPositionMap"), 0);
			glUniform1i(materialShader("gNormalMap"), 1);
			glUniform1i(materialShader("gAlbedoMap"), 2);
			glUniform1i(materialShader("gMaterialMap"), 3);
			glUniform1i(materialShader("skyTexture"), 4);

			glUniform1i(materialShader("numWaves"), numberWaves);
			glUniform1f(materialShader("waterHeight"), height);
			glUniform1fv(materialShader("amplitude"), numberWaves, _amplitudes);
			glUniform1fv(materialShader("wavelength"), numberWaves, _wavelength);
			glUniform1fv(materialShader("speed"), numberWaves, _speed);
			glUniform2fv(materialShader("direction"), numberWaves, _direction);
			glUniform1f(materialShader("time"), viewer.time);
			
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			materialShader.unUse();

			glBindVertexArray(0);
		}
	}
}