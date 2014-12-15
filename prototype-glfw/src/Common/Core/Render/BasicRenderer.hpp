/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 04:44:30
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 15:33:07
*/

#ifndef DEFAULT_RENDERER_HPP
#define DEFAULT_RENDERER_HPP

#include <Core/Render/Renderer.hpp>
#include <Core/Render/RenderNode.hpp>

#include <Core/GL/GBuffer.hpp>

#include <vector>

namespace amaze{
	namespace render{
		class BasicRenderer : public Renderer{
		public:
			void init();

			std::vector<RenderNode *> geometryNodes;
			std::vector<RenderNode *> skyNodes;
			std::vector<RenderNode *> lightNodes;
			std::vector<RenderNode *> postProcessingNodes;

			virtual void render(const Viewer & viewer);
		
		private:
			gl::GBuffer gBuffer;
			// GLuint m_skyMapTexture; 
		};
	}
}

#endif // DEFAULT_RENDERER_HPP
