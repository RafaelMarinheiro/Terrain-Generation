/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 17:18:09
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 17:40:58
*/

#ifndef CORE_SHADER_HPP
#define CORE_SHADER_HPP

#include <Core/GL/OpenGL.hpp>

#include <string>
#include <map>

namespace amaze{
	namespace gl{
		class Shader{
		public:
			enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
			static ShaderType fromGLShaderType(GLenum glshader);
			static GLenum toGLShaderType(ShaderType shader);

			Shader(void);
			~Shader(void);
			void loadFromString(Shader::ShaderType whichShader, const std::string& source);
			void loadFromFile(Shader::ShaderType whichShader, const std::string& filename);
			void createAndLinkProgram();
			void use();
			void unUse();
			void addAttribute(const std::string& attribute);
			void addUniform(const std::string& uniform);
			GLuint getProgram() const;
			//An indexer that returns the location of the attribute/uniform
			GLuint operator[](const std::string& attribute);
			GLuint operator()(const std::string& uniform);
			//Program deletion
			void deleteProgram() {glDeleteProgram(_program);_program=-1;}

		private:
			GLuint	_program;
			int _totalShaders;
			GLuint _shaders[3];//0->vertexshader, 1->fragmentshader, 2->geometryshader
			std::map<std::string,GLuint> _attributeList;
			std::map<std::string,GLuint> _uniformLocationList;
		};	
	}
}

#endif // CORE_SHADER_HPP