/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 04:33:42
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-20 04:43:29
*/

#include <Core/Render/RenderNode.hpp>

namespace amaze{
	namespace render{

		void TransformationNode::render(const Viewer & viewer,
										RenderPass renderPass,
										const glm::mat4x4 & worldMatrix){
			child->render(viewer, renderPass, worldMatrix*transformation);
		}

		void GroupNode::render(const Viewer & viewer,
							   RenderPass renderPass,
							   const glm::mat4x4 & worldMatrix){
			for(int i = 0; i < children.size(); i++){
				children[i]->render(viewer, renderPass, worldMatrix);
			}
		}

	}
}