/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-19 07:28:01
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 18:48:39
*/

#include <Core/Input/SunController.hpp>

#include <iostream>
#include <cmath>

namespace amaze{
	SunController::SunController(){
		sensitivity[0] = 0.005;
		sensitivity[1] = 0.005;

		sun[0] = 0;
		sun[1] = acos(-1);
	}

	glm::vec3 SunController::getSunDirection(){
		float cx, sx, cy, sy;
		cx = cos(sun[0]); sx = sin(sun[0]);
		cy = cos(sun[1]); sy = sin(sun[1]);

		glm::vec3 direction(cy*cx, sy, cy*sx);

		return direction;
	}

	void SunController::update(){
		if(keyState[0]){
			sun[0] += sensitivity[0];
		}

		if(keyState[1]){
			sun[0] -= sensitivity[0];
		}

		if(keyState[2]){
			sun[1] += sensitivity[1];
		}

		if(keyState[3]){
			sun[1] -= sensitivity[1];
		}

		const float MYPI = acos(-1);

		while(sun[0] < -MYPI){
			sun[0] += MYPI*2;
		}

		while(sun[0] > MYPI){
			sun[0] -= MYPI*2;
		}

		if(sun[1] > MYPI/2){
			sun[1] = MYPI/2;
		}

		if(sun[1] < -MYPI/2){
			sun[1] = -MYPI/2;
		}
	}

	void SunController::handleKeyPress(int key){
		if(key == GLFW_KEY_LEFT){
			keyState[0] = true;
		} else if(key == GLFW_KEY_RIGHT){
			keyState[1] = true;
		} else if(key == GLFW_KEY_UP){
			keyState[2] = true;
		} else if(key == GLFW_KEY_DOWN){
			keyState[3] = true;
		}
	}

	void SunController::handleKeyRelease(int key){
		if(key == GLFW_KEY_LEFT){
			keyState[0] = false;
		} else if(key == GLFW_KEY_RIGHT){
			keyState[1] = false;
		} else if(key == GLFW_KEY_UP){
			keyState[2] = false;
		} else if(key == GLFW_KEY_DOWN){
			keyState[3] = false;
		}
	}
}