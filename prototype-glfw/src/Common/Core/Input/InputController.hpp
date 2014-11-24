/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-19 23:02:00
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 23:08:23
*/

#ifndef CORE_INPUT_CONTROLLER_HPP
#define CORE_INPUT_CONTROLLER_HPP

#include <Core/Input/InputController.hpp>

namespace amaze{
	namespace input{
		class InputController{
		public:

			virtual void update(){};
			virtual void handleMouseMove(float x, float y){};
			virtual void handleKeyPress(int key){};
			virtual void handleKeyRelease(int key){};
		};
	}
}

#endif // CORE_INPUT_CONTROLLER_HPP
