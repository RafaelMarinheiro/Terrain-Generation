/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-19 07:28:01
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 06:09:48
*/

#include <Core/Input/MouseCameraController.hpp>

#include <iostream>
#include <cmath>

namespace amaze{
	MouseCameraController::MouseCameraController(){
		sensitivity[0] = 0.005;
		sensitivity[1] = 0.005;

		rotation[0] = 0;
		rotation[1] = 0;
	}

	void MouseCameraController::update(){
		float cx, sx, cy, sy;
		cx = cos(rotation[0]*acos(-1)/180); sx = sin(rotation[0]*acos(-1)/180);
		cy = cos(rotation[1]*acos(-1)/180); sy = sin(rotation[1]*acos(-1)/180);

		glm::vec3 direction(cy*cx, sy, cy*sx);

		glm::vec3 movem;

		if(keyState[0]){
			// std::cout << "Movendo" << std::endl;
			movem = movem + direction;
		}

		if(keyState[1]){
			// std::cout << "Movendo" << std::endl;
			movem = movem - direction;
		}

		// movem = 0.01*movem;
		movem.x *= 0.1;
		movem.y *= 0.1;
		movem.z *= 0.1;
		camera->position += movem;
		camera->direction = direction;
	}

	void MouseCameraController::handleMouseMove(float x, float y){
		
		rotation[0] += x/sensitivity[0];
		rotation[1] -= y/sensitivity[1];
		// std::cout << "Mouse (" << x << ", " << y << ")" << std::endl;
		// std::cout << "Rotation (" << rotation[0]  << ", " << rotation[1] << ")" << std::endl;
		
		if(rotation[1] < -90){
			rotation[1] = -90;
		}

		if(rotation[1] > 90){
			rotation[1] = 90;
		}

		while(rotation[0] < -180){
			rotation[0] += 360;
		}

		while(rotation[0] > 180){
			rotation[0] -= 360;
		}
	}

	void MouseCameraController::handleKeyPress(int key){
		if(key == 'W'){
			keyState[0] = true;
		} else if(key == 'S'){
			keyState[1] = true;
		} else if(key == 'A'){
			keyState[2] = true;
		} else{
			keyState[3] = true;
		}
	}

	void MouseCameraController::handleKeyRelease(int key){
		if(key == 'W'){
			keyState[0] = false;
		} else if(key == 'S'){
			keyState[1] = false;
		} else if(key == 'A'){
			keyState[2] = false;
		} else{
			keyState[3] = false;
		}
	}
}