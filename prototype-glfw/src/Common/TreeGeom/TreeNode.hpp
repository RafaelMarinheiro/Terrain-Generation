



#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <TreeGeom/Tree.hpp>


#include <Core/GL/Shader.hpp>
#include <Core/Render/RenderNode.hpp>


namespace amaze{

	class TreeNode : public render::RenderNode{
	public:
		void init(Tree * tree);
		void destroy();

		virtual void render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix);
	private:
		Tree * tree;
		unsigned int nindices;

		GLuint vao;
		GLuint vbo;
		GLuint ibo;
		GLuint tex;
		gl::Shader materialShader;
	};
}
#endif