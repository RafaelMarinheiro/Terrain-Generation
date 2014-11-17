/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:53:16
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 16:06:44
*/

#ifndef CORE_Window_SYSTEM_HPP
#define CORE_Window_SYSTEM_HPP

#include <Core/System/System.hpp>

namespace amaze{
	namespace core{
		class WindowSystem : public System{
		protected:
			virtual bool v_init();
			virtual bool v_destroy();
		};
	}
}

#endif // CORE_GLFW_SYSTEM_HPP
