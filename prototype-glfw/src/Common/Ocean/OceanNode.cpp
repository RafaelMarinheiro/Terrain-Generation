/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 05:54:33
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 06:02:44
*/

#include <Ocean/OceanNode.hpp>

#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

namespace amaze{
	void OceanNode::init(float _height){
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			float arr[8] = {-100, -100,	-100, 100, 		100, 100, 	100, -100};
			glBufferData(GL_ARRAY_BUFFER, sizeof(arr), &arr[0], GL_STATIC_DRAW);
		}

		{
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Water/Water.main.glsl"));

			materialShader.loadFromFiles(files);

			materialShader.addUniform("modelMatrix");
			materialShader.addUniform("viewMatrix");
			materialShader.addUniform("projectionMatrix");

			materialShader.addAttribute("position");

			glBindVertexArray(vao);
			materialShader.use();

			glEnableVertexAttribArray(materialShader["position"]);
			glVertexAttribPointer(materialShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);
		
			materialShader.unUse();
			glBindVertexArray(0);
		}
	}

	void OceanNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		materialShader = gl::Shader();
	}

	void OceanNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_MATERIAL_PASS){
			glBindVertexArray(vao);

			// std::cerr << "oi";
			materialShader.use();
			glUniformMatrix4fv(materialShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(materialShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(materialShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));

			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			materialShader.unUse();

			glBindVertexArray(0);
		}
	}
}