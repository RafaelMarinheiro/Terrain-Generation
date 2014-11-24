/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 04:19:10
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 02:47:24
*/

#ifndef CORE_RENDER_NODE_HPP
#define CORE_RENDER_NODE_HPP

#include <vector>

#include <Core/Math/Vector.hpp>
#include <Core/Render/Renderer.hpp>


namespace amaze{
	namespace render{

		class RenderNode{
		public:
			virtual ~RenderNode(){};
			virtual void render(const Viewer & viewer, RenderPass renderPass, const glm::mat4x4 & worldMatrix) = 0;
		};

		class TransformationNode : public RenderNode{
		public:
			glm::mat4x4 transformation;

			RenderNode * child;

			virtual void render(const Viewer & viewer, RenderPass renderPass, const glm::mat4x4 & worldMatrix);
		};

		class GroupNode : public RenderNode{
		public:

			virtual void render(const Viewer & viewer, RenderPass renderPass, const glm::mat4x4 & worldMatrix);

			std::vector<RenderNode *> children;
		};

	}
}


#endif // CORE_RENDER_NODE_HPP
