/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 04:49:22
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 20:52:04
*/

#include <Core/Render/BasicRenderer.hpp>

#include <Core/GL/OpenGL.hpp>

namespace amaze{
	namespace render{
		void BasicRenderer::init(){
			gBuffer.init(800, 600);
			// glGenTextures(1, &m_skyMapTexture);
		}

		void BasicRenderer::render(const Viewer & viewer){
			glm::mat4x4 identity;

			gBuffer.bindForWriting();

			glViewport(0, 0, 800, 600);

			glDepthMask(GL_TRUE);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);

			glDisable(GL_BLEND);

				for(int i = 0; i < geometryNodes.size(); i++){
					geometryNodes[i]->render(viewer, DEFERRED_DEPTH_PASS, identity);
				}

			glDepthMask(GL_TRUE);

				for(int i = 0; i < geometryNodes.size(); i++){
					geometryNodes[i]->render(viewer, DEFERRED_MATERIAL_PASS, identity);
				}

			glDisable(GL_DEPTH_TEST);

			// glEnable(GL_BLEND);
			// glBlendEquation(GL_FUNC_ADD);
			// glBlendFunc(GL_ONE, GL_ONE);
			
			//SkyMap

			gBuffer.bindForSkyMapRendering();
			glViewport(0, 0, 512, 512);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for(int i = 0; i < skyNodes.size(); i++){
				skyNodes[i]->render(viewer, DEFERRED_SKY_PASS, identity);
			}

			glViewport(0, 0, 800, 600);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			gBuffer.bindForReading();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// glReadBuffer(GL_TEXTURE0 + gl::GBuffer::GBUFFER_NUM_TEXTURES);
			// glBlitFramebuffer(0, 0, 512, 512, 0, 0, 512, 512,  GL_COLOR_BUFFER_BIT, GL_LINEAR);

			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glBindFramebuffer(GL_FRAMEBUFFER, 0);
			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// gBuffer.bindForReading();

			// gBuffer.setReadBuffer(gl::GBuffer::GBUFFER_TEXTURE_TYPE_ALBEDO);
			// glBlitFramebuffer(0, 0, 800, 600,
			// 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			// gBuffer.setReadBuffer(gl::GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
			// glBlitFramebuffer(0, 0, 800, 600, 
			// 0, 600, 800, 1200, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			// gBuffer.setReadBuffer(gl::GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
			// glBlitFramebuffer(0, 0, 800, 600, 
			// 800, 600, 1600, 1200, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			for(int i = 0; i < lightNodes.size(); i++){
				lightNodes[i]->render(viewer, DEFERRED_LIGHT_PASS, identity);
			}

			// for(int i = 0; i < postProcessingNodes.size(); i++){
			// 	postProcessingNodes[i]->render(viewer, DEFERRED_POST_PROCESSING_PASS, identity);
			// }
		}
	}
}