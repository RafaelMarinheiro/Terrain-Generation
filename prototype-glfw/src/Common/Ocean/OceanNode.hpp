/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 05:53:26
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 06:04:32
*/

#ifndef OCEAN_NODE_HPP
#define OCEAN_NODE_HPP

#include <Core/GL/Shader.hpp>
#include <Core/Render/RenderNode.hpp>
#include <Core/Math/Vector.hpp>


namespace amaze{
	class OceanNode : public render::RenderNode{
	public:

		void init(float height);
		void destroy();

		virtual void render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix);
	
	private:
		float height;
		int numberWaves;
		float _amplitudes[8];
		float _wavelength[8];
		float _speed[8];
		float _direction[16];
		GLuint vao;
		GLuint vbo;
		gl::Shader materialShader;
	};
}

#endif // OCEAN_NODE_HPP
