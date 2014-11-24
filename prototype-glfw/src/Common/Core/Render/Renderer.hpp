/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 03:21:41
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 06:14:01
*/

#ifndef CORE_RENDERER_HPP
#define CORE_RENDERER_HPP

#include <Core/Render/Viewer.hpp>

namespace amaze{
	namespace render{
		enum RenderPass{
			DEFERRED_FIRST_PASS,
				DEFERRED_DEPTH_PASS,			//Write to the Depth Buffer
				DEFERRED_MATERIAL_PASS,			//Write to the GBuffer
				DEFERRED_LIGHT_PASS,			//Do the Lighting
				DEFERRED_POST_PROCESSING_PASS,	//Run some post-processing effect
			DEFERRED_LAST_PASS,

			FORWARD_FIRST_PASS,
				FORWARD_ALL_PASS,
			FORWARD_LAST_PASS,
		};

		class Renderer{
		public:
			virtual void render(const Viewer & viewer) = 0;
		};
	}
}

#endif // CORE_RENDERER_HPP
