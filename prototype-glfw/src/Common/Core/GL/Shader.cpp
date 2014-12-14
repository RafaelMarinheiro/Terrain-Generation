/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 17:20:32
* @Last Modified by:   Rafael Farias Marinheiro
* @Last Modified time: 2014-11-24 15:34:20
*/

#include <Core/GL/Shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace amaze{
	namespace gl{
		Shader::Shader(void)
		{
			_program = -1;
			_attributeList.clear();
			_uniformLocationList.clear();
		}

		Shader::~Shader(void)
		{
			if(_program != -1){
				glDeleteProgram(_program);
			}
			_attributeList.clear();
			_uniformLocationList.clear();
		}

		bool Shader__compile(GLenum type, const char ** program_source, int n, GLuint & shader){
			shader = glCreateShader(type);

			glShaderSource(shader, n, program_source, NULL);

			GLint status;

			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if(status == GL_FALSE){
				GLint infoLogLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar * infoLog = new GLchar[infoLogLength];
				glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
				cerr << "Shader Compiling Error: " << infoLog << endl;
				delete[] infoLog;
				return false;
			}

			return true;

		}

		bool Shader::loadFromString(const std::string & strings, bool use_geo){
			const char * program_source[3];

			_program = glCreateProgram();
			
			int nshaders = 0;
			GLuint _shaders[3];

			program_source[0] = "#version 330 core\n";
			program_source[2] = strings.c_str();

			bool made_it = true;

			//Vertex Shader
			if(made_it){
				program_source[1] = "#define _VERTEX_\n";

				if(Shader__compile(GL_VERTEX_SHADER, program_source, 3, _shaders[nshaders])){
					glAttachShader(_program, _shaders[nshaders]);
					nshaders++;
				} else{
					made_it = false;
				}
			}

			//Geometry Shader
			if(made_it && use_geo){
				program_source[1] = "#define _GEOMETRY_\n";

				if(Shader__compile(GL_GEOMETRY_SHADER, program_source, 3, _shaders[nshaders])){
					glAttachShader(_program, _shaders[nshaders]);
					nshaders++;
				} else{
					made_it = false;
				}
			}

			if(made_it){
				program_source[1] = "#define _FRAGMENT_\n";

				if(Shader__compile(GL_FRAGMENT_SHADER, program_source, 3, _shaders[nshaders])){
					glAttachShader(_program, _shaders[nshaders]);
					nshaders++;
				} else{
					made_it = false;
				}				
			}

			
			if(made_it){
				GLint status;
				glLinkProgram(_program);
				glGetProgramiv(_program, GL_LINK_STATUS, &status);
				if(status == GL_FALSE){
					GLint infoLogLength;

					glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
					GLchar * infoLog = new GLchar[infoLogLength];
					glGetProgramInfoLog(_program, infoLogLength, NULL, infoLog);
					cerr << "Shader Linking Error" << infoLog << endl;
					delete[] infoLog;

					made_it = false;
				}		
			}

			for(int i = 0; i < nshaders; i++){
				glDeleteShader(_shaders[i]);
			}

			if(!made_it){
				glDeleteProgram(_program);
			}

			return made_it;
		}

		bool Shader::loadFromStrings(const std::vector<std::string> & strings, bool use_geo){
			std::ostringstream os;
			std::copy(strings.begin(), strings.end(), ostream_iterator<string>(os));
			
			return this->loadFromString(os.str(), use_geo);
		}

		bool Shader::loadFromFiles(const std::vector<std::string> & files, bool use_geo){
			
			vector<string> strings;

			bool made_it = true;
			for(int i = 0; i < files.size() && made_it; i++){
				ifstream fp;
				fp.open(files[i].c_str(), ios_base::in);
				if(fp){
					string buffer(istreambuf_iterator<char>(fp), (istreambuf_iterator<char>()));
					strings.push_back(buffer);
				} else{
					cerr << "Error loading Shader File: " << files[i] << endl;
					made_it = false;
				}
			}

			if(made_it){
				return this->loadFromStrings(strings, use_geo);
			}

			return false;		
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
	}
}