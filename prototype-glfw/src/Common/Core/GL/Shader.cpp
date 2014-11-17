/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 17:20:32
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 17:43:46
*/

#include <Core/GL/Shader.hpp>

#include <iostream>
#include <fstream>

using namespace std;

namespace amaze{
	namespace gl{
		Shader::ShaderType Shader::fromGLShaderType(GLenum glshader){
			if(glshader == GL_VERTEX_SHADER){
				return Shader::VERTEX_SHADER;
			} else if(glshader == GL_FRAGMENT_SHADER){
				return Shader::FRAGMENT_SHADER;
			} else{
				return Shader::GEOMETRY_SHADER;
			}
		}

		GLenum Shader::toGLShaderType(Shader::ShaderType shader){
			if(shader == Shader::VERTEX_SHADER){
				return GL_VERTEX_SHADER;
			} else if(shader == Shader::FRAGMENT_SHADER){
				return GL_FRAGMENT_SHADER;
			} else{
				return GL_GEOMETRY_SHADER;
			}
		}


		Shader::Shader(void)
		{
			_totalShaders=0;
			_shaders[VERTEX_SHADER]=0;
			_shaders[FRAGMENT_SHADER]=0;
			_shaders[GEOMETRY_SHADER]=0;
			_attributeList.clear();
			_uniformLocationList.clear();
		}

		Shader::~Shader(void)
		{
			_attributeList.clear();
			_uniformLocationList.clear();
		}

		void Shader::loadFromString(Shader::ShaderType ttype, const string& source) {
			GLenum type = Shader::toGLShaderType(ttype);
			GLuint shader = glCreateShader (type);
			
			const char * ptmp = source.c_str();
			glShaderSource (shader, 1, &ptmp, NULL);
			
			//check whether the shader loads fine
			GLint status;
			glCompileShader (shader);
			glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				GLint infoLogLength;
				glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar *infoLog= new GLchar[infoLogLength];
				glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
				cerr<<"Compile log: "<<infoLog<<endl;
				delete [] infoLog;
			}
			_shaders[ttype] = shader;
		}


		void Shader::createAndLinkProgram() {
			_program = glCreateProgram ();
			if (_shaders[VERTEX_SHADER] != 0) {
				glAttachShader (_program, _shaders[VERTEX_SHADER]);
			}
			if (_shaders[FRAGMENT_SHADER] != 0) {
				glAttachShader (_program, _shaders[FRAGMENT_SHADER]);
			}
			if (_shaders[GEOMETRY_SHADER] != 0) {
				glAttachShader (_program, _shaders[GEOMETRY_SHADER]);
			}
			
			//link and check whether the program links fine
			GLint status;
			glLinkProgram (_program);
			glGetProgramiv (_program, GL_LINK_STATUS, &status);
			if (status == GL_FALSE) {
				GLint infoLogLength;
				
				glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar *infoLog= new GLchar[infoLogLength];
				glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
				cerr<<"Link log: "<<infoLog<<endl;
				delete [] infoLog;
			}
			
			glDeleteShader(_shaders[VERTEX_SHADER]);
			glDeleteShader(_shaders[FRAGMENT_SHADER]);
			glDeleteShader(_shaders[GEOMETRY_SHADER]);
		}

		void Shader::use() {
			glUseProgram(_program);
		}

		void Shader::unUse() {
			glUseProgram(0);
		}

		void Shader::addAttribute(const string& attribute) {
			_attributeList[attribute]= glGetAttribLocation(_program, attribute.c_str());
		}

		//An indexer that returns the location of the attribute
		GLuint Shader::operator [](const string& attribute) {
			return _attributeList[attribute];
		}

		void Shader::addUniform(const string& uniform) {
			GLuint uni = glGetUniformLocation(_program, uniform.c_str());
			_uniformLocationList[uniform] = uni;
		}

		GLuint Shader::operator()(const string& uniform){
			return _uniformLocationList[uniform];
		}
		GLuint Shader::getProgram() const {
			return _program;
		}
		
		void Shader::loadFromFile(Shader::ShaderType type, const string& filename){
			ifstream fp;
			fp.open(filename.c_str(), ios_base::in);
			if(fp) {
				string buffer(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
				loadFromString(type, buffer);
			} else {
				cerr<<"Error loading shader: "<<filename<<endl;
			}
		}
	}
}