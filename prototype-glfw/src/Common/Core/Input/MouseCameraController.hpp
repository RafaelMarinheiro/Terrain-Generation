/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-19 07:12:07
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-19 23:08:34
*/

#include <Core/GL/Camera.hpp>

#include <Core/Input/InputController.hpp>

#ifndef MOUSE_CAMERA_CONTROLLER_HPP
#define MOUSE_CAMERA_CONTROLLER_HPP

namespace amaze{
	class MouseCameraController : public input::InputController{
	public:
		MouseCameraController();

		gl::Camera * camera;

		virtual void update();

		virtual void handleMouseMove(float x, float y);
		virtual void handleKeyPress(int key);
		virtual void handleKeyRelease(int key);

	private:
		bool keyState[4];
		//horizontal, vertical
		float sensitivity[2];

		//horizontal, vertical
		float rotation[2];
	};
}

#endif // MOUSE_CAMERA_CONTROLLER_HPP
