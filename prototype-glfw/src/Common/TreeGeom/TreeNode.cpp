



#include <TreeGeom/TreeNode.hpp>
#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <iostream>

namespace amaze{


	void TreeNode::init(Tree * tree){
		this-> tree = tree;
	}

	void TreeNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);
		glDeleteTextures(1, &tex);
		materialShader = gl::Shader();
		tree = NULL;
	}
}