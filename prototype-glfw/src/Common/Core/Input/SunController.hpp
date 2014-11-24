/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-19 07:12:07
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 23:18:06
*/

#ifndef SUN_CONTROLLER_HPP
#define SUN_CONTROLLER_HPP

#include <Core/Core.hpp>
#include <Core/Math.hpp>

#include <Core/Input/InputController.hpp>

namespace amaze{
	class SunController : public input::InputController{
	public:
		SunController();

		glm::vec3 getSunDirection();
		virtual void update();
		virtual void handleKeyPress(int key);
		virtual void handleKeyRelease(int key);

	private:
		bool keyState[4];
		//horizontal, vertical
		float sensitivity[2];

		//horizontal, vertical
		float sun[2];
	};
}

#endif // SUN_CONTROLLER_HPP
