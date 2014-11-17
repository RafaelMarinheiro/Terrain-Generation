/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:53:36
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 17:40:17
*/

#include <Core/Window/System/WindowSystem.hpp>

#include <Core/GL/OpenGL.hpp>

namespace amaze{
	namespace core{
		bool WindowSystem::v_init(){
			bool ret = glfwInit();

			return (ret == GL_TRUE);
		}

		bool WindowSystem::v_destroy(){
			glfwTerminate();
			return true;
		}
	}
}