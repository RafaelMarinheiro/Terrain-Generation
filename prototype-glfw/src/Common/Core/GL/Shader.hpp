/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 17:18:09
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 03:22:08
*/

#ifndef CORE_SHADER_HPP
#define CORE_SHADER_HPP

#include <Core/GL/OpenGL.hpp>

#include <string>
#include <map>
#include <vector>

namespace amaze{
	namespace gl{
		class Shader{
		public:
			Shader(void);
			~Shader(void);

			bool loadFromString(const std::string & strings, bool use_geo=false);
			bool loadFromStrings(const std::vector<std::string> & strings, bool use_geo=false);
			bool loadFromFiles(const std::vector<std::string> & files, bool use_geo=false);

			void use();
			void unUse();
			void addAttribute(const std::string& attribute);
			void addUniform(const std::string& uniform);
			GLuint getProgram() const;
			//An indexer that returns the location of the attribute/uniform
			GLuint operator[](const std::string& attribute);
			GLuint operator()(const std::string& uniform);

		private:
			GLuint	_program;
			std::map<std::string,GLuint> _attributeList;
			std::map<std::string,GLuint> _uniformLocationList;
		};	
	}
}

#endif // CORE_SHADER_HPP