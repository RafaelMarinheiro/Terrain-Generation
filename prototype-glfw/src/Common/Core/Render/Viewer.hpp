/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 03:37:07
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 04:37:29
*/

#ifndef CORE_SCENE_HPP
#define CORE_SCENE_HPP

#include <Core/GL/Camera.hpp>

namespace amaze{
	namespace render{
		class Viewer{
		public:
			gl::Camera camera;
			float time;
			glm::vec3 sunPosition;
		};
	}
}

#endif // CORE_SCENE_HPP
