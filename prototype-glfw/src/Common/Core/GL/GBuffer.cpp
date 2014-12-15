/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 06:29:31
* @Last Modified by:   marinheiro
* @Last Modified time: 2014-12-14 23:05:25
*/

#include <Core/GL/GBuffer.hpp>

#include <cstdio>

namespace amaze{
	namespace gl{
		void GBuffer::init(unsigned int windowWidth, unsigned int windowHeight){
			// Create the FBO
			glGenFramebuffers(1, &m_fbo);    
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

			// Create the gbuffer textures
			glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);
			glGenTextures(1, &m_depthTexture);
			glGenTextures(1, &m_finalTexture);

			GLenum DrawBuffers[GBUFFER_NUM_TEXTURES]; 
			for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES; i++) {
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
				DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			}

			// depth
			glBindTexture(GL_TEXTURE_2D, m_depthTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, windowWidth, windowHeight, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

			// final
			glBindTexture(GL_TEXTURE_2D, m_finalTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + GBUFFER_NUM_TEXTURES, GL_TEXTURE_2D, m_finalTexture, 0);	
			// printf("%d\n", GL_COLOR_ATTACHMENT0 + GBUFFER_NUM_TEXTURES);

			glDrawBuffers(GBUFFER_NUM_TEXTURES, DrawBuffers);
			GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

			if (Status != GL_FRAMEBUFFER_COMPLETE) {
				printf("Framebuffer error, status: 0x%x\n", Status);
				// return false;
			}

			// restore default FBO
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

			// sky
			glGenFramebuffers(1, &m_skyFbo);   
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_skyFbo);

			glGenTextures(1, &m_skyTexture);
			glBindTexture(GL_TEXTURE_2D, m_skyTexture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 512, 512, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_skyTexture, 0);
		
			glDrawBuffers(1, DrawBuffers);

			if (Status != GL_FRAMEBUFFER_COMPLETE) {
				printf("Framebuffer error, status: 0x%x\n", Status);
				// return false;
			}

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


		}

		void GBuffer::bindForWriting(){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		}

		void GBuffer::bindForReading(){
			// glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
			// glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

			for(unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES; i++){
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
			}
			glActiveTexture(GL_TEXTURE0 + GBUFFER_NUM_TEXTURES);
			glBindTexture(GL_TEXTURE_2D, m_skyTexture);

			glActiveTexture(GL_TEXTURE0 + GBUFFER_NUM_TEXTURES + 1);
			// glBindTexture()
		}

		void GBuffer::bindForSkyMapRendering(){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_skyFbo);
		}

		void GBuffer::setReadBuffer(GBuffer::GBufferTextureType type){
		    glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
		}
	}
}