/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-23 01:58:35
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 15:11:09
*/

#include <Atmosphere/AtmosphereNode.hpp>

#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <iostream>

namespace amaze{
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
			files.push_back(core::Resources::pathForResource("Shaders/Atmosphere/SunLight.glsl"));

			sunLightShader.loadFromFiles(files);

			sunLightShader.addUniform("modelMatrix");
			sunLightShader.addUniform("viewMatrix");
			sunLightShader.addUniform("projectionMatrix");

			sunLightShader.addUniform("gPositionMap");
			sunLightShader.addUniform("gNormalMap");
			sunLightShader.addUniform("gAlbedoMap");
			sunLightShader.addUniform("gMaterialMap");

			sunLightShader.addUniform("lightDirection");

			sunLightShader.addAttribute("position");


			glBindVertexArray(vao);
			sunLightShader.use();

			glEnableVertexAttribArray(sunLightShader["position"]);
			glVertexAttribPointer(sunLightShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);

			sunLightShader.unUse();
			glBindVertexArray(0);
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
			glUniform3fv(sunLightShader("lightDirection"), 1, glm::value_ptr(sunPosition)); //For testing
			
			glUniform1i(sunLightShader("gPositionMap"), 0);
			glUniform1i(sunLightShader("gNormalMap"), 1);
			glUniform1i(sunLightShader("gAlbedoMap"), 2);
			glUniform1i(sunLightShader("gMaterialMap"), 3);

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			sunLightShader.unUse();

			glBindVertexArray(0);
		}
	}
}