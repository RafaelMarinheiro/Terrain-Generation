/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-23 01:58:28
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 02:49:16
*/

#ifndef ATMOSPHERE_NODE_HPP
#define ATMOSPHERE_NODE_HPP

#include <Core/GL/Shader.hpp>
#include <Core/Render/RenderNode.hpp>
#include <Core/Math/Vector.hpp>

namespace amaze{
	class AtmosphereNode : public render::RenderNode{
	public:

		void init();
		void destroy();

		virtual void render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix);
	
		glm::vec3 sunPosition;

	private:
		
		GLuint vao;
		GLuint vbo;
		gl::Shader sunLightShader;
	};
}

#endif // ATMOSPHERE_NODE_HPP
