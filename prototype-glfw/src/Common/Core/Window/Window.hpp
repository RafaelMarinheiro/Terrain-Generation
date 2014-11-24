/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:01:16
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 14:30:36
*/

#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <Core/GL/OpenGL.hpp>
#include <string>

namespace amaze{
	namespace core{
		class Window{
		public:
			Window(const std::string & name, int width, int height);
			virtual ~Window();

			void makeContextCurrent();

			bool shouldClose();

			void swapBuffers();

			GLFWwindow * getWindow() const{return _glfw_window;}
		private:
			GLFWwindow * _glfw_window; 
		};
	}
}

#endif // CORE_WINDOW_H