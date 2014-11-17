/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:08:23
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 16:40:56
*/

#include <Core/Window/Window.hpp>


namespace amaze{
	namespace core{
		Window::Window(const std::string & name, int width, int height){
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			_glfw_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
			glfwMakeContextCurrent(_glfw_window);
			glewExperimental = GL_TRUE;

			glewInit();
		}

		Window::~Window(){

		}

		void Window::makeContextCurrent(){
			glfwMakeContextCurrent(_glfw_window);
		}

		bool Window::shouldClose(){
			return glfwWindowShouldClose(_glfw_window);
		}

		void Window::swapBuffers(){
			glfwSwapBuffers(_glfw_window);
		}
	}
}