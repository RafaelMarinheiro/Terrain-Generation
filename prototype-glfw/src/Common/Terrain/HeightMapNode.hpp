/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 04:56:39
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 02:13:11
*/

#ifndef HEIGHT_MAP_NODE_HPP
#define HEIGHT_MAP_NODE_HPP

#include <Terrain/HeightMap.hpp>

#include <Core/GL/Shader.hpp>
#include <Core/Render/RenderNode.hpp>
#include <Core/Math/Vector.hpp>


namespace amaze{
	class HeightMapNode : public render::RenderNode{
	public:

		void init(HeightMap * heightMap, float height);
		void destroy();

		virtual void render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix);
	
	GLuint texture;
	float height;
	HeightMap * heightMap;
	private:

		unsigned int nindices;

		GLuint vao;
		GLuint vbo;
		GLuint ibo;
		gl::Shader materialShader;
	};
}

#endif // HEIGHT_MAP_NODE_HPP
