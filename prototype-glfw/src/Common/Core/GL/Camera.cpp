/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 16:45:05
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 17:14:18
*/

#include <Core/GL/Camera.hpp>

namespace amaze{
	namespace gl{
		Camera::Camera()
			:Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)) {
		
		}
	
		Camera::Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up,
					   float fovY, float aspect, float near, float far){
			this->position = position;
			this->direction = glm::normalize(direction);
			this->up = glm::normalize(up);
			this->fovY = fovY;
			this->aspect = aspect;
			this->near = near;
			this->far = far;
		}
	
		glm::mat4x4 Camera::viewMatrix() const{
			return glm::lookAt(position, position+direction, up);
		}
		
		glm::mat4x4 Camera::projectionMatrix() const{
			return glm::perspective(fovY, aspect, near, far);
		}
		
		void Camera::lookAt(const glm::vec3& target){
			this->direction = glm::normalize(target - position);
		}
		
		void Camera::setPerspective(float fovY, float aspect, float near, float far){
			this->fovY = fovY;
			this->aspect = aspect;
			this->near = near;
			this->far = far;
		}
	}
}