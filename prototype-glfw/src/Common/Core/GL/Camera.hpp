/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 16:44:53
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 17:16:24
*/

#ifndef CORE_GL_CAMERA_HPP
#define CORE_GL_CAMERA_HPP

#include <Core/Math/Vector.hpp>

namespace amaze{
	namespace gl{
		class Camera{
		public:
			Camera();
			Camera(const glm::vec3 & position, const glm::vec3& target, const glm::vec3& up,
				   float fovY=acos(-1)/4, float aspect=4.0/3.0, float near=1, float far=100.0);
			
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 up;

			float fovY;
			float aspect;
			float near;
			float far;
			
			glm::mat4x4 viewMatrix() const;
			glm::mat4x4 projectionMatrix() const;
			
			void lookAt(const glm::vec3& target);
			void setPerspective(float fovY, float aspect, float near, float far);
			
		};
	}
}

#endif // CORE_GL_CAMERA_HPP
